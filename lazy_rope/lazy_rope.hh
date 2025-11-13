#include <concepts>
#include <vector>

#include "../concepts/lazy_rope_op.hh"
#include "../utils/utils.hh"


template <typename Op>
requires LazyRopeOp<Op>
class LazyRope {

public:

  LazyRope(int n);

  typename Op::Value::Value query(int l, int r);

  void update(int l, int r, typename Op::Update::Value upd);

private:
  std::vector<typename Op::Value::Value> value;
  std::vector<typename Op::Update::Value> lazy;
  int size;

  typename Op::Value::Value query_impl(int node, int l_, int r_, int l, int r);
  void update_impl(int node, int l_, int r_, int l, int r, typename Op::Update::Value upd);  
  void propagate(int node, int l_, int r_);
};


template <typename Op>
requires LazyRopeOp<Op>
LazyRope<Op>::LazyRope(int n)
{
  assert(n > 0);
  
  size = 1;
  while (size < n) size = size << 1;

  value = std::vector<typename Op::Value::Value>(2 * size - 1);
  lazy = std::vector<typename Op::Update::Value>(2 * size - 1);

  for (int i = 0 ; i < value.size() ; i++) {
    value.at(i) = Op::Value::neut();
    lazy.at(i) = Op::Update::neut();
  }
}



template <typename Op>
requires LazyRopeOp<Op>
typename Op::Value::Value
LazyRope<Op>::query(int l, int r)
{
  return LazyRope<Op>::query_impl(0, 0, size, l, r);
}

template <typename Op>
requires LazyRopeOp<Op>
typename Op::Value::Value
LazyRope<Op>::query_impl(int node, int l_, int r_, int l, int r)
{
    LazyRope<Op>::propagate(node, l_, r_); 

    if (l <= l_ && r_ <= r)
        return value[node];

    if (r <= l_ || r_ <= l) 
        return Op::Value::neut();   

    int m = (l_ + r_) / 2;

    return Op::Value::op(query_impl(LEFT(node), l_, m, l, r),
                         query_impl(RIGHT(node), m, r_, l, r));
}


template <typename Op>
requires LazyRopeOp<Op>
void
LazyRope<Op>::update(int l, int r, typename Op::Update::Value upd)
{
  LazyRope<Op>::update_impl(0, 0, size, l, r, upd);
}

template <typename Op>
requires LazyRopeOp<Op>
void
LazyRope<Op>::update_impl(int node, int l_, int r_, int l, int r, typename Op::Update::Value upd)
{
  LazyRope<Op>::propagate(node, l_, r_);
  
  if (l <= l_ && r_ <= r) { lazy[node] = upd; LazyRope<Op>::propagate(node, l_, r_); return; }
  if (r <= l_ || r_ <= l) { return; }
  
  int m_ = (l_ + r_) / 2;
  
  update_impl(LEFT(node), l_, m_, l, r, upd);
  update_impl(RIGHT(node), m_, r_, l, r, upd);
  
  value[node] = Op::Value::op(value[LEFT(node)], value[RIGHT(node)]);
}


template <typename Op>
requires LazyRopeOp<Op>
void
LazyRope<Op>::propagate(int node, int l_, int r_)
{
  int len = r_ - l_;
  
  if (len > 1) {
    lazy[LEFT(node)] = Op::Update::op(lazy[LEFT(node)], lazy[node]);
    lazy[RIGHT(node)] = Op::Update::op(lazy[RIGHT(node)], lazy[node]);
  }
  
  value[node] = Op::apply(lazy[node], value[node], len);
  lazy[node] = Op::Update::neut();
}



