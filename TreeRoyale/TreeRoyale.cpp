#include "TreeRoyale.h"

using namespace std;

int currentPage = 0;
int maxPage = 0;

int main() {
    ClashRoyaleData data;

    QueryResult qr = data.queryRedBlackTree(15, 0, "popularity");
    qr.print();

    QueryResult qr2 = data.queryMinHeap(15, 0, "popularity");
    qr2.print();

    QueryResult qr3 = data.queryMinHeap(15, 0, "winrate");
    qr3.print();

    QueryResult qr4 = data.queryMinHeap(15, 0, "winrate");
    qr4.print();

    string sort = "popularity";
    vector<vector<int>> sortedDecks = outputSortedDecks(qr2);
    generateWindow(sortedDecks, qr, qr2, qr3, qr4, sort, data);
}

void updateTopMessageWidth(sf::Text& userInputText, sf::Text& top3Text, sf::Text& middleText, sf::Text& goblinGiantText, sf::Text& lastText, sf::Text& globalRankText, sf::RenderWindow& window) {
    float totalWidth = userInputText.getLocalBounds().width +
        top3Text.getLocalBounds().width +
        middleText.getLocalBounds().width +
        goblinGiantText.getLocalBounds().width +
        lastText.getLocalBounds().width +
        globalRankText.getLocalBounds().width;
    float xPos = (window.getSize().x - totalWidth) / 2.0f;
    float yPos = 50;
    userInputText.setPosition(xPos, yPos);
    xPos += userInputText.getLocalBounds().width;
    top3Text.setPosition(xPos, yPos);
    xPos += top3Text.getLocalBounds().width;
    middleText.setPosition(xPos, yPos);
    xPos += middleText.getLocalBounds().width;
    goblinGiantText.setPosition(xPos, yPos);
    xPos += goblinGiantText.getLocalBounds().width;
    lastText.setPosition(xPos, yPos);
    xPos += lastText.getLocalBounds().width;
    globalRankText.setPosition(xPos, yPos);
}

string getCardName(int cardId) {
    static const std::vector<std::string> cardNames = {
        "Knight", "Archers", "Goblins", "Giant", "P.E.K.K.A",
        "Minions", "Balloon", "Witch", "Barbarians", "Golem",
        "Skeletons", "Valkyrie", "Skeleton Army", "Bomber", "Musketeer",
        "Baby Dragon", "Prince", "Wizard", "Mini P.E.K.K.A", "Spear Goblins",
        "Giant Skeleton", "Hog Rider", "Minion Horde", "Ice Wizard", "Royal Giant",
        "Guards", "Princess", "Dark Prince", "Three Musketeers", "Lava Hound",
        "Ice Spirit", "Fire Spirit", "Miner", "Sparky", "Bowler",
        "Lumberjack", "Battle Ram", "Inferno Dragon", "Ice Golem", "Mega Minion",
        "Dart Goblin", "Goblin Gang", "Electro Wizard", "Elite Barbarians", "Hunter",
        "Executioner", "Bandit", "Royal Recruits", "Night Witch", "Bats",
        "Royal Ghost", "Ram Rider", "Zappies", "Rascals", "Cannon Cart",
        "Mega Knight", "Skeleton Barrel", "Flying Machine", "Wall Breakers", "Royal Hogs",
        "Goblin Giant", "Fisherman", "Magic Archer", "Electro Dragon", "Firecracker",
        "Elixir Golem", "Battle Healer", "Skeleton King", "Archer Queen", "Golden Knight",
        "Skeleton Dragons", "Mother Witch", "Electro Spirit", "Electro Giant", "Cannon",
        "Goblin Hut", "Mortar", "Inferno Tower", "Bomb Tower", "Barbarian Hut",
        "Tesla", "Elixir Collector", "X-Bow", "Tombstone", "Furnace",
        "Goblin Cage", "Goblin Drill", "Fireball", "Arrows", "Rage",
        "Rocket", "Goblin Barrel", "Freeze", "Mirror", "Lightning",
        "Zap", "Poison", "Graveyard", "The Log", "Tornado",
        "Clone", "Earthquake", "Barbarian Barrel", "Heal Spirit", "Giant Snowball",
        "Royal Delivery"
    };

    if (cardId >= 0 && cardId < cardNames.size()) {
        return cardNames[cardId];
    }
    return "Unknown";
}

