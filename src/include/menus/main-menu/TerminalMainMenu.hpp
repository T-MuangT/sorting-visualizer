#ifndef TERMINAL_MAIN_MENU_HPP
#define TERMINAL_MAIN_MENU_HPP

#include <string>

#include "../../AlgorithmRunner.hpp"

void displayMainMenu();

AlgorithmRunner selectMainMenuAlgorithm();

AlgorithmRunner selectPlaceholderMenu(const std::string& familyName);

#endif // TERMINAL_MAIN_MENU_HPP