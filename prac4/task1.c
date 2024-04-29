#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float roundToNDigits(int numberToRound, int digits) {
  int denominator = pow(10, digits);
  numberToRound *= denominator;
  numberToRound = round(numberToRound);
  numberToRound /= denominator;
  return numberToRound;
}

bool simulateRandomEventWithProbability(float probability) {
  float denominator = 1 / probability;
  roundToNDigits(denominator, 1);
  return rand() <= RAND_MAX / denominator;
}

int *experiment(float probability) {
  int *results = malloc(2 * sizeof(int));
  bool eventHappened;
  for (int i = 0; i < 100; i++) {
    eventHappened = simulateRandomEventWithProbability(probability);
    results[0] += eventHappened;
    results[1] += !eventHappened;
  }
  return results;
}

int main() {
  srand(getpid());
  int *results = experiment(0.25);
  printf("Ones: %d\n Zeroes: %d\n", results[0], results[1]);
  free(results);
}
