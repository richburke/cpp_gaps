#include <iostream>
#include <utility>
#include "MontanaDeck.h"

const int MAX_RESHUFFLES{35};
int attempts{0};

bool solve(MontanaDeck &deck)
{
  if (deck.is_goal())
  {
    return true;
  }

  std::vector<std::pair<int, int>> moves = deck.find_moves();

  if (moves.size() == 0)
  {
    std::cout << "No available moves" << std::endl;
    return false;
  }

  for (auto move : moves)
  {
    // MontanaDeck copy = deck;
    std::cout << move.first << " " << move.second << " " << std::endl;

    deck.move(move.first, move.second);
    // copy.move(move.first, move.second);
    attempts++;
    std::cout << "Attempts " << attempts << std::endl;

    if (attempts > 100)
    {
      std::cout << "Exceeded number of attempts" << std::endl;
      return false;
    }

    if (deck.is_goal())
    {
      return true;
    }
    // std::cout << "-------------------" << std::endl;
    // copy.display();
  }

  return solve(deck) ? true : false;
}

int main()
{
  /**
   * - Research strategies
   *   - if moving a king would have it in front of a space, give very low priority
   *   - moving a space to the last position for a row and not preceded by a king gets a very low value
   *   - moving a card to close to its proper sequence gets proportionally higher value
   *   - moving a card to a space away from its proper sequence gets a proportionally lower value
   *   - moving a card to its proper suit gets a somewhat high value
   *   - moving a 2 to the leftmost column gets a very high value
   *   - moving a 2 away from the leftmost column gets a very low value
   * - Prioritize moves
   *   - implement a priority queue
   * - Record successful moves
   */
  MontanaDeck deck{};
  deck.initialize();
  deck.shuffle();
  deck.display();

  std::cout << "-------------------" << std::endl;
  bool is_solved{false};
  int reshuffles{0};

  do
  {
    is_solved = solve(deck);
    if (is_solved)
    {
      break;
    }

    std::cout << "Attempts: \n"
              << attempts
              << std::endl;
    attempts = 0;

    deck.display();
    deck.reshuffle();
  } while (!is_solved && ++reshuffles < MAX_RESHUFFLES);

  deck.display();
  std::cout << "Solved: \n"
            << std::boolalpha
            << is_solved
            << std::endl;

  return 0;
}
