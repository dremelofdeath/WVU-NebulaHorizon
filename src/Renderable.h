/*
 *  Sprite.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/15/09.
 *  Copyright 2009 West Virginia University. All rights reserved.
 *
 */

#ifndef NHZ_RENDERABLE_H
#define NHZ_RENDERABLE_H

class Renderable {
	public:
        virtual void render() = 0;
        virtual void idle() = 0;
};

#endif
