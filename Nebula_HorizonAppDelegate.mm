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
#import "src/RenderQueue.h"
#import "src/Player.h"
#import "src/EnemySpawner.h"
#import "src/Skycube.h"

@implementation Nebula_HorizonAppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application 
	const char *title = "Nebula Horizon";
	set_window_id(create_window(title, 40, 40, 800, 600));
    atexit(&exit_callback);
    create_callbacks();
    init_opengl();
    Player player(5.0f, 5.0f);
    EnemySpawner spawner(&player);
	RenderQueue::getInstance()->enqueue(player);
	RenderQueue::getInstance()->enqueue(spawner);
    Skycube skycube("north.raw", "south.raw", "east.raw",
                    "west.raw", "up.raw", "down.raw");
    RenderQueue::getInstance()->enqueue(skycube);
    glutMainLoop();
}

@end
