#include <stdio.h>
#include <stdlib.h>

int** allocate_matrix(int rows, int cols) {
    int **matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void fill_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int** transpose_matrix(int **matrix, int rows, int cols) {
    int **transpose = allocate_matrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }
    return transpose;
}

void deallocate_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int **matrix = allocate_matrix(N, M);
    fill_matrix(matrix, N, M);
    
    int **transpose = transpose_matrix(matrix, N, M);
    print_matrix(transpose, M, N);
    
    deallocate_matrix(matrix, N);
    deallocate_matrix(transpose, M);
    
    return 0;
}