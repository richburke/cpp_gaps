#include "MontanaDeck.h"

Card MontanaDeck::get_empty_card()
{
    return {'-', '-', -1};
}

bool MontanaDeck::is_empty_card(Card card)
{
    return card.value == -1;
}

std::vector<int> MontanaDeck::get_row_starting_indices()
{
    return std::vector<int>{INDEX_ROW_START_1, INDEX_ROW_START_2, INDEX_ROW_START_3, INDEX_ROW_START_4};
};

std::vector<int> MontanaDeck::get_row_ending_indices()
{
    return std::vector<int>{INDEX_ROW_END_1, INDEX_ROW_END_2, INDEX_ROW_END_3, INDEX_ROW_END_4};
};

std::pair<int, int> MontanaDeck::get_row_indices(int index)
{
    for (int i = 0; i < row_indices.size(); i++)
    {
        if (index >= row_indices.at(i).first && index <= row_indices.at(i).second)
        {
            return row_indices.at(i);
        }
    }
    return {-1, -1};
};

std::vector<int> MontanaDeck::find_sequence_break_indices() const
{
    std::vector<int> break_indices{};

    for (auto row_start_index : get_row_starting_indices())
    {
        std::vector<Card> cards_in_row = get_cards_by_indices(row_start_index, row_start_index + COUNT_PER_ROW - 1);
        int break_index = get_break_in_sequence(cards_in_row);
        if (break_index != -1)
        {
            break_indices.push_back(row_start_index + break_index);
        }
    }

    return break_indices;
}

bool MontanaDeck::is_first_column(int x)
{
    std::vector<int> v = get_row_starting_indices();
    return std::find(v.begin(), v.end(), x) != v.end();
}

bool MontanaDeck::is_last_column(int x)
{
    std::vector<int> v = get_row_ending_indices();
    return std::find(v.begin(), v.end(), x) != v.end();
}

bool MontanaDeck::is_space_valid(int space) const
{
    if (space == INDEX_ROW_END_1 ||
        space == INDEX_ROW_END_2 ||
        space == INDEX_ROW_END_3 ||
        space == INDEX_ROW_END_4)
    {
        return false;
    }

    if (space > 0)
    {
        // Is not preceded by another space
        if (deck.at(space - 1).value == CARD_VALUE_ACE)
        {
            return false;
        }
        // Is not preceded by a king
        if (deck.at(space - 1).value == CARD_VALUE_KING)
        {
            return false;
        }
    }

    return true;
}

int MontanaDeck::get_row_index(int position) const
{
    return 1;
}

std::vector<int> MontanaDeck::find_all_gaps() const
{
    std::vector<int> spaces{};
    Card card;
    for (int i = 0; i < deck.size(); i++)
    {
        card = deck.at(i);
        if (card.value == CARD_VALUE_ACE)
        {
            spaces.push_back(i);
        }
    }
    return spaces;
}

std::vector<int> MontanaDeck::find_valid_gaps() const
{
    std::vector<int> valid = {};
    std::vector<int> spaces = find_all_gaps();

    for (auto space : spaces)
    {
        if (is_space_valid(space))
        {
            valid.push_back(space);
        }
    }
    return valid;
}

Card MontanaDeck::find_previous_card(int space) const
{
    if (space == INDEX_ROW_START_1 || space == INDEX_ROW_START_2 || space == INDEX_ROW_START_3 || space == INDEX_ROW_START_4)
    {
        return MontanaDeck::get_empty_card();
    }
    return deck.at(space - 1);
}

Card MontanaDeck::get_previous_card(int index) const
{
    if (index < 0)
    {
        return MontanaDeck::get_empty_card();
    }
    if (index == INDEX_ROW_START_1 || index == INDEX_ROW_START_2 || index == INDEX_ROW_START_3 || index == INDEX_ROW_START_4)
    {
        return MontanaDeck::get_empty_card();
    }
    return deck.at(index - 1);
}

Card MontanaDeck::get_next_card(int index) const
{
    if (index >= deck.size() - 1)
    {
        return MontanaDeck::get_empty_card();
    }
    return deck.at(index + 1);
}

