#include <string>
#include <vector>

#include "../../../include/algorithms/TreeEventData.hpp"
#include "../../../include/algorithms/TreeStructure.hpp"
#include "UnbalancedBstTreeSort.hpp"

void unbalancedBstTreeSort(std::vector<int>& arr, VisualizationSession& session) {
    if (arr.empty()) {
        session.onArrayEvent(arr, SortEvent::Compare, -1, -1, "Unbalanced Binary Search Tree Sort: Empty Array");
        return;
    }

    session.onArrayEvent(arr, SortEvent::Compare, -1, -1, "Unbalanced Binary Search Tree Sort: Original Array");

    session.beginTreePhase("Unbalanced Binary Search Tree Sort: Create Tree");
    UnbalancedBstTree tree;

    // Insert each element into the tree.
    for (size_t i = 0; i < arr.size(); ++i) {
        const int value = arr[i];
        const int srcIdx = static_cast<int>(i);
        const int treeNodeIdx = tree.insert(value);
        const auto& nodes = tree.getNodes();
        const auto& node = nodes[static_cast<size_t>(treeNodeIdx)];
        session.onTreeEvent(AuxEvent::InsertInTree, TreeEventData{.srcIdx = srcIdx, .treeNodeIdx = treeNodeIdx, .parentIdx = node.parent, .value = value}, "Unbalanced Binary Search Tree Sort: Insert " + std::to_string(value));

        if (node.parent != -1) {
            const auto& parent = nodes[static_cast<size_t>(node.parent)];

            if (parent.left == treeNodeIdx) {
                session.onTreeEvent(AuxEvent::LinkLeft, TreeEventData{.srcIdx = srcIdx, .treeNodeIdx = treeNodeIdx, .parentIdx = node.parent}, "Unbalanced Binary Search Tree Sort: Link Left");
            } else if (parent.right == treeNodeIdx) {
                session.onTreeEvent(AuxEvent::LinkRight, TreeEventData{.srcIdx = srcIdx, .treeNodeIdx = treeNodeIdx, .parentIdx = node.parent}, "Unbalanced Binary Search Tree Sort: Link Right");
            }
        }
    }

    // Perform in-order traversal to obtain sorted elements.
    std::vector<int> sortedElements;

    tree.inOrderTraversal([&](int treeNodeIdx) {
        const auto& nodes = tree.getNodes();
        const auto& node = nodes[static_cast<size_t>(treeNodeIdx)];

        sortedElements.push_back(node.value);

        session.onTreeEvent(AuxEvent::VisitInOrder, TreeEventData{.treeNodeIdx = treeNodeIdx, .value = node.value}, "Unbalanced Binary Search Tree Sort: Visit " + std::to_string(node.value));
    });

    // Copy sorted elements back into the original array.
    for (size_t i = 0; i < sortedElements.size(); ++i) {
        arr[i] = sortedElements[i];
        session.onArrayEvent(arr, SortEvent::Swap, static_cast<int>(i), static_cast<int>(i), "Unbalanced Binary Search Tree Sort: Write Back " + std::to_string(sortedElements[i]));
    }

    session.endTreePhase(arr, "Unbalanced Binary Search Tree Sort: Tree Traversal Complete");
}