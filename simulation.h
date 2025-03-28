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
#include "angle.h"      // for ANGLE


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight) :
      posUpperRight(posUpperRight),
      ground(posUpperRight), projectile()
   {

      // Set the horizontal position of the howitzer. This should be random.
      // See uiDraw.h which has random() defined.
      ptHowitzer.setPixelsX(Position(posUpperRight).getPixelsX() / 2.0);

      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(ptHowitzer);
   }

      Ground ground;                   // the ground, described in ground.h
      Position  projectilePath[20];    // path of the projectile, described in position.h
      Position  ptHowitzer;            // location of the howitzer
      Position  posUpperRight;          // size of the screen
      Angle angle;                     // angle of the howitzer, in radians 
      double time;                     // amount of time since the last firing, in seconds
      Projectile projectile;           // information of the projectile fired
      //double t;                        // increment of time
      //double hangTime;                 // time bullet is in air
      //double currentGravity;           // value for current gravity
      //double currentAirDensity;        // value for current Air Density
      //double currentDragCoefficient;   // value for current Drag Coefficent
      //double currentSpeedOfSound;      // value for current speed of Sound
      //double mach;                     // speed in mach
};
