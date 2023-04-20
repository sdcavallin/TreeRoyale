#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


void displayDecks(sf::RenderWindow& window, const std::vector<std::vector<sf::Sprite>>& deckSprites);
void generateWindow();
