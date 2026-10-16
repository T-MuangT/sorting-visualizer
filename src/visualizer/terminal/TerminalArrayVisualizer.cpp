#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstdio>

#include "../../include/visualizer/terminal/TerminalArrayVisualizer.hpp"

TerminalArrayVisualizer::TerminalArrayVisualizer(int delayMs) : delayMs(delayMs) {}

void TerminalArrayVisualizer::clearScreen() const {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void TerminalArrayVisualizer::renderBars(const std::vector<int>& arr, int idx1, int idx2, char marker) const {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "[";
        if (static_cast<int>(i) == idx1 ||
            static_cast<int>(i) == idx2) {
            std::cout << marker;
        } else {
            std::cout << " ";
        }
        std::cout << "] ";

        for (int v = 0; v < arr[i]; ++v) {
            std::cout << "#";
        }

        std::cout << " (" << arr[i] << ")\n";
    }
}

void TerminalArrayVisualizer::waitForNextFrame() const {
    std::fflush(stdout);

    if (delayMs > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

void TerminalArrayVisualizer::renderFrame(const std::vector<int>& arr, SortEvent event, int idx1, int idx2, const std::string& stepName, const SortStats& stats) {
    clearScreen();

    std::cout << "==== Terminal Visualizer ====\n";
    std::cout << "View: Main Array\n";
    std::cout << "Step: " << stepName << "\n";
    std::cout << "Reads: " << stats.getComparisons() << " | Writes: " << stats.getSwaps() << "\n\n";

    const bool isMovement = event == SortEvent::Swap || event == SortEvent::Shift || event == SortEvent::Insert;

    renderBars(arr, idx1, idx2, isMovement ? '!' : '*');
    std::cout << "\nLegend: [*] Comparing  [!] Swapping\n";
    waitForNextFrame();
}

void TerminalArrayVisualizer::renderAuxFrame(const std::vector<int>& arr, AuxEvent event, int highlightedIdx, const std::string& label, const std::string& stepName, const SortStats& stats) {
    clearScreen();

    std::cout << "==== Terminal Visualizer ====\n";
    std::cout << "View: Auxiliary Array\n";
    std::cout << "Step: " << stepName << "\n";
    std::cout << "Array: " << label << "\n";
    std::cout << "Reads: " << stats.getComparisons() << " | Writes: " << stats.getSwaps() << "\n";

    char marker = '?';

    switch (event) {
        case AuxEvent::PlaceInPartition:
        case AuxEvent::PlaceInBucket:
            marker = '+';
            break;

        case AuxEvent::WriteFromAuxPartition:
        case AuxEvent::FlushBucket:
        case AuxEvent::PlaceCountOutput:
            marker = '!';
            break;

        case AuxEvent::CompareInAux:
            marker = '*';
            break;

        case AuxEvent::IncrementCount:
            marker = '+';
            break;

        case AuxEvent::AccumulateCount:
            marker = '*';
            break;

        case AuxEvent::InsertInTree:
        case AuxEvent::LinkLeft:
        case AuxEvent::LinkRight:
        case AuxEvent::VisitInOrder:
            // These events belong to the tree visualization path.
            marker = '?';
            break;
    }

    renderBars(arr, highlightedIdx, -1, marker);
    std::cout << "\nLegend: [+] Placing  [!] Flushing  [*] Comparing\n";
    waitForNextFrame();
}