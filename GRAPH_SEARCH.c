#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Adding for Calculate the Time
#include "GRAPH_SEARCH.h"
#include "data_types.h"

int N;
int ACTIONS_NUMBER;

int main() {
    clock_t start_time = clock();  // Start Time

    Node root, *goal;
    State *goal_state = NULL;
    enum METHODS method;
    int Max_Level, level;
    float alpha;

    // ==================== Get the matrix size from the user =====================
    printf("Select matrix size: 1) 4x4  2) 8x8  3) 10x10: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) N = 4;
    else if (choice == 2) N = 8;
    else if (choice == 3) N = 10;
    else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }

    ACTIONS_NUMBER = N * N;

    // ==================== Manuel or Random Matrix? =====================
    printf("Use random matrix? (1 = Yes, 0 = No): ");
    int use_random;
    scanf("%d", &use_random);

    // ==================== Algorithm Selection =====================
    printf("1 --> Breast-First Search\n");
    printf("2 --> Uniform-Cost Search\n");
    printf("3 --> Depth-First Search\n");
    printf("4 --> Depth-Limited Search\n");
    printf("5 --> Iterative Deepening Search\n");
    printf("6 --> Greedy Search\n");
    printf("7 --> A* Search\n");
    printf("8 --> Generalized A* Search\n");
    printf("Select a method to solve the problem: ");
    scanf("%d", &method);

    if (method == DepthLimitedSearch) {
        printf("Enter maximum level for depth-limited search : ");
        scanf("%d", &Max_Level);
    }

    if (method == GeneralizedAStarSearch) {
        printf("Enter value of alpha for Generalized A* Search : ");
        scanf("%f", &alpha);
    }

    // ==================== Initial State =====================
    root.parent = NULL;
    root.path_cost = 0;
    root.action = NO_ACTION;
    root.Number_of_Child = 0;

    printf("======== SELECTION OF INITIAL STATE =============== \n");
    root.state = *(Create_State(use_random));
    if(use_random){
        Print_State(&(root.state)); // Ğrint the initial state
    }
   
    if (PREDETERMINED_GOAL_STATE) {
        printf("======== SELECTION OF GOAL STATE =============== \n");
        goal_state = Create_State(use_random);
    }

    if (method == GreedySearch || method == AStarSearch || method == GeneralizedAStarSearch) {
        root.state.h_n = Compute_Heuristic_Function(&(root.state), goal_state);
        if (PREDETERMINED_GOAL_STATE)
            goal_state->h_n = 0;
    }

    // ==================== Search Algorithm Call =====================
    switch (method) {
        case BreastFirstSearch:
        case GreedySearch:
            goal = First_GoalTest_Search_TREE(method, &root, goal_state);
            break;

        case DepthFirstSearch:
        case DepthLimitedSearch:
            goal = DepthType_Search_TREE(method, &root, goal_state, Max_Level);
            break;

        case IterativeDeepeningSearch:
            for (level = 0; TRUE; level++) {
                goal = DepthType_Search_TREE(method, &root, goal_state, level);
                if (goal != FAILURE) {
                    printf("The goal is found in level %d.\n", level);
                    break;
                }
            }
            break;

        case UniformCostSearch:
        case AStarSearch:
        case GeneralizedAStarSearch:
            goal = First_InsertFrontier_Search_TREE(method, &root, goal_state, alpha);
            break;

        default:
            printf("ERROR: Unknown method.\n");
            exit(-1);
    }

        // ==================== Calculate the Time and Print =====================
    clock_t end_time = clock();  // Stop the Tİme
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %.3f seconds\n", duration);  // Print
    
    // ==================== Solution Notation =====================
    Show_Solution_Path(goal);

    return 0;
}
