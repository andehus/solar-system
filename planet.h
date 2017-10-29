//#define n 365
#include "global.h"
#include <iostream>
#include <iomanip>
#include <math.h>
class Planet
{
 public:
  const char *name;
  double mass;
  double distance;
  double pos[dim];
  double vel[dim];
  double kEnergy;
  double pEnergy;

  Planet();
  Planet(const char *name, double mass,double x, double y, double z, double vx, double vy, double vz,bool nasa);
  double  getDistance(Planet *other);
  double KineticEnergy();
  double PotentialEnergy(Planet *p, double G);
  double AngularMomentum();
  void print();

};
