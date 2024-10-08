#include <stdio.h>
#include <stdlib.h>

#define LIMITAR 10
#define MAX_VALUES 1000
#define FILENAME "interno_inversamente_ordenados.txt"

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void hybridSort(int arr[], int left, int right) {
    if (left < right) {
        if (right - left + 1 <= LIMITAR) {
            insertionSort(arr, left, right);
        } else {
            int middle = left + (right - left) / 2;
            hybridSort(arr, left, middle);
            hybridSort(arr, middle + 1, right);
            merge(arr, left, middle, right);
        }
    }
}

int main() {
    int arr[MAX_VALUES];
    int n = 0;

    // Abrir o arquivo para leitura
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 1;
    }

    // Ler os valores do arquivo
    while (fscanf(fp, "%d", &arr[n]) != EOF && n < MAX_VALUES) {
        n++;
    }

    // Fechar o arquivo
    fclose(fp);

    hybridSort(arr, 0, n-1);

    printf("Array após a ordenação:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
