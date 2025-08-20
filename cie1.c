#include <stdio.h>
#include <time.h>

int main() {
    int fact = 1;
    int num;
    clock_t start, end;
    double time_taken;

    printf("Enter a number: ");
    scanf("%d", &num);

    start = clock();

    for(int i = 1; i <= num; i++) {
        fact = fact * i;
    }

    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Factorial: %d\n", fact);
    printf("Execution time: %f seconds\n", time_taken);

    return 0;
}
