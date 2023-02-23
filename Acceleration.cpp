#include "Acceleration.h"
#include <cmath>

/*************************************************************************
 * Computes the horizontal acceleration with the thrust and angle
 *************************************************************************/
void Acceleration::computeHorizontalComponent(const double& angle, const double& thrust)
{
   //angle is in radians
   //an angle of 0 means the lander is straight up

   accelerationX = (std::sin(angle) * thrust * -1);
}

/*************************************************************************
 * Computes the vertical acceleration with the thrust and angle it then adds acceleration due to gravity
 *************************************************************************/
void Acceleration::computeVerticalComponent(const double& angle, const double& thrust, double gravity)
{
   //angle is in radians
   //an angle of 0 means the lander is straight up

   accelerationY = (std::cos(angle) * thrust + gravity);
}

/*************************************************************************
 * Constructs the acceleration object and sets the values to 0
 *************************************************************************/
Acceleration::Acceleration()
{
   this->accelerationX = 0;
   this->accelerationY = 0;
}

/*************************************************************************
 * calls the compute horizontal and compute vertical functions
 *************************************************************************/
void Acceleration::update(const double& angle, const double& thrust, double gravity)
{
   computeHorizontalComponent(angle, thrust);
   computeVerticalComponent(angle, thrust, gravity);
}

/*************************************************************************
 * getters for the acceleration components
 *************************************************************************/
double Acceleration::getAccelerationX() const
{
   return accelerationX;
}

double Acceleration::getAccelerationY() const
{
   return accelerationY;
}