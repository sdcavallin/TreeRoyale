#pragma once
#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>

class ClashRoyaleDeck {
public:
	std::unordered_set<int> cards;
	std::vector<int> sortedCards;
	std::string deckStr;
	static bool sortByPopularity; // false = winRate, true = gamesPlayed
	int wins, gamesPlayed;
	double winRate;
	ClashRoyaleDeck(std::string deck);
	ClashRoyaleDeck();
	double computeWinRate();
	void printDeckAndSortValue(bool withCardNames);
	bool operator<(const ClashRoyaleDeck& deck) const;
};
