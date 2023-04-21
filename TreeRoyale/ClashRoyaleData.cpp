#include "ClashRoyaleData.h"
#include "QueryResult.h" // ???

// Load API data into container
ClashRoyaleData::ClashRoyaleData() {
    std::cout << "[Data] Loading 100,000 data points...\n";
    std::ifstream f("100k_battles.csv");
    std::string line;
    getline(f, line); // skip first line
    while (getline(f, line)) {
        std::stringstream str(line);
        std::string deckStr1 = "";
        std::string deckStr2 = "";
        std::string card = "";
        std::getline(str, card, ','); // skip index
        int i = 0;
        while (i < 8 && std::getline(str, card, ',')) {
            deckStr1 += card + ",";
            i++;
        }
        
        if (deckMap.find(deckStr1) == deckMap.end()) {
            deckMap[deckStr1] = ClashRoyaleDeck(deckStr1);
        }
        deckMap[deckStr1].gamesPlayed++;

        i = 0;
        while (i < 8 && std::getline(str, card, ',')) {
            deckStr2 += card + ",";
            i++;
        }
        if (deckMap.find(deckStr2) == deckMap.end()) {
            deckMap[deckStr2] = ClashRoyaleDeck(deckStr2);
        }
        deckMap[deckStr2].gamesPlayed++;

        std::getline(str, card, ','); // skip trophies
        std::getline(str, card, ',');
        std::getline(str, card, ','); // get outcome

        if (card == "1") {
            deckMap[deckStr1].wins++;
        }
        else {
            deckMap[deckStr2].wins++;
        }
        
    }
    std::cout << "[Data] Loading Done!\n";
    std::cout << "[Data] Computing Winrates...\n";

    for (auto it = deckMap.begin(); it != deckMap.end(); it++) {
        it->second.computeWinRate();
    }

    std::cout << "[Data] Done!\n";
    std::cout << "[Data] Winrate for deck [5,6,12,13,29,37,88,94,]: " << deckMap["5,6,12,13,29,37,88,94,"].computeWinRate() << "%\n";
}

// Example: Display the decks of the [topN] players who use [card] in their deck sorted by [sortBy]
QueryResult ClashRoyaleData::queryRedBlackTree(int topN, int card, std::string sortBy) {
    // Goblin Giant = 60
    std::set<ClashRoyaleDeck> set;
    // first put everything into set then try reducing count

    if (sortBy == "popularity") {
        ClashRoyaleDeck::sortByPopularity = true;
    }
    else {
        ClashRoyaleDeck::sortByPopularity = false;
    }

    for (auto it = deckMap.begin(); it != deckMap.end(); it++) {
        ClashRoyaleDeck deck = it->second;
        if (deck.cards.find(card) != deck.cards.end()) set.insert(deck);
    }

    QueryResult qr;
    int i = 0;
    for (auto deck : set) {
        if (i >= topN) break;
        qr.deckList.push_back(deck);
        i++;
    }
;
    return qr;
}

// Example: Display the decks of the [topN] players who use [card] in their deck sorted by [sortBy]
QueryResult ClashRoyaleData::queryMinHeap(int topN, int card, std::string sortBy) {
    QueryResult QR(true);
    return QR;
}

/* // old json parse
* using json = nlohmann::json;
        std::ifstream f("top10k.txt");
        if (f.fail()) cout << "fail";
        json data = json::parse(f);
        for (auto it : data) {
            for (auto k : it) {
                std::cout << "value: " << k["name"] << '\n';
            }
        }
 */