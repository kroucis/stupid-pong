//
//  SPGameWindowController.h
//  StupidPong
//
//  Created by Kyle Roucis on 4/21/19.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import "AppDelegate.h"

NS_ASSUME_NONNULL_BEGIN

extern PlayerInputs inputs;

@protocol SPGameViewDrawDelegate <NSObject>

- (void) draw:(CGContextRef)context;

@end

@interface SPGameView : NSView

@property (weak) IBOutlet id<SPGameViewDrawDelegate> drawDelegate;

- (void) drawRectAt:(Vector2)point  width:(float)w  height:(float)h  color:(NSColor*)color  context:(CGContextRef)context;
- (void) drawCircleAt:(Vector2)point  radius:(float)r  color:(NSColor*)color  context:(CGContextRef)context;

@end

@interface SPGameWindowController : NSWindowController

@property (weak) IBOutlet SPGameView *gamView;
@property const State* const gameState;

@end

NS_ASSUME_NONNULL_END
