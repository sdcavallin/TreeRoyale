#pragma once
#include <vector>
#include "ClashRoyaleDeck.h"

class QueryResult {
public:
	std::vector<ClashRoyaleDeck> deckList;
	int timeElapsed;
	std::string queryType;
	QueryResult(std::vector<ClashRoyaleDeck> decklist, int timeelapsed, std::string querytype);
	QueryResult(bool sampleQuery);
	QueryResult();
	void print();
};