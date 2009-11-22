/*
 *  RenderQueue.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/15/09.
 *
 */

#include "RenderQueue.h"

RenderQueue* RenderQueue::_singleton = 0;

RenderQueue::RenderQueue() {
}

RenderQueue* RenderQueue::getInstance() {
    if(_singleton == 0) {
        _singleton = new RenderQueue;
    }
    return _singleton;
}

void RenderQueue::enqueue(Renderable& spr) {
    _sprites.push_back(&spr);
}

void RenderQueue::dequeue(Renderable& spr) {
    std::vector<Renderable*>::reverse_iterator vector_it = _sprites.rbegin();
    bool found_it = false;
    while(vector_it != _sprites.rend() && !found_it) {
        if(&spr == *vector_it) {
            // note that this converts to a plain iterator for erase()
            _sprites.erase((++vector_it).base());
            found_it = true;
        }
        vector_it++;
    }
}

void RenderQueue::render() {
    std::vector<Renderable*>::iterator vector_it = _sprites.begin();
    while(vector_it != _sprites.end()) {
        (*vector_it)->render();
        vector_it++;
    }
}

void RenderQueue::idle() {
    std::vector<Renderable*>::iterator vector_it = _sprites.begin();
    while(vector_it != _sprites.end()) {
        (*vector_it)->idle();
        vector_it++;
    }
}

void RenderQueue::clear() {
    _sprites.clear();
}

std::vector<Renderable*>::size_type RenderQueue::size() {
    return _sprites.size();
}
