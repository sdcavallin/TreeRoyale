#pragma once
#include <string>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class ClashRoyaleDeck {
public:
	std::unordered_set<int> cards;
	std::vector<int> sortedCards;
	std::string deckStr;
	static bool sortByPopularity; // false = winRate, true = gamesPlayed
	static std::unordered_map<int, std::string> getCardName;
	static std::unordered_map<std::string, int> getCardId;
	static void loadMaps();
	int wins, gamesPlayed;
	double winRate;
	ClashRoyaleDeck(std::string deck);
	ClashRoyaleDeck();
	double computeWinRate();
	void printDeckAndSortValue(bool withCardNames);
	bool operator<(const ClashRoyaleDeck& deck) const;
};
