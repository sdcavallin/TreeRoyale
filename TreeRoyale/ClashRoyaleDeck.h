#pragma once
#include <string>
#include <unordered_set>
#include <vector>


class ClashRoyaleDeck {
public:
	std::unordered_set<int> cards;
	int wins, gamesPlayed;
	double winRate;
	ClashRoyaleDeck(std::string deck);
	ClashRoyaleDeck();
	double computeWinRate();
};
