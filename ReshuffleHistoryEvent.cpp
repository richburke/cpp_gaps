#include "ReshuffleHistoryEvent.h"

void ReshuffleHistoryEvent::out(std::ostream &os) const
{
  os << "Reshuffle"
     << "\n";
}

MontanaDeck ReshuffleHistoryEvent::get_initial_deck() const
{
  return this->initial_deck;
}

MontanaDeck ReshuffleHistoryEvent::get_reshuffled_deck() const
{
  return this->reshuffled_deck;
}

void ReshuffleHistoryEvent::set_initial_deck(const MontanaDeck v)
{
  this->initial_deck = v;
}

void ReshuffleHistoryEvent::set_reshuffled_deck(const MontanaDeck v)
{
  this->reshuffled_deck = v;
}
