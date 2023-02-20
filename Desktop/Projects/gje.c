#include <stdlib.h>
#include <stdio.h>

int **array_copy2d(int **src, int rows, int cols) {
    int **result = (int **)malloc(sizeof(int *) * rows);
    for (int row = 0; row < rows; row++) {
        result[row] = (int *)malloc(sizeof(int) * cols);
        for (int col = 0; col < cols; col++) {
            result[row][col] = src[row][col];
        }
    }
    return result;
}

void print_matrix(int **matrix, int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    }
}

void swap_rows(int **matrix, int r1, int r2, int cols) {
    int *temp = matrix[r1];
    matrix[r1] = matrix[r2];
    matrix[r2] = temp;
}

void scale_row(int **matrix, int r, int cols, double factor) {
    for (int c = 0; c < cols; c++) {
        matrix[r][c] = (int)(matrix[r][c] * factor);
    }
}

void add_rows(int **matrix, int r1, int r2, int cols, int factor) {
    for (int c = 0; c < cols; c++) {
        matrix[r1][c] += matrix[r2][c] * factor;
    }
}

void gauss_jordan_elimination(int **matrix, int rows, int cols) {
    int pivot_row = 0;
    for (int pivot_col = 0; pivot_col < cols; pivot_col++) {
        int max_row = pivot_row;
        for (int row = pivot_row + 1; row < rows; row++) {
            if (abs(matrix[row][pivot_col]) > abs(matrix[max_row][pivot_col])) {
                max_row = row;
            }
        }
        if (matrix[max_row][pivot_col] == 0) {
            continue;
        }
        if (max_row != pivot_row) {
            swap_rows(matrix, pivot_row, max_row, cols);
        }
        scale_row(matrix, pivot_row, cols, 1.0 / matrix[pivot_row][pivot_col]);
        for (int row = 0; row < rows; row++) {
            if (row != pivot_row) {
                add_rows(matrix, row, pivot_row, cols, -matrix[row][pivot_col]);
            }
        }
        pivot_row++;
    }
}

int main() {
    int rows, cols;
    printf("How many rows? ");
    scanf("%d", &rows);
    printf("How many cols? ");
    scanf("%d", &cols);

    int **my_array = (int **)malloc(rows * sizeof(int *));
    for (int r = 0; r < rows; r++) {
        my_array[r] = (int *)malloc(cols * sizeof(int));
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("Enter at row %d col %d: ", r, c);
            scanf("%d", &my_array[r][c]);
        }
    }

    printf("\nOriginal matrix:\n");
    print_matrix(my_array, rows, cols);

    int **result = array_copy2d(my_array, rows, cols);
    gauss_jordan_elimination(result, rows, cols);

    printf("\nReduced row echelon form:\n");
    print_matrix(result, rows, cols);


free (result);
}
