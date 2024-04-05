#include "ReshuffleHistoryEvent.h"

void ReshuffleHistoryEvent::out(std::ostream &os) const
{
  os << "===\n"
     << "Reshuffle (" << reshuffle_count << ")\n"
     << get_initial_deck()
     << "---\n"
     << get_reshuffled_deck()
     << "\n";
}

MontanaDeck ReshuffleHistoryEvent::get_initial_deck() const
{
  return initial_deck;
}

int ReshuffleHistoryEvent::get_reshuffle_count() const
{
  return reshuffle_count;
}

MontanaDeck ReshuffleHistoryEvent::get_reshuffled_deck() const
{
  return reshuffled_deck;
}

void ReshuffleHistoryEvent::set_initial_deck(const MontanaDeck v)
{
  initial_deck = v;
}

void ReshuffleHistoryEvent::set_reshuffle_count(const int v)
{
  reshuffle_count = v;
}

void ReshuffleHistoryEvent::set_reshuffled_deck(const MontanaDeck v)
{
  reshuffled_deck = v;
}
