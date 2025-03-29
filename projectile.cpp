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

       Position pos = lastState.pos;
       Velocity v = lastState.v;
       

       double altitude  = pos.getMetersY();
       double longitude = pos.getMetersX();
       double t = 1.0;

       double g = - gravityFromAltitude(altitude);
       double density = densityFromAltitude(altitude);
       double mach = speedSoundFromAltitude(altitude);
       double speed = v.getSpeed();
       double machSpeed = v.getSpeed()/mach;
       double drag = dragFromMach(machSpeed);

       double dragForceY = forceFromDrag(density, drag, radius, v.getDY());
       double dragForceX = forceFromDrag(density, drag, radius, v.getDX());
       
       

       double dragDDY = accelerationFromForce(dragForceY, mass);
       double dragDDX = accelerationFromForce(dragForceX, mass);

       double dragDY = velocityFromAcceleration(dragDDY, t);
       double dragDX = velocityFromAcceleration(dragDDX, t);


       std::cout << std::fixed << setprecision(14);


       // altitude
       pos.setMetersY(altitude + v.getDY() * t + 0.5 * (g - dragDDY) * t * t);
       cout << "  dragForceY: " << dragForceY << endl;
       cout << "  dragDY:     " << dragDY << endl;
       cout << "  dragDDY:    " << dragDDY << endl;
       cout << "  gravity:    " << g <<endl;

       v.addDY(g - dragDY);


       // longitude
       pos.setMetersX(longitude + v.getDX() * t + (0.5 * - dragDDX) * t * t);

       cout << "  DX:         " << v.getDX() << endl;
       cout << "  Drag:       " << drag << endl;
       cout << "  dragForceX: " << dragForceX << endl;
       cout << "  dragDX:     " << dragDX << endl;
       cout << "  dragDDX:    " << dragDDX << endl << endl;
       v.addDX(- dragDDX);


       PositionVelocityTime CurrentState(pos, v, simulationTime);

       flightPath.push_back(CurrentState);
    }
   
 }


