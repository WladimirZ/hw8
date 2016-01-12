#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void step (double* const qp, const double dt) {
  qp[2] = qp[2] - dt * qp[0] / ( sqrt(qp[0]*qp[0]+qp[1]*qp[1])*(qp[0]*qp[0]+qp[1]*qp[1]) );
  qp[3] = qp[3] - dt * qp[1] / ( sqrt(qp[0]*qp[0]+qp[1]*qp[1])*(qp[0]*qp[0]+qp[1]*qp[1]) );
  qp[0] = qp[0] + dt * qp[2];
  qp[1] = qp[1] + dt * qp[3];
}

double H (const double* const qp) {
  return 0.5 * ( qp[2]*qp[2] + qp[3]*qp[3] ) - 1.0 / sqrt( qp[0]*qp[0] + qp[1]*qp[1] );
}

int main() {
  const double e = 0.6;
  double qp[4] = { 1-e, 0, 0, sqrt((1+e)/(1-e)) }; // q1 q2 p1 p2
  
  const double t_end = 20*M_PI;
  const double dt = 0.0005;
  const int N = int(t_end/dt);
  double t = 0;
  
  ofstream out ("sol");
  out << t << "\t" << qp[0] << "\t" << qp[1] << "\t" << qp[2] << "\t" << qp[3] << "\t" << H(qp) << endl;
  
  for (int i=0; i<N; i++) {
    step(qp,dt);
    t += dt;
    out << t << "\t" << qp[0] << "\t" << qp[1] << "\t" << qp[2] << "\t" << qp[3] << "\t" << H(qp) << endl;
  }
  
  out.close();
  
  return 0;
}