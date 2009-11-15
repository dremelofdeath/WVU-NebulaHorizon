/*
 *  RenderQueue.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/15/09.
 *
 */

#ifndef NHZ_RENDERQUEUE_H
#define NHZ_RENDERQUEUE_H

#include <vector>

class RenderQueue {
    public:
        ~RenderQueue();
        static RenderQueue* getInstance();
        void enqueue(Sprite& spr, ...);
        void dequeue(Sprite& spr, ...);
        void render();
        void clear();
    protected:
        RenderQueue();
        void initialize();
    private:
        static RenderQueue* _singleton;
        vector<Sprite&> _sprites;
}

#endif
