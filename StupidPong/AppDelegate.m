//
//  AppDelegate.m
//  StupidPong
//
//  Created by Kyle Roucis on 4/21/19.
//

#import "AppDelegate.h"

#import "SPGameWindowController.h"

#define     PADDLE_SIZE     (Vector2) { 20, 70.0 }
#define     PADDLE_SPEED    200.0
#define     BALL_RADIUS     10.0
#define     PLAY_AREA_HEIGHT    300.0
#define     PLAY_AREA_WIDTH     460.0
#define     BALL_SPEED      250.0
#define     PADDLE_X        200.0
#define     VICTORY_POINTS  7

double(*get_timestamp)(void);
State(*update)(const State* const, PlayerInputs inputs, double deltaSeconds);
void(*render)(const State* const);

Vector2 Vector2_add(Vector2 left, Vector2 right)
{
    return (Vector2){ left.x + right.x, left.y + right.y };
}

Vector2 Vector2_subtract(Vector2 left, Vector2 right)
{
    return (Vector2){ left.x - right.x, left.y - right.y };
}

Vector2 Vector2_scalarMultiply(Vector2 left, float scalar)
{
    return (Vector2){ left.x * scalar, left.y * scalar };
}

float Vector2_squaredMagnitude(Vector2 vec)
{
    return (vec.x * vec.x) + (vec.y * vec.y);
}

float Vector2_magnitude(Vector2 vec)
{
    return sqrt(Vector2_squaredMagnitude(vec));
}

Vector2 Vector2_normalized(Vector2 vec)
{
    float mag = Vector2_magnitude(vec);
    return (Vector2){ vec.x / mag, vec.y / mag };
}

Vector2 Vector2_randomUnitVector()
{
    double x = (double)arc4random() / (double)INT_MAX;
    x -= 0.5;
    x *= 2.0;
    
    double y = (double)arc4random() / (double)INT_MAX;
    y -= 0.5;
    y *= 2.0;
    
    double mag = sqrt((x * x) + (y * y));
    return (Vector2){ x / mag, y / mag };
}

State* StateBuffer_advanceBuffer(StateBuffer* buffer)
{
    buffer->currentBuffer = (buffer->currentBuffer + 1) % STATE_BUFFER_SIZE;
    return &buffer->buffer[buffer->currentBuffer];
};

//void draw(const State* const state)
//{
//
//}
//
//State update(const State* const previousState, float deltaSeconds)
//{
//    return (State){
//        0,
//
//    };
//}

static StateBuffer stateBuffer;
static State* statePtr = stateBuffer.buffer;

void game()
{
    State* oldStatePtr = statePtr;
    statePtr = StateBuffer_advanceBuffer(&stateBuffer);
    double deltaTime = get_timestamp() - oldStatePtr->previousTime;
    PlayerInputs newInputs = process(oldStatePtr, deltaTime);
    (*statePtr) = update(oldStatePtr, newInputs, deltaTime);
    statePtr->previousTime = get_timestamp();
    render(statePtr);
}

//void mainLoop()
//{
//    (*statePtr) = initialState();   // Set initial state through the statePtr
//    while (statePtr->gameOver == false)
//    {
//        State* oldStatePtr = statePtr;
//        statePtr = StateBuffer_advanceBuffer(&stateBuffer);
//        float deltaTime = time(NULL) - oldStatePtr->previousTime;
//        (*statePtr) = update(oldStatePtr, deltaTime);
//        statePtr->previousTime = time(NULL);
//        draw(statePtr);
//    }
//}

// BIND

State initialState()
{
    /**
     double previousTime;
     PlayerInputs inputs;
     PaddlePositions paddlePositions;
     Ball ball;
     Score score;
     bool gameOver;
     **/
    return (State){
        get_timestamp(),
        (PlayerInputs) { NONE, NONE },
        (Paddles) {
            (Paddle) {
                (Vector2) { -PADDLE_X, 0.0 },
                PADDLE_SIZE
            },
            (Paddle) {
                (Vector2) { PADDLE_X, 0.0 },
                PADDLE_SIZE
            }
        },
        (Ball) {
            (Vector2) { 0.0, 0.0 },
            Vector2_randomUnitVector(),
            BALL_RADIUS
        },
        (Score) { 0, 0 },
        false
    };
}

double cocoa_get_timestamp()
{
    return [NSDate timeIntervalSinceReferenceDate];
}

Ball update_ball(const State* const previousState, double deltaSeconds)
{
    return (Ball){
        Vector2_add(previousState->ball.pos, Vector2_scalarMultiply(previousState->ball.vel, deltaSeconds * BALL_SPEED)),
        previousState->ball.vel,
        previousState->ball.radius
    };
}

Vector2 update_paddle_position(Vector2 pos, Input input, double deltaSeconds)
{
    float halfAreaHeight = PLAY_AREA_HEIGHT / 2.0;
    float paddleMove = PADDLE_SPEED * deltaSeconds;
    switch (input)
    {
        case NONE:
        {
            return pos;
        } break;
        case UP:
        {
            float y = MIN(MAX(pos.y + paddleMove, -halfAreaHeight), halfAreaHeight);
            return (Vector2) { pos.x, y };
        } break;
        case DOWN:
        {
            float y = MIN(MAX(pos.y - paddleMove, -halfAreaHeight), halfAreaHeight);
            return (Vector2) { pos.x, y };
        } break;
    }
}

