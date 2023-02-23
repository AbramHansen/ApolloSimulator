#include "LunarModule.h"
/******************************
* adds the velocity to the position
******************************/
void LunarModule::updatePostion()
{
   position.addX(velocity.getVelocityX());
   position.addY(velocity.getVelocityY());
}

/******************************
* initializes the lunar module to default values
******************************/
LunarModule::LunarModule()
{
   this->position = Point();
   velocity = Velocity();
   crashed = false;
   win = false;
   fuel = 5000;
   angle = 0;
}

/******************************
* initializes the lunar module with a position and velocity
******************************/
LunarModule::LunarModule(Point position, double velocityX, double velocityY)
{
   this->position = position;
   velocity = Velocity(velocityX, velocityY);
   crashed = false;
   win = false;
   fuel = 5000;
   angle = 0;
}

/******************************
*updates acceleration and fuel depending on user input
******************************/
void LunarModule::update(const Interface* pUI, double gravity)
{
   Acceleration acceleration;
   if (pUI->isRight() && fuel >= 1)
   {
      angle -= 0.1;
      --fuel;
   }
   if (pUI->isLeft() && fuel >= 1)
   {
      angle += 0.1;
      --fuel;
   }

   if (pUI->isUp() && fuel >= 10)
   {
      acceleration.update(angle, THRUST / WEIGHT, gravity);
      fuel -= 10;
   }
   else
   {
      acceleration.update(angle, 0, gravity);
   }

   double time = pUI->frameRate();
   velocity.update(acceleration, time);
   updatePostion();
}