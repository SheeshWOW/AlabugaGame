#pragma once

typedef enum {
    Idle = 0,
    Walk = 1,
    Jump = 2,
} ActorState;

typedef enum {
    Down = 0,
    Right = 1,
    Left = 2,
    Up = 3,
} ActorDirection;

typedef struct {
    double x, y;
} MoveDirection;