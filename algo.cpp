#include "algo.h"
#include "planet.h"
Algo::Algo(double b, int n)
{
  G = 4*M_PI*M_PI;
  integration_points = n;
  final_time = b;
  h = final_time/((double)integration_points);
  dt = final_time/((double)integration_points);
  relativistic_correction = false;  
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
  double r = current->getDistance(other);

  //NORMAL
  //Fx -= G*current->mass*other->mass*rel_dist[0]/(r*r*r);
  //Fy -= G*current->mass*other->mass*rel_dist[1]/(r*r*r);
  //Fz -= G*current->mass*other->mass*rel_dist[2]/(r*r*r);
  double corr = 0.0;
  /* relativistic correction */
  if(relativistic_correction){
    //l = r x v = (ry*vz-rz*vy)i -(rx*vz-rz*vx)j+(rx*vy-ry*vx)k
    //l^2 = ((ry*vz-rz*vy))i^2 +(-(rx*vz-rz*vx)j)^2+((rx*vy-ry*vx)k)^2
    double l2 = pow((current->pos[1]*current->vel[2]-current->pos[2]*current->vel[1]),2)
      +pow((-(current->pos[0]*current->pos[2]-current->pos[2]*current->vel[0])),2)
      +pow((current->pos[0]*current->vel[1]-current->pos[1]*current->vel[0]),2);
    corr = (3*l2)/(r*r*63145*63145);    
  }
  //POW for testing beta -> 3
  Fx -= (G*current->mass*other->mass*rel_dist[0])/(pow(r,_beta))*(1+corr);
  Fy -= (G*current->mass*other->mass*rel_dist[1])/(pow(r,_beta))*(1+corr);
  Fz -= (G*current->mass*other->mass*rel_dist[2])/(pow(r,_beta))*(1+corr);
}
void Algo::KineticEnergy()
{
  for(int i = 0; i<p_vec.size(); i++)
    p_vec[i]->kEnergy = p_vec[i]->KineticEnergy();
}
 /* set potential energy for all planets to zero 
  * loop over all planets, update current pot energy, 
  * loop over all planets for each planet and update
  * the pot energy */
void Algo::PotentialEnergy()
{
  for(int i = 0; i<p_vec.size(); i++)
    p_vec[i]->pEnergy = 0.0;

  for(int i = 0; i<p_vec.size(); i++)
    for(int j = i+1; j<p_vec.size(); j++) {
      p_vec[i]->pEnergy += p_vec[i]->PotentialEnergy(p_vec[j],G);
      p_vec[j]->pEnergy += p_vec[j]->PotentialEnergy(p_vec[i],G);
    }
}
void Algo::printEnergy(double time)
{
  KineticEnergy();
  PotentialEnergy();
  efile<<time<<" ";
  for(int i = 0; i<p_vec.size(); i++) {
    efile<<p_vec[i]->kEnergy<<" "<<p_vec[i]->pEnergy<<" ";
  }
  efile<<endl;
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

void Algo::run_eulercromer()
{
  /* file init */
  outfile.open("eulercromer.txt",ofstream::out | ofstream::trunc);

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
  /* file init */
  outfile.open("euler.txt",ofstream::out | ofstream::trunc);
  efile.open("euler_energy.txt",ofstream::out | ofstream::trunc);
  lfile.open("euler_l.txt",ofstream::out | ofstream::trunc);  
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
	/* angular momentum */
	if(!strcmp(p_vec[p]->name,"Earth"))
	  lfile<<time<<" "<<p_vec[p]->AngularMomentum()<<endl;
	double Fx = - G*p_vec[sun]->mass*p_vec[p]->mass*p_vec[p]->pos[0]/(r*r*r);
	double Fy = - G*p_vec[sun]->mass*p_vec[p]->mass*p_vec[p]->pos[1]/(r*r*r);
	double Fz = - G*p_vec[sun]->mass*p_vec[p]->mass*p_vec[p]->pos[2]/(r*r*r);
	double ax = Fx/p_vec[p]->mass;
	double ay = Fy/p_vec[p]->mass;
	double az = Fz/p_vec[p]->mass;
	
	p_vec[p]->pos[0] = p_vec[p]->pos[0]+h*p_vec[p]->vel[0];
	p_vec[p]->pos[1] = p_vec[p]->pos[1]+h*p_vec[p]->vel[1];
	p_vec[p]->pos[2] = p_vec[p]->pos[2]+h*p_vec[p]->vel[2];
	p_vec[p]->vel[0] = p_vec[p]->vel[0]+h*ax;
	p_vec[p]->vel[1] = p_vec[p]->vel[1]+h*ay;
	p_vec[p]->vel[2] = p_vec[p]->vel[2]+h*az;
      }
      outfile<<p_vec[p]->pos[0]<<" "<<p_vec[p]->pos[1]<<" "<<p_vec[p]->pos[2]<<" ";
    }
    printEnergy(time);
    outfile<<endl;
    time+=h;
  }
  outfile.close();
  efile.close();
  lfile.close();
}

