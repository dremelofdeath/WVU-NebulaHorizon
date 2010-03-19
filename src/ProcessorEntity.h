/*
 *  ProcessorEntity.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/3/09.
 *
 */

#ifndef NHZ_PROCESSORENTITY_H
#define NHZ_PROCESSORENTITY_H

#include "Renderable.h"

class ProcessorEntity : public Renderable {
  public:
    void render() const;
    virtual void idle(int elapsed) = 0;
};

#endif
