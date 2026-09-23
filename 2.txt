#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 50000


void fill_random(int* a, int n) {
    for (int i = 0; i < n; i++) a[i] = rand();
}

void fill_ascending(int* a, int n) {
    for (int i = 0; i < n; i++) a[i] = i;
}

void fill_descending(int* a, int n) {
    for (int i = 0; i < n; i++) a[i] = n - i;
}

void fill_half(int* a, int n) {
    for (int i = 0; i < n / 2; i++) a[i] = i;
    for (int i = n / 2; i < n; i++) a[i] = rand();
}


int compare(const void* x, const void* y) {
    int a = *(const int*)x;
    int b = *(const int*)y;
    return (a > b) - (a < b);
}


void shell_sort(int* items, int count) {
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (x < items[j]); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}


void qs(int* items, int left, int right) {
    int i, j;
    int x, y;
    i = left; j = right;
    x = items[(left + right) / 2];
    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;
        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}


void run_case(const char* title, void (*fill)(int*, int), int* orig, int* work) {
    clock_t s, e;

    printf("--- %s ---\n", title);
    fill(orig, N);

    memcpy(work, orig, N * sizeof(int));
    s = clock();
    shell_sort(work, N);
    e = clock();
    printf("Shell: %.6f\n", (double)(e - s) / CLOCKS_PER_SEC);

    memcpy(work, orig, N * sizeof(int));
    s = clock();
    qs(work, 0, N - 1);
    e = clock();
    printf("QS:    %.6f\n", (double)(e - s) / CLOCKS_PER_SEC);

    memcpy(work, orig, N * sizeof(int));
    s = clock();
    qsort(work, N, sizeof(int), compare);
    e = clock();
    printf("Std:   %.6f\n\n", (double)(e - s) / CLOCKS_PER_SEC);
}

int main(void) {
    int* orig = (int*)malloc(N * sizeof(int));
    int* work = (int*)malloc(N * sizeof(int));
    if (!orig || !work) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    run_case("1. Random", fill_random, orig, work);
    run_case("2. Ascending", fill_ascending, orig, work);
    run_case("3. Descending", fill_descending, orig, work);
    run_case("4. Half", fill_half, orig, work);

    free(orig);
    free(work);
    return 0;
}