#include "ClashRoyaleDeck.h"

ClashRoyaleDeck::ClashRoyaleDeck(std::string deck) {
	wins = 0;
	gamesPlayed = 0;
	winRate = 0;
	
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
	winRate = 0;
	cards.insert(-1);
}

double ClashRoyaleDeck::computeWinRate() {
	winRate = (wins * 1.0) / (gamesPlayed * 1.0) * 100;
	return winRate;
}