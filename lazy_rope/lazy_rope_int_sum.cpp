#include "lazy_rope_int_sum.hh"
#include <assert.h>

#define LEFT(node) (2 * node + 1)
#define RIGHT(node) (2 * node + 2)

LazyRopeIntSum::LazyRopeIntSum(int n)
{ 
  assert(n > 0);
  
  size = 1;
  while (size < n) size = size << 1;

  value = std::vector<int>(2 * size - 1);
  lazy = std::vector<int>(2 * size - 1);

  for (int i = 0 ; i < value.size() ; i++) {
    lazy.at(i) = 0;
    value.at(i) = 0;
  }
}


void
LazyRopeIntSum::propagate(int node, int l_, int r_) {
    int len = r_ - l_;

    if (len > 1) {

        lazy[LEFT(node)] = lazy[LEFT(node)] + lazy[node];
        lazy[RIGHT(node)] = lazy[RIGHT(node)] + lazy[node];
    }
    
    value[node] = value[node] + lazy[node] * len;
    lazy[node] = 0;
}




int
LazyRopeIntSum::query_impl(int node, int l_, int r_, int l, int r)
{
    propagate(node, l_, r_); 

    if (l <= l_ && r_ <= r)
        return value[node];

    if (r <= l_ || r_ <= l) 
        return 0;   

    int m = (l_ + r_) / 2;

    return query_impl(LEFT(node), l_, m, l, r) +
           query_impl(RIGHT(node), m, r_, l, r);
}


int
LazyRopeIntSum::query(int l, int r)
{
    return LazyRopeIntSum::query_impl(0, 0, size, l, r);
}



void
LazyRopeIntSum::update_impl(int node, int l_, int r_, int l, int r, int upd)
{
    propagate(node, l_, r_);
    
    if (l <= l_ && r_ <= r) { lazy[node] = upd; propagate(node, l_, r_); return; }
    if (r <= l_ || r_ <= l) { return; }
    
    int m_ = (l_ + r_) / 2;
    
    update_impl(LEFT(node), l_, m_, l, r, upd);
    update_impl(RIGHT(node), m_, r_, l, r, upd);
    
    value[node] = value[LEFT(node)] + value[RIGHT(node)];
}

void
LazyRopeIntSum::update(int l, int r, int upd)
{
    LazyRopeIntSum::update_impl(0, 0, size, l, r, upd);
}


