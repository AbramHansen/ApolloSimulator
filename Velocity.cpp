#include "Velocity.h"

/*************************************************************************
 * Constructor to initialize velocity
 *************************************************************************/
Velocity::Velocity(double velocityX, double velocityY)
{
   this->velocityX = velocityX;
   this->velocityY = velocityY;
}

/*************************************************************************
 * Constructor to initialize everything to 0;
 *************************************************************************/
Velocity::Velocity()
{
   velocityX = 0;
   velocityY = 0;
}

/*************************************************************************
 * adds acceleration to the components
 *************************************************************************/
void Velocity::update(const Acceleration& acceleration, double time)
{
   velocityX += acceleration.getAccelerationX() * time;
   velocityY += acceleration.getAccelerationY() * time;
}

/*************************************************************************
 * Getters for the components
 *************************************************************************/
double Velocity::getVelocityX() const
{
   return velocityX;
}

double Velocity::getVelocityY() const
{
   return velocityY;
}

/*************************************************************************
 * Getters for the total velocity (used for speed)
 *************************************************************************/
double Velocity::getTotalVelocity() const
{
   return std::sqrt(velocityX * velocityX + velocityY * velocityY);
}