Card MontanaDeck::find_previous_nongap_on_row(int position) const
{
    std::pair<int, int> indices = get_row_indices(position);
    if (indices.first == position)
    {
        return MontanaDeck::get_empty_card();
    }
    for (int i = indices.second; i > indices.first; i--)
    {
        Card card = deck.at(i);
        if (card.value != CARD_VALUE_ACE)
        {
            return card;
        }
    }

    return MontanaDeck::get_empty_card();
}

Card MontanaDeck::find_next_card(Card prev) const
{
    if (prev.value == CARD_VALUE_KING)
    {
        std::cerr << "Previous card was a king " << prev.suit_key << prev.card_key << std::endl;
        return MontanaDeck::get_empty_card();
    }

    return {
        prev.suit_key,
        Deck::get_next_card_key(prev.card_key),
        prev.value + 1};
}

// std::vector<Card> MontanaDeck::get_prioritized_deuces() const
// {
//     /**
//      * @todo
//      */
//     return std::vector<Card>{};
// }

int MontanaDeck::get_card_index(Card test) const
{
    Card card;
    for (int i = 0; i < deck.size(); i++)
    {
        card = deck.at(i);
        if (card.suit_key == test.suit_key && card.card_key == test.card_key)
        {
            return i;
        }
    }
    return -1;
}

std::vector<std::pair<int, int>> MontanaDeck::find_moves() const
{
    std::vector<int> gaps = find_valid_gaps();
    std::vector<std::pair<int, int>> moves{};

    for (auto space_index : gaps)
    {
        Card prev = find_previous_card(space_index);
        if (MontanaDeck::is_empty_card(prev))
        {
            // std::cout << "Get deuces" << std::endl;
            continue;
        }

        Card next = find_next_card(prev);
        if (next.is_ace())
        {
            std::cout << "Can't move a gap." << std::endl; // @todo Remove after complete
            continue;
        }

        int move_index = get_card_index(next);
        // std::cout << "Space: " << space_index << " Move: " << move_index << std::endl;
        moves.push_back(std::make_pair(space_index, move_index));
    }

    return moves;
}

void MontanaDeck::move(int space_index, int move_index)
{
    Card ace = deck.at(space_index);
    Card card = deck.at(move_index);
    deck.at(space_index) = card;
    deck.at(move_index) = ace;
}

bool MontanaDeck::is_goal() const
{
    std::vector<int> row_starting_indices = get_row_starting_indices();
    for (auto row_start_index : row_starting_indices)
    {
        // std::cout << deck.at(row_start_index + COUNT_PER_ROW - 1).value << std::endl;
        if (deck.at(row_start_index + COUNT_PER_ROW - 1).value != CARD_VALUE_ACE)
        {
            return false;
        }

        // std::cout << "Row start index: " << row_start_index << " " << (row_start_index + COUNT_PER_ROW - 2) << std::endl;
        std::vector<Card> cards_in_row = get_cards_by_indices(row_start_index, row_start_index + COUNT_PER_ROW - 2);

        // for (auto card : cards_in_row)
        // {
        //     std::cout << card.suit_key << card.card_key << " ";
        // }

        int break_index = get_break_in_sequence(cards_in_row);
        if (break_index != -1)
        {
            return false;
        }
    }
    return true;
}

// /**
//  * @todo
//  * Not sure I need this.
//  */
// bool MontanaDeck::is_stuck() const
// {
//     std::vector<Gap> gaps{};
//     std::vector<int> gaps_indices = find_all_gaps();
//     for (auto gap_index : gaps_indices)
//     {
//         Card gap = deck.at(gap_index);
//         Card previous = find_previous_nongap_on_row(gap_index);

//         gaps.push_back({gap, previous, gap_index});
//     }

//     for (auto gap : gaps)
//     {
//         std::cout << "Previous: " << gap.previous_nongap.suit_key << gap.previous_nongap.card_key << std::endl;
//         if (gap.previous_nongap.value == CARD_VALUE_KING)
//         {
//             return true;
//         }
//     }
//     return false;
//     /**
//      * - a space in the last position for a row, but not preceded by a king or another space
//      * - is the next card that is not a space to the
//      */
// }

std::vector<Card> MontanaDeck::get_cards_by_indices(const int start, const int end) const
{
    std::vector<Card> cards{};
    for (int i = start; i <= end; i++)
    {
        cards.push_back(deck.at(i));
    }
    return cards;
}

