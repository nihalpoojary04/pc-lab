#include <stdio.h>
#include <omp.h>

int main() {
    int num;
    unsigned long long fact = 1;
    double start, end, time_taken;

    printf("Enter a number: ");
    scanf("%d", &num);

    start = omp_get_wtime();

    #pragma omp parallel for reduction(*:fact)
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }

    end = omp_get_wtime();

    time_taken = end - start;

    printf("Factorial: %llu\n", fact);
    printf("Execution time: %f seconds\n", time_taken);

    return 0;
}
