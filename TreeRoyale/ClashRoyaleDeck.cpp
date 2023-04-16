#pragma once
#include <string>
#include <unordered_set>

using namespace std;


class ClashRoyaleDeck {
public:
	unordered_set<int> cards;
	//bool equals(ClashRoyaleDeck deck);
	// not sure why equals function makes error, probably includes and pragma once
};

/*bool ClashRoyaleDeck::equals(ClashRoyaleDeck deck) {
	// ...
	return false;
}*/