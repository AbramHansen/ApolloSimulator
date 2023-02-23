#pragma once
#include "point.h"
#include "Velocity.h"
#include "Acceleration.h"
#include "uiInteract.h"

class LunarModule
{
private:
   Point position;
   Velocity velocity;
   
   int fuel;
   double angle;
   bool crashed;
   bool win;
   const double WEIGHT = 15103.00;
   const double THRUST = 45000.00;
   const int WIDTH = 20;

   void updatePostion();

public:
   LunarModule();
   LunarModule(Point position, double velocityX, double velocityY);

   void update(const Interface* pUI, double gravity);

   //getters

   Point getPosition() const
   {
      return position;
   }

   double getSpeed() const
   {
      return std::abs(velocity.getTotalVelocity());
   }

   int getFuel() const
   {
      return fuel;
   }

   double getAngle() const
   {
      return angle;
   }

   int getWidth() const
   {
      return WIDTH;
   }

   //setters

   void setCrashed()
   {
      crashed = true;
   }

   void setWin()
   {
      win = true;
   }

   bool isCrashed() const
   {
      return crashed;
   }

   bool didWin() const
   {
      return win;
   }
};

