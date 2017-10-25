#include "algo.h"
#include "planet.h"
Algo::Algo(double b, int n)
{
  G = 4*M_PI*M_PI;
  integration_points = n;
  final_time = b;
  h = final_time/((double)integration_points);
  dt = final_time/((double)integration_points);
}
void Algo::add(Planet *p)
{
  p_vec.push_back(p);
}

void Algo::GForce(Planet *current, Planet *other, double F[])
{
  double r_rel[dim];
  double r = current->getDistance(other);
  for(int i = 0; i<dim; i++) {
    r_rel[i] = current->pos[i]-other->pos[i];
    F[i] -=G*current->mass*other->mass*r_rel[i]/(r*r*r);
  }
}
/* calculates the Gravitational force 
 * rel_dist is x_rel, y_rel, z_rel */
void Algo::GravitationalForce(Planet *current, Planet *other, double &Fx,double &Fy,double &Fz)
{
  double rel_dist[dim];
  for(int i = 0; i<dim; i++){
    rel_dist[i] = current->pos[i]-other->pos[i];
  }
  cout<<"current pos: "<<current->pos[0]<<endl;
  cout<<"other pos: "<<other->pos[0]<<endl;
  double r = current->getDistance(other);
  cout<<"rel_dist: "<<rel_dist[0]<<endl;
  cout<<"r "<<r<<endl;
  Fx -= G*current->mass*other->mass*rel_dist[0]/(r*r*r);
  Fy -= G*current->mass*other->mass*rel_dist[1]/(r*r*r);
  Fz -= G*current->mass*other->mass*rel_dist[2]/(r*r*r);
  cout<<"GFx: "<<Fx<<endl;
}
/* create matrix on heap 
 * returns pointer */
double** Algo::getMatrix(int row,int col)
{
  double** matrix;
  matrix = new double*[row];
  for(int i = 0; i<row; i++)
    matrix[i] = new double[col];
  for(int i = 0; i<row; i++){
    for(int j = 0; j<col; j++)
      matrix[i][j] = 0.0;
  }
  return matrix;
}
void Algo::printInfo()
{
  cout<<"integrationpoints: "<<integration_points<<endl;
  cout<<"finaltime: "<<final_time<<endl;
  cout<<"h: "<<h<<endl;  
}
void Algo::run_simple_euler()
{
  /* file init */
  outfile.open("data.txt",ofstream::out | ofstream::trunc);

  /* writing headers to file */
  int sun = 0; 
  double r;
  for(int p = 0; p<p_vec.size(); p++){
    outfile<<p_vec[p]->name<<"x"<<" ";
    outfile<<p_vec[p]->name<<"y"<<" ";
    outfile<<p_vec[p]->name<<"z"<<" ";
    if(!strcmp(p_vec[p]->name,"Sun"))
      sun = p;
  }
  outfile<<endl;
  
  /* loopning over all planets */
  for(int p = 0; p<p_vec.size(); p++){
    /* writing initial to file */
    outfile<<p_vec[p]->pos[0]<<" "<<p_vec[p]->pos[1]<<" "<<p_vec[p]->pos[2]<<" ";
  }
  outfile<<endl;
  /* loop time  */
  double time = 0.0+h;
  while(time<final_time) {
    /* loop all planets */
    for(int p = 0; p<p_vec.size(); p++) {
      /* calculating one step for one planet */
      r = sqrt(p_vec[p]->pos[0]*p_vec[p]->pos[0]+p_vec[p]->pos[1]*p_vec[p]->pos[1]+p_vec[p]->pos[2]*p_vec[p]->pos[2]);
      /* skip calculations for the Sun when in origo*/
      if(r!=0){
	double Fx = - G*p_vec[sun]->mass*p_vec[p]->mass*p_vec[p]->pos[0]/(r*r*r);
	cout<<Fx<<endl;
	double Fy = - G*p_vec[sun]->mass*p_vec[p]->mass*p_vec[p]->pos[1]/(r*r*r);
	double Fz = - G*p_vec[sun]->mass*p_vec[p]->mass*p_vec[p]->pos[2]/(r*r*r);
	double ax = Fx/p_vec[p]->mass;
	double ay = Fy/p_vec[p]->mass;
	double az = Fz/p_vec[p]->mass;
	p_vec[p]->vel[0] = p_vec[p]->vel[0]+h*ax;
	p_vec[p]->vel[1] = p_vec[p]->vel[1]+h*ay;
	p_vec[p]->vel[2] = p_vec[p]->vel[2]+h*az;
	p_vec[p]->pos[0] = p_vec[p]->pos[0]+h*p_vec[p]->vel[0];
	p_vec[p]->pos[1] = p_vec[p]->pos[1]+h*p_vec[p]->vel[1];
	p_vec[p]->pos[2] = p_vec[p]->pos[2]+h*p_vec[p]->vel[2];
      }
      outfile<<p_vec[p]->pos[0]<<" "<<p_vec[p]->pos[1]<<" "<<p_vec[p]->pos[2]<<" ";
    }
    outfile<<endl;
    time+=h;
  }
  outfile.close();
}
void Algo::run_euler()
{

}