Paddles update_paddles(const State* const previousState, double deltaSeconds)
{
    return (Paddles){
        (Paddle) {
            update_paddle_position(previousState->paddles.left.pos,
                                   previousState->inputs.left,
                                   deltaSeconds),
            previousState->paddles.left.size
        },
        (Paddle) {
            update_paddle_position(previousState->paddles.right.pos,
                                   previousState->inputs.right,
                                   deltaSeconds),
            previousState->paddles.right.size
        },
    };
}

Vector2 closestPointOnPaddle(Vector2 point, Paddle paddle)
{
    Vector2 result;
    
    {
        // x
        float cx = point.x;
        float minX = paddle.pos.x - (paddle.size.x / 2.0);
        float maxX = paddle.pos.x + (paddle.size.x / 2.0);
        if (cx < minX)
        {
            cx = minX;
        }
        else if (cx > maxX)
        {
            cx = maxX;
        }
        
        result.x = cx;
    }
    
    {
        // y
        float cy = point.y;
        float minY = paddle.pos.y - (paddle.size.y / 2.0);
        float maxY = paddle.pos.y + (paddle.size.y / 2.0);
        if (cy < minY)
        {
            cy = minY;
        }
        else if (cy > maxY)
        {
            cy = maxY;
        }
        
        result.y = cy;
    }
    
    return result;
}

bool check_game_over(Score scores)
{
    return scores.left >= VICTORY_POINTS
    || scores.right >= VICTORY_POINTS;
}

bool check_ball_paddle_overlapping(Ball ball, Paddle paddle)
{
    Vector2 closest = closestPointOnPaddle(ball.pos, paddle);
    float dist = Vector2_squaredMagnitude(Vector2_subtract(closest, ball.pos));
    return ball.radius * ball.radius > dist;
    
//    BBSCollision3 BBSContinuum_sphere_aabb(BBSSphere sphere0, BBSAABB aabb1)
//    {
//        BBSCollision3 collision;
//
//        BBSPoint3 closest = BBSContinuum_closestPointOnAABB(sphere0.origin, aabb1);
//
//        real dist = BBSVec3SquaredDistance(sphere0.origin, closest);
//        if (sphere0.radius * sphere0.radius > dist)
//        {
//            collision.type = BBSValidCollision;
//            collision.interpenetration = sqrt(sphere0.radius * sphere0.radius - dist);
//            collision.normal = BBSVec3Normalize(BBSVec3Subtract(sphere0.origin, aabb1.origin));
//        }
//        else
//        {
//            collision.type = BBSNoCollision;
//        }
//
//        return collision;
//    }
//
//    // x projection
//    float p_halfwidth = paddle.size.x / 2.0;
//    if (ball.pos.x + ball.radius > paddle.pos.x + p_halfwidth)
//    {
//        return false;
//    }
//
//    // y projection
//    float p_halfheight = paddle.size.y / 2.0;
//    if (ball.pos.y + ball.radius > paddle.pos.y + p_halfheight)
//    {
//        return false;
//    }
//
//    return true;
}

State pong_update(const State* const previousState, PlayerInputs newInputs, double deltaSeconds)
{
    /**
     double previousTime;
     PlayerInputs inputs;
     PaddlePositions paddlePositions;
     Ball ball;
     Score score;
     bool gameOver;
     **/
    
    Score newScore = previousState->score;
    
    // Update ball position
    Ball newBall = update_ball(previousState, deltaSeconds);
    
    // Check arena bounds
    float halfWidth = PLAY_AREA_WIDTH / 2.0;
    float halfHeight = PLAY_AREA_HEIGHT / 2.0;
    if (newBall.pos.x - newBall.radius < -halfWidth)
    {
        newScore.right += 1;
        newBall.pos = (Vector2){ 0.0, 0.0 };
        newBall.vel = Vector2_randomUnitVector();
    }
    else if (newBall.pos.x + newBall.radius > halfWidth)
    {
        newScore.left += 1;
        newBall.pos = (Vector2){ 0.0, 0.0 };
        newBall.vel = Vector2_randomUnitVector();
    }
    
    if (newBall.pos.y + newBall.radius > halfHeight)
    {
        newBall.pos.y = halfHeight - newBall.radius;
        newBall.vel = (Vector2) { newBall.vel.x, -newBall.vel.y };
    }
    else if (newBall.pos.y - newBall.radius < -halfHeight)
    {
        newBall.pos.y = -halfHeight + newBall.radius;
        newBall.vel = (Vector2) { newBall.vel.x, -newBall.vel.y };
    }
    
    if (check_game_over(newScore))
    {
        return initialState();
    }
    
    Paddles newPaddles = update_paddles(previousState, deltaSeconds);
    
    //.. Check paddle collisions
    
    if (newBall.pos.x > 0
        && check_ball_paddle_overlapping(newBall, newPaddles.right))  // Check right paddle if the ball is on the right side of the screen
    {
        newBall.vel.x *= -1.0;
    }
    else if (check_ball_paddle_overlapping(newBall, newPaddles.left))                    // Otherwise, check the left paddle
    {
        newBall.vel.x *= -1.0;
    }
    
    
    return (State){
        0,
        newInputs,
        newPaddles,
        newBall,
        newScore,
        false
    };
}

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    get_timestamp = &cocoa_get_timestamp;
    update = &pong_update;
    (*statePtr) = initialState();
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
