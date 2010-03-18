//
//  Nebula_HorizonAppDelegate.m
//  Nebula Horizon
//
//  Created by Zachary Murray on 11/23/09.
//  Copyright 2009 West Virginia University. All rights reserved.
//

#import <GLUT/glut.h>
#import "Nebula_HorizonAppDelegate.h"
#import "src/handlers.h"

@implementation Nebula_HorizonAppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  // Insert code here to initialize your application 
  main_springload(); // platform independent way to always start the same
}

@end
