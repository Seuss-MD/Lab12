/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include <math.h>       // for PI
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include "projectile.h" // for PROJECTILE
#include "howitzer.h"   // for HOWITZER
#include "angle.h"      // for ANGLE

#include <vector>       // for VECTOR
#include <tuple>        // for TUPLE


#define initial_speed         827      // m/s
#define bullet_weight         46.7     // kg
#define bullet_diameter       154.89   // mm
#define bullet_radius         bullet_diameter * 0.5 * 0.001
#define bullet_surface_area   M_PI*bullet_radius*bullet_radius

using namespace std;

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight) :
      posUpperRight(posUpperRight),
      ground(posUpperRight), projectile(), howitzer()
   {
      time = -999.9;
      hasFired = false;
      // Set the horizontal position of the howitzer. This should be random.
      // See uiDraw.h which has random() defined.
      howitzer.generatePosition(this-> posUpperRight);
      
      // ptHowitzer.setPixelsX(Position(posUpperRight).getPixelsX() / 2.0);

      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(howitzer.getPosition());

      ptHowitzer = howitzer.getPosition();
      // set time to 0

      // This is to make the bullet travel across the screen. Notice how there are 
      // 20 pixels, each with a different age. This gives the appearance
      // of a trail that fades off in the distance.
      
   }
   void gamePlay();
   void input(const Interface* pUI);
   void display();
   bool onTarget(Position posTarget, Position posProjectile);

private:
   Ground ground;                   // the ground, described in ground.h
   Position  projectileTrail[20];    // path of the projectile, described in position.h
   Position  ptHowitzer;            // location of the howitzer
   Position  posUpperRight;          // size of the screen
   Angle angle;                     // angle of the howitzer, in radians 
   double time;                     // amount of time since the last firing, in seconds
   Projectile projectile;           // information of the projectile fired
   Howitzer howitzer;               // information of the Howitzer
   double t;                        // increment of time
   double hangTime;                 // time bullet is in air
   double currentGravity;           // value for current gravity
   double currentAirDensity;        // value for current Air Density
   double currentDragCoefficient;   // value for current Drag Coefficent
   double currentSpeedOfSound;      // value for current speed of Sound
   double mach;                     // speed in mach
   bool   hasFired;

   // Tables
   vector<pair<double, double>> gravityTable;
   vector<pair<double, double>> airDensityTable;
   vector<pair<double, double>> dragCoefficientTable;
   vector<pair<double, double>> speedOfSoundTable;
};
