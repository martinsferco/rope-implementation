#include <stdio.h>
#include <assert.h>
#include <vector>

#include "lazy_rope_int_sum.hh"

void test_lazy_rope_int_sum();
void test_lazy_rope_int_max();

void test_generic_lazy_rope_int_sum();
void test_generic_lazy_rope_int_max();


int main() {

    test_lazy_rope_int_sum();
    test_lazy_rope_int_max();
    test_generic_lazy_rope_int_sum();
    test_generic_lazy_rope_int_max();
}


void test_lazy_rope_int_sum()
{
    std::vector<int> ropeValues = std::vector<int> { 1, -3, 8, 2, 5, -6 };
    LazyRopeIntSum rope = LazyRopeIntSum(ropeValues.size());

    for (int i = 0 ; i < ropeValues.size() ; i++)
        rope.update(i, i + 1, ropeValues.at(i));

    for (int i = 0 ; i < ropeValues.size() ; i++)
        assert(rope.query(i, i + 1) == ropeValues.at(i));

    assert(rope.query(0, 3) == 6);
    assert(rope.query(0, 2) == -2);
    assert(rope.query(2, 4) == 10);
    assert(rope.query(0, ropeValues.size()) == 7);

    rope.update(0, ropeValues.size(), 2);
    assert(rope.query(0, ropeValues.size()) == 19);
    assert(rope.query(0, 2) == 2);

    rope.update(0, 2, 2);
    assert(rope.query(0, 2) == 6);
    assert(rope.query(0, ropeValues.size()) == 23);
}

void test_lazy_rope_int_max()
{

}
void test_generic_lazy_rope_int_sum()
{

}
void test_generic_lazy_rope_int_max()
{

}
