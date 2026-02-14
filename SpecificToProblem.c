#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>

// ==================== Dynamic memory allocation ====================
State* Allocate_State() {
    State *state = (State *)malloc(sizeof(State));
    if (!state) Warning_Memory_Allocation();

    state->lights = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; ++i)
        state->lights[i] = (int *)malloc(N * sizeof(int));

    return state;
}

// ==================== Memory release ====================
void Free_State(State *state) {
    for (int i = 0; i < N; ++i)
        free(state->lights[i]);
    free(state->lights);
    free(state);
}

// ==================== Create an initial state ====================
State* Create_State(int use_random) {
    State *state = Allocate_State();

    if (use_random) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                state->lights[i][j] = rand() % 2;
    } else {
        printf("Enter the matrix (%dx%d) row by row (0 or 1):\n", N, N);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                scanf("%d", &state->lights[i][j]);
    }

    return state;
}

// ==================== Print status on screen ====================
void Print_State(const State *const state) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            printf("%d ", state->lights[i][j]);
        printf("\n");
    }
}

int Get_Action_Enum_Index(int action) {
    if (N == 4) {
        return action; // PRESS_0_0 ... PRESS_3_3
    } else if (N == 8) {
        return 16 + action; // PRESS_0_0_8 ... PRESS_7_7_8
    } else if (N == 10) {
        return 80 + action; // PRESS_0_0_10 ... PRESS_9_9_10
    } else {
        return -1; // Unsupported size
    }
}

int Get_Action_From_Enum_Index(int enum_index) {
    if (N == 4) {
        return enum_index;
    } else if (N == 8) {
        return enum_index - 16;
    } else if (N == 10) {
        return enum_index - 80;
    } else {
        return -1;
    }
}


// ==================== Print action (int version) ====================

void Print_Action(const int action_enum_index) {
    int action = Get_Action_From_Enum_Index(action_enum_index);
    int x = action / N;
    int y = action % N;
    printf("Press (%d, %d)", x, y);
}


// ==================== Transition model (next state production) ====================
int Result(const State *const parent_state, const int action, Transition_Model *const trans_model) {
    int x = action / N;
    int y = action % N;

    State *new_state = Allocate_State();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            new_state->lights[i][j] = parent_state->lights[i][j];

    int dx[] = {0, 1, -1, 0, 0};
    int dy[] = {0, 0, 0, 1, -1};

    for (int k = 0; k < 5; ++k) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx >= 0 && ny >= 0 && nx < N && ny < N)
            new_state->lights[nx][ny] = 1 - new_state->lights[nx][ny];
    }

    trans_model->new_state = *new_state;
    trans_model->step_cost = 1;
    return TRUE;
}

// ==================== Calculate Heuristic ====================
float Compute_Heuristic_Function(const State *const state, const State *const goal) {
    float count = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (state->lights[i][j] == 1)
                count++;
    return count;
}

// ==================== Goal test ====================
int Goal_Test(const State *const state, const State *const goal_state) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (state->lights[i][j] != 0)
                return 0;
    return 1;
}
