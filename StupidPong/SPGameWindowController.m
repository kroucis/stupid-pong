//
//  SPGameWindowController.m
//  StupidPong
//
//  Created by Kyle Roucis on 4/21/19.
//

#import "SPGameWindowController.h"

PlayerInputs inputs;
PlayerInputs(*process)(const State* const, double deltaSeconds);

static SPGameWindowController* gameWindowController;

@interface SPGameWindowController ()

- (void) render;

@end

@interface SPGameWindowController (SPGameViewDrawDelegate) <SPGameViewDrawDelegate>

@end

PlayerInputs pong_process_input(const State* const state, double deltaTime)
{
//    printf("%d <> %d\n", inputs.left, inputs.right);
    return inputs;
}

void pong_render(const State* const state)
{
//    printf("%1.3f,%1.3f\n", state->ball.pos.x, state->ball.pos.y);
//    printf("%d <> %d\n", state->inputs.left, state->inputs.right);
    
    [gameWindowController setGameState:state];
    [gameWindowController render];
}

@implementation SPGameWindowController

- (void) awakeFromNib
{
    [super awakeFromNib];

    gameWindowController = self;
    
    process = &pong_process_input;
    render = &pong_render;
    
    [NSTimer scheduledTimerWithTimeInterval:(1.0/30.0)
                                    repeats:true
                                      block:^(NSTimer * _Nonnull timer) {
                                            game();
                                      }];
}

- (void) keyUp:(NSEvent*)event
{
    if ([[event characters] isEqualToString:@"q"]
        || [[event characters] isEqualToString:@"a"])
    {
        inputs.left = NONE;
    }
    
    if ([[event characters] isEqualToString:@"o"]
        || [[event characters] isEqualToString:@"l"])
    {
        inputs.right = NONE;
    }
}

- (void) keyDown:(NSEvent*)event
{
    if ([[event characters] isEqualToString:@"q"])
    {
        inputs.left = UP;
    }
    else if ([[event characters] isEqualToString:@"a"])
    {
        inputs.left = DOWN;
    }
    
    if ([[event characters] isEqualToString:@"o"])
    {
        inputs.right = UP;
    }
    else if ([[event characters] isEqualToString:@"l"])
    {
        inputs.right = DOWN;
    }
}

- (void) render
{
    [[self gamView] setNeedsDisplay:true];
}

- (void) draw:(CGContextRef)context
{
    const State* const gameStatePtr = [self gameState];
    if (gameStatePtr != NULL)
    {
        // Draw arena
        
        SPGameView* gameView = [self gamView];
        
//        [gameView drawCircleAt:(Vector2){0.0,0.0}
//                        radius:14
//                         color:[NSColor darkGrayColor]
//                       context:context];
//        
//        [gameView drawRectAt:(Vector2){0.0,0.0}
//                       width:4
//                      height:[gameView bounds].size.height
//                       color:[NSColor darkGrayColor]
//                     context:context];
        
        // Draw Ball
        [gameView drawCircleAt:gameStatePtr->ball.pos
                              radius:gameStatePtr->ball.radius
                               color:[NSColor greenColor]
                             context:context];
        
        // Draw left paddle
        Vector2 leftPaddlePos = (Vector2) { gameStatePtr->paddles.left.pos.x, gameStatePtr->paddles.left.pos.y };
        [gameView drawRectAt:leftPaddlePos width:gameStatePtr->paddles.left.size.x height:gameStatePtr->paddles.left.size.y color:[NSColor redColor] context:context];
        
        // Draw right paddle
        Vector2 rightPaddlePos = (Vector2) { gameStatePtr->paddles.right.pos.x, gameStatePtr->paddles.right.pos.y };
        [gameView drawRectAt:rightPaddlePos width:gameStatePtr->paddles.right.size.x height:gameStatePtr->paddles.right.size.y color:[NSColor blueColor] context:context];
        
        // Draw left score
        for (int i = 0; i < gameStatePtr->score.left; i++)
        {
            Vector2 scorePos = (Vector2) { -10.0 - ((float)i * 10.0), 160.0 };
            [gameView drawRectAt:scorePos width:3 height:10 color:[NSColor systemPinkColor] context:context];
        }
        
        // Draw right score
        for (int i = 0; i < gameStatePtr->score.right; i++)
        {
            Vector2 scorePos = (Vector2) { 10.0 + ((float)i * 10.0), 160.0 };
            [gameView drawRectAt:scorePos width:3 height:10 color:[NSColor cyanColor] context:context];
        }
    }
}

@end


@implementation SPGameView

- (void) drawRect:(NSRect)dirtyRect
{
    CGContextRef gc = [NSGraphicsContext currentContext].CGContext;
    CGContextSaveGState(gc);
    CGContextSetFillColor(gc, CGColorGetComponents([[NSColor blackColor] CGColor]));
    CGContextFillRect(gc, [self bounds]);
    [[self drawDelegate] draw:gc];
    CGContextRestoreGState(gc);
}

- (void) drawRectAt:(Vector2)point  width:(float)w  height:(float)h  color:(NSColor*)color  context:(CGContextRef)context
{
    CGContextSaveGState(context);
    float widthDiv2 = [self bounds].size.width / 2.0;
    float heightDiv2 = [self bounds].size.height / 2.0;
    float w2 = w / 2.0;
    float h2 = h / 2.0;
    NSRect rect = CGRectMake((point.x - w2) + widthDiv2, (point.y - h2) + heightDiv2, w, h);
    NSBezierPath *path = [NSBezierPath bezierPathWithRect:rect];
    [path addClip];
    
    const CGFloat *components = CGColorGetComponents([color CGColor]);
    CGContextSetRGBFillColor(context, components[0],components[1],components[2],components[3]);
    CGContextFillRect(context, NSRectToCGRect(rect));
    CGContextRestoreGState(context);
}

- (void) drawCircleAt:(Vector2)point  radius:(float)r  color:(NSColor*)color  context:(CGContextRef)context
{
    CGContextSaveGState(context);
    float widthDiv2 = [self bounds].size.width / 2.0;
    float heightDiv2 = [self bounds].size.height / 2.0;
    float r2 = r * 2.0f;
    NSRect rect = CGRectMake((point.x - (r / 2.0)) + widthDiv2, (point.y - (r / 2.0)) + heightDiv2, r2, r2);
    NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:rect xRadius:r yRadius:r];
    [path addClip];
    
    const CGFloat *components = CGColorGetComponents(color.CGColor);
    CGContextSetRGBFillColor(context, components[0],components[1],components[2],components[3]);
    CGContextFillRect(context, NSRectToCGRect(rect));
    CGContextRestoreGState(context);
}

@end