void Algo::run_verlet()
{
  /* file init */
  outfile.open("verlet.txt",ofstream::out | ofstream::trunc);
  efile.open("energy.txt",ofstream::out | ofstream::trunc);
  anglefile.open("angle.txt",ofstream::out | ofstream::trunc);
  lfile.open("l.txt",ofstream::out | ofstream::trunc);
  
  /* writing headers to file */
  efile<<"time"<<" ";
  for(int p = 0; p<p_vec.size(); p++){
    outfile<<p_vec[p]->name<<"x"<<" ";
    outfile<<p_vec[p]->name<<"y"<<" ";
    outfile<<p_vec[p]->name<<"z"<<" ";
    efile<<p_vec[p]->name<<"k"<<" "<<p_vec[p]->name<<"p"<<" ";
  }
  outfile<<endl;
  efile<<endl;
  /* loopning over all planets */
  for(int p = 0; p<p_vec.size(); p++){
    /* writing initial to file */
    outfile<<p_vec[p]->pos[0]<<" "<<p_vec[p]->pos[1]<<" "<<p_vec[p]->pos[2]<<" ";
  }
  outfile<<endl;

  /* init */
  double angmom = 0.0;
  double Fx,Fy,Fz,Fxn,Fyn,Fzn;
  double **a = getMatrix(p_vec.size(),dim);
  double **anew = getMatrix(p_vec.size(),dim);
  /* clock/timer */
  clock_t start, stop;
  start = clock();
  /* loop time  */
  double time = 0.0+dt;
  while(time<final_time){
    /* loop all planets */
    for(int i = 0; i<p_vec.size(); i++) {
      if(!strcmp(p_vec[i]->name,"Sun"))
	continue;
      /* angular momentum */
      if(!strcmp(p_vec[i]->name,"Earth"))
	lfile<<time<<" "<<p_vec[i]->AngularMomentum()<<endl;
      /* reset forces */
      Fx = Fy = Fz = Fxn = Fyn = Fzn = 0.0;
      
      /* calculate forces */
      for(int j = 0; j<p_vec.size(); j++){
	if(i != j) {
	  GravitationalForce(p_vec[i],p_vec[j],Fx,Fy,Fz);
	}
      }

      /* calculate acceleration */
      a[i][0] = Fx/p_vec[i]->mass;
      //cout<<"a: "<<a[i][0]<<" Fx: "<<Fx<<" mass: "<<p_vec[i]->mass<<endl;
      a[i][1] = Fy/p_vec[i]->mass;
      a[i][2] = Fz/p_vec[i]->mass;
      
      /* calculate pos */
      for(int j = 0; j<dim; j++) {
	  p_vec[i]->pos[j] += p_vec[i]->vel[j]*dt+0.5*dt*dt*a[i][j];
      }
      if(!strcmp(p_vec[i]->name,"Mercury")){
	for(int j = 0; j<p_vec.size(); j++){
	  if(i!=j) {
	    anglefile<<p_vec[i]->pos[0]<<" "<<p_vec[i]->pos[1]<<" "<<p_vec[i]->getDistance(p_vec[j])<<endl;
	  }
	}
      }
      /* loop all planets */
      for(int j = 0; j<p_vec.size(); j++) {
	if(i != j) {
	  GravitationalForce(p_vec[i],p_vec[j],Fxn,Fyn,Fzn);
	}
      }
      /* calculate acceleration exerted for this planet */
      anew[i][0] = Fxn/p_vec[i]->mass;
      anew[i][1] = Fyn/p_vec[i]->mass;
      anew[i][2] = Fzn/p_vec[i]->mass;
      
      for(int j = 0; j<dim; j++) 
	p_vec[i]->vel[j] += 0.5*dt*(a[i][j]+anew[i][j]);      
      
    }// end loop planets
    printEnergy(time);
    /* write positions to file */
    for(int i = 0; i<p_vec.size(); i++)
      outfile<<p_vec[i]->pos[0]<<" "<<p_vec[i]->pos[1]<<" "<<p_vec[i]->pos[2]<<" ";
    outfile<<endl;
    
    time += dt;
  }// end loop time
  stop = clock();
  cout<<"Algorithm time: "<<((float) (stop-start)/CLOCKS_PER_SEC)<<"s"<<endl;
  efile.close();
  lfile.close();
  anglefile.close();
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
