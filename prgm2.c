#include <stdio.h>
#include <omp.h>

int main() {
    int n = 8;
    #pragma omp parallel for schedule(static,2)
    for (int i = 0; i < n; i++) {
        int tid = omp_get_thread_num();
        printf("Iteration %d handled by Thread %d\n", i, tid);
    }
    return 0;
}

#gcc schedule_static.c -fopenmp -o schedule_static
#./schedule_static
