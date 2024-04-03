#ifndef _HISTORY_EVENT_H_
#define _HISTORY_EVENT_H_

#include <iostream>

enum class HistoryEventType
{
  unknown,
  move,
  reshuffle
};

class HistoryEvent
{
private:
  enum HistoryEventType type
  {
    HistoryEventType::unknown
  };

public:
  HistoryEvent(enum HistoryEventType type)
      : type{type} {}
  virtual ~HistoryEvent() = default;
  HistoryEvent(HistoryEvent &rhs) = default;
  HistoryEvent(HistoryEvent &&rhs) = default;

  // virtual void out(std::ostream &os) const;
  virtual void out(std::ostream &os) const
  {
    os << "Fix! Not calling derived out() methods!\n";
  }

  HistoryEventType get_type() const;
  void set_type(enum HistoryEventType v);
};

#endif // _HISTORY_EVENT_H_
