#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Matrix {
  int rows;
  int cols;
  double **matrix;
};

struct Matrix *initializeMatrix(int rows, int cols) {
  struct Matrix *newMatrix = malloc(sizeof(struct Matrix));
  newMatrix->rows = rows;
  newMatrix->cols = cols;

  newMatrix->matrix = malloc(sizeof(double *) * rows);
  for (int i = 0; i < newMatrix->rows; i++) {
    newMatrix->matrix[i] = malloc(sizeof(double) * cols);
    for (int j = 0; j < newMatrix->cols; j++) {
      newMatrix->matrix[i][j] = 0;
    }
  }

  return newMatrix;
}

void fillMatrix(struct Matrix *matrixToFill) {
  double **matrixArray = matrixToFill->matrix;
  matrixArray[0][0] = 0.3;
  matrixArray[0][1] = 0.5;
  matrixArray[0][2] = 0.1;
  matrixArray[0][3] = 0.1;

  matrixArray[1][0] = 0.4;
  matrixArray[1][1] = 0.2;
  matrixArray[1][2] = 0.2;
  matrixArray[1][3] = 0.2;

  matrixArray[2][0] = 0.1;
  matrixArray[2][1] = 0.1;
  matrixArray[2][2] = 0.6;
  matrixArray[2][3] = 0.2;

  matrixArray[3][0] = 0.2;
  matrixArray[3][1] = 0.4;
  matrixArray[3][2] = 0.3;
  matrixArray[3][3] = 0.1;
}

void printMatrix(struct Matrix *matrixToPrint) {
  for (int i = 0; i < matrixToPrint->rows; i++) {
    for (int j = 0; j < matrixToPrint->cols; j++) {
      printf("%.9f ", matrixToPrint->matrix[i][j]);
    }
    printf("\n");
  }
}

void freeMatrixMemory(struct Matrix *matrixToFree) {
  for (int i = 0; i < matrixToFree->rows; i++) {
    free(matrixToFree->matrix[i]);
  }
  free(matrixToFree->matrix);

  free(matrixToFree);
}

struct Matrix *multiplyMatrix(struct Matrix *firstMatrix,
                              struct Matrix *secondMatrix) {
  if (firstMatrix->rows != secondMatrix->cols) {
    return NULL;
  }

  struct Matrix *outputMatrix =
      initializeMatrix(firstMatrix->rows, secondMatrix->cols);

  for (int i = 0; i < firstMatrix->rows; i++) {
    for (int j = 0; j < secondMatrix->cols; j++) {
      for (int k = 0; k < secondMatrix->rows; k++) {
        outputMatrix->matrix[i][j] +=
            firstMatrix->matrix[i][k] * secondMatrix->matrix[k][j];
      }
    }
  }

  return outputMatrix;
}

void markovChainStep(struct Matrix *matrix, int step) {
  *matrix = *multiplyMatrix(matrix, matrix);
  if (matrix == NULL) {
    perror("There was an error with matrix multiplication!");
    return;
  }

  printf("P^%d\n", step);
  printMatrix(matrix);
  printf("\n");
}

void executeNMarkovChainSteps(struct Matrix *matrix, int steps) {
  for (int i = 0; i < steps; i++) {
    markovChainStep(matrix, i + 2);
  }
}

int main() {
  struct Matrix *team2Matrix = initializeMatrix(4, 4);
  fillMatrix(team2Matrix);
  printf("P\n");
  printMatrix(team2Matrix);

  executeNMarkovChainSteps(team2Matrix, 5);

  freeMatrixMemory(team2Matrix);
}
