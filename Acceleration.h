#pragma once
/*************************************************************************
 * Acceleration
 * class to compute the components of acceleration
 *************************************************************************/
class Acceleration
{
private:
   double accelerationX;
   double accelerationY;

   void computeHorizontalComponent(const double& angle, const double& thrust);
   void computeVerticalComponent(const double& angle, const double& thrust, double gravity);
public:
   Acceleration();
   void update(const double& angle, const double& thrust, double gravity);
   double getAccelerationX() const;
   double getAccelerationY() const;
};