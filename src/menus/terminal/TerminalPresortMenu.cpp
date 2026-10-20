#include <iostream>
#include <string>
#include <exception>

#include "../../include/menus/terminal/TerminalPresortMenu.hpp"

namespace {
    Pattern selectPattern() {
        std::cout << "\nSelect Array Data Pattern:\n";
        std::cout << "  1. Uniform Random\n";
        std::cout << "  2. Reverse Sorted\n";
        std::cout << "  3. Nearly Sorted\n";
        std::cout << "Choice [1-3] (Default is Uniform Random): ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice.empty() || choice == "1") {
            return Pattern::UniformRandom;
        } else if (choice == "2") {
            return Pattern::ReverseSorted;
        } else if (choice == "3") {
            return Pattern::NearlySorted;
        } else {
            std::cout << "Invalid choice. Using default (Uniform Random).\n";
            return Pattern::UniformRandom;
        }
    }
}

PresortConfig selectPresortConfig() {
    PresortConfig config;
    config.pattern = selectPattern();

    std::string input;

    std::cout << "Enter Array Size (Default is 32): ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        try {
            std::size_t parsed = 0;
            auto value = std::stoull(input, &parsed);

            if (parsed != input.size() || value == 0) {
                throw std::invalid_argument("Invalid array size");
            }

            config.arraySize = static_cast<std::size_t>(value);
        } catch (const std::exception&) {
            std::cout << "Invalid array size. Using default (32).\n";
        }
    }

    std::cout << "Enter Frame Delay (ms) (Default is 100 ms): ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        try {
            std::size_t parsed = 0;
            int value = std::stoi(input, &parsed);

            if (parsed != input.size() || value < 0) {
                throw std::invalid_argument("Invalid frame delay");
            }

            config.delayMs = value;
        } catch (const std::exception&) {
            std::cout << "Invalid frame delay. Using default (100 ms).\n";
        }
    }

    return config;
}