#include <iostream>
#include <utility>
#include <functional>
#include <random> // Only needed for dev
#include <queue>
#include <unordered_map>
#include <string>
#include <cmath>
#include <iomanip>
#include "MontanaDeck.h"
#include "State.h"
#include "MoveHistoryEvent.h"
#include "ReshuffleHistoryEvent.h"

const int MAX_RESHUFFLES{3};

template <typename T>
void display(std::priority_queue<T> pq)
{
  std::cout << "[\n";
  while (!pq.empty())
  {
    T elem = pq.top();
    pq.pop();
    std::cout << elem << " ";
  }
  std::cout << "]" << std::endl;
}

template <typename T>
auto stream_out(std::function<void(std::ostream &, T)> f)
{
  return [f](const T &v)
  {
    return [v, f](std::ostream &os)
    {
      f(os, v);
    };
  };
}

int calculate_deck_score(MontanaDeck deck)
{
  int score{0};
  // For decks with a lot of cards in sequence, give a very high value.
  /**
   * @todo
   * - Would be cool to do on a sliding scale--the greater the sequence,
   *   the proportionally higher the score.
   * - Would also be good to do a "sliding window" and determine how many
   *   cards are in sequence, regardless of whether or not they start at 2.
   */
  score += deck.calculate_total_in_sequence() * 50;

  // Rows that already have a 2 in the first gap get a high score.
  std::vector<int> starting_indexes = MontanaDeck::get_row_starting_indices();
  for (auto index : starting_indexes)
  {
    Card current = deck.get_deck()[index];
    if (current.is_deuce())
    {
      score += 100;
    }
    if (current.is_ace())
    {
      score += 80;
    }
  }

  return score;
}

int calculate_score(MontanaDeck deck, std::pair<int, int> move)
{
  int score{0};
  score += calculate_deck_score(deck);

  Card current = deck.get_deck()[move.second];
  Card gap = deck.get_deck()[move.first];
  Card previous = deck.get_previous_card(move.second);
  Card next = deck.get_next_card(move.second);

  // Moving a 2 to the leftmost column gets a very high value.
  if (MontanaDeck::is_first_column(move.first) && current.is_deuce())
  {
    score += 200;
  }

  // For gaps that immediately follow a sequence break, give a very high score.
  std::vector<int> gaps = deck.find_sequence_break_indices();
  for (auto gap : gaps)
  {
    if (gap == move.first)
    {
      score += 75;
      break;
    }
  }

  // If moving a king would have it in front of a gap, give it a very low score.
  if (current.is_king() && next.is_ace())
  {
    score -= 50;
  }
  // If the move involves a space in the last position for a row and not
  // preceded by a king, give a very low value
  if (MontanaDeck::is_last_column(move.second) && !previous.is_king())
  {
    score -= 50;
  }
  // Moving a 2 away from the leftmost column gets a very low value.
  if (MontanaDeck::is_first_column(move.second) && current.is_deuce())
  {
    score -= 90;
  }

  return score;
}

bool does_state_exist_in_queue(std::priority_queue<State> pq, State &state)
{
  while (!pq.empty())
  {
    auto test = pq.top();
    pq.pop();
    if (test == state)
    {
      return true;
    }
  }
  return false;
}

std::vector<State> determine_moves(MontanaDeck &deck, std::priority_queue<State> &pq)
{
  std::vector<std::pair<int, int>> possible_moves = deck.find_moves();
  std::vector<State> move_states{};

  for (auto move : possible_moves)
  {
    State state{move, deck, calculate_score(deck, move)};
    if (!does_state_exist_in_queue(pq, state))
    {
      move_states.push_back(state);
    }
  }
  return move_states;
}

void add_moves(std::priority_queue<State> &pq, std::vector<State> &move_states)
{
  for (auto move_state : move_states)
  {
    pq.push(move_state);
  }
}

State get_move(std::priority_queue<State> &pq)
{
  auto move = pq.top();
  pq.pop();
  return move;
}

MontanaDeck make_move(State move)
{
  auto move_deck = move.get_deck();
  move_deck.move(move.get_move().first, move.get_move().second);
  return move_deck;
}

bool check_key(const std::unordered_map<std::string, bool> m, std::string key)
{
  return m.find(key) != m.end();
}

bool can_reshuffle(State move_state)
{
  return move_state.get_reshuffles() < MAX_RESHUFFLES;
}

