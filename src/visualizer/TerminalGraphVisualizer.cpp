#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../include/visualizer/TerminalGraphVisualizer.hpp"

TerminalGraphVisualizer::TerminalGraphVisualizer(int delayMs, int maxVisibleNodes) : delayMs(delayMs), maxVisibleNodes(maxVisibleNodes) {}

void TerminalGraphVisualizer::clearScreen() const {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

bool TerminalGraphVisualizer::isHighlighted(const std::vector<int>& highlightedNodes, int nodeIdx) {
    return std::find(
        highlightedNodes.begin(),
        highlightedNodes.end(),
        nodeIdx) != highlightedNodes.end();
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

void TerminalGraphVisualizer::renderFrame(const std::vector<TreeNode>& nodes, AuxEvent event, const std::vector<int>& highlightedNodes, const std::string& stepName, const SortStats& stats) {
    clearScreen();

    std::cout << "==== Terminal Visualizer ====\n";
    std::cout << "Step: " << stepName << "\n";
    std::cout << "Event: " << eventName(event) << "\n";
    std::cout << "Reads: " << stats.getComparisons()
              << " | Writes: " << stats.getSwaps() << "\n\n";

    if (nodes.empty()) {
        std::cout << "(empty tree)\n";
    } else {
        int rootIdx = -1;

        for (size_t i = 0; i < nodes.size(); ++i) {
            if (nodes[i].parent == -1) {
                rootIdx = static_cast<int>(i);
                break;
            }
        }

        if (rootIdx == -1) {
            std::cout << "(invalid tree: no root)\n";
        } else {
            std::vector<int> depths(nodes.size(), -1);

            std::vector<int> stack;
            stack.push_back(rootIdx);
            depths[static_cast<size_t>(rootIdx)] = 0;

            int maxDepth = 0;

            while (!stack.empty()) {
                const int nodeIdx = stack.back();
                stack.pop_back();

                const int depth = depths[static_cast<size_t>(nodeIdx)];
                maxDepth = std::max(maxDepth, depth);

                const TreeNode& node = nodes[static_cast<size_t>(nodeIdx)];

                if (node.left >= 0 && node.left < static_cast<int>(nodes.size()) && depths[static_cast<size_t>(node.left)] == -1) {
                    depths[static_cast<size_t>(node.left)] = depth + 1;
                    stack.push_back(node.left);
                }

                if (node.right >= 0 && node.right < static_cast<int>(nodes.size()) && depths[static_cast<size_t>(node.right)] == -1) {
                    depths[static_cast<size_t>(node.right)] = depth + 1;
                    stack.push_back(node.right);
                }
            }

            // Select focus node
            int focusIdx = rootIdx;

            for (const int nodeIdx : highlightedNodes) {
                if (nodeIdx >= 0 && nodeIdx < static_cast<int>(nodes.size()) && depths[static_cast<size_t>(nodeIdx)] >= 0) {
                    focusIdx = nodeIdx;
                    break;
                }
            }

            // Determine visible nodes
            std::vector<bool> visible(nodes.size(), false);

            int current = focusIdx;

            while (current >= 0 && current < static_cast<int>(nodes.size()) && !visible[static_cast<size_t>(current)]) {
                visible[static_cast<size_t>(current)] = true;
                current = nodes[static_cast<size_t>(current)].parent;
            }

            // Expand visible nodes downwards
            bool changed = true;

            while (changed) {
                changed = false;

                int visibleCount = 0;

                for (const bool isVisible : visible) {
                    if (isVisible) {
                        ++visibleCount;
                    }
                }

                if (visibleCount >= maxVisibleNodes) {
                    break;
                }

                for (size_t i = 0; i < nodes.size(); ++i) {
                    if (!visible[i]) {
                        continue;
                    }

                    const TreeNode& node = nodes[i];

                    if (node.left >= 0 && node.left < static_cast<int>(nodes.size()) && !visible[static_cast<size_t>(node.left)]) {
                        visible[static_cast<size_t>(node.left)] = true;
                        changed = true;

                        ++visibleCount;

                        if (visibleCount >= maxVisibleNodes) {
                            break;
                        }
                    }

                    if (node.right >= 0 && node.right < static_cast<int>(nodes.size()) && !visible[static_cast<size_t>(node.right)]) {

                        visible[static_cast<size_t>(node.right)] = true;
                        changed = true;

                        ++visibleCount;

                        if (visibleCount >= maxVisibleNodes) {
                            break;
                        }
                    }
                }
            }

            // Assign positions to visible nodes for rendering
            std::vector<int> positions(nodes.size(), -1);
            int nextPosition = 0;

            std::vector<std::pair<int, bool>> traversal;
            traversal.push_back({rootIdx, false});

            while (!traversal.empty()) {
                const auto [nodeIdx, visited] = traversal.back();
                traversal.pop_back();

                if (nodeIdx < 0 || nodeIdx >= static_cast<int>(nodes.size()) || !visible[static_cast<size_t>(nodeIdx)]) {
                    continue;
                }

                const TreeNode& node = nodes[static_cast<size_t>(nodeIdx)];

                if (!visited) {
                    if (node.right >= 0 && node.right < static_cast<int>(nodes.size()) && visible[static_cast<size_t>(node.right)]) {
                        traversal.push_back({node.right, false});
                    }

                    traversal.push_back({nodeIdx, true});

                    if (node.left >= 0 && node.left < static_cast<int>(nodes.size()) && visible[static_cast<size_t>(node.left)]) {
                        traversal.push_back({node.left, false});
                    }
                } else {
                    positions[static_cast<size_t>(nodeIdx)] = nextPosition++;
                }
            }

            int minDepth = maxDepth;
            int visibleMaxDepth = 0;

            for (size_t i = 0; i < nodes.size(); ++i) {
                if (!visible[i]) {
                    continue;
                }

                minDepth = std::min(minDepth, depths[i]);
                visibleMaxDepth = std::max(visibleMaxDepth, depths[i]);
            }

            // Indicate if there are nodes above the visible range
            if (minDepth > 0) {
                std::cout << "...\n";
            }

            constexpr int nodeSpacing = 6;

            for (int depth = minDepth; depth <= visibleMaxDepth; ++depth) {
                std::ostringstream nodeLine;
                std::ostringstream edgeLine;

                bool hasNodes = false;

                for (size_t i = 0; i < nodes.size(); ++i) {
                    if (!visible[i] || depths[i] != depth) {
                        continue;
                    }

                    const int position = positions[i];

                    while (static_cast<int>(nodeLine.tellp()) < position * nodeSpacing) {
                        nodeLine << ' ';
                    }

                    const bool active = isHighlighted(highlightedNodes, static_cast<int>(i));
                    const char marker = active ? markerFor(event) : ' ';

                    nodeLine << '['
                             << marker << ' '
                             << nodes[i].value
                             << ']';

                    hasNodes = true;
                }

                if (!hasNodes) {
                    continue;
                }

                std::cout << nodeLine.str() << "\n";

                if (depth == visibleMaxDepth) {
                    continue;
                }

                bool hasEdges = false;

                for (size_t i = 0; i < nodes.size(); ++i) {
                    if (!visible[i] || depths[i] != depth) {
                        continue;
                    }

                    const TreeNode& node = nodes[i];

                    if (node.left >= 0 && node.left < static_cast<int>(nodes.size()) && visible[static_cast<size_t>(node.left)]) {
                        const int parentPos = positions[i];
                        const int childPos = positions[static_cast<size_t>(node.left)];
                        const int edgePos = std::min(parentPos, childPos) * nodeSpacing + 2;

                        while (static_cast<int>(edgeLine.tellp()) < edgePos) {
                            edgeLine << ' ';
                        }

                        edgeLine << '/';
                        hasEdges = true;
                    }

                    if (node.right >= 0 && node.right < static_cast<int>(nodes.size()) && visible[static_cast<size_t>(node.right)]) {
                        const int parentPos = positions[i];
                        const int childPos = positions[static_cast<size_t>(node.right)];
                        const int edgePos = std::min(parentPos, childPos) * nodeSpacing + 4;

                        while (static_cast<int>(edgeLine.tellp()) < edgePos) {
                            edgeLine << ' ';
                        }

                        edgeLine << '\\';
                        hasEdges = true;
                    }
                }

                if (hasEdges) {
                    std::cout << edgeLine.str() << "\n";
                }
            }

            // Indicate if there are nodes below the visible range
            bool truncatedBelow = false;

            for (size_t i = 0; i < nodes.size(); ++i) {
                if (!visible[i]) {
                    continue;
                }

                const TreeNode& node = nodes[i];

                if ((node.left >= 0 && node.left < static_cast<int>(nodes.size()) && !visible[static_cast<size_t>(node.left)]) || (node.right >= 0 && node.right < static_cast<int>(nodes.size()) && !visible[static_cast<size_t>(node.right)])) {
                    truncatedBelow = true;
                    break;
                }
            }

            if (truncatedBelow) {
                std::cout << "...\n";
            }
        }
    }

    std::cout << "\nLegend: [+] Inserting  [*] Linking  [!] Visiting\n";
    std::fflush(stdout);

    if (delayMs > 0) {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(delayMs));
    }
}