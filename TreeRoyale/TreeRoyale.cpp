#include "TreeRoyale.h"

using namespace std;

int currentPage = 0;
int maxPage = 0;

int main() {
    ClashRoyaleData data;
    // Goblin Giant = 60
    // Hunter = 44  <-- Discrepency between RedBlack and MinHeap results??
    QueryResult qr = data.queryRedBlackTree(9, 98, "popularity");
    qr.print();

    QueryResult qr2 = data.queryMinHeap(9, 98, "popularity");
    qr2.print();

    vector<vector<int>> sortedDecks = outputSortedDecks(qr2);
    generateWindow(sortedDecks);
}

vector<vector<int>> outputSortedDecks(const QueryResult& queryResult) {
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
                yPos += sprite.getGlobalBounds().height + 30;
                xPos = (window.getSize().x - rowWidth) / 2.0f;
            }
        }
    }
}

void generateWindow(const vector<vector<int>>& sortedDecks) {
    sf::RenderWindow window(sf::VideoMode(1376, 768), "Tree Royale");
    window.setFramerateLimit(60);

    maxPage = (sortedDecks.size() - 1) / 3;

    sf::Texture backButtonTexture;
    sf::Texture forwardButtonTexture;
    sf::Sprite backButton = createButton(backButtonTexture, "assets/back.png", sf::Vector2f(66, window.getSize().y - 70));
    sf::Sprite forwardButton = createButton(forwardButtonTexture, "assets/next.png", sf::Vector2f(window.getSize().x - 183, window.getSize().y - 70));

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
    userInputText.setString("Display the decks of the ");

    sf::Text top3Text;
    top3Text.setFont(font);
    top3Text.setCharacterSize(18);
    top3Text.setFillColor(sf::Color(200, 200, 200));
    top3Text.setString("top 3");

    sf::Text middleText;
    middleText.setFont(font);
    middleText.setCharacterSize(18);
    middleText.setFillColor(sf::Color::Black);
    middleText.setString(" players who use ");

    sf::Text goblinGiantText;
    goblinGiantText.setFont(font);
    goblinGiantText.setCharacterSize(18);
    goblinGiantText.setFillColor(sf::Color(200, 200, 200));
    goblinGiantText.setString("Goblin Giant");

    sf::Text lastText;
    lastText.setFont(font);
    lastText.setCharacterSize(18);
    lastText.setFillColor(sf::Color::Black);
    lastText.setString(" in their deck sorted by ");

    sf::Text globalRankText;
    globalRankText.setFont(font);
    globalRankText.setCharacterSize(18);
    globalRankText.setFillColor(sf::Color(200, 200, 200));
    globalRankText.setString("global rank");

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

    sf::Text elapsedTimeText;
    elapsedTimeText.setFont(font);
    elapsedTimeText.setCharacterSize(14);
    elapsedTimeText.setFillColor(sf::Color::Black);
    elapsedTimeText.setString("Time Elapsed: Using Red-Black Tree: 123ms / Using Max Heap: 456ms");
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

