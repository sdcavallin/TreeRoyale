#include "ClashRoyaleData.h"
#include "QueryResult.h" // ???

// Load API data into container
ClashRoyaleData::ClashRoyaleData() {
    /*ifstream f("100k_battles.csv");
    string line;
    getline(f, line);
    cout << f;*/
}

// Example: Display the decks of the [topN] players who use [card] in their deck sorted by [sortBy]
QueryResult ClashRoyaleData::queryRedBlackTree(int topN, std::string card, std::string sortBy) {
    QueryResult QR;
    return QR;
}

// Example: Display the decks of the [topN] players who use [card] in their deck sorted by [sortBy]
QueryResult ClashRoyaleData::queryMinHeap(int topN, std::string card, std::string sortBy) {
    QueryResult QR;
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