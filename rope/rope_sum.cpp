#include "rope_sum.hh"

RopeSum::RopeSum(int n)
{
  data = std::vector<int>(n);
}

void
RopeSum::update(int i, int x)
{
  RopeSum::update_aux(0, 0, data.size(), i, x);
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

  update_aux(left_child(node), l_, m, i, x);
  update_aux(right_child(node), m, r_, i, x);

  data[node] = data[left_child(node)] + data[right_child(node)];
}


int 
RopeSum::interval_sum(int l, int r) 
{
  return interval_sum_aux(0, 0, data.size(), l, r);
}


int 
RopeSum::interval_sum_aux(int node, int l_, int r_, int l, int r) {

  if (l <= l_ && r_ <= r) 
    return data[node];

  if (r <= l_ || r_ <= l) 
    return 0;

  int m = (l_ + r_) / 2;

  return interval_sum_aux(left_child(node), l_, m, l, r) +
         interval_sum_aux(right_child(node), m, r_, l, r);
}


inline int
RopeSum::left_child(int nodo) { return 2 * nodo + 1; }

inline int
RopeSum::right_child(int nodo) { return 2 * nodo + 2; }

