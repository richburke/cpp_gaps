#include "HistoryEvent.h"
#include "MontanaDeck.h"

class ReshuffleHistoryEvent : public HistoryEvent
{
private:
  int reshuffle_count{0};
  MontanaDeck initial_deck{};
  MontanaDeck reshuffled_deck{};

public:
  ReshuffleHistoryEvent() : HistoryEvent(HistoryEventType::reshuffle){};
  virtual ~ReshuffleHistoryEvent() = default;
  ReshuffleHistoryEvent(ReshuffleHistoryEvent &rhs) = default;
  ReshuffleHistoryEvent(ReshuffleHistoryEvent &&rhs) = default;
  void out(std::ostream &os) const override;

  MontanaDeck get_initial_deck() const;
  int get_reshuffle_count() const;
  MontanaDeck get_reshuffled_deck() const;
  void set_initial_deck(const MontanaDeck v);
  void set_reshuffle_count(const int v);
  void set_reshuffled_deck(const MontanaDeck v);
};
