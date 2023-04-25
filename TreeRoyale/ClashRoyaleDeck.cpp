#include "ClashRoyaleDeck.h"

std::unordered_map<int, std::string> ClashRoyaleDeck::getCardName;
std::unordered_map<std::string, int> ClashRoyaleDeck::getCardId;

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
			sortedCards.push_back(std::stoi(s));
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
	// serves as a requirement for minimum number of games played in order to be included in sort by win rate results
	if (gamesPlayed <= 3) winRate = 0;
	else if (gamesPlayed <= 12) winRate = winRate * (log2(gamesPlayed) / 6);
	else if (gamesPlayed <= 16) winRate = winRate * (log2(gamesPlayed) / 4);
	// weighting winrate as slightly higher if deck is more popular
	winRate = winRate + 1.5*(log2(gamesPlayed) - 4);
	
	return winRate;
}

void ClashRoyaleDeck::loadMaps() {
	std::ifstream f("cardlist.csv");
	std::string line;
	getline(f, line); // skip first line
	while (getline(f, line)) {
		std::string s;
		std::stringstream str(line);
		getline(str, s, ','); // skip index
		getline(str, s, ','); // get id
		int id = stoi(s);
		getline(str, s, ','); // get card name
		getCardName[id] = s;
		getCardId[s] = id;
	}
	f.close();
}

void ClashRoyaleDeck::printDeckAndSortValue(bool withCardNames) {
	if (withCardNames) {
		std::cout << "[";
		for (int card : sortedCards) {
			std::cout << getCardName[card] << ",";
		}
		std::cout << "]: " << gamesPlayed << " | " << winRate << "%\n";
	}
	else {
		std::cout << "[" << deckStr << "]: " << gamesPlayed << " | " << winRate << "%\n";
	}
}

bool ClashRoyaleDeck::sortByPopularity = false;

bool ClashRoyaleDeck::operator<(const ClashRoyaleDeck& deck) const {
	if (sortByPopularity) {
		return (gamesPlayed > deck.gamesPlayed);
	}
	else {
		return (winRate > deck.winRate);
	}
}
