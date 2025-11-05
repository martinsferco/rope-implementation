#include "rope.hh"
#include "rope_sum.hh"
#include <vector>
#include <assert.h>
#include <string>
#include <set>

int main() {

  test_rope_sum();
  test_rope_int_sum();
  test_rope_string_concat();
  test_rope_sets_union();

  return 0;
}


void test_rope_sum() {

  std::vector<int> ropeValues = { 3, 7, -1, -1, 9};
  RopeSum rope = RopeSum(ropeValues.size());

  
  for (int i = 0 ; i < ropeValues.size() ; i++) 
    rope.update(i, ropeValues.at(i));

  
  for (int i = 0 ; i < ropeValues.size() ; i++) 
    assert(rope.interval_sum(i, i + 1) == ropeValues.at(i));

  assert(rope.interval_sum(1,4) == 5);
}


struct Sum {
  
  using Value = int;
  static int op(int x, int y) { return x + y; }
  static int neut() { return 0; } 
};

void test_rope_int_sum() {

  std::vector<int> ropeValues = { 3, 7, -1, -1, 9};
  Rope<Sum> ropeSum = Rope<Sum>(ropeValues.size());

  for (int i = 0 ; i < ropeValues.size() ; i++) 
    ropeSum.update(i, ropeValues.at(i));

  
  for (int i = 0 ; i < ropeValues.size() ; i++) 
    assert(ropeSum.query(i, i + 1) == ropeValues.at(i));

  assert(ropeSum.query(1,4) == 5);
}

struct Concat {
  
  using Value = std::string;
  static std::string op(std::string s, std::string t) { return s + t; }
  static std::string neut() { return ""; }
};

void test_rope_string_concat() {

  std::vector<std::string> ropeValues = { "Hola ", "somos ", "Marto ", "y ", "Octa"};
  Rope<Concat> ropeConcat = Rope<Concat>(ropeValues.size());

  for (int i = 0 ; i < ropeValues.size() ; i++) 
    ropeConcat.update(i, ropeValues.at(i));

  
  for (int i = 0 ; i < ropeValues.size() ; i++) 
    assert(ropeConcat.query(i, i + 1) == ropeValues.at(i));

  assert(ropeConcat.query(0, 6) == "Hola somos Marto y Octa");
  assert(ropeConcat.query(1, 5) == "somos Marto y ");
}


struct Union {

  using Value = std::set<int>;
  static std::set<int> op(std::set<int> a, std::set<int> b)
  { 
    std::set<int> resultado = a;       
    resultado.insert(b.begin(), b.end()); 
    return resultado; 
  }

  static std::set<int> neut() { return std::set<int>(); }
};

void test_rope_sets_union() {

  std::vector<std::set<int>> ropeValues =
  {
    std::set<int>() = {1}, 
    std::set<int>() = {2}, 
    std::set<int>() = {3}, 
    std::set<int>() = {4}, 
    std::set<int>() = {5}, 
  };

  Rope<Union> ropeUnion = Rope<Union>(ropeValues.size());

  for (int i = 0 ; i < ropeValues.size() ; i++) 
    ropeUnion.update(i, ropeValues.at(i));

  
  for (int i = 0 ; i < ropeValues.size() ; i++) 
    assert(ropeUnion.query(i, i + 1) == ropeValues.at(i));

  std::set<int> set_test_1 = std::set<int>() = { 1, 2, 3, 4, 5 };
  std::set<int> set_test_2 = std::set<int>() = { 2, 3, 4 };
  assert(ropeUnion.query(0, 6) == set_test_1);
  assert(ropeUnion.query(1, 5) == set_test_2);
}