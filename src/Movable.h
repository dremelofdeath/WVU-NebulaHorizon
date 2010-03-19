/*
 *  Movable.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/3/09.
 *
 */

#ifndef NHZ_MOVABLE_H
#define NHZ_MOVABLE_H

class Movable {
  public:
    void setX(const double value);
    void setY(const double value);
    void setZ(const double value);
    double getX() const;
    double getY() const;
    double getZ() const;
    void copyCoordinatesFrom(const Movable& object);
  protected:
    double _x, _y, _z;
    void initialize();
    void initialize(const double x, const double y, const double z);
    void doTranslation() const; // used by children's render() methods
};

#endif
