#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float eventProbabilities[4] = {0.25, 0.4, 0.15, 0.2},
      prefixSum[5] = {0, 0.25, 0.65, 0.80, 1};

double generateRandomNumberInclusive() {
  return (double)rand() / (double)RAND_MAX; // generates number from 0 to 1
}

void simulateSingleEvent(int *results) {
  bool eventHappened = generateRandomNumberInclusive() <= 0.25;
  results[0] += eventHappened;
  results[1] += !eventHappened;
}

void simulateMultipleEvents(int *results) {
  for (int i = 0; i < 4; i++) {
    double randNumber = generateRandomNumberInclusive();
    results[i] += randNumber >= prefixSum[i] && randNumber <= prefixSum[i + 1];
  }
}

int *experiment(void (*eventSimulation)(int *)) {
  int *results = malloc(sizeof(int) * 4);
  for (int i = 0; i < 4; i++) {
    results[i] = 0;
  }

  for (int i = 0; i < 10000; i++) {
    (*eventSimulation)(results);
  }
  return results;
}

void simulateAndPrintForOneEvent() {
  int *results;
  results = experiment((*simulateSingleEvent));
  printf("Results for a single event:\nHappened: %d\nNot happened: %d\n",
         results[0], results[1]);
  free(results);
}

void simulateAndPrintForMultipleEvents() {
  int *results = experiment((*simulateMultipleEvents));
  printf("Results for a multiple events:\nEvent 1: %d\nEvent 2: %d\nEvent 3: "
         "%d\nEvent 4: %d\n",
         results[0], results[1], results[2], results[3]);
  free(results);
}

int main() {
  srand(getpid());
  simulateAndPrintForOneEvent();
  simulateAndPrintForMultipleEvents();
}
