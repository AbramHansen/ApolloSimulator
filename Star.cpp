#include "Star.h"
/*************************************************************************
 * Initializes the location of the star to a random x and y within the screen size
 *************************************************************************/
Star::Star(const Point& ptUpperRight)
{
   int starX = rand() % (int)ptUpperRight.getX();
   int starY = rand() % (int)ptUpperRight.getY();
   position = Point(starX, starY);
   phase = rand() % 255;
}

/*************************************************************************
 * Updates the phase by adding one. Called every frame
 *************************************************************************/
void Star::update()
{
   phase++;
}