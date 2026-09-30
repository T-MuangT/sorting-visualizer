#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include "../include/visualizer/TerminalTableVisualizer.hpp"

TerminalTableVisualizer::TerminalTableVisualizer(int delayMs) : delayMs(delayMs) {}

void TerminalTableVisualizer::clearScreen() const {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

bool TerminalTableVisualizer::isHighlighted(
    const std::vector<TableCell>& highlighted,
    int row,
    int pos)
{
    return std::any_of(
        highlighted.begin(),
        highlighted.end(),
        [row, pos](const TableCell& cell) {
            return cell.row == row && cell.pos == pos;
        });
}

const char* TerminalTableVisualizer::eventName(AuxEvent event) {
    switch (event) {
        case AuxEvent::PlaceInBucket:
            return "Place in Table";
        case AuxEvent::FlushBucket:
            return "Flush Table";
        case AuxEvent::CompareInAux:
            return "Compare in Auxiliary Table";
        case AuxEvent::IncrementCount:
            return "Increment Value Tabulation in Table";
        case AuxEvent::AccumulateCount:
            return "Accumulate Value Tabulation";
        case AuxEvent::PlaceCountOutput:
            return "Place Value and Decrement from Value Tabulation";
    }

    return "Auxiliary Event";
}

char TerminalTableVisualizer::markerFor(AuxEvent event) {
    switch (event) {
        case AuxEvent::PlaceInBucket:
            return '+';
        case AuxEvent::FlushBucket:
            return '!';
        case AuxEvent::CompareInAux:
            return '*';
        case AuxEvent::IncrementCount:
            return '+';
        case AuxEvent::AccumulateCount:
            return '*';
        case AuxEvent::PlaceCountOutput:
            return '!';
    }

    return '?';
}

bool TerminalTableVisualizer::isCountEvent(AuxEvent event) {
    switch (event) {
        case AuxEvent::IncrementCount:
        case AuxEvent::AccumulateCount:
        case AuxEvent::PlaceCountOutput:
            return true;

        default:
            return false;
    }
}

void TerminalTableVisualizer::renderFrame(
    const std::vector<TableRow>& rows,
    AuxEvent event,
    const std::vector<TableCell>& highlighted,
    const std::string& stepName,
    const SortStats& stats)
{
    clearScreen();

    size_t labelWidth = 5;
    int valueWidth = 1;
    for (const auto& row : rows) {
        labelWidth = std::max(labelWidth, row.label.size());
        for (int value : row.values) {
            valueWidth = std::max(valueWidth, static_cast<int>(std::to_string(value).size()));
        }
    }

    std::cout << "==== Terminal Visualizer ====\n";
    std::cout << "Step: " << stepName << "\n";
    std::cout << "Event: " << eventName(event) << "\n";
    std::cout << "Comparisons: " << stats.getComparisons()
              << " | Swaps: " << stats.getSwaps() << "\n\n";

    if (rows.empty()) {
        std::cout << "(no auxiliary rows)\n";
    }

    for (size_t rowIdx = 0; rowIdx < rows.size(); ++rowIdx) {
        const auto& row = rows[rowIdx];
        std::cout << std::left << std::setw(static_cast<int>(labelWidth)) << row.label
                  << " | ";

        if (row.values.empty()) {
            std::cout << "(empty)";
        }

        for (size_t pos = 0; pos < row.values.size(); ++pos) {
            const bool active = isHighlighted(
                highlighted,
                static_cast<int>(rowIdx),
                static_cast<int>(pos));
            const char marker = active ? markerFor(event) : ' ';

            std::cout << "[" << marker << " "
                      << std::right << std::setw(valueWidth + 1) << row.values[pos]
                      << "] ";
        }

        std::cout << "\n";
    }

    if (isCountEvent(event)) {
        std::cout << "\nLegend: [+] Incrementing  [!] Decrementing  [*] Accumulating\n";
    } else {
        std::cout << "\nLegend: [+] Placed  [!] Flushing  [*] Comparing\n";
    }
    std::fflush(stdout);

    if (delayMs > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}
