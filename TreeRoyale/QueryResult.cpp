#include "QueryResult.h"

QueryResult::QueryResult(std::vector<ClashRoyaleDeck> decklist, int timeelapsed, std::string querytype) {
	deckList = decklist;
	timeElapsed = timeelapsed;
	queryType = querytype;
}

// sample result
QueryResult::QueryResult(bool sampleQuery) {
	std::vector<ClashRoyaleDeck> sampleDeckList;

	ClashRoyaleDeck sampleDeck1("8,34,37,52,69,88,92,97,");
	ClashRoyaleDeck sampleDeck2("6,10,30,31,35,72,92,104,");
	ClashRoyaleDeck sampleDeck3("15,43,63,65,66,89,99,103,");
	sampleDeckList.push_back(sampleDeck1);
	sampleDeckList.push_back(sampleDeck2);
	sampleDeckList.push_back(sampleDeck3);

	timeElapsed = 123;
	deckList = sampleDeckList;
	queryType = "Sample";
}

QueryResult::QueryResult() {
	timeElapsed = 123;
	queryType = "Sample";
}

void QueryResult::print() {
	std::cout << "--- Query " << queryType << " --- \n";
	for (ClashRoyaleDeck deck : deckList) {
		deck.printDeckAndSortValue(false);
	}
	std::cout << "---- Time: " << timeElapsed << "ms ----\n";
}