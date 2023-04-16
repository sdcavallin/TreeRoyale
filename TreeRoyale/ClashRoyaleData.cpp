#pragma once
#include <string>
#include "QueryResult.cpp"

using namespace std;

class ClashRoyaleData {
	
public:
	// sortBy possible values = {"globalRank", "numberWins"}
	QueryResult queryRedBlackTree(int topN, string card, string sortBy);
	QueryResult queryMinHeap(int topN, string card, string sortBy);
	ClashRoyaleData();
};

// Load API data into container
ClashRoyaleData::ClashRoyaleData() {
	
}

// Example: Display the decks of the [topN] players who use [card] in their deck sorted by [sortBy]
QueryResult ClashRoyaleData::queryRedBlackTree(int topN, string card, string sortBy) {
	return QueryResult();
}

// Example: Display the decks of the [topN] players who use [card] in their deck sorted by [sortBy]
QueryResult ClashRoyaleData::queryMinHeap(int topN, string card, string sortBy) {
	return QueryResult();
}