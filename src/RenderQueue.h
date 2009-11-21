/*
 *  RenderQueue.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/15/09.
 *
 */

#include <vector>
#include "Renderable.h"

#ifndef NHZ_RENDERQUEUE_H
#define NHZ_RENDERQUEUE_H

class RenderQueue : public Renderable {
    public:
        RenderQueue();
        static RenderQueue* getInstance();
        void enqueue(Renderable& spr);
        void dequeue(Renderable& spr);
        void render();
        void idle();
        void clear();
        std::vector<Renderable*>::size_type size();
    private:
        static RenderQueue* _singleton;
        std::vector<Renderable*> _sprites;
};

#endif
