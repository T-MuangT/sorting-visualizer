#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "../../include/visualizer/terminal/TerminalGraphVisualizer.hpp"

TerminalGraphVisualizer::TerminalGraphVisualizer(int delayMs, int maxVisibleNodes) : delayMs(delayMs), maxVisibleNodes(maxVisibleNodes) {}

void TerminalGraphVisualizer::clearScreen() const {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

bool TerminalGraphVisualizer::isHighlighted(const std::vector<int>& highlightedNodes, int nodeIdx) {
    return std::find(highlightedNodes.begin(), highlightedNodes.end(), nodeIdx) != highlightedNodes.end();
}

const char* TerminalGraphVisualizer::eventName(AuxEvent event) {
    switch (event) {
        case AuxEvent::InsertInTree:
            return "Insert in Tree";

        case AuxEvent::LinkLeft:
            return "Link Left Child";

        case AuxEvent::LinkRight:
            return "Link Right Child";

        case AuxEvent::VisitInOrder:
            return "Visit In-Order";

        default:
            return "Graph Event";
    }
}

char TerminalGraphVisualizer::markerFor(AuxEvent event) {
    switch (event) {
        case AuxEvent::InsertInTree:
            return '+';

        case AuxEvent::LinkLeft:
        case AuxEvent::LinkRight:
            return '*';

        case AuxEvent::VisitInOrder:
            return '!';

        default:
            return '?';
    }
}

void TerminalGraphVisualizer::renderGraph(
    const std::vector<TreeNode>& nodes,
    AuxEvent event,
    const std::vector<int>& highlightedNodes) {
    if (nodes.empty()) {
        std::cout << "(empty tree)\n";
        return;
    }

    int rootIdx = -1;

    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i].parent == -1) {
            rootIdx = static_cast<int>(i);
            break;
        }
    }

    if (rootIdx == -1) {
        std::cout << "(invalid tree: no root)\n";
        return;
    }

    int focusIdx = rootIdx;

    for (const int nodeIdx : highlightedNodes) {
        if (nodeIdx >= 0 && nodeIdx < static_cast<int>(nodes.size())) {
            focusIdx = nodeIdx;
            break;
        }
    }

    // Build the path from the root to the focused node.
    std::string path;
    int current = focusIdx;
    bool validPath = true;

    while (current != rootIdx) {
        if (current < 0 || current >= static_cast<int>(nodes.size())) {
            validPath = false;
            break;
        }

        const TreeNode& node = nodes[static_cast<size_t>(current)];
        const int parentIdx = node.parent;

        if (parentIdx < 0 || parentIdx >= static_cast<int>(nodes.size())) {
            validPath = false;
            break;
        }

        const TreeNode& parent = nodes[static_cast<size_t>(parentIdx)];

        if (parent.left == current) {
            path.push_back('L');
        } else if (parent.right == current) {
            path.push_back('R');
        } else {
            validPath = false;
            break;
        }

        current = parentIdx;
    }

    if (!validPath) {
        std::cout << "(invalid tree path)\n";
        return;
    }

    std::reverse(path.begin(), path.end());

    const int depth = static_cast<int>(path.size());
    const TreeNode& focusNode = nodes[static_cast<size_t>(focusIdx)];

    // Determine the parent
    const int parentIdx = focusNode.parent;

    // Determine the child to display
    //
    // For link events, the event itself tells us which branch
    // is currently relevant.
    //
    // Otherwise, if there is only one child, display it.
    // If both children exist, prefer the left child for the
    // terminal's single "down" position.
    int childIdx = -1;

    if (event == AuxEvent::LinkLeft) {
        childIdx = focusNode.left;
    } else if (event == AuxEvent::LinkRight) {
        childIdx = focusNode.right;
    } else if (focusNode.left != -1 && focusNode.right == -1) {
        childIdx = focusNode.left;
    } else if (focusNode.right != -1 && focusNode.left == -1) {
        childIdx = focusNode.right;
    } else if (focusNode.left != -1) {
        childIdx = focusNode.left;
    }

    // Header describing the current tree location
    std::cout << "Position: " << (path.empty() ? "ROOT" : path) << "\n";
    std::cout << "Depth:    " << depth << "\n\n";

    // Parent node
    std::cout << "Parent\n";

    if (parentIdx >= 0 &&
        parentIdx < static_cast<int>(nodes.size())) {
        const TreeNode& parentNode =
            nodes[static_cast<size_t>(parentIdx)];

        std::cout << "  [  "
                  << parentNode.value
                  << "]\n";

        char direction = '?';

        if (parentNode.left == focusIdx) {
            direction = 'L';
        } else if (parentNode.right == focusIdx) {
            direction = 'R';
        }

        std::cout << "    |\n";
        std::cout << "    | " << direction << "\n";
        std::cout << "    v\n";
    } else {
        std::cout << "  (none: root)\n";
    }

    // Current node
    const bool active = isHighlighted(highlightedNodes, focusIdx);
    const char marker = active ? markerFor(event) : ' ';

    std::cout << "Current\n";
    std::cout << "  [" << marker << ' ' << focusNode.value << "]\n";

    // Child node
    std::cout << "\nChild\n";

    if (childIdx >= 0 && childIdx < static_cast<int>(nodes.size())) {
        const TreeNode& childNode = nodes[static_cast<size_t>(childIdx)];
        char direction = '?';

        if (focusNode.left == childIdx) {
            direction = 'L';
        } else if (focusNode.right == childIdx) {
            direction = 'R';
        }

        std::cout << "    |\n";
        std::cout << "    | " << direction << "\n";
        std::cout << "    v\n";
        std::cout << "  [  " << childNode.value << "]\n";
    } else {
        std::cout << "  (none)\n";
    }
}

