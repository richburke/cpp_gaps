#include <string>
#include <iostream>
#include <sstream>
#include "MontanaDeck.h"

/**
 * Change to State
 * initial
 * current
 * history
 * move
 * score
 */

class Move
{
  friend std::ostream &operator<<(std::ostream &os, const Move &rhs);
  friend bool operator<(const Move &x, const Move &rhs);

  std::pair<int, int> move{0, 0};
  MontanaDeck deck{}; // State of deck prior to move
  int score{0};

public:
  Move() = default;
  Move(std::pair<int, int> move, MontanaDeck deck, int score)
      : move{move}, deck{deck}, score{score} {}

  std::pair<int, int> get_move() const;
  MontanaDeck get_deck() const;
  int get_score() const;
  // bool operator<(const Move &rhs) const;
  // bool operator>(const Move &rhs) const;
  bool operator==(const Move &rhs) const;
  void display() const;

  // bool operator<(const Move &rhs) const
  // {
  //   std::cout << "COMPARING <" << std::endl;
  //   // std::cout << "Comparing " << score << " to " << rhs.score << std::endl;
  //   return this->score < rhs.score;
  // }

  bool operator>(const Move &rhs) const
  {
    std::cout << "COMPARING >" << std::endl;
    // std::cout << "Comparing " << score << " to " << rhs.score << std::endl;
    return this->score > rhs.score;
  }
};
