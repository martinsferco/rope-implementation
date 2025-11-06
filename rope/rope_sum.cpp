#include "rope_sum.hh"
#include <cassert>
#include <cstdio>

#define LEFT(node) (2 * node + 1)
#define RIGHT(node) (2 * node + 2)

RopeSum::RopeSum(int n)
{
  assert(n > 0);
  
  size = 1;
  while (size < n) size = size << 1;

  data = std::vector<int>(2 * size + 1);

  for (int i = 0 ; i < data.size() ; i++) 
    data.at(i) = 0;
}

void
RopeSum::update(int i, int x)
{
  RopeSum::update_aux(0, 0, size, i, x);
}

void 
RopeSum::update_aux(int node, int l_, int r_, int i, int x)
{
  int l = i;
  int r = i + 1;

  if (l <= l_ && r_ <= r)
  {
    data[node] = x;
    return;
  }

  if (r <= l_ || r_ <= l) 
    return;

  int m = (l_ + r_) / 2;

  update_aux(LEFT(node), l_, m , i, x);
  update_aux(RIGHT(node), m, r_, i, x);

  
  data[node] = data[LEFT(node)] + data[RIGHT(node)];
}


int 
RopeSum::interval_sum(int l, int r) 
{
  return interval_sum_aux(0, 0, size, l, r);
}


int 
RopeSum::interval_sum_aux(int node, int l_, int r_, int l, int r) {

  if (l <= l_ && r_ <= r) 
    return data[node];

  if (r <= l_ || r_ <= l) 
    return 0;

  int m = (l_ + r_) / 2;

  return interval_sum_aux(LEFT(node), l_, m, l, r) +
         interval_sum_aux(RIGHT(node), m, r_, l, r);
}



