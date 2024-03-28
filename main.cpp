#include <iostream>
#include <utility>
#include <random> // Only needed for dev
#include <queue>
#include <cmath>
#include "MontanaDeck.h"
// #include "Move.h"

// 15 -> 33673
// 10 -> 123826
// 9 -> 43531
// 8 -> 252462

/**
 * @todo
 * Restructure
 *  - Remove recursion
 *    - get moves
 *    - add to queue
 *    - iterate through queue
 *
 * - Create hashmap of decks
 *   - moves for each(?)
 *   - attempted
 *   - if in queue,
 *     - don't determine moves
 *   - if attempted,
 *     - don't add moves to queue
 *
 *  - Get all decks from hashmap that have not been attempted.
 *  - Determine their moves.
 *  - Add moves to queue
 *  - Mark them as attempted.
 *
 *  - Add the first deck to the hashmap
 *  - Get its moves
 *  - Add the moves to the queue
 * - Do while the queue is not empty
 *
 * - Deck
 * - Number of reshuffles
 */

const int MAX_ATTEMPTS{100000};
const double DRAIN_PERCENTAGE{0.10};
/**
 * @todo
 * - Add score threshold limit
 */
const double PQ_LIMIT{5};

int attempts{0};
int highest{-100};

// struct compare
// {
//   bool operator()(Move &a, Move &b) // overloading both operators
//   {
//     std::cout << "COMPARE via struct" << std::endl;
//     return a.get_score() < b.get_score(); // if you want increasing order;(i.e increasing for minPQ)
//   }
// };

#include <string>
#include <iostream>
#include <sstream>
#include "MontanaDeck.h"

/**
 * Change to State
 * initial
 * current
 * history
 * move
 * score
 */

class Move
{
  friend std::ostream &operator<<(std::ostream &os, const Move &rhs);
  // friend bool operator<(const Move &x, const Move &rhs);

  std::pair<int, int> move{0, 0};
  MontanaDeck deck{}; // State of deck prior to move
  int score{0};

public:
  // Move() = default;
  Move(std::pair<int, int> move, MontanaDeck deck, int score)
      : move{move}, deck{deck}, score{score} {}

  // std::pair<int, int> get_move() const;
  // MontanaDeck get_deck() const;
  // int get_score() const;
  // bool operator<(const Move &rhs) const;
  // bool operator>(const Move &rhs) const;
  // bool operator==(const Move &rhs) const;
  // void display() const;

  bool operator<(const Move &rhs) const
  {
    // std::cout << "COMPARING < m1" << std::endl;
    // std::cout << "Comparing " << score << " to " << rhs.score << std::endl;
    return this->score < rhs.score;
  }

  bool operator>(const Move &rhs) const
  {
    // std::cout << "COMPARING >" << std::endl;
    // std::cout << "Comparing " << score << " to " << rhs.score << std::endl;
    return this->score > rhs.score;
  }

  std::pair<int, int> get_move() const
  {
    return move;
  }

  MontanaDeck get_deck() const
  {
    return deck;
  }

  int get_score() const
  {
    return score;
  }

  bool operator==(const Move &rhs) const
  {
    std::stringstream ss_this{};
    std::stringstream ss_rhs{};

    // std::cout << "base" << std::endl;
    // std::cout << this->get_move().first << std::endl;
    // std::cout << "test" << std::endl;
    // std::cout << rhs.get_move().first << std::endl;

    ss_this << this->get_move().first << "*" << this->get_move().second;
    ss_rhs << rhs.get_move().first << "*" << rhs.get_move().second;

    // std::cout << "base-" << std::endl;
    // std::cout << *this << std::endl;

    // std::cout << "--- get this hash ---" << std::endl;
    // std::cout << "--- " << this->deck << " ---" << std::endl;
    std::string deck_this = this->get_deck().get_hash();
    // std::cout << "--- got this hash ---" << std::endl;
    // std::cout << "test-" << std::endl;
    // std::cout << rhs << std::endl;
    // std::cout << "--- get rhs hash ---" << std::endl;
    std::string deck_rhs = rhs.get_deck().get_hash();
    // std::cout << "--- got rhs hash ---" << std::endl;

    return (ss_this.str() == ss_rhs.str() &&
            deck_this == deck_rhs);
  }

