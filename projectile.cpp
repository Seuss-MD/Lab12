/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 #include "position.h"
 #include "velocity.h"
 using namespace std;


 /*********************************************
  * PROJECTILE : ADVANCE
  *  
  * 
  * input:   flightPath={pos=100,200 v=0,0 t=100}
  * output:  flightPath={}{pos.x=100      = 100 + 0*1
  *                        pos.y=195.0968 = 200 + 0*1 + .5(-9.806)*1*1
  *                        v.dx =0        = 0 + 0*1
  *                        v.dy =-9.8     = 0 + (-9.8064)*1
  *                        t=101}
  *********************************************/
 void Projectile::advance(double simulationTime)
 {
    if (isFired && !flightPath.empty()) 
    {
       PositionVelocityTime lastState = flightPath.back();

       Position pos = lastState.pos;
       Velocity v = lastState.v;
       const double g = -9.80665;

       pos.setMetersX(pos.getMetersX() + v.getDX() * simulationTime);
       pos.setMetersY(pos.getMetersY() + v.getDX() * simulationTime + 0.5 * g * simulationTime * simulationTime);
       v.setDY(v.getDY() + g * simulationTime);


       flightPath.emplace_back(pos, v, simulationTime);
    }
   

 }


