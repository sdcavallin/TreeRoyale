#pragma once
#include <vector>
#include "ClashRoyaleDeck.cpp"

using namespace std;

class QueryResult {
public:
	vector<ClashRoyaleDeck> deckList;
	int timeElapsed;
	QueryResult(vector<ClashRoyaleDeck> decklist, int timeelapsed);
	QueryResult(); //unneccessary
};

QueryResult::QueryResult(vector<ClashRoyaleDeck> decklist, int timeelapsed) {
	deckList = decklist;
	timeElapsed = timeelapsed;
}
QueryResult::QueryResult() {

}