  // void display() const
  // {
  //   std::cout << "Move: (" << move.first << ", " << move.second << ")"
  //             << " " << score
  //             << " [" << deck << "]"
  //             << std::endl;
  // }
};

// class Move2
// {
//   friend std::ostream &operator<<(std::ostream &os, const Move &rhs);
//   // friend bool operator<(const Move &x, const Move &rhs);

//   std::pair<int, int> move{0, 0};
//   // MontanaDeck deck{}; // State of deck prior to move
//   int score{0};

// public:
//   // Move() = default;
//   // Move(std::pair<int, int> move, MontanaDeck deck, int score)
//   //     : move{move}, deck{deck}, score{score} {}
//   Move2(std::pair<int, int> move, int score)
//       : move{move}, score{score} {}

//   // std::pair<int, int> get_move() const;
//   // MontanaDeck get_deck() const;
//   // int get_score() const;
//   // bool operator<(const Move &rhs) const;
//   // bool operator>(const Move &rhs) const;
//   // bool operator==(const Move &rhs) const;
//   // void display() const;

//   bool operator<(const Move2 &rhs) const
//   {
//     std::cout << "COMPARING < m2" << std::endl;
//     // std::cout << "Comparing " << score << " to " << rhs.score << std::endl;
//     return this->score < rhs.score;
//   }

//   std::pair<int, int> get_move() const
//   {
//     return move;
//   }

//   int get_score() const
//   {
//     return score;
//   }
// };

std::ostream &operator<<(std::ostream &os, const Move &rhs)
{
  os << "Move: (" << rhs.get_move().first << ", " << rhs.get_move().second << ")"
     << " " << rhs.get_score()
     << "\n"
     << rhs.get_deck();
  return os;
}
// std::ostream &operator<<(std::ostream &os, const Move2 &rhs)
// {
//   os << "Move: (" << rhs.get_move().first << ", " << rhs.get_move().second << ")"
//      << " " << rhs.get_score()
//      << "\n";
//   //  << rhs.get_deck();
//   return os;
// }

// class Person
// {
//   friend std::ostream &operator<<(std::ostream &os, const Person &p);
//   std::string name;
//   int age;

// public:
//   Person() : name{"Unknown"}, age{0} {}
//   Person(std::string name, int age)
//       : name{name}, age{age} {}
//   bool operator<(const Person &rhs) const
//   {
//     // return this->age < rhs.age;
//     std::cout << "PERSON COMPARE" << std::endl;
//     return this->name < rhs.name;
//   }
//   bool operator==(const Person &rhs) const
//   {
//     return (this->name == rhs.name && this->age == rhs.age);
//   }
// };

// std::ostream &operator<<(std::ostream &os, const Person &p)
// {
//   os << p.name << ":" << p.age;
//   return os;
// }

template <typename T>
void display(std::priority_queue<T> pq)
{
  std::cout << "[ ";
  while (!pq.empty())
  {
    T elem = pq.top();
    pq.pop();
    std::cout << elem << " ";
  }
  std::cout << "]" << std::endl;
}

/**
 * Sadly this doesn't work, but I'm not sure why.
 */
// template <typename T>
// std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
// {
//   os << "[";
//   for (const auto &element : v)
//   {
//     os << element << " ";
//   }
//   os << "]";
//   return os;
// }

