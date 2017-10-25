#include <iostream>
#include <stdlib.h>
#include "planet.h"
#include <vector>
#include <math.h>
#include "algo.h"
#include "time.h"
#include "global.h"
using namespace std;
int main(int argc, char **argv)
{
  //  cout<<"c:"<<argc<<endl;
  //cout<<"v0:"<<argv[0]<<endl;
  //cout<<"v1:"<<argv[1]<<endl;
  //cout<<"v2:"<<argv[2]<<endl;
  /* Planet(mass,x,y,z,vx,vy,vz) 
   * masses are given in 10^24 (solar mass) 
   * Algo constructor takes steps, integration points 
   * Planet constructor takes name, mass, distance, x, y ,z, vx, vy, vz, nasa */
  Algo *a = new Algo(_final_time,_integration_points);
  a->add(new Planet("Earth",0.000003,1.0,1.0,0.0,0.0,0.0,2*M_PI,0.0,false));
  a->add(new Planet("Sun",1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,false));

    //a->add(new Planet("Earth",0.000003,_distance_earth,_x_earth,_y_earth,_z_earth,_vx_earth,_vy_earth,_vz_earth,true));
  //a->add(new Planet("Mercury",0.000000165,_distance_mercury,_x_mercury,_y_mercury,_z_mercury,_vx_mercury,_vy_mercury,_vz_mercury,true));
  //a->add(new Planet("Neptune",0.0000515,_distance_neptune,_x_neptune,_y_neptune,_z_neptune,_vx_neptune,_vy_neptune,_vz_neptune,true));
  //a->add(new Planet("Venus",0.00000245,_distance_venus,_x_venus,_y_venus,_z_venus,_vx_venus,_vy_venus,_vz_venus,true));
  //a->add(new Planet("PlanetX",0.006,2.0,2.0,0.0,0.0,0.0,1*M_PI,0.0,false));
  /* info */
  //a->print();

  /* timer */
  clock_t start,stop;

  /* run algorithm: simple euler */
  start = clock();
  //a->run_simple_euler();
  //a->printInfo();
  a->run_verlet();
  stop = clock();
  cout<<"Total Time: "<<((float)(stop-start)/CLOCKS_PER_SEC)<<"seconds"<<endl;  
  //  a->run_euler();


  return 0;
}