int displayCardSelectionWindow() {
    sf::RenderWindow selectionWindow(sf::VideoMode(1216, 636), "Select a Card");
    selectionWindow.setFramerateLimit(60);
    vector<sf::Texture> cardTextures(106);
    vector<sf::Sprite> cardSprites(106);
    for (int i = 0; i < 106; ++i) {
        cardTextures[i].loadFromFile("assets/cards/" + to_string(i) + ".png");
        cardSprites[i].setTexture(cardTextures[i]);
    }
    int rows = 7;
    int columns = 16;
    float cardWidth = 75.0f;
    float cardHeight = 90.0f;
    float marginX = 1.0f;
    float marginY = 1.0f;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int index = i * columns + j;
            if (index < cardSprites.size()) {
                cardSprites[index].setScale(cardWidth / cardSprites[index].getLocalBounds().width, cardHeight / cardSprites[index].getLocalBounds().height);
                cardSprites[index].setPosition(j * (cardWidth + marginX), i * (cardHeight + marginY));
            }
        }
    }
    int selectedCardID = -1;
    while (selectionWindow.isOpen()) {
        sf::Event event;
        while (selectionWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                selectionWindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(selectionWindow);
                    for (int i = 0; i < cardSprites.size(); ++i) {
                        if (cardSprites[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            selectedCardID = i;
                            selectionWindow.close();
                            break;
                        }
                    }
                }
            }
        }
        selectionWindow.clear(sf::Color::White);
        sf::Texture backgroundTexture2;
        backgroundTexture2.loadFromFile("assets/background2.png");
        sf::Sprite backgroundSprite2;
        backgroundSprite2.setTexture(backgroundTexture2);
        selectionWindow.draw(backgroundSprite2);
        for (const auto& sprite : cardSprites) {
            selectionWindow.draw(sprite);
        }
        selectionWindow.display();
    }
    return selectedCardID;
}

void updateDeckSprites(vector<vector<int>>& sortedDecks, vector<vector<sf::Sprite>>& deckSprites, vector<sf::Texture>& textures) {
    for (int i = 0; i < sortedDecks.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            int index = i * 8 + j;
            textures[index].loadFromFile("assets/cards/" + to_string(sortedDecks[i][j]) + ".png");
            sf::Sprite sprite;
            sprite.setTexture(textures[index]);
            deckSprites[i][j] = sprite;
        }
    }
}

vector<vector<int>> outputSortedDecks(QueryResult& queryResult) {
    vector<vector<int>> sortedDecks;
    for (const auto& deck : queryResult.deckList) {
        vector<int> sortedDeck(deck.cards.begin(), deck.cards.end());
        sort(sortedDeck.begin(), sortedDeck.end());
        sortedDecks.push_back(sortedDeck);
    }
    int deckIndex = 1;
    for (const auto& sortedDeck : sortedDecks) {
        cout << "Deck " << deckIndex << ": ";
        for (const auto& cardID : sortedDeck) {
            cout << cardID << " ";
        }
        cout << endl;
        deckIndex++;
    }
    return sortedDecks;
}

sf::Sprite createButton(sf::Texture& texture, const std::string& imagePath, const sf::Vector2f& position) {
    texture.loadFromFile(imagePath);
    sf::Sprite button(texture);
    button.setScale(117.0f / button.getLocalBounds().width, 60.0f / button.getLocalBounds().height);
    button.setPosition(position);
    return button;
}

