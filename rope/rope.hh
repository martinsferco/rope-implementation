#include <concepts>
#include <vector>

template<typename Op>

// Aca posiblementen tengamos pedir en los concepts cosas como neutro, clausura, etc  
// O algo como Value
class Rope {

public:

  Rope(int n);

  typename Op::Value query(int l, int r);

  void update(int i, typename Op::Value x);

private:

  std::vector<typename Op::Value> data;
};


template<typename Op>
Rope<Op>::Rope(int n)
{
  data = std::vector<typename Op::Value>(n);
}


// Esto va a ser similar a lo que hicimos en RopeSum
template<typename Op>
typename Op::Value 
Rope<Op>::query(int l, int r) {


}

// Esto va a ser similar a lo que hicimos en RopeSum
template<typename Op>
void
Rope<Op>::update(int i, typename Op::Value x) {

}

