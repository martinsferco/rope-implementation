#include <concepts>
#include <vector>

#include "lazy_update.hh"


template <typename Op>
requires LazyUpdate<Op>

class LazyRope {

public:

  LazyRope(int n);

  typename Op::Value query(int l, int r);

  void update(int l, int r, typename Op::Update x);

private:
  std::vector<typename Op::Value> data;
  std::vector<typename Op::Update> lazy;
  int size;
};


template <typename Op>
requires LazyUpdate<Op>
LazyRope<Op>::LazyRope(int n)
{
  assert(n > 0);
  
  size = 1;
  while (size < n) size = size << 1;

  data = std::vector<typename Op::Value>(2 * size - 1);
  lazy = std::vector<typename Op::Value>(2 * size - 1);

  for (int i = 0 ; i < data.size() ; i++) {
    lazy.at(i) = Op::neut();
    data.at(i) = Op::neut();
  }

}



template <typename Op>
requires LazyUpdate<Op>
typename Op::Value
LazyRope<Op>::query(int l, int r)
{

}

template <typename Op>
requires LazyUpdate<Op>
void
LazyRope<Op>::update(int l, int r, typename Op::Update x)
{

}


