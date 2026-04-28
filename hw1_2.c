#include <stdio.h>
#include <stdlib.h>

void reverse_array(int *arr, int N) {
    for (int i = 0; i < N / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[N - 1 - i];
        arr[N - 1 - i] = temp;
    }
}

void print_array(int *arr, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    
    int *arr = (int*)malloc(N * sizeof(int));
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    reverse_array(arr, N);
    print_array(arr, N);
    
    free(arr);
    return 0;
}