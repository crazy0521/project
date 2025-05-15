// Multithreading : matrix multiplication ,multiple operations (add , sub , multiple, div) using Multithreading

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10

int A[MAX][MAX], B[MAX][MAX];
int rowA, colA, rowB, colB;

typedef struct {
    int row;
    int col;
} Position;

void *multiply(void *arg) {
    Position *pos = (Position *)arg;
    int i, sum = 0;

    for (i = 0; i < colA; i++) {
        sum += A[pos->row][i] * B[i][pos->col];
    }

    int *result = malloc(sizeof(int));
    *result = sum;

    pthread_exit(result);
}

int main() {
    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &rowA, &colA);
    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &rowB, &colB);

    if (colA != rowB) {
        printf("Matrix multiplication not possible!\n");
        return -1;
    }

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < rowA; i++)
        for (int j = 0; j < colA; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < rowB; i++)
        for (int j = 0; j < colB; j++)
            scanf("%d", &B[i][j]);

    pthread_t threads[MAX * MAX];
    Position positions[MAX * MAX];
    int result[MAX][MAX];
    int thread_count = 0;

    // Create threads for each element in result matrix
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            positions[thread_count].row = i;
            positions[thread_count].col = j;
            pthread_create(&threads[thread_count], NULL, multiply, &positions[thread_count]);
            thread_count++;
        }
    }

    // Collect results from each thread
    for (int i = 0; i < thread_count; i++) {
        int *value;
        pthread_join(threads[i], (void **)&value);
        int r = positions[i].row;
        int c = positions[i].col;
        result[r][c] = *value;
        free(value);
    }

    // Display Result
    printf("\nResultant Matrix:\n");
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}










// multiple operations using Multithreading

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Operands;

void *add(void *args) {
    Operands *op = (Operands *)args;
    int *res = malloc(sizeof(int));
    *res = op->a + op->b;
    pthread_exit(res);
}

void *subtract(void *args) {
    Operands *op = (Operands *)args;
    int *res = malloc(sizeof(int));
    *res = op->a - op->b;
    pthread_exit(res);
}

void *multiply(void *args) {
    Operands *op = (Operands *)args;
    int *res = malloc(sizeof(int));
    *res = op->a * op->b;
    pthread_exit(res);
}

void *divide(void *args) {
    Operands *op = (Operands *)args;
    float *res = malloc(sizeof(float));
    if (op->b == 0) {
        printf("Division by zero error.\n");
        *res = 0.0;
    } else {
        *res = (float)op->a / op->b;
    }
    pthread_exit(res);
}

int main() {
    pthread_t tid1, tid2, tid3, tid4;
    Operands op;

    printf("Enter two integers: ");
    scanf("%d %d", &op.a, &op.b);

    int *sum, *diff, *prod;
    float *quot;

    pthread_create(&tid1, NULL, add, &op);
    pthread_create(&tid2, NULL, subtract, &op);
    pthread_create(&tid3, NULL, multiply, &op);
    pthread_create(&tid4, NULL, divide, &op);

    pthread_join(tid1, (void **)&sum);
    pthread_join(tid2, (void **)&diff);
    pthread_join(tid3, (void **)&prod);
    pthread_join(tid4, (void **)&quot);

    printf("\nResults:\n");
    printf("Addition: %d + %d = %d\n", op.a, op.b, *sum);
    printf("Subtraction: %d - %d = %d\n", op.a, op.b, *diff);
    printf("Multiplication: %d * %d = %d\n", op.a, op.b, *prod);
    printf("Division: %d / %d = %.2f\n", op.a, op.b, *quot);

    // Free dynamically allocated memory
    free(sum);
    free(diff);
    free(prod);
    free(quot);

    return 0;
}