void Algo::run_verlet()
{
  /* file init */
  outfile.open("vv.txt",ofstream::out | ofstream::trunc);
  
  /* writing headers to file */
  for(int p = 0; p<p_vec.size(); p++){
    outfile<<p_vec[p]->name<<"x"<<" ";
    outfile<<p_vec[p]->name<<"y"<<" ";
    outfile<<p_vec[p]->name<<"z"<<" ";
  }
  outfile<<endl;
  /* loopning over all planets */
  for(int p = 0; p<p_vec.size(); p++){
    /* writing initial to file */
    outfile<<p_vec[p]->pos[0]<<" "<<p_vec[p]->pos[1]<<" "<<p_vec[p]->pos[2]<<" ";
  }
  outfile<<endl;

  /* init */
  double Fx,Fy,Fz,Fxn,Fyn,Fzn;
  double **a = getMatrix(p_vec.size(),dim);
  double **anew = getMatrix(p_vec.size(),dim);
  
  /* loop time  */
  double time = 0.0+dt;
  // while(time<final_time) {
  while(time<final_time){
    cout<<"time: "<<time<<endl;
    /* loop all planets */
    for(int i = 0; i<p_vec.size(); i++) {
      /* reset forces */
      Fx = Fy = Fz = Fxn = Fyn = Fzn = 0.0;
      
      /* calculate forces */
      for(int j = i+1; j<p_vec.size(); j++) 
	GravitationalForce(p_vec[i],p_vec[j],Fx,Fy,Fz);
      
      /* calculate acceleration */
      a[i][0] = Fx/p_vec[i]->mass;
      cout<<"a: "<<a[i][0]<<" Fx: "<<Fx<<" mass: "<<p_vec[i]->mass<<endl;
      a[i][1] = Fy/p_vec[i]->mass;
      a[i][2] = Fz/p_vec[i]->mass;
      
      /* calculate pos */
      for(int j = 0; j<dim; j++) {
	p_vec[i]->pos[j] += p_vec[i]->vel[j]*dt+0.5*dt*dt*a[i][j];
	if(j == 0)
	  cout<<"pos: "<<p_vec[i]->vel[j]*dt*0.5*dt*dt*a[i][j]<<" pos-> "<<p_vec[i]->pos[j]<<endl;
      }
      /* loop all planets */
      for(int j = i+1; j<p_vec.size(); j++) 
	GravitationalForce(p_vec[i],p_vec[j],Fxn,Fyn,Fzn);
      
      /* calculate acceleration exerted for this planet */
      anew[i][0] = Fxn/p_vec[i]->mass;
      anew[i][1] = Fyn/p_vec[i]->mass;
      anew[i][2] = Fzn/p_vec[i]->mass;
      
      for(int j = 0; j<dim; j++) 
	p_vec[i]->vel[j] += 0.5*dt*(a[i][j]+anew[i][j]);      
      
      
    }// end loop planets
    for(int i = 0; i<p_vec.size(); i++)
      outfile<<p_vec[i]->pos[0]<<" "<<p_vec[i]->pos[1]<<" "<<p_vec[i]->pos[2]<<" ";
    outfile<<endl;
    time += dt;
  }// end loop time
  outfile.close();
  delete_matrix(a);
  delete_matrix(anew);
}// end vv method
/* Deallocation of matrix */
void Algo::delete_matrix(double **matrix)
{ 
  for (int i=0; i<p_vec.size(); i++)
    delete [] matrix[i];
  delete [] matrix;
}
