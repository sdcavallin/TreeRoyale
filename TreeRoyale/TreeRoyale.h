#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "ClashRoyaleData.h"

void updateTopMessageWidth(sf::Text& userInputText, sf::Text& top3Text, sf::Text& middleText, sf::Text& goblinGiantText, sf::Text& lastText, sf::Text& globalRankText, sf::RenderWindow& window);
std::string getCardName(int cardId);
int displayCardSelectionWindow();
void updateDeckSprites(std::vector<std::vector<int>>& sortedDecks, std::vector<std::vector<sf::Sprite>>& deckSprites, std::vector<sf::Texture>& textures);
std::vector<std::vector<int>> outputSortedDecks(QueryResult& queryResult);
void displayDecks(sf::RenderWindow& window, const std::vector<std::vector<sf::Sprite>>& deckSprites, int page);
void generateWindow(std::vector<std::vector<int>>& sortedDecks, QueryResult& qr, QueryResult& qr2, QueryResult& qr3, QueryResult& qr4, std::string& sort, ClashRoyaleData data);

