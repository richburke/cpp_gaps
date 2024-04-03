#include "MoveHistoryEvent.h"

std::pair<IndexedCard, IndexedCard> MoveHistoryEvent::get_move() const
{
  return this->move;
}

void MoveHistoryEvent::set_move(const std::pair<IndexedCard, IndexedCard> v)
{
  this->move = v;
}

void MoveHistoryEvent::out(std::ostream &os) const
{
  move.first.out(os);
  os << " <-> ";
  move.second.out(os);
  os << "\n";
}