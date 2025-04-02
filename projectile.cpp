/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


#include <list>
#include <iostream>
#include <iomanip>  // for setprecision and fixed

 #include "projectile.h"
 #include "angle.h"
 #include "position.h"
 #include "velocity.h"
 #include "physics.h"
 #include "acceleration.h"

 using namespace std;


 /*********************************************
  * PROJECTILE : ADVANCE
  *    s  = s0 + v t + ½ a t2 
  *    s  = distance in meters (m)
  *    s0 = initial distance (m)
  *    v  = velocity (m/s)
  *    t  = time (s)
  *    a  = acceleration (m/s2)
  *********************************************/
 void Projectile::advance(double simulationTime)
 {
    if (!flightPath.empty()) 
    {
       PositionVelocityTime lastState = flightPath.back();

       Position pos  = lastState.pos;
       Velocity v    = lastState.v;
       Angle dragA   = v.getAngle();

       Velocity      dragV;
       Acceleration  dragAcc;
       
       double t         = 1.0;

       double altitude  = pos.getMetersY();
       double longitude = pos.getMetersX();

       double g         = - gravityFromAltitude(altitude);
       double density   = densityFromAltitude(altitude);
       double mach      = speedSoundFromAltitude(altitude);
       
       double speed     = v.getSpeed();
       double machSpeed = v.getSpeed()/mach;
       double drag      = dragFromMach(machSpeed);
       double dragForce = forceFromDrag(density, drag, radius, v.getSpeed());

       if (dragForce == 0)
       {
         dragV.setDY(0.0);
         dragV.setDX(0.0);
         dragAcc.setDDY(0.0);
         dragAcc.setDDX(0.0);
       }

       else
       {
       dragV.set(dragA, dragForce);
       dragAcc.set(dragA, dragForce);

       dragAcc.setDDY(accelerationFromForce(dragV.getDY(), mass));
       dragAcc.setDDX(accelerationFromForce(dragV.getDX(), mass));

       dragV.setDY(velocityFromAcceleration(dragAcc.getDDY(), t));
       dragV.setDX(velocityFromAcceleration(dragAcc.getDDX(), t));
       }

       // altitude going down
       if (v.getDY() < 0)
       {
          pos.setMetersY
          (
          altitude + v.getDY() * t + 0.5 * (g + dragAcc.getDDY()) * t * t
          );

          v.addDY(g + dragAcc.getDDY());


          // longitude
          pos.setMetersX
          (
          longitude + v.getDX() * t + (0.5 * + dragAcc.getDDX()) * t * t
          );

          v.addDX(dragAcc.getDDX());
       }

       // altitude going up
       else
       {
          pos.setMetersY
          (
          altitude + v.getDY() * t + 0.5 * (g -dragAcc.getDDY()) * t * t
          );

          v.addDY(g -dragAcc.getDDY());

          // longitude
          pos.setMetersX
          (
          longitude + v.getDX() * t + (0.5 * -dragAcc.getDDX()) * t * t
          );

          v.addDX(-dragAcc.getDDX());
       }

       PositionVelocityTime CurrentState(pos, v, simulationTime);
       flightPath.push_back(CurrentState);
    }
   
 }


