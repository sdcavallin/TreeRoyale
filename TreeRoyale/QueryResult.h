#pragma once
#include <vector>
#include "ClashRoyaleDeck.h"

class QueryResult {
public:
	std::vector<ClashRoyaleDeck> deckList;
	int timeElapsed;
	QueryResult(std::vector<ClashRoyaleDeck> decklist, int timeelapsed);
	QueryResult(bool sampleQuery);
	QueryResult();
	void print();
};