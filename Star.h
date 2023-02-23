#pragma once
#include "point.h"

/*************************************************************************
 * Star
 * Holds the location and phase of the star and updates the phase accordingly
 *************************************************************************/
class Star
{
private:
   unsigned char phase;
   Point position;
public:
   Star(const Point& ptUpperRight);
   Star() 
   {
      position = Point(0, 0);
      phase = 0;
   }

   void update();

   /*************************************************************************
 * getters
 *************************************************************************/
   char getPhase() const
   {
      return phase;
   }

   Point getPosition() const
   {
      return position;
   }
};

