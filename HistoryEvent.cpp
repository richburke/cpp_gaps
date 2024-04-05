#include "HistoryEvent.h"

HistoryEventType HistoryEvent::get_type() const
{
  return this->type;
}

void HistoryEvent::set_type(enum HistoryEventType v)
{
  this->type = type;
}
