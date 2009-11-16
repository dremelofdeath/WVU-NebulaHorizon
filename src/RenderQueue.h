/*
 *  RenderQueue.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/15/09.
 *
 */

#include <vector>
#include "Sprite.h"

#ifndef NHZ_RENDERQUEUE_H
#define NHZ_RENDERQUEUE_H

class RenderQueue {
    public:
        static RenderQueue* getInstance();
        void enqueue(Sprite& spr);
        void dequeue(Sprite& spr);
        void render();
        void clear();
        std::vector<Sprite*>::size_type size();
    protected:
        RenderQueue();
    private:
        static RenderQueue* _singleton;
        std::vector<Sprite*> _sprites;
};

#endif
