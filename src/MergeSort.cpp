
#include "MergeSort.h"

void MergeSort::merge(int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<float> L(n1, 0), R(n2, 0);

    for (int i = 0; i < n1; i++) {
        L[i] = numbers[l + i];
        stats.addAssigment();
    }
    for (int j = 0; j < n2; j++) {
        R[j] = numbers[m + 1 + j];
        stats.addAssigment();
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        stats.addComparison();
        stats.addAssigment();

        if (L[i] <= R[j]) {
            numbers[k] = L[i];
            i++;
        }
        else {
            numbers[k] = R[j];
            j++;
        }

        k++;

        DO_CHECKSTEP;
    }

    while (i < n1) {
        numbers[k] = L[i];
        stats.addAssigment();
        i++;
        k++;

        DO_CHECKSTEP;
    }

    while (j < n2) {
        numbers[k] = R[j];
        stats.addAssigment();
        j++;
        k++;

        DO_CHECKSTEP;
    }

    DO_PROGRESSIVE_CHECKSTEP;
}

void MergeSort::mergeSort(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void MergeSort::sorter() {
    DO_STARTED;

    mergeSort(0, numbers.size() - 1);

    DO_FINISHED;
}
