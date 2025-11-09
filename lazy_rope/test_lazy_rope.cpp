#include <stdio.h>
#include <assert.h>
#include <vector>
#include <climits>

#include "lazy_rope_int_sum.hh"
#include "lazy_rope.hh"

void test_lazy_rope_int_sum();

void test_generic_lazy_rope_int_sum_sum();
void test_generic_lazy_rope_int_max();


int main() {

    test_lazy_rope_int_sum();
    test_generic_lazy_rope_int_sum_sum();
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


struct IntSumSum {

    using Value = int;
    using Update = int;

    static int apply(int upd, int val, int len) {
        return val + upd * len; 
    }

    static int value_op(int x, int y) { return x + y; }
    static int update_op(int x, int y) { return x + y; }

    static int neut_value() { return 0; }
    static int neut_update() { return 0; }

};


void test_generic_lazy_rope_int_sum_sum() {
    std::vector<int> ropeValues = std::vector<int> { 1, -3, 8, 2, 5, -6 };
    LazyRope<IntSumSum> rope = LazyRope<IntSumSum>(ropeValues.size());

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



struct IntSumMax {

    using Value = int;
    using Update = int;

    static int apply(int upd, int val, int len) {
        return val + upd; 
    }

    static int value_op(int x, int y) { return x < y ? y : x; }
    static int update_op(int x, int y) { return x + y; }

    static int neut_value() { return INT_MIN; }
    static int neut_update() { return 0; }
};

void test_generic_lazy_rope_int_max()
{
    std::vector<int> ropeValues = std::vector<int> { 1, -3, 8, 2, 5, -6 };
    LazyRope<IntSumMax> rope = LazyRope<IntSumMax>(ropeValues.size());

    for (int i = 0 ; i < ropeValues.size() ; i++)
        rope.update(i, i + 1, ropeValues.at(i));

    for (int i = 0 ; i < ropeValues.size() ; i++)
        assert(rope.query(i, i + 1) == ropeValues.at(i));

    assert(rope.query(0, 2) == 1);
    assert(rope.query(0, ropeValues.size()) == 8);
    assert(rope.query(1, 5) == 8);

    rope.update(4, 6, 10);
    assert(rope.query(0, ropeValues.size()) == 15);
}