int calculate_score(MontanaDeck deck, std::pair<int, int> move)
{
  int score{0};

  // For decks with a lot of cards in sequence, give a very high value.
  /**
   * @todo
   * Would be cool to do on a sliding scale--the greater the sequence,
   * the proportionally higher the score.
   */
  score += deck.calculate_total_in_sequence() * 10;

  // if (move.second == 33)
  // {
  //   score += 1;
  // }
  // if (move.second == 43)
  // {
  //   score += 2;
  // }
  // if (move.second == 18)
  // {
  //   score += 3;
  // }

  Card current = deck.get_deck()[move.second];
  // std::cout << current.suit_key << current.card_key << std::endl;
  Card gap = deck.get_deck()[move.first];
  Card previous = deck.get_previous_card(move.second);
  Card next = deck.get_next_card(move.second);

  // std::cout << "Current: " << current.suit_key << current.card_key << std::endl;
  // std::cout << "Next: " << next.suit_key << next.card_key << std::endl;

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

  // When moving a 2 to the leftmost column, give a very high value.
  if (MontanaDeck::is_first_column(move.second) && current.is_deuce())
  {
    score += 50;
  }
  // If moving a king would have it in front of a gap, give i a very low
  // priority.
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
  /**
   * - determine the state of the move
   *   - moving a card to close to its proper sequence gets proportionally higher value
   *   - moving a card to a space away from its proper sequence gets a proportionally lower value
   *   - moving a card to its proper suit gets a somewhat high value
   * */
  // std::random_device rd;  // obtain a random number from hardware
  // std::mt19937 gen(rd()); // seed the generator
  // // std::mt19937 gen();
  // std::uniform_int_distribution<> distr(-10, 100); // define the range

  // return distr(gen);
}

std::priority_queue<Move> trim_priority_queue(std::priority_queue<Move> source, int limit)
{
  std::priority_queue<Move> result{};
  int count{0};
  while (!source.empty())
  {
    if (count >= limit)
    {
      break;
    }
    result.push(source.top());
    source.pop();
    count++;
  }
  return result;
}

// bool does_move_exist_in_queue(std::priority_queue<Move, std::vector<Move>, compare> pq, Move &move)
bool does_move_exist_in_queue(std::priority_queue<Move> pq, Move &move)
{
  while (!pq.empty())
  {
    auto test = pq.top();
    pq.pop();
    if (test == move)
    {
      // std::cout << "EQUALS MOVE" << test << " " << move << std::endl;
      // std::cout << "---!after equals (true)!---" << std::endl;
      return true;
    }
  }
  // std::cout << "---!after equals (false)!---" << std::endl;
  return false;
}

// std::pair<bool, MontanaDeck> solve(MontanaDeck &deck, std::priority_queue<Move, std::vector<Move>, compare> &pq)
std::pair<bool, MontanaDeck> solve(MontanaDeck &deck, std::priority_queue<Move> &pq)
{
  if (deck.is_goal())
  {
    std::cout << "*** SOLUTION!!! ***" << std::endl;
    return {true, deck};
  }

  std::vector<std::pair<int, int>> moves = deck.find_moves();
  if (moves.size() == 0 && pq.empty())
  {
    if (moves.size() == 0)
    {
      std::cout << "No available moves" << std::endl;
    }
    if (pq.empty())
    {
      std::cout << "Moves queue is empty" << std::endl;
    }

    if (!deck.is_reshufflable())
    {
      return {false, deck};
    }

    deck.reshuffle();
    return solve(deck, pq);
  }

  for (auto move : moves)
  {
    Move m{move, deck, calculate_score(deck, move)};
    Card previous = deck.get_deck()[move.first];
    Card current = deck.get_deck()[move.second];
    // std::cout << previous.suit_key << previous.card_key << std::endl;
    // std::cout << current.suit_key << current.card_key << std::endl;
    // std::cout << "--- " << moves.size() << " ---" << std::endl;
    if (!does_move_exist_in_queue(pq, m))
    {
      // std::cout << "---!push!---" << std::endl;
      // std::cout << m << std::endl;
      pq.push(m);
    }
  }
  // std::cout << "---?" << pq.size() << "?---" << std::endl;

  // if (attempts > 3)
  // {
  //   display(pq);
  //   exit(0);
  // }

  /**
   * @todo
   * Remove when solved.
   */
  attempts++;
  // std::cout << "Attempts " << attempts << std::endl;
  if (attempts >= MAX_ATTEMPTS)
  {
    std::cout << "Exceeded number of attempts" << std::endl;
    return {false, deck};
  }
  /***/

  /**
   * @todo
   * Always drain a percentage of the queue.
   * - Drain 10% of the queue
   */
  // std::cout << pq.size() << std::endl;
  // int drain = std::ceil(pq.size() * DRAIN_PERCENTAGE);
  // for (int i = 0; i < drain; i++)
  // {
  //   auto move = pq.top();
  //   if (move.get_score() > highest)
  //   {
  //     highest = move.get_score();
  //     std::cout << ": " << highest << std::endl;
  //   }
  //   pq.pop();
  //   // std::cout << pq.size() << std::endl;
  //   // std::cout << "Move: " << move.get_score() << std::endl;
  //   auto move_deck = move.get_deck();
  //   move_deck.move(move.get_move().first, move.get_move().second);

  //   return solve(move_deck, pq);
  // }

  if (pq.size() > PQ_LIMIT)
  {
    pq = trim_priority_queue(pq, PQ_LIMIT);
    // std::cout << "-- trimming --" << std::endl;
  }

  auto move = pq.top();

  std::cout << "=== " << pq.size() << " ===" << std::endl;

  if (move.get_score() > highest)
  {
    highest = move.get_score();
    std::cout << ": " << highest << std::endl;
  }
  pq.pop();
  // std::cout << pq.size() << std::endl;
  // std::cout << "Move: " << move.get_score() << std::endl;
  auto move_deck = move.get_deck();
  move_deck.move(move.get_move().first, move.get_move().second);

  return solve(move_deck, pq);
}

