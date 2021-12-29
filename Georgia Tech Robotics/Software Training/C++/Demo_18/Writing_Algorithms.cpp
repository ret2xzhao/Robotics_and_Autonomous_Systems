#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

enum Suit { Clubs, Diamonds, Hearts, Spades };

struct Card {
    Suit suit;
    int value;
    bool operator<(const Card& rhs) const {
        return std::tie(value, suit) < std::tie(rhs.value, rhs.suit);
    }
};

std::ostream& operator<<(std::ostream& stream, const Card& c) {
    switch(c.value) {
        case 1: stream << 'A'; break;
        case 11: stream << 'J'; break;
        case 12: stream << 'Q'; break;
        case 13: stream << 'K'; break;
        default: stream << c.value; break;
    }
    switch(c.suit) {
        case Clubs: stream << "\U00002663"; break;
        case Diamonds: stream << "\U00002666"; break;
        case Hearts: stream << "\U00002665"; break;
        case Spades: stream << "\U00002660"; break;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::vector<Card>& v) {
    if(v.empty()) {
        return stream << "[]";
    }
    stream << '[';
    for(auto i = 0; i < v.size() - 1; ++i) {
        stream << v[i] << ", ";
    }
    stream << v.back() << ']';
    return stream;
}

template<typename InputIterator1, 
         typename InputIterator2, 
         typename OutputIterator, 
         typename Operation>
void outer_product(InputIterator1 first1, InputIterator1 last1, 
                  InputIterator2 first2, InputIterator2 last2, 
                  OutputIterator d_first, 
                  Operation op) {
    while(first1 != last1) {
        auto curr2 = first2;
        while(curr2 != last2) {
            *d_first = op(*first1, *curr2);
            ++d_first;
            ++curr2;
        }
        ++first1;
    }
}

std::vector<Card> GenerateDeck() {
    std::vector<Card> deck;
    std::array<int, 13> values;
    std::iota(values.begin(), values.end(), 1);
    std::array<Suit, 4> suits = {Clubs, Diamonds, Hearts, Spades};
    auto build_card = [](const Suit s, const int v) {
        return Card{s,v};
    };
    outer_product(suits.begin(), suits.end(), 
                  values.begin(), values.end(), 
                  std::back_inserter(deck), 
                  build_card);
    return deck;
}

void ShuffleDeck(std::vector<Card>& deck) {
    std::random_device dev;
    std::default_random_engine eng(dev());
    std::shuffle(deck.begin(), deck.end(), eng);
}

std::vector<Card> Draw(std::vector<Card>& deck, const std::size_t count) {
    std::vector<Card> hand;
    std::copy_n(deck.begin(), count, std::back_inserter(hand));
    deck.erase(deck.begin(), deck.begin() + count);
    return hand;
}

void CutDeck(std::vector<Card>& deck, const std::size_t position) {
    std::rotate(deck.begin(), deck.begin() + position, deck.end());
}

int main() {

    auto deck = GenerateDeck();

    ShuffleDeck(deck);

    std::cout << deck << "\n\n";

    CutDeck(deck, 6);

    std::cout << "After cut:\n" << deck << "\n\n";

    const auto hand = Draw(deck, 5);

    std::cout << hand << "\n\n";

    const auto max_card_iter = std::max_element(hand.begin(), hand.end());

    std::cout << "Highest card: " << *max_card_iter << "\n";

    std::vector<Card> heart_cards;
    std::copy_if(hand.begin(), hand.end(), std::back_inserter(heart_cards), [](const Card& c){
        return c.suit == Hearts;
    });
    std::cout << "Heart cards: " << heart_cards << "\n";

    return 0;
}