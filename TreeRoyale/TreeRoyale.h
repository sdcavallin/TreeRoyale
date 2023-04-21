#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "ClashRoyaleData.h"

std::vector<std::vector<int>> outputSortedDecks(const QueryResult& queryResult);
void displayDecks(sf::RenderWindow& window, const std::vector<std::vector<sf::Sprite>>& deckSprites);
void generateWindow(const std::vector<std::vector<int>>& sortedDecks);
