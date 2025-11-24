#include <stdio.h>
#include <omp.h>

int fib(int n) {
    if (n < 2) return n;
    int x, y;
    #pragma omp task shared(x)
    x = fib(n - 1);
    #pragma omp task shared(y)
    y = fib(n - 2);
    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 10;
    int result;
    double start, end;
    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    end = omp_get_wtime();
    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Execution Time: %f seconds\n", end - start);
    return 0;
}

#gcc fib_task.c -fopenmp -o fib_task
#./fib_task
