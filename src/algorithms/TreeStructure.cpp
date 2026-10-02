#include <cstddef>

#include "../include/algorithms/TreeStructure.hpp"

int UnbalancedBstTree::insert(int value) {
    const int newNodeIdx = static_cast<int>(nodes.size());
    nodes.push_back({.value = value});

    if (root == -1) {
        root = newNodeIdx;
        return newNodeIdx;
    }

    int currentIdx = root;

    while (true) {
        Node& currentNode = nodes[static_cast<size_t>(currentIdx)];

        if (value <= currentNode.value) {
            if (currentNode.left == -1) {
                currentNode.left = newNodeIdx;
                nodes[static_cast<size_t>(newNodeIdx)].parent = currentIdx;
                return newNodeIdx;
            }

            currentIdx = currentNode.left;
        } else {
            if (currentNode.right == -1) {
                currentNode.right = newNodeIdx;
                nodes[static_cast<size_t>(newNodeIdx)].parent = currentIdx;
                return newNodeIdx;
            }

            currentIdx = currentNode.right;
        }
    }
}

void UnbalancedBstTree::inOrderTraversal(int nodeIdx, std::vector<int>& values) const {
    if (nodeIdx == -1) {
        return;
    }

    const Node& node = nodes[static_cast<size_t>(nodeIdx)];

    inOrderTraversal(node.left, values);
    values.push_back(node.value);
    inOrderTraversal(node.right, values);
}

void UnbalancedBstTree::inOrderTraversal(std::vector<int>& values) const {
    inOrderTraversal(root, values);
}

void UnbalancedBstTree::inOrderTraversal(int nodeIdx, const std::function<void(int)>& visit) const {
    if (nodeIdx == -1) {
        return;
    }

    const Node& node = nodes[static_cast<size_t>(nodeIdx)];

    inOrderTraversal(node.left, visit);
    visit(nodeIdx);
    inOrderTraversal(node.right, visit);
}

void UnbalancedBstTree::inOrderTraversal(const std::function<void(int)>& visit) const {
    inOrderTraversal(root, visit);
}

const std::vector<UnbalancedBstTree::Node>& UnbalancedBstTree::getNodes() const noexcept {
    return nodes;
}

int UnbalancedBstTree::getRoot() const noexcept {
    return root;
}