void displayDecks(sf::RenderWindow& window, const vector<vector<sf::Sprite>>& deckSprites, int page) {
    float yPos = 100.0f;
    int startIndex = page * 3;
    for (int i = startIndex; i < startIndex + 3 && i < deckSprites.size(); ++i) {
        const auto& row = deckSprites[i];
        float rowWidth = 0.0f;
        for (const auto& sprite : row) {
            rowWidth += sprite.getGlobalBounds().width + 10;
        }
        rowWidth -= 10;
        float xPos = (window.getSize().x - rowWidth) / 2.0f;
        int cardIndex = 0;
        for (const auto& sprite : row) {
            sf::Sprite tempSprite = sprite;
            tempSprite.setPosition(xPos, yPos);
            window.draw(tempSprite);
            xPos += sprite.getGlobalBounds().width + 10;
            if (++cardIndex % 8 == 0) {
                yPos += sprite.getGlobalBounds().height + 29;
                xPos = (window.getSize().x - rowWidth) / 2.0f;
            }
        }
    }
}

void generateWindow(vector<vector<int>>& sortedDecks, QueryResult& qr, QueryResult& qr2, QueryResult& qr3, QueryResult& qr4, string& sort, ClashRoyaleData data) {
    bool running = true;
    while (running) {
        sf::RenderWindow window(sf::VideoMode(1376, 768), "Tree Royale");
        window.setFramerateLimit(60);
        maxPage = (sortedDecks.size() - 1) / 3;
        sf::Texture backButtonTexture;
        sf::Texture forwardButtonTexture;
        sf::Sprite backButton = createButton(backButtonTexture, "assets/back.png", sf::Vector2f(68, window.getSize().y - 70));
        sf::Sprite forwardButton = createButton(forwardButtonTexture, "assets/next.png", sf::Vector2f(window.getSize().x - 185, window.getSize().y - 70));

        sf::Texture toggleSortButtonTexture;
        // sf::Sprite toggleSortButton = createButton(toggleSortButtonTexture, "assets/next.png", sf::Vector2f(window.getSize().x - 185, 50));

        sf::Font font;
        font.loadFromFile("assets/font.ttf");

        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("assets/background.png");
        sf::Sprite backgroundSprite;
        backgroundSprite.setTexture(backgroundTexture);

        sf::Text titleText;
        titleText.setFont(font);
        titleText.setString("Tree Royale");
        titleText.setCharacterSize(24);
        titleText.setFillColor(sf::Color::Black);
        float titleTextX = (window.getSize().x - titleText.getLocalBounds().width) / 2.0f;
        titleText.setPosition(titleTextX, 10);

        sf::Text userInputText;
        userInputText.setFont(font);
        userInputText.setCharacterSize(18);
        userInputText.setFillColor(sf::Color::Black);
        userInputText.setString("Display the ");

        sf::Text top3Text;
        top3Text.setFont(font);
        top3Text.setCharacterSize(18);
        top3Text.setFillColor(sf::Color::Black);
        top3Text.setString("top 15");

        sf::Text middleText;
        middleText.setFont(font);
        middleText.setCharacterSize(18);
        middleText.setFillColor(sf::Color::Black);
        middleText.setString(" decks that use ");

        sf::Text goblinGiantText;
        goblinGiantText.setFont(font);
        goblinGiantText.setCharacterSize(18);
        goblinGiantText.setFillColor(sf::Color(255, 208, 83));
        goblinGiantText.setString("Knight");

        sf::Text lastText;
        lastText.setFont(font);
        lastText.setCharacterSize(18);
        lastText.setFillColor(sf::Color::Black);
        lastText.setString(" sorted by ");

        sf::Text globalRankText;
        globalRankText.setFont(font);
        globalRankText.setCharacterSize(18);
        globalRankText.setFillColor(sf::Color(255, 208, 83));
        globalRankText.setString("popularity");

        updateTopMessageWidth(userInputText, top3Text, middleText, goblinGiantText, lastText, globalRankText, window);

        sf::Text elapsedTimeText;
        elapsedTimeText.setFont(font);
        elapsedTimeText.setCharacterSize(14);
        elapsedTimeText.setFillColor(sf::Color::Black);
        elapsedTimeText.setString("Time Elapsed: Using Red-Black Tree: " + std::to_string(qr.timeElapsed) + "ms / Using Min Heap: " + std::to_string(qr2.timeElapsed) + "ms");
        float elapsedTimeTextX = (window.getSize().x - elapsedTimeText.getLocalBounds().width) / 2.0f;
        elapsedTimeText.setPosition(elapsedTimeTextX, window.getSize().y - elapsedTimeText.getLocalBounds().height - 10);

        vector<vector<sf::Sprite>> deckSprites(sortedDecks.size());
        vector<sf::Texture> textures(sortedDecks.size() * 8);

        for (int i = 0; i < sortedDecks.size(); ++i) {
            for (int j = 0; j < 8; ++j) {
                int index = i * 8 + j;
                textures[index].loadFromFile("assets/cards/" + to_string(sortedDecks[i][j]) + ".png");
                sf::Sprite sprite;
                sprite.setTexture(textures[index]);
                deckSprites[i].push_back(sprite);
            }
        }

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && currentPage > 0) {
                            currentPage--;
                        }
                        else if (forwardButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && currentPage < maxPage) {
                            currentPage++;
                        }
                        else if (globalRankText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            if (sort == "popularity") {
                                sort = "winrate";
                                globalRankText.setString("win rate");
                                sortedDecks = outputSortedDecks(qr4);
                            }
                            else {
                                sort = "popularity";
                                globalRankText.setString("popularity");
                                sortedDecks = outputSortedDecks(qr2);
                            }
                            maxPage = (sortedDecks.size() - 1) / 3;
                            currentPage = 0;
                            elapsedTimeText.setString("Time Elapsed: Using Red-Black Tree: " + std::to_string(qr.timeElapsed) + "ms / Using Min Heap: " + std::to_string(qr2.timeElapsed) + "ms");
                            updateDeckSprites(sortedDecks, deckSprites, textures);
                        }
                        else if (goblinGiantText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            int selectedCardID = displayCardSelectionWindow();
                            if (selectedCardID != -1) {
                                goblinGiantText.setString(getCardName(selectedCardID));
                                updateTopMessageWidth(userInputText, top3Text, middleText, goblinGiantText, lastText, globalRankText, window);
                                qr = data.queryRedBlackTree(15, selectedCardID, "popularity");
                                qr.print();
                                qr2 = data.queryMinHeap(15, selectedCardID, "popularity");
                                qr2.print();
                                qr3 = data.queryRedBlackTree(15, selectedCardID, "winrate");
                                qr3.print();
                                qr4 = data.queryMinHeap(15, selectedCardID, "winrate");
                                qr4.print();
                            }
                            if (sort == "popularity") {
                                sortedDecks = outputSortedDecks(qr2);
                            }
                            else {
                                sortedDecks = outputSortedDecks(qr4);
                            }
                            maxPage = (sortedDecks.size() - 1) / 3;
                            currentPage = 0;
                            elapsedTimeText.setString("Time Elapsed: Using Red-Black Tree: " + std::to_string(qr.timeElapsed) + "ms / Using Min Heap: " + std::to_string(qr2.timeElapsed) + "ms");
                            updateDeckSprites(sortedDecks, deckSprites, textures);
                        }

                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(backgroundSprite);
            window.draw(titleText);
            window.draw(userInputText);
            window.draw(top3Text);
            window.draw(middleText);
            window.draw(goblinGiantText);
            window.draw(lastText);
            window.draw(globalRankText);
            // window.draw(toggleSortButton);

            displayDecks(window, deckSprites, currentPage);

            if (currentPage > 0) {
                window.draw(backButton);
            }
            if (currentPage < maxPage) {
                window.draw(forwardButton);
            }

            window.draw(elapsedTimeText);
            window.display();
        }
    }
}

