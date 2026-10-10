#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };

    for (int idx = 0; idx < 7; idx++) {
        int N = sizes[idx];
        clock_t start, end;

        int* a = (int*)malloc(sizeof(int) * (size_t)N * (size_t)N);
        int* b = (int*)malloc(sizeof(int) * (size_t)N * (size_t)N);
        int* c = (int*)malloc(sizeof(int) * (size_t)N * (size_t)N);

        if (!a || !b || !c) {
            printf("Memory error at N=%d\n", N);
            free(a); free(b); free(c);
            continue;
        }

        srand((unsigned int)time(NULL));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i * N + j] = rand() % 100 + 1;

        srand((unsigned int)time(NULL) + 1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                b[i * N + j] = rand() % 100 + 1;

        start = clock();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int elem_c = 0;
                for (int r = 0; r < N; r++) {
                    elem_c += a[i * N + r] * b[r * N + j];
                }
                c[i * N + j] = elem_c;
            }
        }

        end = clock();
        double time_sec = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("N = %-6d | Time: %.6f sec\n", N, time_sec);

        free(a); free(b); free(c);
    }
    return 0;
}