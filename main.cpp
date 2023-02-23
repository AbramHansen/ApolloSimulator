/*************************************************************
 * Contributors:
 *      Abram Hansen
 *      Jeremy Harrington
 * Assignment Description:
 *      Simulate the Apollo 11 landing using real data about the lander
 *****************************************************************/

#include <cstdlib>

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "Star.h"
#include "LunarModule.h"

using namespace std;

/*************************************************************************
 * Simulator
 * class to manage the objects accociated with the simulator and update/draw them accordingly
 *************************************************************************/
class Simulator
{
private:
   ogstream gout;

   Point ptLM;           // location of the LM on the screen
   Point ptUpperRight;   // size of the screen
   double angle;         // angle the LM is pointing
   const double gravity = -1.625; // gravity constant for the moon

   Ground ground;

   Star stars[50];

   LunarModule lunarModule;
public:
   /*************************************************************************
 * Initializes the lunar module to be at the top center of the screen and initializes the stars
 *************************************************************************/
   Simulator(const Point& ptUpperRight) :
          angle(0.0),
          ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY()),
          ground(ptUpperRight),
          lunarModule(ptLM, 0, 0)
   { 
      this->ptUpperRight = ptUpperRight;

      // Initialize all the stars
      for (auto& star : stars)
      {
         star = Star(ptUpperRight);
      }
   }

   /*************************************************************************
 * updates the lunar module only if it is not in a crashed or win state
 *************************************************************************/
   void updateLunarModule(const Interface* pUI)
   {
      if (!(lunarModule.isCrashed()))
      {
         lunarModule.update(pUI, gravity);

         //check for win/crashed state
         if (ground.hitGround(lunarModule.getPosition(), lunarModule.getWidth()))
         {
            lunarModule.setCrashed();
         }
         if (ground.onPlatform(lunarModule.getPosition(), lunarModule.getWidth()))
         {
            lunarModule.setCrashed();
            if (lunarModule.getSpeed() < 4)
            {
               lunarModule.setWin();
            }
         }
      }
   }

   /*************************************************************************
 * calls the star class's draw and update functions
 *************************************************************************/
   void drawStars()
   {
      for (int i = 0; i < 50; i++)
      {
         // Draw the current star and update the phase
         gout.drawStar(stars[i].getPosition(), stars[i].getPhase());
         stars[i].update();
      }
   }

   /*************************************************************************
 * calls the draw ground function
 *************************************************************************/
   void drawGround()
   {
      ground.draw(gout);
   }

   /*************************************************************************
 * Always draws the landerm but only draws the flames if it is not in a crashed state
 *************************************************************************/
   void drawLander(const Interface* pUI)
   {
      gout.drawLander(lunarModule.getPosition() /*position*/, lunarModule.getAngle() /*angle*/);

      //only draw the flames if it is not crashed
      if (!lunarModule.isCrashed())
      {
         gout.drawLanderFlames(lunarModule.getPosition(), lunarModule.getAngle(), /*angle*/
            pUI->isUp(), pUI->isLeft(), pUI->isRight());
      }
   }

   /*************************************************************************
 * Draws the fuel amount in the top left of the screen
 *************************************************************************/
   void drawFuel()
   {
      gout.setPosition(Point(20, ptUpperRight.getY() - 20));
      gout << "Fuel: " << lunarModule.getFuel() << "\n";
   }

   /*************************************************************************
* Draws the altitude amount in the top left of the screen
*************************************************************************/
   void drawAltitude()
   {
      gout.setPosition(Point(20, ptUpperRight.getY() - 40));
      gout << "Altitude: " << ground.getElevation(lunarModule.getPosition()) << "\n";
   }

   /*************************************************************************
* Draws the speed amount in the top left of the screen
*************************************************************************/
   void drawSpeed()
   {
      gout.setPosition(Point(20, ptUpperRight.getY() - 60));
      gout << "Speed: " << lunarModule.getSpeed() << "\n";
   }

   /*************************************************************************
* Checks if the lunar module has crashed or has landed on the pad and draws the
* corrisponding message in the center of the screen
*************************************************************************/
   void checkStatus()
   {
      if (lunarModule.isCrashed())
      {
         if (lunarModule.didWin())
         {
            gout.setPosition(Point(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0));
            gout << "Landing Successful!" "\n";
         }
         else
         {
            gout.setPosition(Point(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0));
            gout << "Crash!" "\n";
         }
      }
   }
};

/*************************************************************************
 * Callback is called every frame and is responsible for when things are drawn to the screen
 * and when they are updated.
 *************************************************************************/
void callBack(const Interface *pUI, void * p)
{
   // the first step is to cast the void pointer into a game object.
   Simulator * pSimulator = (Simulator *)p;  

   //update the lunar module
   pSimulator->updateLunarModule(pUI);

   // draw the stars
   pSimulator->drawStars();

   // put win or crashed on screen
   pSimulator->checkStatus();

   // draw the ground
   pSimulator->drawGround();

   // draw the lander and its flames
   pSimulator->drawLander(pUI);

   // put fuel amount on the screen
   pSimulator->drawFuel();

   // put altitude on the screen
   pSimulator->drawAltitude();

   // put speed on the screen
   pSimulator->drawSpeed();
}

/*********************************
 * Initializes the simulator and calls the display engine.
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance, 
   _In_opt_ HINSTANCE hPrevInstance, 
   _In_ PWSTR pCmdLine, 
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char ** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Point ptUpperRight(400.0, 400.0);
   Interface ui(0, NULL, 
                "Lunar Module Simulator", 
                 ptUpperRight);

   // Initialize the game class
   Simulator simulator(ptUpperRight);

   // set everything into action
   ui.run(callBack, &simulator);             

   return 0;
}
