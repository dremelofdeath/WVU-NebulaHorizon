//
//  Nebula_HorizonAppDelegate.h
//  Nebula Horizon
//
//  Created by Zachary Murray on 11/23/09.
//  Copyright 2009 West Virginia University. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface Nebula_HorizonAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