// template <typename T, S, R>
// void display(std::priority_queue<Move, std::vector<Move>, compare> &pq)
// {
//   std::cout << "[ ";
//   while (!pq.empty())
//   {
//     Move elem = pq.top();
//     pq.pop();
//     std::cout << elem << " ";
//   }
//   std::cout << "]" << std::endl;
// }

// template <typename T>
// std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
// {
//   os << "[";
//   for (const auto &element : v)
//   {
//     os << element << " ";
//   }
//   os << "]";
//   return os;
// }

int main()
{
  /**
   * - Research strategies
   * - Record successful moves
   */
  MontanaDeck deck{};
  std::pair<bool, MontanaDeck> result{false, deck};
  std::priority_queue<Move> pq{};

  deck.initialize();
  deck.shuffle();
  deck.display();

  std::cout << "-------------------" << std::endl;

  do
  {
    result = solve(deck, pq);
    if (result.first)
    {
      break;
    }

    // std::cout << "Attempts: \n"
    //           << attempts
    //           << std::endl;
    // attempts = 0;

    // std::cout << "pq size " << pq.size() << std::endl;
    // std::cout << "-------------------" << std::endl;
    // std::cout << pq.top() << std::endl;
    // std::cout << "-------------------" << std::endl;

    // deck.display();
  } while (!result.first);

  // deck.display();
  std::cout << "Solved: " << std::boolalpha << result.first << "\n"
            << result.second << "\n"
            << "Attempts: " << attempts << "\n"
            << "Items remaining in queue: " << pq.size() << "\n"
            << std::endl;

  std::cout << "-------------------" << std::endl;
  display(pq);

  // std::priority_queue<Person> pq_person;
  // pq_person.push(Person{"A", 10});
  // pq_person.push(Person{"B", 1});
  // pq_person.push(Person{"C", 14});
  // pq_person.push(Person{"D", 18});
  // pq_person.push(Person{"E", 7});
  // pq_person.push(Person{"F", 27});

  // display(pq_person);

  // std::priority_queue<Move> pq_move1;
  // pq_move1.push(Move{{0, 1}, MontanaDeck{}, 11});
  // pq_move1.push(Move{{0, 1}, MontanaDeck{}, 1});
  // pq_move1.push(Move{{0, 1}, MontanaDeck{}, 14});
  // pq_move1.push(Move{{0, 1}, MontanaDeck{}, 18});
  // pq_move1.push(Move{{0, 1}, MontanaDeck{}, 32});
  // pq_move1.push(Move{{0, 1}, MontanaDeck{}, 4});
  // pq_move1.push(Move{{0, 1}, MontanaDeck{}, 64});
  // display(pq_move1);
  // std::cout << "===" << std::endl;

  // std::priority_queue<Move2> pq_move2;
  // pq_move2.push(Move2{{0, 1}, 10});
  // pq_move2.push(Move2{{0, 1}, 1});
  // pq_move2.push(Move2{{0, 1}, 14});
  // pq_move2.push(Move2{{0, 1}, 18});
  // pq_move2.push(Move2{{0, 1}, 7});
  // pq_move2.push(Move2{{0, 1}, 27});
  // display(pq_move2);

  return 0;
}
