#pragma once
#include <string>
#include <unordered_set>
#include <vector>


class ClashRoyaleDeck {
public:
	std::vector<int> cards;
	int wins, gamesPlayed;
	double winRate;
	ClashRoyaleDeck(std::string deck);
	double computeWinRate();
};