MontanaDeck get_healthiest_deck(std::priority_queue<State> &pq)
{
  auto healthiest = pq.top().get_deck();
  int health_score{-10000};

  std::cout << "healthiest " << pq.size() << "\n"
            << healthiest << std::endl;

  while (!pq.empty())
  {
    auto test_deck = pq.top().get_deck();
    auto test_score = calculate_deck_score(test_deck);
    pq.pop();

    if (test_score > health_score)
    {
      healthiest = test_deck;
    }
  }
  return healthiest;
}

std::pair<IndexedCard, IndexedCard> convert_move_to_indexed_cards(const std::pair<int, int> move, const MontanaDeck &deck)
{
  Card current = deck.get_deck()[move.second];
  Card gap = deck.get_deck()[move.first];

  std::pair<IndexedCard, IndexedCard> indexed_cards{
      {current, move.second}, {gap, move.first}};
  return indexed_cards;
}

std::ostream &operator<<(std::ostream &os, const IndexedCard &rhs)
{
  os << rhs.card.suit_key << rhs.card.card_key << " (" << std::setw(2) << rhs.index << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, std::function<void(std::ostream &)> f)
{
  f(os);
  return os;
}

auto render_history_events = ([](std::ostream &os, const std::vector<std::shared_ptr<HistoryEvent>> rhs)
                              {
                   os << "Events (" << rhs.size() << "): \n";
                   for (auto const &event : rhs)
                   {
                      event->out(os);
                   } });

auto stream_out_history_events = stream_out<std::vector<std::shared_ptr<HistoryEvent>>>(render_history_events);

int main()
{
  MontanaDeck initial_deck{};
  MontanaDeck updated_deck{};
  std::pair<bool, MontanaDeck> result{false, initial_deck};
  std::priority_queue<State> pq{};
  std::unordered_map<std::string, bool> hm{};
  std::vector<State> move_states{};
  State move_state{};
  bool is_solved{false};
  int iterations{0};

  initial_deck.initialize();
  initial_deck.shuffle();

  hm[initial_deck.get_hash()] = true;
  move_states = determine_moves(initial_deck, pq);
  add_moves(pq, move_states);

  while (pq.size() != 0)
  {
    iterations++;
    move_state = get_move(pq);
    updated_deck = make_move(move_state);

    if (updated_deck.is_goal())
    {
      is_solved = true;
      break;
    }

    if (check_key(hm, updated_deck.get_hash()))
    {
      continue; // We've already attempted this deck.
    }

    move_state.set_deck_score(calculate_deck_score(updated_deck));
    std::shared_ptr<MoveHistoryEvent> sptr_move_event = std::make_shared<MoveHistoryEvent>();
    sptr_move_event->set_move(convert_move_to_indexed_cards(
        move_state.get_move(),
        move_state.get_deck()));
    move_state.add_to_history(sptr_move_event);

    initial_deck.display();
    std::cout << "=== " << std::setw(6) << pq.size() << " ===" << std::setw(10) << iterations << " ===" << std::setw(3) << move_state.get_reshuffles() << " ===" << std::endl;
    updated_deck.display();
    std::cout << "---" << std::endl;
    if (pq.size() > 0)
    {
      get_healthiest_deck(pq).display();
    }
    std::cout << std::endl;

    hm[updated_deck.get_hash()] = true;
    move_states = determine_moves(updated_deck, pq);
    if (move_states.size() == 0)
    {
      if (can_reshuffle(move_state))
      {
        State s{};
        s.set_reshuffles(move_state.get_reshuffles() + 1);
        updated_deck.reshuffle();

        s.set_deck(updated_deck);
        move_states.push_back(s);

        std::shared_ptr<ReshuffleHistoryEvent> reshuffle_event = std::make_shared<ReshuffleHistoryEvent>();
        reshuffle_event->set_reshuffle_count(move_state.get_reshuffles() + 1);
        reshuffle_event->set_initial_deck(move_state.get_deck());
        reshuffle_event->set_reshuffled_deck(updated_deck);
        move_state.add_to_history(reshuffle_event);
      }
      else
      {
        std::cout << "No available reshuffles" << std::endl;
      }
    }

    for (auto &new_move_state : move_states)
    {
      new_move_state.set_history(move_state.get_history());
    }

    add_moves(pq, move_states);
  }

  std::cout << "Solved: " << std::boolalpha << is_solved << "\n"
            << updated_deck << "\n"
            << stream_out_history_events(move_state.get_history()) << "\n"
            << "Attempts: " << iterations << "   "
            << "Items remaining in queue: " << pq.size() << "\n"
            << std::endl;
  return 0;
}
