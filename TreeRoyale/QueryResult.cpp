#include "QueryResult.h"

QueryResult::QueryResult(std::vector<ClashRoyaleDeck> decklist, int timeelapsed) {
	deckList = decklist;
	timeElapsed = timeelapsed;
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
}

QueryResult::QueryResult() {
	timeElapsed = 123;
}

void QueryResult::print() {
	std::cout << "--- QueryResult ---\n";
	for (ClashRoyaleDeck deck : deckList) {
		deck.printDeckAndSortValue();
	}
	std::cout << "--- Time: " << timeElapsed << " ---\n";
}