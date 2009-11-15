/*
 *  RenderQueue.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/15/09.
 *
 */

#include <cstdarg>
#include "RenderQueue.h"

RenderQueue::_singleton = 0x0;

RenderQueue* RenderQueue::getInstance() {
    if(_singleton == 0x0) {
        _singleton = new RenderQueue;
    }
    return _singleton;
}

void RenderQueue::enqueue(Sprite& spr) {
    _sprites.push_back(spr);
}

void RenderQueue::dequeue(Sprite& spr) {
    vector<Sprite&>::iterator vector_it = _sprites.rbegin();
    bool found_it = false;
    while(vector_it != _sprites.rend() && !found_it) {
        if(spr == *vector_it) {
            _sprites.erase(vector_it);
            found_it = true;
        }
        vector_it++;
    }
}

void RenderQueue::render() {
    vector<Sprite&>::iterator vector_it = _sprites.begin();
    while(vector_it != _sprites.end()) {
        vector_it->render();
    }
}

void RenderQueue::clear() {
    _sprites.clear();
}

vector<Sprite&>::size_type RenderQueue::size() {
    return _sprites.size();
}
