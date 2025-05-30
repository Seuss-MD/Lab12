/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>

#include <iostream>
using namespace std;

#include "position.h"
#include "velocity.h"
#include "angle.h"
#include "physics.h"
#include "uiDraw.h"
#include "ground.h"

#define MASS      46.70       // kg
#define RADIUS    0.077545    // m

// forward declaration for the unit test class
class TestProjectile; 

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{

private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      PositionVelocityTime(const Position& p, const Velocity& v, double time)
         : pos(p), v(v), t(time) {
      }

      Position pos;
      Velocity v;
      double t;
   };
   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   list<PositionVelocityTime> flightPath;


public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(MASS), radius(RADIUS) 
   {
      double area = areaFromRadius(radius); 
   }


   void reset() {mass = MASS; radius = RADIUS; flightPath = {}; }

   void fire(Angle a, Position pos, double muzzleVelocity)
   {
      reset();
      Velocity muzzleV;
      muzzleV.set(a, muzzleVelocity);
      PositionVelocityTime path(pos, muzzleV, 1.0);
      flightPath.push_back(path);
   };

   Position getPosition()
   {
      if (!flightPath.empty())
         return flightPath.back().pos; 

   }

   void drawFlightPath(ogstream& gout)
   {

      if (flightPath.empty())
         return;

      int i = 0;
      std::list<PositionVelocityTime>::iterator it = --flightPath.end(); // Start at last element

      do {
         gout.drawProjectile(it->pos, i);
         if (it == flightPath.begin()) 
            return;
         --it;
         ++i;
      } while (i < 5);

   };




   // advance the round forward until the next unit of time
   void advance(double simulationTime);

};