#pragma once
#include <string>
#include <unordered_set>

using namespace std;

// TODO: Make new API calls for 10 consecutive seasons
// API data might look differently now
// Name the text files by season, like 2022-06-players for the json list of players for that season
// For every player in the 100k, I need to query the API and get their profile information
// I need to store 100k profile informations somehow. Likely a text file with my own format

// Class Deprecated

class ClashRoyalePlayer {
public:
	string name, playerTag;
	int trophies, rank, numWins;
	unordered_set<string> deck;
};