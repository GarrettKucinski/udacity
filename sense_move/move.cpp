#include "localization.h"

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