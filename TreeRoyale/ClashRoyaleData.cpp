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
    f.close();
    std::cout << "[Data] Loading Done!\n";

    ClashRoyaleDeck::loadMaps();

    std::cout << "[Data] Computing Winrates...\n";

    for (auto it = deckMap.begin(); it != deckMap.end(); it++) {
        it->second.computeWinRate();
    }

    std::cout << "[Data] Done!\n";
}

// Example: Display the [topN] decks containing [card] sorted by [sortBy]
QueryResult ClashRoyaleData::queryRedBlackTree(int topN, int card, std::string sortBy) {
    auto startTime = std::chrono::high_resolution_clock::now();
    std::set<ClashRoyaleDeck> set;

    if (sortBy == "popularity") {
        ClashRoyaleDeck::sortByPopularity = true;
    }
    else {
        ClashRoyaleDeck::sortByPopularity = false;
    }

    for (auto it = deckMap.begin(); it != deckMap.end(); it++) {
        ClashRoyaleDeck deck = it->second;
        if (deck.cards.find(card) != deck.cards.end()) {
            set.insert(deck);
        }
    }

    QueryResult qr;
    int i = 0;
    for (ClashRoyaleDeck deck : set) {
        if (i >= topN) break;
        qr.deckList.push_back(deck);
        i++;
    }
    //std::cout << (set.find(deckMap["28,38,44,46,50,59,102,103,"]))->gamesPlayed;
    qr.queryType = "RedBlack";

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    qr.timeElapsed = (int) duration.count();

    return qr;
}

// Example: Display the [topN] decks containing [card] sorted by [sortBy]
QueryResult ClashRoyaleData::queryMinHeap(int topN, int card, std::string sortBy) {
    auto startTime = std::chrono::high_resolution_clock::now();
    std::priority_queue<ClashRoyaleDeck> pq;

    if (sortBy == "popularity") {
        ClashRoyaleDeck::sortByPopularity = true;
    }
    else {
        ClashRoyaleDeck::sortByPopularity = false;
    }

    for (auto it = deckMap.begin(); it != deckMap.end(); it++) {
        ClashRoyaleDeck deck = it->second;
        if (deck.cards.find(card) != deck.cards.end()) {
            if (pq.size() < topN) {
                pq.push(deck);
            }
            else {
                if (deck < pq.top()) {
                    pq.pop();
                    pq.push(deck);
                }
            }
        }
    }

    QueryResult qr;
    while (!pq.empty()) {
        qr.deckList.push_back(pq.top());
        pq.pop();
    }
    qr.queryType = "MinHeap";

    std::reverse(qr.deckList.begin(), qr.deckList.end());

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    qr.timeElapsed = (int) duration.count();

    return qr;
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