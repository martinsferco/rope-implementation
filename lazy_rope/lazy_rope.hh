#include <concepts>
#include <vector>

#include "lazy_update.hh"

#define LEFT(node) (2 * node + 1)
#define RIGHT(node) (2 * node + 2)


template <typename Op>
requires LazyUpdate<Op>
class LazyRope {

public:

  LazyRope(int n);

  typename Op::Value query(int l, int r);

  void update(int l, int r, typename Op::Update upd);

private:
  std::vector<typename Op::Value> value;
  std::vector<typename Op::Update> lazy;
  int size;

  typename Op::Value query_impl(int node, int l_, int r_, int l, int r);
  void update_impl(int node, int l_, int r_, int l, int r, typename Op::Update upd);  
  void propagate(int node, int l_, int r_);
};


template <typename Op>
requires LazyUpdate<Op>
LazyRope<Op>::LazyRope(int n)
{
  assert(n > 0);
  
  size = 1;
  while (size < n) size = size << 1;

  value = std::vector<typename Op::Value>(2 * size - 1);
  lazy = std::vector<typename Op::Value>(2 * size - 1);

  for (int i = 0 ; i < value.size() ; i++) {
    lazy.at(i) = Op::neut_update();
    value.at(i) = Op::neut_value();
  }
}



template <typename Op>
requires LazyUpdate<Op>
typename Op::Value
LazyRope<Op>::query(int l, int r)
{
  return LazyRope<Op>::query_impl(0, 0, size, l, r);
}

template <typename Op>
requires LazyUpdate<Op>
typename Op::Value
LazyRope<Op>::query_impl(int node, int l_, int r_, int l, int r)
{
    LazyRope<Op>::propagate(node, l_, r_); 

    if (l <= l_ && r_ <= r)
        return value[node];

    if (r <= l_ || r_ <= l) 
        return Op::neut_value();   

    int m = (l_ + r_) / 2;

    return Op::value_op(query_impl(LEFT(node), l_, m, l, r),
                        query_impl(RIGHT(node), m, r_, l, r));
}


template <typename Op>
requires LazyUpdate<Op>
void
LazyRope<Op>::update(int l, int r, typename Op::Update upd)
{
  LazyRope<Op>::update_impl(0, 0, size, l, r, upd);


  for (int i = 0 ; i < value.size() ; i++)
    printf("[%d] = %d ", i, value.at(i));

  printf("\n");

}

template <typename Op>
requires LazyUpdate<Op>
void
LazyRope<Op>::update_impl(int node, int l_, int r_, int l, int r, typename Op::Update upd)
{
    LazyRope<Op>::propagate(node, l_, r_);
    
    if (l <= l_ && r_ <= r) { lazy[node] = upd; LazyRope<Op>::propagate(node, l_, r_); return; }
    if (r <= l_ || r_ <= l) { return; }
    
    int m_ = (l_ + r_) / 2;
    
    update_impl(LEFT(node), l_, m_, l, r, upd);
    update_impl(RIGHT(node), m_, r_, l, r, upd);
    
    value[node] = Op::value_op(value[LEFT(node)], value[RIGHT(node)]);
}


template <typename Op>
requires LazyUpdate<Op>
void
LazyRope<Op>::propagate(int node, int l_, int r_)
{
  int len = r_ - l_;
  
  if (len > 1) {
    lazy[LEFT(node)] = Op::update_op(lazy[LEFT(node)], lazy[node]);
    lazy[RIGHT(node)] = Op::update_op(lazy[RIGHT(node)], lazy[node]);
  }
  
  value[node] = Op::apply(lazy[node], value[node], len);
  lazy[node] = Op::neut_update();
}



