#include <utility>
#include "HistoryEvent.h"
#include "Deck.h"

class MoveHistoryEvent : public HistoryEvent
{
private:
  std::pair<IndexedCard, IndexedCard> move{};

public:
  MoveHistoryEvent() : HistoryEvent(HistoryEventType::move){};
  virtual ~MoveHistoryEvent() = default;
  MoveHistoryEvent(MoveHistoryEvent &rhs) = default;
  std::pair<IndexedCard, IndexedCard> get_move() const;
  void set_move(const std::pair<IndexedCard, IndexedCard> v);
  void out(std::ostream &os) const override;
};
