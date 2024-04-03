#include "HistoryEvent.h"

HistoryEventType HistoryEvent::get_type() const
{
  return this->type;
}

void HistoryEvent::set_type(enum HistoryEventType v)
{
  this->type = type;
}

// void HistoryEvent::out(std::ostream &os) const
// {
//   os << "Fix! Not calling derived out() methods!\n";
// }
