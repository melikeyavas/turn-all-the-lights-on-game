#ifndef DATA_TYPES_H
#define DATA_TYPES_H

extern int N;

// ====== WRITE YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) DATA TYPES =======

enum ACTIONS {
    // ==== 4x4 ====
    PRESS_0_0, PRESS_0_1, PRESS_0_2, PRESS_0_3,
    PRESS_1_0, PRESS_1_1, PRESS_1_2, PRESS_1_3,
    PRESS_2_0, PRESS_2_1, PRESS_2_2, PRESS_2_3,
    PRESS_3_0, PRESS_3_1, PRESS_3_2, PRESS_3_3,

    // ==== 8x8 ====
    PRESS_4x4_END, // separator
    PRESS_0_0_8, PRESS_0_1_8, PRESS_0_2_8, PRESS_0_3_8, PRESS_0_4_8, PRESS_0_5_8, PRESS_0_6_8, PRESS_0_7_8,
    PRESS_1_0_8, PRESS_1_1_8, PRESS_1_2_8, PRESS_1_3_8, PRESS_1_4_8, PRESS_1_5_8, PRESS_1_6_8, PRESS_1_7_8,
    PRESS_2_0_8, PRESS_2_1_8, PRESS_2_2_8, PRESS_2_3_8, PRESS_2_4_8, PRESS_2_5_8, PRESS_2_6_8, PRESS_2_7_8,
    PRESS_3_0_8, PRESS_3_1_8, PRESS_3_2_8, PRESS_3_3_8, PRESS_3_4_8, PRESS_3_5_8, PRESS_3_6_8, PRESS_3_7_8,
    PRESS_4_0_8, PRESS_4_1_8, PRESS_4_2_8, PRESS_4_3_8, PRESS_4_4_8, PRESS_4_5_8, PRESS_4_6_8, PRESS_4_7_8,
    PRESS_5_0_8, PRESS_5_1_8, PRESS_5_2_8, PRESS_5_3_8, PRESS_5_4_8, PRESS_5_5_8, PRESS_5_6_8, PRESS_5_7_8,
    PRESS_6_0_8, PRESS_6_1_8, PRESS_6_2_8, PRESS_6_3_8, PRESS_6_4_8, PRESS_6_5_8, PRESS_6_6_8, PRESS_6_7_8,
    PRESS_7_0_8, PRESS_7_1_8, PRESS_7_2_8, PRESS_7_3_8, PRESS_7_4_8, PRESS_7_5_8, PRESS_7_6_8, PRESS_7_7_8,

    // ==== 10x10 ====
    PRESS_8x8_END, // separator
    PRESS_0_0_10, PRESS_0_1_10, PRESS_0_2_10, PRESS_0_3_10, PRESS_0_4_10, PRESS_0_5_10, PRESS_0_6_10, PRESS_0_7_10, PRESS_0_8_10, PRESS_0_9_10,
    PRESS_1_0_10, PRESS_1_1_10, PRESS_1_2_10, PRESS_1_3_10, PRESS_1_4_10, PRESS_1_5_10, PRESS_1_6_10, PRESS_1_7_10, PRESS_1_8_10, PRESS_1_9_10,
    PRESS_2_0_10, PRESS_2_1_10, PRESS_2_2_10, PRESS_2_3_10, PRESS_2_4_10, PRESS_2_5_10, PRESS_2_6_10, PRESS_2_7_10, PRESS_2_8_10, PRESS_2_9_10,
    PRESS_3_0_10, PRESS_3_1_10, PRESS_3_2_10, PRESS_3_3_10, PRESS_3_4_10, PRESS_3_5_10, PRESS_3_6_10, PRESS_3_7_10, PRESS_3_8_10, PRESS_3_9_10,
    PRESS_4_0_10, PRESS_4_1_10, PRESS_4_2_10, PRESS_4_3_10, PRESS_4_4_10, PRESS_4_5_10, PRESS_4_6_10, PRESS_4_7_10, PRESS_4_8_10, PRESS_4_9_10,
    PRESS_5_0_10, PRESS_5_1_10, PRESS_5_2_10, PRESS_5_3_10, PRESS_5_4_10, PRESS_5_5_10, PRESS_5_6_10, PRESS_5_7_10, PRESS_5_8_10, PRESS_5_9_10,
    PRESS_6_0_10, PRESS_6_1_10, PRESS_6_2_10, PRESS_6_3_10, PRESS_6_4_10, PRESS_6_5_10, PRESS_6_6_10, PRESS_6_7_10, PRESS_6_8_10, PRESS_6_9_10,
    PRESS_7_0_10, PRESS_7_1_10, PRESS_7_2_10, PRESS_7_3_10, PRESS_7_4_10, PRESS_7_5_10, PRESS_7_6_10, PRESS_7_7_10, PRESS_7_8_10, PRESS_7_9_10,
    PRESS_8_0_10, PRESS_8_1_10, PRESS_8_2_10, PRESS_8_3_10, PRESS_8_4_10, PRESS_8_5_10, PRESS_8_6_10, PRESS_8_7_10, PRESS_8_8_10, PRESS_8_9_10,
    PRESS_9_0_10, PRESS_9_1_10, PRESS_9_2_10, PRESS_9_3_10, PRESS_9_4_10, PRESS_9_5_10, PRESS_9_6_10, PRESS_9_7_10, PRESS_9_8_10, PRESS_9_9_10
};
 // All Actions


typedef struct State {
    int **lights; // 0 = Close, 1 = Open
    float h_n;        // Heuristic
} State;


// ================== YOU DO NOT NEED TO CHANGE THIS PART ======================

enum METHODS
{
	BreastFirstSearch = 1,   UniformCostSearch = 2,        DepthFirstSearch = 3,    
	DepthLimitedSearch= 4,   IterativeDeepeningSearch = 5, GreedySearch = 6,
    AStarSearch = 7, GeneralizedAStarSearch = 8  
};

// This struct is used to determine a new state and action in transition model
typedef struct Transition_Model
{
    State new_state;
    float step_cost;
}Transition_Model;

typedef struct Node
{
    State state;
    float path_cost;
    enum ACTIONS action; //The action applied to the parent to generate this node
    struct Node *parent;
    int Number_of_Child; // required for depth-first search algorithms
}Node;

typedef struct Queue  // Used for frontier
{
    Node *node;
    struct Queue *next;
}Queue;



#endif
