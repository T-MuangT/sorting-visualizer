#pragma once

#include <functional>
#include <vector>

class UnbalancedBstTree {
public:
    struct Node {
        int value;
        int parent = -1;
        int left = -1;
        int right = -1;
    };

private:
    std::vector<Node> nodes;
    int root = -1;

    void inOrderTraversal(
        int nodeIdx,
        std::vector<int>& values) const;

    void inOrderTraversal(
        int nodeIdx,
        const std::function<void(int)>& visit) const;

public:
    int insert(int value);

    void inOrderTraversal(
        std::vector<int>& values) const;

    void inOrderTraversal(
        const std::function<void(int)>& visit) const;

    [[nodiscard]] const std::vector<Node>& getNodes() const noexcept;
    [[nodiscard]] int getRoot() const noexcept;
};