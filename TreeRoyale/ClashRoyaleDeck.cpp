#include "ClashRoyaleDeck.h"

ClashRoyaleDeck::ClashRoyaleDeck(std::string deck) {
	wins = 0;
	gamesPlayed = 0;
	winRate = -1;
	deckStr = deck;
	sortByPopularity = false;
	
	int deckIndex = 0;
	std::string s = "";
	for (int i = 0; i < deck.length(); i++) {
		if (deck[i] == ',') {
			cards.insert(std::stoi(s));
			s = "";
		}
		else {
			s += deck[i];
		}
	}
}

ClashRoyaleDeck::ClashRoyaleDeck() {
	wins = 0;
	gamesPlayed = 0;
	winRate = -1;
	cards.insert(-1);
}

double ClashRoyaleDeck::computeWinRate() {
	winRate = (wins * 1.0) / (gamesPlayed * 1.0) * 100;
	return winRate;
}

void ClashRoyaleDeck::printDeckAndSortValue() {
	std::cout << "[" << deckStr << "]: " << gamesPlayed << " | " << winRate << "%\n";
}

void ClashRoyaleDeck::setSortBy(bool sortByPop) {
	sortByPopularity = sortByPop;
}

bool ClashRoyaleDeck::sortByPopularity = false;

bool ClashRoyaleDeck::operator<(const ClashRoyaleDeck& deck) const {
	if (sortByPopularity) return (gamesPlayed > deck.gamesPlayed);
	else return (winRate > deck.winRate); // reverse order
}
