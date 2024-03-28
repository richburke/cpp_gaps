// #include "Move.h"

// std::pair<int, int> Move::get_move() const
// {
//   return move;
// }

// MontanaDeck Move::get_deck() const
// {
//   return deck;
// }

// int Move::get_score() const
// {
//   return score;
// }

// bool Move::operator==(const Move &rhs) const
// {
//   std::stringstream ss_this{};
//   std::stringstream ss_rhs{};

//   std::string deck_this = this->get_deck().get_hash();
//   std::string deck_rhs = rhs.get_deck().get_hash();

//   return (ss_this.str() == ss_rhs.str() &&
//           deck_this == deck_rhs);
// }

// void Move::display() const
// {
//   std::cout << "Move: (" << move.first << ", " << move.second << ")"
//             << " " << score
//             // << " [" << start_state << "]"
//             << std::endl;
// }

// std::string display_deck(const std::vector<Card> &deck)
// {
//   std::stringstream result;
//   result << "[";
//   size_t index{0};
//   for (const auto &element : deck)
//   {
//     result << element.suit_key << element.card_key << (index < deck.size() - 1 ? " " : "");
//     index++;
//   }
//   result << "]";
//   return result.str();
// }

// std::ostream &operator<<(std::ostream &os, const Move &rhs)
// {
//   os << "Move: (" << rhs.get_move().first << ", " << rhs.get_move().second << ")"
//      << " " << rhs.get_score()
//      << "\n"
//      << rhs.get_deck();
//   return os;
// }

// bool operator<(const Move &x, const Move &rhs)
// {
//   std::cout << "COMPARING <" << std::endl;
//   // std::cout << "Comparing " << score << " to " << rhs.score << std::endl;
//   return x.score < rhs.score;
// }

// std::ostream &operator<<(std::ostream &os, const std::vector<Card> &rhs)
// {
//   os << "[";
//   for (const auto &element : rhs)
//   {
//     os << element.suit_key << element.card_key << " ";
//   }
//   os << "]";
//   return os;
// }

// std::ostream &operator<<(std::ostream &os, const Card &rhs)
// {
//   os << rhs.suit_key << rhs.card_key << " ";
//   return os;
// }
