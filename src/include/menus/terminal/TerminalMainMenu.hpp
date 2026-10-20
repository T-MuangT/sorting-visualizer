#pragma once

#include <string>

#include "../../AlgorithmRunner.hpp"

void displayMainMenu();
AlgorithmRunner selectMainMenuAlgorithm(bool& shouldExit);
AlgorithmRunner selectPlaceholderMenu(const std::string& familyName);