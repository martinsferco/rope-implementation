#include <concepts>
#include <cassert>
#include <vector>

#define LEFT(node) (2 * node + 1)
#define RIGHT(node) (2 * node + 2)

template<typename Op>
concept Monoidal = requires(Op::Value x, Op::Value y) {
  
  typename Op::Value;
  { Op::op(x, y) } -> std::same_as<typename Op::Value>; 
  // T::op(x, T::op(y, z)) == T::op(T::op(x, y), z)
  { Op::neut()   } -> std::same_as<typename Op::Value>; 
  // T::op(x, T::neut()) == x
  // T::op(T::neut(), x) == x
};


template<typename Op>
requires Monoidal<Op>

class Rope {

public:

  Rope(int n);

  typename Op::Value query(int l, int r);

  void update(int i, typename Op::Value x);

private:

  std::vector<typename Op::Value> data;
  int size;

  void update_aux(int node, int l_, int r_, int i, typename Op::Value x);
  typename Op::Value query_aux(int node, int l_, int r_, int l, int r);
};


template<typename Op>
requires Monoidal<Op>
Rope<Op>::Rope(int n)
{
  assert(n > 0);
  
  size = 1;
  while (size < n) size = size << 1;

  data = std::vector<typename Op::Value>(2 * size + 1);

  for (int i = 0 ; i < data.size() ; i++) 
    data.at(i) = Op::neut();
}


template<typename Op>
requires Monoidal<Op>
typename Op::Value 
Rope<Op>::query(int l, int r)
{
  return query_aux(0, 0, size, l, r);
}

template<typename Op>
requires Monoidal<Op>
void
Rope<Op>::update(int i, typename Op::Value x)
{
  update_aux(0, 0, size, i, x);
}

template<typename Op>
requires Monoidal<Op>
void 
Rope<Op>::update_aux(int node, int l_, int r_, int i, typename Op::Value x)
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

  update_aux(LEFT(node), l_, m, i, x);
  update_aux(RIGHT(node), m, r_, i, x);

  data[node] = Op::op(data[LEFT(node)], data[RIGHT(node)]);
}

template<typename Op>
requires Monoidal<Op>
typename Op::Value 
Rope<Op>::query_aux(int node, int l_, int r_, int l, int r) 
{
  if (l <= l_ && r_ <= r) 
    return data[node];

  if (r <= l_ || r_ <= l) 
    return Op::neut();

  int m = (l_ + r_) / 2;

  return Op::op(query_aux(LEFT(node), l_, m, l, r),
                query_aux(RIGHT(node), m, r_, l, r));
}

