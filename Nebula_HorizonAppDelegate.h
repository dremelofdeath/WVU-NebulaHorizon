//
//  Nebula_HorizonAppDelegate.h
//  Nebula Horizon
//
//  Created by Zachary Murray on 11/23/09.
//  Copyright 2009 West Virginia University. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AppKit/NSApplication.h>

#if (MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5)
@interface Nebula_HorizonAppDelegate : NSObject {
#else
@interface Nebula_HorizonAppDelegate : NSObject <NSApplicationDelegate> {
#endif
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
