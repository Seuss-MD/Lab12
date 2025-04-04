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
#define time_unit             1.0      // s

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
      time          = -999.9;
      timeUnit      = time_unit;
      status        = Status::READY;

      // Set the horizontal position of the howitzer. This should be random.
      howitzer.generatePosition(this-> posUpperRight);
      

      // Generate the ground, target and set the vertical position of the howitzer.
      ground.reset(howitzer.getPosition());
      ptHowitzer    = howitzer.getPosition();
      target        = ground.getTarget();
      
      //Position for the Status Text
      posTextStatus = posUpperRight;
      posTextStatus.addPixelsX(-220);
      posTextStatus.addPixelsY(-15);
      
   }

   enum class Status
   {
      READY,      
      FIRED,    
      HIT_TARGET, 
      MISS        
   };

   void gamePlay();
   void input(const Interface* pUI);
   void display();
   void onGround(Position posProjectile);
   void calculateTime(Position previousPos);

private:
   Ground ground;                   // the ground, described in ground.h
   Position  projectileTrail[20];    // path of the projectile, described in position.h
   Position  ptHowitzer;            // location of the howitzer
   Position  posUpperRight;          // size of the screen
   Angle angle;                     // angle of the howitzer, in radians 
   double time;                     // amount of time since the last firing, in seconds
   Projectile projectile;           // information of the projectile fired
   Howitzer howitzer;               // information of the Howitzer
   double timeUnit;
   Position target;
   Position posTextStatus;

   Status status;

   string getStatus()
   {
      switch (status)
      {
      case Status::READY:
         return "READY";
      case Status::FIRED:
         return "FIRED";
      case Status::HIT_TARGET:
         return "HIT_TARGET";
      case Status::MISS:
         return "MISS";
      default:
         return "UNKNOWN";
      }
   }

   // Tables
   vector<pair<double, double>> gravityTable;
   vector<pair<double, double>> airDensityTable;
   vector<pair<double, double>> dragCoefficientTable;
   vector<pair<double, double>> speedOfSoundTable;
};
