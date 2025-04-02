/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION
#include <vector>        // for VECTOR
#include <tuple>         // for TUPLE

// Tables
vector<pair<double, double>> gravityTable = {
     {0.0,    9.807},
     {1000.0, 9.804},
     {2000.0, 9.801},
     {3000.0, 9.797},
     {4000.0, 9.794},
     {5000.0, 9.791},
     {6000.0, 9.788},
     {7000.0, 9.785},
     {8000.0, 9.782},
     {9000.0, 9.779},
     {10000.0,9.776},
     {15000.0,9.761},
     {20000.0,9.745},
     {25000.0,9.730},
     {30000.0,9.715},
     {40000.0,9.684},
     {50000.0,9.654},
     {60000.0,9.624},
     {70000.0,9.594},
     {80000.0,9.564}
};

vector<pair<double, double>> airDensityTable = {
  {0.0, 1.2250000},
  {1000.0, 1.1120000},
  {2000.0, 1.0070000},
  {3000.0, 0.9093000},
  {4000.0, 0.8194000},
  {5000.0, 0.7364000},
  {6000.0, 0.6601000},
  {7000.0, 0.5900000},
  {8000.0, 0.5258000},
  {9000.0, 0.4671000},
  {10000.0, 0.4135000},
  {15000.0, 0.1948000},
  {20000.0, 0.0889100},
  {25000.0, 0.0400800},
  {30000.0, 0.0184100},
  {40000.0, 0.0039960},
  {50000.0, 0.0010270},
  {60000.0, 0.0003097},
  {70000.0, 0.0000828},
  {80000.0, 0.0000185}
};

vector<pair<double, double>> dragCoefficientTable = {
  {0.300, 0.1629},
  {0.500, 0.1659},
  {0.700, 0.2031},
  {0.890, 0.2597},
  {0.920, 0.3010},
  {0.960, 0.3287},
  {0.980, 0.4002},
  {1.000, 0.4258},
  {1.020, 0.4335},
  {1.060, 0.4483},
  {1.240, 0.4064},
  {1.530, 0.3663},
  {1.990, 0.2897},
  {2.870, 0.2297},
  {2.890, 0.2306},
  {5.000, 0.2656}
};

vector<pair<double, double>> speedOfSoundTable = {
  {0.0, 340.0},
  {1000.0, 336.0},
  {2000.0, 332.0},
  {3000.0, 328.0},
  {4000.0, 324.0},
  {5000.0, 320.0},
  {6000.0, 316.0},
  {7000.0, 312.0},
  {8000.0, 308.0},
  {9000.0, 303.0},
  {10000.0, 299.0},
  {15000.0, 295.0},
  {20000.0, 295.0},
  {25000.0, 295.0},
  {30000.0, 305.0},
  {40000.0, 324.0},
  {50000.0, 337.0},
  {60000.0, 319.0},
  {70000.0, 289.0},
  {80000.0, 269.0}
};

void Simulator::gamePlay()
{
   projectile.advance(time);

   time += 1.0;
   if (hasFired)
   {
      Position posTarget = ground.getTarget();
      Position posProjectile = projectile.getPosition();

      if (ground.getElevationMeters(projectile.getPosition()) >= posProjectile.getMetersY())
      {
         bool hit = onTarget(posTarget, posProjectile);
         if (hit == true)
            cout << "You hit the target!";
         projectile.reset();
         time = 0.0;
         hasFired = false;
      }
   }
}


bool Simulator::onTarget(Position posTarget, Position posProjectile)
{
   // not on the target if we are too high
   if (posProjectile.getPixelsY() > posTarget.getPixelsY() + 1.0)
      return false;

   // not on the target if we are too far left
   if (posTarget.getPixelsX() - posProjectile.getPixelsX() >= 5.0)
      return false;

   // not on the target if we are too far right
   if (posTarget.getPixelsX() - posProjectile.getPixelsX() <= -5.0)
      return false;

   return true;
}

void Simulator::input(const Interface* pUI)
{
   
   if (pUI->isRight())
      howitzer.rotate(0.05);
   //pSim->angle.add(0.05);
   if (pUI->isLeft())
      howitzer.rotate(-0.05);
   //pSim->angle.add(-0.05);

// move by a little
   if (pUI->isUp())
      howitzer.raise(0.003);
   if (pUI->isDown())
      howitzer.raise(-0.003);

   if (pUI->isSpace())
   {
      projectile.fire(howitzer.getElevation(), ptHowitzer, howitzer.getMuzzleVelocity());
      time = 0.0;
      hasFired = true;
   }
}

void Simulator::display()
{
   ogstream gout;

   ground.draw(gout);
   howitzer.draw(gout, time);
   projectile.drawFlightPath(gout);

   if (hasFired)
   {
      // draw some text on the screen
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      gout << " Time since the bullet was fired: "
         << time << "s\n";
   }

}

