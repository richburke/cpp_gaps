#ifndef _MONTANA_DECK_H_
#define _MONTANA_DECK_H_
#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <queue>
#include "Deck.h"

const int COUNT_PER_ROW = 13;
const int INDEX_ROW_START_1 = 0;
const int INDEX_ROW_START_2 = 13;
const int INDEX_ROW_START_3 = 26;
const int INDEX_ROW_START_4 = 39;
const int INDEX_ROW_END_1 = INDEX_ROW_START_2 - 1;
const int INDEX_ROW_END_2 = INDEX_ROW_START_3 - 1;
const int INDEX_ROW_END_3 = INDEX_ROW_START_4 - 1;
const int INDEX_ROW_END_4 = 51;

const std::vector<std::pair<int, int>> row_indices{
    {INDEX_ROW_START_1, INDEX_ROW_END_1},
    {INDEX_ROW_START_2, INDEX_ROW_END_2},
    {INDEX_ROW_START_3, INDEX_ROW_END_3},
    {INDEX_ROW_START_4, INDEX_ROW_END_4}};

struct Gap
{
    Card gap;
    Card previous_nongap;
    int position;
};

class MontanaDeck : public Deck
{
    friend std::ostream &operator<<(std::ostream &os, const MontanaDeck &rhs);

private:
    int reshuffle_count{0};
    int get_card_index(Card card) const;
    // std::vector<Card> get_prioritized_deuces() const;
    static Card get_empty_card();
    static bool is_empty_card(Card card);
    static std::pair<int, int> get_row_indices(int index);
    bool is_space_valid(int space) const;
    int get_row_index(int position) const;
    std::vector<int> find_all_gaps() const;
    std::vector<int> find_valid_gaps() const;
    Card find_previous_card(int space) const;
    Card find_next_card(Card card) const;
    Card find_previous_nongap_on_row(int position) const;
    std::vector<Card> get_cards_by_indices(int start, int end) const;
    int get_break_in_sequence(std::vector<Card> cards) const;
    void replace_cards(std::queue<Card> cards);

public:
    MontanaDeck() = default;
    ~MontanaDeck() = default;
    bool is_goal() const;
    // bool is_reshufflable() const;
    // bool is_stuck() const;
    void display() const;
    void move(int, int);
    std::vector<std::pair<int, int>> find_moves() const;
    void reshuffle();
    static std::vector<int> get_row_starting_indices();
    static std::vector<int> get_row_ending_indices();
    std::vector<int> find_sequence_break_indices() const;
    static bool is_first_column(int index);
    static bool is_last_column(int index);
    Card get_previous_card(int index) const;
    Card get_next_card(int index) const;
    int calculate_total_in_sequence() const;
    std::string get_hash() const;
};

#endif // _MONTANA_DECK_H_
