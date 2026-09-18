// Smoothsort (Dijkstra, 1981).
//
// This is a direct port of the well-known reference derivation by
// Martin Knoblauch Revuelta (itself adapted from Keith Schwarz's
// "Smoothsort Demystified"), translated line-for-line into the
// index-based / SortCallback-instrumented style used by this codebase,
// instead of the raw-pointer style of the original C source.
#include "SmoothSort.hpp"
#include <cstdint>
#include <vector>
#include <string>

namespace {

// Leonardo numbers L[0..44]; L[44] already exceeds 2^32, comfortably
// beyond any array size we need to handle with 32/64-bit indices.
const uint64_t L[] = {
    1ULL, 1ULL, 3ULL, 5ULL, 9ULL, 15ULL, 25ULL, 41ULL, 67ULL, 109ULL,
    177ULL, 287ULL, 465ULL, 753ULL, 1219ULL, 1973ULL, 3193ULL, 5167ULL,
    8361ULL, 13529ULL, 21891ULL, 35421ULL, 57313ULL, 92735ULL, 150049ULL,
    242785ULL, 392835ULL, 635621ULL, 1028457ULL, 1664079ULL, 2692537ULL,
    4356617ULL, 7049155ULL, 11405773ULL, 18454929ULL, 29860703ULL,
    48315633ULL, 78176337ULL, 126491971ULL, 204668309ULL, 331160281ULL,
    535828591ULL, 866988873ULL, 1402817465ULL, 2269806339ULL
};

struct HeapSizes {
    uint64_t mask;  // bit k set => a heap of Leonardo order (offset + k) exists
    int offset;     // Leonardo order of the smallest (rightmost) heap
};

inline bool lessAt(const std::vector<int>& arr, int i, int j,
                    SortCallback& notify, const char* desc) {
    if (notify) notify(SortEvent::Compare, i, j, desc);
    return arr[i] < arr[j];
}

inline void swapAt(std::vector<int>& arr, int i, int j,
                    SortCallback& notify, const char* desc) {
    std::swap(arr[i], arr[j]);
    if (notify) notify(SortEvent::Swap, i, j, desc);
}

// Ordinary sift-down within one Leonardo heap of the given order, rooted
// at index `root`. Both children (if order >= 2) are already valid
// Leonardo heaps; this restores the heap property at `root`.
void siftIn(std::vector<int>& arr, int root, int order, SortCallback& notify) {
    if (order < 2) return; // a leaf, no children to sift down into

    int startRoot = root;
    while (order >= 2) {
        int right = root - 1;
        int left = right - static_cast<int>(L[order - 2]);

        int next;
        int nextOrder;
        // Compare the two children's roots directly (not against a
        // running "largest" value) to decide which subtree could hold
        // a larger value than the other child.
        if (lessAt(arr, right, left, notify, "Smoothsort: Compare Heap Children")) {
            next = left;
            nextOrder = order - 1;
        } else {
            next = right;
            nextOrder = order - 2;
        }

        // If the chosen child's root doesn't exceed the current value
        // at `root`, the heap property already holds here.
        if (!lessAt(arr, root, next, notify, "Smoothsort: Compare Heap Root with Chosen Child")) {
            break;
        }

        swapAt(arr, root, next, notify, "Smoothsort: Sift Down");
        root = next;
        order = nextOrder;
    }
    (void)startRoot;
}

// Restore ordering across heap boundaries: compare the (possibly
// newly-placed) value at `root` — the root of the rightmost heap
// described by `hsz` — against the effective root of the heap
// immediately to its left, swapping and walking left as necessary, then
// finish with an ordinary siftIn in whichever heap the value lands in.
void interheapSift(std::vector<int>& arr, int root, HeapSizes hsz,
                    SortCallback& notify) {
    while (hsz.mask != 1) {
        // "Effective root" of the current heap: the larger of its own
        // root and (if it has children) its children's roots — because
        // if a child is larger, the value could still belong further
        // left only if it beats that child too.
        int effectiveRoot = root;
        if (hsz.offset > 1) {
            int right = root - 1;
            int left = right - static_cast<int>(L[hsz.offset - 2]);
            if (lessAt(arr, effectiveRoot, left, notify, "Smoothsort: Trinkle Compare with Left Child"))
                effectiveRoot = left;
            if (lessAt(arr, effectiveRoot, right, notify, "Smoothsort: Trinkle Compare with Right Child"))
                effectiveRoot = right;
        }

        int nextHeapRoot = root - static_cast<int>(L[hsz.offset]);
        if (!lessAt(arr, effectiveRoot, nextHeapRoot, notify, "Smoothsort: Trinkle Compare with Previous Heap Root")) {
            break;
        }

        swapAt(arr, root, nextHeapRoot, notify, "Smoothsort: Trinkle Swap with Previous Heap Root");
        root = nextHeapRoot;

        // Drop the heap we just moved past from the (local) list.
        do {
            hsz.mask >>= 1;
            hsz.offset++;
        } while (!(hsz.mask & 1ULL));
    }
    siftIn(arr, root, hsz.offset, notify);
}

HeapSizes heapify(std::vector<int>& arr, int n, SortCallback& notify) {
    HeapSizes hsz;
    hsz.mask = 1;
    hsz.offset = 1; // first element treated as a trivial heap of order 1

    for (int i = 1; i < n; ++i) {
        bool willBeFusedLater;

        if (hsz.mask & 2ULL) {
            // Last two heap orders are consecutive Leonardo numbers:
            // fuse them into one heap of the next order, rooted at i.
            hsz.mask = (hsz.mask >> 2) | 1ULL;
            hsz.offset += 2;
        }
        else if (hsz.offset == 1) {
            hsz.mask = (hsz.mask << 1) | 1ULL;
            hsz.offset = 0;
        }
        else {
            hsz.mask = (hsz.mask << (hsz.offset - 1)) | 1ULL;
            hsz.offset = 1;
        }

        willBeFusedLater =
            ((hsz.mask & 2ULL) && (i + 1 < n)) ||
            (hsz.offset > 0 && (1ULL + static_cast<uint64_t>(i) + L[hsz.offset - 1] < static_cast<uint64_t>(n)));

        if (willBeFusedLater) {
            // Don't propagate the root leftward yet — this heap is
            // about to be absorbed into a larger one anyway.
            siftIn(arr, i, hsz.offset, notify);
        }
        else {
            interheapSift(arr, i, hsz, notify);
        }
    }
    return hsz;
}

void extract(std::vector<int>& arr, int n, HeapSizes hsz, SortCallback& notify) {
    for (int i = n - 1; i > 1; --i) {
        if (hsz.offset < 2) {
            // Last heap has order 0 or 1 (a single element): just drop
            // it from the list; the element is already in its final
            // sorted place.
            do {
                hsz.mask >>= 1;
                hsz.offset++;
            } while (!(hsz.mask & 1ULL));
        } else {
            int right = i - 1;
            int left = right - static_cast<int>(L[hsz.offset - 2]);
            hsz.mask &= ~1ULL; // remove the current heap from the list

            int children[2] = {left, right};
            for (int c = 0; c < 2; ++c) {
                hsz.mask = (hsz.mask << 1) | 1ULL;
                hsz.offset--;
                interheapSift(arr, children[c], hsz, notify);
            }
        }
    }
}
} // anonymous namespace

void smoothSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    if (n < 2) return;

    HeapSizes hsz = heapify(arr, n, notify);
    extract(arr, n, hsz, notify);
}