int MontanaDeck::get_break_in_sequence(std::vector<Card> cards) const
{
    /*
    const size_t length = cards.size();
        size_t index{0};
        int prev{cards.at(index).value};

        while (index < length)
        {
            index++;
            if (cards.at(index).value != prev + 1)
            {
                return index - 1;
            }
            prev = cards.at(index).value;
        }
    */

    // std::cout << "sequence: " << cards.size() << std::endl;

    if (cards.size() == 0)
    {
        return -1;
    }

    size_t index{0};
    int prev{cards.at(index).value};

    if (prev != CARD_VALUE_DEUCE)
    {
        return 0;
    }

    do
    {

        // std::cout << "?" << cards.at(index).value << std::endl;
        index++;

        /**
         * @todo
         * Fix this. Shouldn't need it.
         */
        if (index >= cards.size())
        {
            return -1;
        }
        if (cards.at(index).value != prev + 1)
        {
            return index;
        }
        prev = cards.at(index).value;
    } while (index < cards.size());

    return -1;
}

int MontanaDeck::calculate_total_in_sequence() const
{
    int total{0};
    for (auto row_start_index : get_row_starting_indices())
    {
        std::vector<Card> cards_in_row = get_cards_by_indices(row_start_index, row_start_index + COUNT_PER_ROW - 1);
        int break_index = get_break_in_sequence(cards_in_row);
        if (break_index == -1)
        {
            total += COUNT_PER_ROW;
        }
        else
        {
            total += break_index;
        }
    }
    return total;
}

void MontanaDeck::replace_cards(std::queue<Card> replacements)
{
    int index{0};
    const int length = deck.size();
    while (!replacements.empty() && index < length)
    {
        if (is_empty_card(deck.at(index)))
        {
            deck.at(index) = replacements.front();
            replacements.pop();
        }
        index++;
    }
}

void MontanaDeck::reshuffle()
{
    std::vector<Card> cards_to_shuffle{};

    std::vector<int> row_starting_indices = get_row_starting_indices();
    for (auto row_start_index : row_starting_indices)
    {
        std::vector<Card> cards_in_row = get_cards_by_indices(row_start_index, row_start_index + COUNT_PER_ROW - 1);
        int break_index = get_break_in_sequence(cards_in_row);
        if (break_index == -1)
        {
            continue;
        }

        for (int i = row_start_index + break_index; i < row_start_index + COUNT_PER_ROW; i++)
        {
            cards_to_shuffle.push_back(deck.at(i));
            deck.at(i) = get_empty_card();
        }
    }

    // std::cout << "Cards to shuffle\n";
    // for (auto card : cards_to_shuffle)
    // {
    //     std::cout << card.suit_key << card.card_key << " ";
    // }
    // std::cout << std::endl;

    std::random_shuffle(cards_to_shuffle.begin(), cards_to_shuffle.end());
    // std::cout << "After shuffle\n";
    // for (auto card : cards_to_shuffle)
    // {
    //     std::cout << card.suit_key << card.card_key << " ";
    // }
    // std::cout << std::endl;

    // display();

    std::queue<Card> q;
    for (auto card : cards_to_shuffle)
    {
        q.push(card);
    }

    replace_cards(q);
    // display();
}

/**
 * @todo
 * Remove in favor of insertion operator
 */
void MontanaDeck::display() const
{
    for (auto row_index : get_row_starting_indices())
    {
        for (int i = 0; i < COUNT_PER_ROW; i++)
        {
            std::cout << deck[row_index + i].suit_key << deck[row_index + i].card_key << " ";
        }
        std::cout << std::endl;
    }
}

std::string MontanaDeck::get_hash() const
{
    std::stringstream ss{};
    // std::cout << "=== start hash ===" << std::endl;
    for (auto card : deck)
    {
        // std::cout << card.suit_key << card.card_key << card.value << std::endl;
        ss << card.suit_key << card.card_key;
    }
    // std::cout << "=== finish hash ===" << std::endl;
    // std::cout << "----" << std::endl;
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const MontanaDeck &rhs)
{
    for (auto row_index : MontanaDeck::get_row_starting_indices())
    {
        for (int i = 0; i < COUNT_PER_ROW; i++)
        {
            os << rhs.deck[row_index + i].suit_key << rhs.deck[row_index + i].card_key << " ";
        }
        std::cout << std::endl;
    }
    return os;
}
