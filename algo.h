#include <iostream> //cout,endl
#include <iomanip> //setw
#include <stdlib.h>
#include <fstream> //ofstream
#include "global.h" //define
#include <cstring>  //strcmp
#include <cmath>
#define _USE_MATH_DEFINES
//#include "planet.h"
#include <vector>
using namespace std;
class Planet;
class Algo{
 private:
  int integration_points;
  double final_time;
  int n; //integration points
  double b,h,dt,G;
  vector<Planet*> p_vec; //planet vector with pointer to all planets
  ofstream outfile;
  ofstream efile;
  ofstream lfile;
  ofstream anglefile;
 public:
  bool relativistic_correction;
  Algo(double b,int n);
  void add(Planet *p);
  void run_eulercromer();
  void run_euler();
  void run_verlet();
  void print();
  void printInfo();
  void printEnergy(double time);
  void GForce(Planet *current, Planet *other, double F[]);
  void KineticEnergy();
  void PotentialEnergy();
  void GravitationalForce(Planet *current, Planet *other, double &Fx, double &Fy, double &Fz);
  double** getMatrix(int row,int col);
  void delete_matrix(double **matrix);
};
