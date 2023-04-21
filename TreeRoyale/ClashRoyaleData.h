#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <queue>
#include <chrono>
#include "QueryResult.h"
#include "ClashRoyaleDeck.h"

class ClashRoyaleData {
public:
    std::unordered_map<std::string, ClashRoyaleDeck> deckMap;
    QueryResult queryRedBlackTree(int topN, int card, std::string sortBy);
    QueryResult queryMinHeap(int topN, int card, std::string sortBy);
    ClashRoyaleData();
};
