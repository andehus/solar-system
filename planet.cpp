#include "planet.h"
Planet::Planet()
{
  mass = 0.0;
}
/* constructor */
Planet::Planet(const char *name,double mass, double distance, double x, double y, double z, double vx, double vy, double vz, bool nasa)
{
  this->mass = mass;
  this->distance = distance;
  pos[0] = x;
  pos[1] = y;
  pos[2] = z;
  vel[0] = vx;
  vel[1] = vy;
  vel[2] = vz;
  /* if real data given in AU/day 
   * mulitply with 365 to get AU/yr */
  if(nasa)
    for(int i = 0; i<3; i++) {
      vel[i]*=365;
    }
  this->name = name;
}
/* calculates r between this and other planet */
/*double Planet::getDistance(Planet *other)
{
  double r = 0.0;
  for(int i = 0; i<dim; i++)
    r += (pos[i]-other->pos[i])*(pos[i]-other->pos[i]);
  //std::cout<<"r: "<<sqrt(r)<<std::endl;
  return sqrt(r);
}
*/
double Planet::getDistance(Planet *other)
{
  double x1,y1,z1,x2,y2,z2,xx,yy,zz;

    x1 = this->pos[0];
    y1 = this->pos[1];
    z1 = this->pos[2];

    x2 = other->pos[0];
    y2 = other->pos[1];
    z2 = other->pos[2];

    xx = x1-x2;
    yy = y1-y2;
    zz = z1-z2;

    return sqrt(xx*xx + yy*yy + zz*zz);
}

