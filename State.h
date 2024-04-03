#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "HistoryEvent.h"
#include "MontanaDeck.h"

/**
 * @todo
 * Change to MoveState
 */
class State
{
  friend std::ostream &operator<<(std::ostream &os, const State &rhs);

private:
  MontanaDeck deck{}; // State of deck prior to move
  std::vector<std::unique_ptr<HistoryEvent>> history{};
  std::pair<int, int> move{0, 0};
  int deck_score{0};
  int score{0};
  int reshuffles{0};

public:
  State() = default;
  State(std::pair<int, int> move, MontanaDeck deck, int score)
      : move{move}, deck{deck}, score{score} {}

  bool operator<(const State &rhs) const;
  bool operator==(const State &rhs) const;

  // std::vector<std::unique_ptr<HistoryEvent>> get_history() const;
  std::pair<int, int> get_move() const;
  MontanaDeck get_deck() const;
  int get_score() const;
  int get_reshuffles() const;
  void set_deck(MontanaDeck v);
  // void set_history(std::vector<std::unique_ptr<HistoryEvent>> v);
  void set_reshuffles(int v);
  void set_deck_score(int v);
  int add_to_history(std::unique_ptr<HistoryEvent> event);
};
