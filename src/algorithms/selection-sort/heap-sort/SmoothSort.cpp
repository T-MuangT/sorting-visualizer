#include "SmoothSort.hpp"
#include <algorithm>

namespace {

// Helper to wrap comparisons with the visualization callback
inline bool safeCompare(const std::vector<int>& arr, int i, int j, SortCallback& notify, const std::string& desc) {
    if (notify) notify(SortEvent::Compare, i, j, desc);
    return arr[i] > arr[j];
}

// Helper to wrap swaps with the visualization callback
inline void safeSwap(std::vector<int>& arr, int i, int j, SortCallback& notify, const std::string& desc) {
    std::swap(arr[i], arr[j]);
    if (notify) notify(SortEvent::Swap, i, j, desc);
}

void sift(std::vector<int>& arr, int r, int b_val, int c_val, SortCallback& notify) {
    int rt = r;
    while (b_val >= 3) {
        int r2 = rt - b_val + c_val + 1;
        int r1 = rt - 1;

        int large = rt;
        if (safeCompare(arr, r1, rt, notify, "Smooth Sort: Compare child roots")) {
            large = r1;
        }
        if (safeCompare(arr, r2, large, notify, "Smooth Sort: Compare with Leonardo root")) {
            large = r2;
        }

        if (large == rt) {
            break;
        } else if (large == r1) {
            safeSwap(arr, rt, r1, notify, "Smooth Sort: Sift Swap Left");
            rt = r1;
            int temp = c_val;
            c_val = b_val - c_val - 1;
            b_val = temp;
        } else {
            safeSwap(arr, rt, r2, notify, "Smooth Sort: Sift Swap Right");
            rt = r2;
            b_val = c_val;
            c_val = rt - r2; // simplified tracker
        }
    }
}

void trinkle(std::vector<int>& arr, int r, unsigned long long p, int b_val, int c_val, SortCallback& notify) {
    while (p > 0) {
        while ((p & 1) == 0) {
            p >>= 1;
            int temp = c_val;
            c_val = b_val - c_val - 1;
            b_val = temp;
        }

        int r1 = r - b_val;
        if (p == 1 || !safeCompare(arr, r1, r, notify, "Smooth Sort: Trinkle Root Check")) {
            break;
        }

        p >>= 1;
        if (b_val == 1) {
            safeSwap(arr, r, r1, notify, "Smooth Sort: Trinkle Swap 1");
            r = r1;
        } else if (b_val >= 3) {
            int r2 = r - b_val + c_val + 1;
            int r3 = r - 1;
            if (safeCompare(arr, r3, r2, notify, "Smooth Sort: Trinkle Subtree Check") || 
                safeCompare(arr, r3, r1, notify, "Smooth Sort: Trinkle Subtree Check 2")) {
                safeSwap(arr, r, r3, notify, "Smooth Sort: Trinkle Swap Right");
                r = r3;
                int temp = c_val;
                c_val = b_val - c_val - 1;
                b_val = temp;
            } else {
                safeSwap(arr, r, r2, notify, "Smooth Sort: Trinkle Swap Left");
                r = r2;
                b_val = c_val;
            }
        }
    }
    sift(arr, r, b_val, c_val, notify);
}

void semitrinkle(std::vector<int>& arr, int r, unsigned long long p, int b_val, int c_val, SortCallback& notify) {
    int r1 = r - b_val + c_val + 1;
    if (safeCompare(arr, r1, r, notify, "Smooth Sort: Semitrinkle Check")) {
        safeSwap(arr, r, r1, notify, "Smooth Sort: Semitrinkle Swap");
        trinkle(std::ref(arr), r1, p, b_val, c_val, std::ref(notify));
    }
}

} // anonymous namespace

void smoothSort(std::vector<int>& arr, SortCallback notify) {
    int n = static_cast<int>(arr.size());
    if (n <= 1) return;

    unsigned long long p = 1;
    int b = 1;
    int c = 1;

    for (int q = 0; q < n; ++q) {
        if ((p & 7) == 3) {
            sift(arr, q, b, c, notify);
            p >>= 2;
            int temp = c;
            c = b - c - 1;
            b = temp;
            b += c + 1; // up operation
        } else if ((p & 3) == 1) {
            if (q + c < n) {
                sift(arr, q, b, c, notify);
            } else {
                trinkle(arr, q, p, b, c, notify);
            }
            while (b > 1) {
                p <<= 1;
                int temp = c;
                c = b - c - 1;
                b = temp;
            }
            p++;
            b = 1;
            c = 1;
        }
        p++;
    }

    trinkle(arr, n - 1, p, b, c, notify);

    for (int q = n - 1; q > 0; --q) {
        if (b == 1) {
            p >>= 1;
            int temp = b;
            b = c;
            c = temp - c - 1;
        } else if (b >= 3) {
            p--;
            int r1 = q - b;
            semitrinkle(arr, r1, p, b, c, notify);
            p <<= 1;
            p++;
            int temp = c;
            c = b - c - 1;
            b = temp;
            semitrinkle(arr, q - 1, p, b, c, notify);
            p <<= 1;
            p++;
            int temp2 = c;
            c = b - c - 1;
            b = temp2;
        }
    }
}