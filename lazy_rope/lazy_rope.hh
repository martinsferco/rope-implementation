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

};


template <typename Op>
requires LazyUpdate<Op>
LazyRope<Op>::LazyRope(int n)
{
  data = std::vector<typename Op::Value>(n);
  lazy = std::vector<typename Op::Update>(n);
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


