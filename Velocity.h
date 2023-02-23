#pragma once
#include "Acceleration.h"
#include <cmath>

/*************************************************************************
 * Veloity
 * holds the velocity of an object and updates it from an acceleration
 *************************************************************************/
class Velocity
{
private:
   double velocityX;
   double velocityY;

public:
   Velocity(double velocityX, double velocityY);
   Velocity();
   void update(const Acceleration& acceleration, double time);

   double getVelocityX() const;
   double getVelocityY() const;
   double getTotalVelocity() const;
};

