
#include "QuickSort.h"

QuickSort::QuickSort(unsigned count) {
	shuffle(count);
	reset();
}

void QuickSort::reset() {
	n = numbers.size();
    l = 0; h = n - 1;
    top = -1;
    j = l;

    stack.clear(); stack.resize(n);

    stack[++top] = l;
    stack[++top] = h;

	stats.reset();
}

bool QuickSort::step() {
    while (top >= 0) {
        h = stack[top--];
        l = stack[top--];

        int x = numbers[h];
        int i = (l - 1);

        while (j <= h - 1) {
            if (numbers[j] <= x) {
                i++;
                std::swap(numbers[i], numbers[j]);
                return false;
            }

            j++;
        }
        j = l;

        std::swap(numbers[i + 1], numbers[h]);

        int p = i + 1;

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }

	return true;
}


/*

#include "QuickSort.h"

QuickSort::QuickSort(unsigned count) {
    shuffle(count);
    reset();
}

void QuickSort::reset() {
    n = numbers.size();
    l = 0; h = n - 1;

    stats.reset();
}

bool QuickSort::step() {
    std::vector<float> stack(h - l + 1, 0.f);

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;

    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];

        // Set pivot element at its correct position
        // in sorted array

        int x = numbers[h];
        int i = (l - 1);

        for (int j = l; j <= h - 1; j++) {
            if (numbers[j] <= x) {
                i++;
                std::swap(numbers[i], numbers[j]);
            }
        }
        std::swap(numbers[i + 1], numbers[h]);

        int p = i + 1;

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }

    return true;
}

*/