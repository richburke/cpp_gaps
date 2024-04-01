#include "HistoryEvent.h"

class MoveHistoryEvent : public HistoryEvent
{
public:
  MoveHistoryEvent() : HistoryEvent(HistoryEventType::move){};
};
