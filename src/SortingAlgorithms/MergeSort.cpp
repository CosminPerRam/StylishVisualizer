
#include "SortingAlgorithms/MergeSort.h"

void MergeSort::merge(const int l, const int m, const int r)
{
    DO_CHECKEXIT;

    const int n1 = m - l + 1;
    const int n2 = r - m;

    std::vector<unsigned> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = numbers[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = numbers[m + 1 + j];

    stats.addAssigments(n1 + n2);

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        stats.addComparisons();
        if (L[i] <= R[j])
            numbers[k] = L[i++];
        else
            numbers[k] = R[j++];
        stats.addAssigments();

        DO_PUT_CURSOR_AT(k++);
        DO_CHECKSTEP;
    }

    while (i < n1) {
        numbers[k] = L[i];
        stats.addAssigments();
        DO_PUT_CURSOR_AT(k);
        i++;
        k++;

        DO_CHECKSTEP;
    }

    while (j < n2) {
        numbers[k] = R[j];
        stats.addAssigments();
        DO_PUT_CURSOR_AT(k);
        j++;
        k++;

        DO_CHECKSTEP;
    }
}

void MergeSort::mergeSort(int l, int r)
{
    if (l < r)
    {
        const int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void MergeSort::sorter() {
    DO_STARTED;

    mergeSort(0, int(numbers.size() - 1));

    DO_FINISHED;
}

const char* MergeSort::getDescription() {
    return "It divides the input array into two halves, calls itself for the two halves, and then it merges the two sorted halves.";
}
