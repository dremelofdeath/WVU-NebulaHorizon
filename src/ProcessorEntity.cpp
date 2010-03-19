/*
 *  ProcessorEntity.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/3/09.
 *
 */

#include "ProcessorEntity.h"

void ProcessorEntity::render() const {
  // never does anything -- only processes time and events
}

void ProcessorEntity::idle(int elapsed) {
  // default implementation does nothing but call the superclass version
  Renderable::idle(elapsed);
}
