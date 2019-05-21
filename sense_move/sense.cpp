#include "localization.h"
#include <string>

using namespace std;

double_v sense(double_v p, string Z) {

  double_v q (p.size());
  double s = 0; 

  for(int i = 0; i < p.size(); i++) {
    bool hit = (Z == world[i]);
    q[i] = (p[i] * (hit * pHit + (1-hit) * pMiss));
    s = s + q[i];
  }
  
  for(int i = 0; i < q.size(); i++) {
    q[i] = q[i] / s;
  }

  return q;
}