#pragma once
#include <vector>

using namespace std;

class QueryResult {
public:
	vector<vector<int>> deckList;
	int timeElapsed;
	QueryResult(vector<vector<int>> decklist, int timeelapsed);
};

QueryResult::QueryResult(vector<vector<int>> decklist, int timeelapsed) {
	deckList = decklist;
	timeElapsed = timeelapsed;
}