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

  HistoryEventType get_type() const;
  void set_type(enum HistoryEventType v);
};
