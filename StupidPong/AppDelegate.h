//
//  AppDelegate.h
//  StupidPong
//
//  Created by Kyle Roucis on 4/21/19.
//

#pragma once

#import <Cocoa/Cocoa.h>

#define     STATE_BUFFER_SIZE   3

typedef enum
{
    NONE = 0,
    UP = 1 << 1,
    DOWN = 1 << 2
} Input;

typedef struct
{
    Input left;
    Input right;
} PlayerInputs;

typedef struct
{
    float x;
    float y;
} Vector2;

typedef struct
{
    int left;
    int right;
} Score;

typedef struct
{
    Vector2 pos;
    Vector2 vel;
    float radius;
} Ball;

typedef struct
{
    Vector2 pos;
    Vector2 size;
} Paddle;

typedef struct
{
    Paddle left;
    Paddle right;
} Paddles;

typedef struct
{
    double previousTime;
    PlayerInputs inputs;
    Paddles paddles;
    Ball ball;
    Score score;
    bool gameOver;
} StupidPongState;

typedef StupidPongState State;

typedef struct
{
    State buffer[STATE_BUFFER_SIZE];
    int currentBuffer;
} StateBuffer;

void game(void);

extern double(*get_timestamp)(void);
extern PlayerInputs(*process)(const State* const, double deltaSeconds);
extern State(*update)(const State* const, PlayerInputs inputs, double deltaSeconds);
extern void(*render)(const State* const);

@interface AppDelegate : NSObject <NSApplicationDelegate>

@end
