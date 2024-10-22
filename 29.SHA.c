#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>n
#define LANES 25
#define CAPACITY_LANES 8
#define LANE_SIZE 64

bool all_lanes_nonzero(unsigned long long *state, int capacity_lanes) {
    int i;
    for (i = 0; i < capacity_lanes; i++) {
        if (state[i] == 0) {
            return false;
        }
    }
    return true;
}

void update_lane(unsigned long long *lane) {
    *lane = rand() % 100;
    if (*lane == 0) *lane = 1;
}

int main() {
    unsigned long long state[LANES] = {0};
    int steps = 0;
    int i;

    srand(time(NULL));

    while (!all_lanes_nonzero(state, CAPACITY_LANES)) {
        for (i = 0; i < CAPACITY_LANES; i++) {
            update_lane(&state[i]);
        }
        steps++;
    }

    printf("All capacity lanes became non-zero after %d steps.\n", steps);

    return 0;
}

