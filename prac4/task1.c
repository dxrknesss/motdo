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

int *experiment(bool (*eventSimulation)()) {
  int *results = malloc(sizeof(int) * 2);
  for (int i = 0; i < 2; i++)
    results[i] = 0;

  for (int i = 0; i < 10000; i++) {
    bool eventHappened = (*eventSimulation)();
    results[0] += eventHappened;
    results[1] += !eventHappened;
  }
  return results;
}

bool simulateOneEvent() { return simulateRandomEventWithProbability(0.25); }

bool simulateMultipleEvents() {
  return simulateRandomEventWithProbability(0.25) &&
         simulateRandomEventWithProbability(0.4) &&
         simulateRandomEventWithProbability(0.15) &&
         simulateRandomEventWithProbability(0.2);
}

void simulateAndPrintForOneEvent() {
  int *results = experiment((*simulateOneEvent));
  printf("Results for a single event:\nHappened: %d\nNot happened: %d\n",
         results[0], results[1]);
  free(results);
}

void simulateAndPrintForMultipleEvents() {
  int *results = experiment((*simulateMultipleEvents));
  printf("Results for a multiple events:\nHappened: %d\nNot happened: %d\n",
         results[0], results[1]);
  free(results);
}

int main() {
  srand(getpid());
  simulateAndPrintForOneEvent();
  simulateAndPrintForMultipleEvents();
}
