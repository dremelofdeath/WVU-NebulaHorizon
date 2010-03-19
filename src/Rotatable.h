/*
 *  Rotatable.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifndef NHZ_ROTATABLE_H
#define NHZ_ROTATABLE_H

class Rotatable {
  public:
    void setXAngle(const double value);
    void setYAngle(const double value);
    void setZAngle(const double value);
    double getXAngle() const;
    double getYAngle() const;
    double getZAngle() const;
    void copyRotationFrom(const Rotatable& object);
  protected:
    double _xAngle, _yAngle, _zAngle;
    void initialize();
    void initialize(const double x, const double y, const double z);
    void doRotation() const; // used by children's render() methods
};

#endif
