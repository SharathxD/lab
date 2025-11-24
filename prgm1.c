#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void parallelMergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(a, l, m);
            #pragma omp section
            parallelMergeSort(a, m + 1, r);
        }
        merge(a, l, m, r);
    }
}

int main() {
    int n = 8;
    int a[] = {38, 27, 43, 3, 9, 82, 10, 5};
    double start, end;

    int seq[n];
    for (int i = 0; i < n; i++) seq[i] = a[i];
    start = omp_get_wtime();
    mergeSort(seq, 0, n - 1);
    end = omp_get_wtime();
    printf("Sequential time: %f\n", end - start);

    int par[n];
    for (int i = 0; i < n; i++) par[i] = a[i];
    start = omp_get_wtime();
    parallelMergeSort(par, 0, n - 1);
    end = omp_get_wtime();
    printf("Parallel time: %f\n", end - start);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", par[i]);
    printf("\n");

    return 0;
}


#gcc mergesort.c -fopenmp -o mergesort
#./mergesort
