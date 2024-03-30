#include "State.h"

bool State::operator<(const State &rhs) const
{
  return score < rhs.score;
}

bool State::operator==(const State &rhs) const
{
  std::stringstream ss_this{};
  std::stringstream ss_rhs{};
  ss_this << this->get_move().first << "*" << this->get_move().second;
  ss_rhs << rhs.get_move().first << "*" << rhs.get_move().second;

  std::string deck_this = deck.get_hash();
  std::string deck_rhs = rhs.get_deck().get_hash();

  return (ss_this.str() == ss_rhs.str() &&
          deck_this == deck_rhs);
}

std::vector<std::pair<int, int>> State::get_history() const
{
  return history;
}

std::pair<int, int> State::get_move() const
{
  return move;
}

MontanaDeck State::get_deck() const
{
  return deck;
}

int State::get_score() const
{
  return score;
}

int State::get_reshuffles() const
{
  return reshuffles;
}

void State::set_deck(MontanaDeck v)
{
  deck = v;
}

void State::set_deck_score(int v)
{
  deck_score = v;
}

void State::set_history(std::vector<std::pair<int, int>> v)
{
  history = v;
}

void State::set_reshuffles(int v)
{
  reshuffles = v;
}

int State::add_to_history(std::pair<int, int> move)
{
  history.push_back(move);
  return history.size();
}

std::ostream &operator<<(std::ostream &os, const State &rhs)
{
  os << "(" << rhs.get_move().first << ", " << rhs.get_move().second << ")"
     << ", " << rhs.get_score()
     << ", " << rhs.get_reshuffles()
     << "\n"
     << rhs.get_deck();
  return os;
}