void TerminalGraphVisualizer::renderFrame(
    const std::vector<TreeNode>& nodes,
    AuxEvent event,
    const std::vector<int>& highlightedNodes,
    const std::string& stepName,
    const SortStats& stats) {

    // Validate the current graph structure before rendering. If the graph is invalid, we will render the last valid graph state instead.
    bool currentGraphValid = true;

    if (!nodes.empty()) {
        int rootIdx = -1;

        for (size_t i = 0; i < nodes.size(); ++i) {
            if (nodes[i].parent == -1) {
                rootIdx = static_cast<int>(i);
                break;
            }
        }

        if (rootIdx == -1) {
            currentGraphValid = false;
        } else {
            int focusIdx = rootIdx;

            for (const int nodeIdx : highlightedNodes) {
                if (nodeIdx >= 0 &&
                    nodeIdx < static_cast<int>(nodes.size())) {
                    focusIdx = nodeIdx;
                    break;
                }
            }

            int current = focusIdx;

            while (current != rootIdx) {
                if (current < 0 ||
                    current >= static_cast<int>(nodes.size())) {
                    currentGraphValid = false;
                    break;
                }

                const TreeNode& node =
                    nodes[static_cast<size_t>(current)];

                const int parentIdx = node.parent;

                if (parentIdx < 0 ||
                    parentIdx >= static_cast<int>(nodes.size())) {
                    currentGraphValid = false;
                    break;
                }

                const TreeNode& parent =
                    nodes[static_cast<size_t>(parentIdx)];

                if (parent.left == current) {
                    current = parentIdx;
                } else if (parent.right == current) {
                    current = parentIdx;
                } else {
                    currentGraphValid = false;
                    break;
                }
            }
        }
    }

    clearScreen();

    std::cout << "==== Terminal Visualizer ====\n";
    std::cout << "Step: " << stepName << "\n";
    std::cout << "Event: " << eventName(event) << "\n";
    std::cout << "Reads: " << stats.getComparisons() << " | Writes: " << stats.getSwaps() << "\n\n";

    if (!currentGraphValid && event == AuxEvent::InsertInTree && hasRenderedGraph) {
        renderGraph(lastRenderedNodes, lastRenderedEvent, lastRenderedHighlights);
    } else {
        renderGraph(nodes, event, highlightedNodes);

        // Only retain a graph after successfully rendering it. An invalid intermediate InsertInTree state must never replace the previous valid graph.
        if (currentGraphValid) {
            lastRenderedNodes = nodes;
            lastRenderedEvent = event;
            lastRenderedHighlights = highlightedNodes;
            hasRenderedGraph = true;
        }
    }

    std::cout
        << "\nLegend: [*] Linking  [!] Visiting\n";

    std::fflush(stdout);

    if (delayMs > 0) {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(delayMs));
    }
}