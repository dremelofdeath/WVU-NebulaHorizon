/*
 * OceanPlane.h
 * Nebula Horizon
 *
 * Created by Zachary Murray on 4/30/2010 6:44:00 AM Eastern Daylight Time
 *
 */

#ifndef NHZ_OCEANPLANE_H
#define NHZ_OCEANPLANE_H

#include "nhz_common.h"
#include "Renderable.h"

class OceanPlane : public Renderable {
  public:
    OceanPlane();
    ~OceanPlane();
    virtual void render() const;
    virtual void idle(const int elapsed);
    virtual bool isRendering() const;
    virtual void disableRendering();
    virtual void resumeRendering();
  protected:
    void initialize();
  private:
    static const GLint _wh = 1024;
    GLuint _reflectionTextureID, _fboID, _rbID;
    bool _isRendering;
};

#endif
