#ifndef _DECK_H_
#define _DECK_H_
#include <string>
#include <vector>

const int CARD_VALUE_ACE = 1;
const int CARD_VALUE_DEUCE = 2;
const int CARD_VALUE_KING = 13;
const char SUIT_KEY_CLUBS = 'C';
const char SUIT_KEY_DIAMONDS = 'D';
const char SUIT_KEY_HEARTS = 'H';
const char SUIT_KEY_SPADES = 'S';

struct Card
{
    char suit_key;
    char card_key;
    int value;
    bool matches_suit(char test)
    {
        return suit_key == test;
    };
    bool matches_card(char test)
    {
        return card_key == test;
    };
    bool is_ace()
    {
        return value == CARD_VALUE_ACE;
    };
    bool is_deuce()
    {
        return value == CARD_VALUE_DEUCE;
    };
    bool is_king()
    {
        return value == CARD_VALUE_KING;
    };
};

struct IndexedCard
{
    Card card;
    int index;
};

class Deck
{
public:
    std::vector<Card> deck{};

    Deck() = default;
    ~Deck() = default;

    void initialize();
    void shuffle();
    void display() const;

    std::vector<Card> get_deck() const;
    static char get_next_card_key(char card_key);
};

#endif // _DECK_H_
