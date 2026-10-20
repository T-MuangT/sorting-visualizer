#include <algorithm>
#include <functional>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../../include/visualizer/graphics/GraphicsGraphVisualizer.hpp"

namespace {
const wxColour kInk(35, 45, 60);
const wxColour kMuted(110, 122, 138);
const wxColour kEdge(139, 153, 171);
const wxColour kNodeFill(230, 240, 252);
const wxColour kNodeBorder(72, 125, 184);
const wxColour kInsert(126, 187, 155);
const wxColour kLink(245, 181, 62);
const wxColour kVisit(172, 130, 213);

bool isHighlighted(const std::vector<int>& selected, int idx) {
    return std::find(selected.begin(), selected.end(), idx) != selected.end();
}

wxColour highlightColour(AuxEvent event) {
    switch (event) {
        case AuxEvent::LinkLeft:
        case AuxEvent::LinkRight:
            return kLink;
        case AuxEvent::VisitInOrder:
            return kVisit;
        default:
            return kInsert;
    }
}
}

GraphicsGraphVisualizer::GraphicsGraphVisualizer() = default;
GraphicsGraphVisualizer::~GraphicsGraphVisualizer() = default;
void GraphicsGraphVisualizer::initialize() {}
void GraphicsGraphVisualizer::shutdown() {}

void GraphicsGraphVisualizer::setRefreshCallback(std::function<void()> callback) {
    std::lock_guard<std::mutex> lock(stateMutex);
    refresh = std::move(callback);
}

void GraphicsGraphVisualizer::renderFrame(const std::vector<TreeNode>& currentNodes, AuxEvent event,
                                          const std::vector<int>& activeNodes, const std::string& name,
                                          const SortStats& currentStats) {
    std::function<void()> refreshCallback;
    {
        std::lock_guard<std::mutex> lock(stateMutex);
        nodes = currentNodes;
        currentEvent = event;
        highlightedNodes = activeNodes;
        stepName = name;
        stats = currentStats;
        refreshCallback = refresh;
    }
    if (refreshCallback)
        refreshCallback();
}

