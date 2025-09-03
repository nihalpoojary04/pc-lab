#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    int root = (int)sqrt((double)num);
    for (int i = 3; i <= root; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;

    printf("Enter the upper limit (n) to find prime numbers: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    if (n < 2) {
        printf("There are no prime numbers up to %d\n", n);
        return 0;
    }

    printf("\nFinding prime numbers from 1 to %d...\n", n);

    double start_time = omp_get_wtime();
    int sequential_prime_count = 0;
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            sequential_prime_count++;
        }
    }
    double time_seq = omp_get_wtime() - start_time;
    printf("\nSequential: Found %d primes in %.6f seconds\n", sequential_prime_count, time_seq);

    start_time = omp_get_wtime();
    int parallel_prime_count = 0;

    #pragma omp parallel for reduction(+:parallel_prime_count) schedule(dynamic)
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            parallel_prime_count++;
        }
    }
    double time_par = omp_get_wtime() - start_time;
    printf("Parallel:   Found %d primes in %.6f seconds\n", parallel_prime_count, time_par);

    if (parallel_prime_count == sequential_prime_count) {
        if (time_par > 0) {
            printf("\nSpeedup: %.2fx\n", time_seq / time_par);
        } else {
            printf("\nSpeedup: Time too short to calculate speedup accurately.\n");
        }
    } else {
        printf("\nMismatch in results! Sequential: %d, Parallel: %d\n", sequential_prime_count, parallel_prime_count);
    }

    return 0;
}
