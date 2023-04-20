#include "ClashRoyaleDeck.h"

ClashRoyaleDeck::ClashRoyaleDeck(std::string deck) {
	wins = 0;
	gamesPlayed = 0;
	winRate = 0;
	
	int deckIndex = 0;
	std::string s = "";
	for (int i = 0; i < deck.length(); i++) {
		if (deck[i] == ',') {
			cards.push_back(std::stoi(s));
			s = "";
		}
		else {
			s += deck[i];
		}
	}
}

double ClashRoyaleDeck::computeWinRate() {
	winRate = (wins * 1.0) / gamesPlayed * 100;
	return winRate;
}