void GraphicsGraphVisualizer::draw(wxDC& dc, const wxRect& bounds) const {
    std::lock_guard<std::mutex> lock(stateMutex);
    dc.SetClippingRegion(bounds);
    dc.SetBrush(wxBrush(wxColour(250, 252, 255)));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(bounds);
    dc.SetTextForeground(kInk);
    dc.SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dc.DrawText("Tree graph", bounds.x + 12, bounds.y + 8);
    dc.SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dc.SetTextForeground(kMuted);
    dc.DrawText(wxString::Format("%s   |   Reads: %llu   Writes: %llu", wxString::FromUTF8(stepName.c_str()),
        static_cast<unsigned long long>(stats.getComparisons()),
        static_cast<unsigned long long>(stats.getSwaps())), bounds.x + 12, bounds.y + 29);

    int root = -1;
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i].parent == -1) {
            root = static_cast<int>(i);
            break;
        }
    }
    if (root == -1) {
        dc.SetTextForeground(kMuted);
        dc.DrawText(nodes.empty() ? "(empty tree)" : "(tree has no root)", bounds.x + 14, bounds.y + 62);
        dc.DestroyClippingRegion();
        return;
    }

    // Build a connected tree from the root. This ignores any placeholder slots
    // supplied by a producer and prevents malformed child links from looping.
    std::vector<int> inorder;
    std::vector<int> depth(nodes.size(), -1);
    std::unordered_set<int> visiting;
    std::unordered_set<int> visited;
    std::function<void(int, int)> visit = [&](int idx, int level) {
        if (idx < 0 || idx >= static_cast<int>(nodes.size()) || visited.contains(idx) || visiting.contains(idx))
            return;
        visiting.insert(idx);
        depth[static_cast<std::size_t>(idx)] = level;
        visit(nodes[static_cast<std::size_t>(idx)].left, level + 1);
        inorder.push_back(idx);
        visit(nodes[static_cast<std::size_t>(idx)].right, level + 1);
        visiting.erase(idx);
        visited.insert(idx);
    };
    visit(root, 0);
    if (inorder.empty()) {
        dc.SetTextForeground(kMuted);
        dc.DrawText("(empty tree)", bounds.x + 14, bounds.y + 62);
        dc.DestroyClippingRegion();
        return;
    }

    std::vector<int> xOrder(nodes.size(), -1);
    for (std::size_t i = 0; i < inorder.size(); ++i)
        xOrder[static_cast<std::size_t>(inorder[i])] = static_cast<int>(i);
    const int graphTop = bounds.y + 62;
    const int graphBottom = bounds.y + bounds.height - 18;
    const int graphHeight = std::max(1, graphBottom - graphTop);
    const int sideMargin = 24;
    const double horizontalStep = static_cast<double>(std::max(1, bounds.width - sideMargin * 2)) / std::max<std::size_t>(1, inorder.size());
    int maxDepth = 0;
    for (const int idx : inorder)
        maxDepth = std::max(maxDepth, depth[static_cast<std::size_t>(idx)]);
    const double verticalStep = maxDepth == 0 ? 0.0 : static_cast<double>(graphHeight - 28) / maxDepth;
    const int radiusByWidth = static_cast<int>(horizontalStep * 0.34);
    const int radiusByHeight = maxDepth == 0 ? 28 : static_cast<int>(verticalStep * 0.29);
    const int radius = std::clamp(std::min(radiusByWidth, radiusByHeight), 7, 27);

    auto pointFor = [&](int idx) {
        const int x = bounds.x + sideMargin + static_cast<int>((xOrder[static_cast<std::size_t>(idx)] + 0.5) * horizontalStep);
        const int y = graphTop + (maxDepth == 0 ? graphHeight / 2 : static_cast<int>(depth[static_cast<std::size_t>(idx)] * verticalStep));
        return wxPoint(x, y);
    };

    // Draw all parent-to-child edges first. Both L and R edges descend.
    dc.SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    for (const int idx : inorder) {
        const auto& node = nodes[static_cast<std::size_t>(idx)];
        const wxPoint parentPoint = pointFor(idx);
        const int children[] = {node.left, node.right};
        const char* directions[] = {"L", "R"};
        for (int childNumber = 0; childNumber < 2; ++childNumber) {
            const int child = children[childNumber];
            if (child < 0 || child >= static_cast<int>(nodes.size()) || depth[static_cast<std::size_t>(child)] < 0)
                continue;
            const wxPoint childPoint = pointFor(child);
            const bool activeEdge = isHighlighted(highlightedNodes, idx) && isHighlighted(highlightedNodes, child);
            dc.SetPen(wxPen(activeEdge ? highlightColour(currentEvent) : kEdge, activeEdge ? 3 : 2));
            dc.DrawLine(parentPoint.x, parentPoint.y + radius, childPoint.x, childPoint.y - radius);
            const int labelX = (parentPoint.x + childPoint.x) / 2 + (childNumber == 0 ? -12 : 5);
            const int labelY = (parentPoint.y + childPoint.y) / 2 - 5;
            dc.SetTextForeground(childNumber == 0 ? wxColour(66, 119, 176) : wxColour(158, 101, 54));
            dc.DrawText(directions[childNumber], labelX, labelY);
        }
    }

    // Then draw every reachable node, preserving the full tree at each event.
    for (const int idx : inorder) {
        const auto& node = nodes[static_cast<std::size_t>(idx)];
        const wxPoint center = pointFor(idx);
        const bool active = isHighlighted(highlightedNodes, idx);
        const wxColour fill = active ? highlightColour(currentEvent) : kNodeFill;
        dc.SetPen(wxPen(active ? fill.ChangeLightness(75) : kNodeBorder, active ? 3 : 2));
        dc.SetBrush(wxBrush(fill));
        dc.DrawCircle(center, radius);
        const wxString value = wxString::Format("%d", node.value);
        dc.SetFont(wxFont(std::max(7, std::min(10, radius / 2 + 3)), wxFONTFAMILY_SWISS,
                          wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        dc.SetTextForeground(kInk);
        wxCoord textWidth = 0, textHeight = 0;
        dc.GetTextExtent(value, &textWidth, &textHeight);
        dc.DrawText(value, center.x - textWidth / 2, center.y - textHeight / 2);
    }
    dc.DestroyClippingRegion();
}
