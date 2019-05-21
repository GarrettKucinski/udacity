#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<double> double_v;
typedef vector<string> string_v;
typedef vector<int> int_v;

double_v p;
string_v measurements;
string_v world;
int_v motions;
double pHit;
double pMiss;
double pExact;
double pOvershoot;
double pUndershoot;

double_v sense(double_v p, string Z);
double_v move(double_v p, int U);
void print_probability();

int main() {
  p = {0.2, 0.2, 0.2, 0.2, 0.2};
  measurements = {"red", "green"};
  world = {"green", "red", "red", "green", "green"};
  motions = {1,1};
  pHit = 0.6;
  pMiss = 0.2;
  pExact = 0.8;
  pOvershoot = 0.1;
  pUndershoot = 0.1;

  for(int i = 0; i < measurements.size(); i++) {
    p = sense(p, measurements[i]);
    p = move(p, motions[i]);
  }

  print_probability();

  return 0;
}

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

double_v move(double_v p, int U) {

  double_v q (p.size());
  double s = 0;

  for(int i = 0; i < p.size(); i++) {
    // The modulo operator behaves a bit different in C++ with negatives
    // If we took it as -1 % p.size(), we'd get zero instead of four
    // -1 + p.size() will give us what we would get from -1 % p.size in Python
    if (i-U < 0) {
        s = pExact * p[(i-U) + p.size()];
    }
    else {
        s = pExact * p[(i-U) % p.size()];
    }
    if (i-U-1 < 0) {
        s = s + pOvershoot * p[(i-U-1) + p.size()];
    }
    else {
        s = s + pOvershoot * p[(i-U-1) % p.size()];
    }
    if (i-U+1 < 0) {
        s = s + pUndershoot * p[(i-U+1) + p.size()];
    }
    else {
        s = s + pUndershoot * p[(i-U+1) % p.size()];
    }

    q[i] = (s);
  }

  return q;
}

void print_probability() {
  for(int i = 0; i < p.size(); i++) {
    cout << p[i] << " ";
  }

  cout << endl;
}