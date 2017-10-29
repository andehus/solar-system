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
  /* Planet(mass,x,y,z,vx,vy,vz) 
   * masses are given in 10^24 (solar mass) 
   * Algo constructor takes steps, integration points 
   * Planet constructor takes name, mass, distance, x, y ,z, vx, vy, vz, nasa */
  Algo *a = new Algo(_final_time,_integration_points);
  /* exercise a,b,c,d */
  if(true){
    a->add(new Planet("Earth",0.000003,1.0,0.0,0.0,0.0,2.0*M_PI,0.0,false));
    //a->add(new Planet("Jupiter",0.001,5.2,0.0,0.0,0.0,(2*5.2/11.86)*M_PI,0.0,false));
    a->add(new Planet("Sun",1.0,0.0,0.0,0.0,0.0,0.0,0.0,false));
  }
  /* exercise e */
  if(false){
    double com = (m_sun*x_sun+m_earth*x_earth+m_jupiter*x_jupiter)/(m_sun+m_earth+m_jupiter);
    double vysun = -(m_earth*vy_earth+m_jupiter*vy_jupiter);
    a->add(new Planet("Jupiter",m_jupiter,x_jupiter-com,y_jupiter,z_jupiter,vx_jupiter,vy_jupiter,vz_jupiter,false));
    a->add(new Planet("Earth",m_earth,x_earth-com,y_earth,z_earth,vx_earth,vy_earth,vz_earth,false));
    a->add(new Planet("Sun",m_sun,x_sun-com,y_sun,z_sun,vx_sun,vysun,vz_sun,false));
    cout<<"Centre of Mass:  "<<com<<endl;
    cout<<"Velocity of Sun: "<<vysun<<endl;
  }
  /* exercise f */
  if(false){
    //It is safe to do this with subtracting the centre of mass (worst case it would be zero)
    double comx = (_m_sun*_x_sun+_m_mercury*_x_mercury+_m_venus*_x_venus+_m_earth*_x_earth+_m_mars*_x_mars*_m_jupiter*_x_jupiter+_m_saturn*_x_saturn
		  +_m_uranus*_x_uranus+_m_neptune*_x_neptune+_m_pluto*_x_pluto);
    double comy = (_m_sun*_y_sun+_m_mercury*_y_mercury+_m_venus*_y_venus+_m_earth*_y_earth+_m_mars*_y_mars*_m_jupiter*_y_jupiter+_m_saturn*_y_saturn
		  +_m_uranus*_y_uranus+_m_neptune*_y_neptune+_m_pluto*_y_pluto);
    a->add(new Planet("Sun",_m_sun,_x_sun-comx,_y_sun-comy,_z_sun,_vx_sun,_vy_sun,_vz_sun,true));
    a->add(new Planet("Mercury",_m_mercury,_x_mercury-comx,_y_mercury-comy,_z_mercury,_vx_mercury,_vy_mercury,_vz_mercury,true));
    a->add(new Planet("Venus",_m_venus,_x_venus-comx,_y_venus-comy,_z_venus,_vx_venus,_vy_venus,_vz_venus,true));
    a->add(new Planet("Earth",_m_earth,_x_earth-comx,_y_earth-comy,_z_earth,_vx_earth,_vy_earth,_vz_earth,true));
    a->add(new Planet("Mars",_m_mars,_x_mars-comx,_y_mars-comy,_z_mars,_vx_mars,_vy_mars,_vz_mars,true));
    a->add(new Planet("Jupiter",_m_jupiter,_x_jupiter-comx,_y_jupiter-comy,_z_jupiter,_vx_jupiter,_vy_jupiter,_vz_jupiter,true));
    a->add(new Planet("Saturn",_m_saturn,_x_saturn-comx,_y_saturn-comy,_z_saturn,_vx_saturn,_vy_saturn,_vz_saturn,true));
    a->add(new Planet("Uranus",_m_uranus,_x_uranus-comx,_y_uranus-comy,_z_uranus,_vx_uranus,_vy_uranus,_vz_uranus,true));
    a->add(new Planet("Neptune",_m_neptune,_x_neptune-comx,_y_neptune-comy,_z_neptune,_vx_neptune,_vy_neptune,_vz_neptune,true));
    a->add(new Planet("Pluto",_m_pluto,_x_pluto-comx,_y_pluto-comy,_z_pluto,_vx_pluto,_vy_pluto,_vz_pluto,true));
  }
  /* exerise g */
  if(false){
    a->add(new Planet("Sun",1.0,0.0,0.0,0.0,0.0,0.0,0.0,false));
    a->add(new Planet("Mercury",_m_mercury,-0.3075,0.0,0.0,0.0,12.44,0.0,false));
    /* relativistic correction */
    a->relativistic_correction = true;
  }
  /* info */
  //a->print();

  /* timer */
  clock_t start,stop;

  /* run algorithm: simple euler */
  start = clock();
  if(!strcmp(argv[1],"verlet")){
    cout<<"Velocity Verlet"<<endl;
    a->run_verlet();
  }
  else if(!strcmp(argv[1],"euler")){
    cout<<"Euler's Forward"<<endl;
    a->run_euler();
  }
  else if(argv[1] != NULL){
    cout<<"Invalid argument: "<<argv[1]<<endl;
    cout<<"Expecting euler or verlet"<<endl;
  }
  else
    cout<<"Missing argument. Expecting euler or verlet"<<endl;
  //a->printInfo();
  //a->run_verlet();
  stop = clock();
  cout<<"Total Time: "<<((float)(stop-start)/CLOCKS_PER_SEC)<<"seconds"<<endl;  
  //  a->run_euler();


  return 0;
}
