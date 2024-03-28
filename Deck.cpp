#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "Deck.h"

std::vector<Card> Deck::get_deck() const
{
    return deck;
}

char Deck::get_next_card_key(char card_key)
{
    if (card_key == 'A')
    {
        return '2';
    }
    if (card_key == '2')
    {
        return '3';
    }
    if (card_key == '3')
    {
        return '4';
    }
    if (card_key == '4')
    {
        return '5';
    }
    if (card_key == '5')
    {
        return '6';
    }
    if (card_key == '6')
    {
        return '7';
    }
    if (card_key == '7')
    {
        return '8';
    }
    if (card_key == '8')
    {
        return '9';
    }
    if (card_key == '9')
    {
        return '0';
    }
    if (card_key == '0')
    {
        return 'J';
    }
    if (card_key == 'J')
    {
        return 'Q';
    }
    if (card_key == 'Q')
    {
        return 'K';
    }
    return ' ';
}

void Deck::initialize()
{
    deck.push_back({SUIT_KEY_CLUBS, '+', 1}); // + is the key for an ace, for now
    deck.push_back({SUIT_KEY_CLUBS, '2', 2});
    deck.push_back({SUIT_KEY_CLUBS, '3', 3});
    deck.push_back({SUIT_KEY_CLUBS, '4', 4});
    deck.push_back({SUIT_KEY_CLUBS, '5', 5});
    deck.push_back({SUIT_KEY_CLUBS, '6', 6});
    deck.push_back({SUIT_KEY_CLUBS, '7', 7});
    deck.push_back({SUIT_KEY_CLUBS, '8', 8});
    deck.push_back({SUIT_KEY_CLUBS, '9', 9});
    deck.push_back({SUIT_KEY_CLUBS, '0', 10});
    deck.push_back({SUIT_KEY_CLUBS, 'J', 11});
    deck.push_back({SUIT_KEY_CLUBS, 'Q', 12});
    deck.push_back({SUIT_KEY_CLUBS, 'K', 13});

    deck.push_back({SUIT_KEY_DIAMONDS, '+', 1});
    deck.push_back({SUIT_KEY_DIAMONDS, '2', 2});
    deck.push_back({SUIT_KEY_DIAMONDS, '3', 3});
    deck.push_back({SUIT_KEY_DIAMONDS, '4', 4});
    deck.push_back({SUIT_KEY_DIAMONDS, '5', 5});
    deck.push_back({SUIT_KEY_DIAMONDS, '6', 6});
    deck.push_back({SUIT_KEY_DIAMONDS, '7', 7});
    deck.push_back({SUIT_KEY_DIAMONDS, '8', 8});
    deck.push_back({SUIT_KEY_DIAMONDS, '9', 9});
    deck.push_back({SUIT_KEY_DIAMONDS, '0', 10});
    deck.push_back({SUIT_KEY_DIAMONDS, 'J', 11});
    deck.push_back({SUIT_KEY_DIAMONDS, 'Q', 12});
    deck.push_back({SUIT_KEY_DIAMONDS, 'K', 13});

    deck.push_back({SUIT_KEY_HEARTS, '+', 1});
    deck.push_back({SUIT_KEY_HEARTS, '2', 2});
    deck.push_back({SUIT_KEY_HEARTS, '3', 3});
    deck.push_back({SUIT_KEY_HEARTS, '4', 4});
    deck.push_back({SUIT_KEY_HEARTS, '5', 5});
    deck.push_back({SUIT_KEY_HEARTS, '6', 6});
    deck.push_back({SUIT_KEY_HEARTS, '7', 7});
    deck.push_back({SUIT_KEY_HEARTS, '8', 8});
    deck.push_back({SUIT_KEY_HEARTS, '9', 9});
    deck.push_back({SUIT_KEY_HEARTS, '0', 10});
    deck.push_back({SUIT_KEY_HEARTS, 'J', 11});
    deck.push_back({SUIT_KEY_HEARTS, 'Q', 12});
    deck.push_back({SUIT_KEY_HEARTS, 'K', 13});

    deck.push_back({SUIT_KEY_SPADES, '+', 1});
    deck.push_back({SUIT_KEY_SPADES, '2', 2});
    deck.push_back({SUIT_KEY_SPADES, '3', 3});
    deck.push_back({SUIT_KEY_SPADES, '4', 4});
    deck.push_back({SUIT_KEY_SPADES, '5', 5});
    deck.push_back({SUIT_KEY_SPADES, '6', 6});
    deck.push_back({SUIT_KEY_SPADES, '7', 7});
    deck.push_back({SUIT_KEY_SPADES, '8', 8});
    deck.push_back({SUIT_KEY_SPADES, '9', 9});
    deck.push_back({SUIT_KEY_SPADES, '0', 10});
    deck.push_back({SUIT_KEY_SPADES, 'J', 11});
    deck.push_back({SUIT_KEY_SPADES, 'Q', 12});
    deck.push_back({SUIT_KEY_SPADES, 'K', 13});
}

void Deck::shuffle()
{
    std::random_shuffle(deck.begin(), deck.end());
}

void Deck::display() const
{
    for (auto card : deck)
    {
        std::cout << card.suit_key << card.card_key << std::endl;
    }
}
