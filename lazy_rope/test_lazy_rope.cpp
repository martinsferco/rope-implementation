#include <stdio.h>
#include <assert.h>
#include <vector>
#include <climits>

#include "lazy_rope_int_sum.hh"
#include "lazy_rope.hh"

void test_lazy_rope_int_sum();
void test_generic_lazy_rope_int_sum_sum();
void test_generic_lazy_rope_int_sum_max();


int main() {

    test_lazy_rope_int_sum();
    test_generic_lazy_rope_int_sum_sum();
    test_generic_lazy_rope_int_sum_max();
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

    printf("[PASS] Test lazy rope int sum\n");
}


struct IntSum {

    using Value = int;
    static int op(int x, int y) { return x + y; }
    static int neut() { return 0; }
};


struct IntMax {

    using Value = int;
    static int op(int x, int y) { return x < y ? y : x; }
    static int neut() { return INT_MIN; }
};


struct IntSumSum {

    using Value = IntSum;
    using Update = IntSum;

    static int apply(int upd, int val, int len) {
        return val + upd * len; 
    }
};


struct IntSumMax {

    using Value = IntMax;
    using Update = IntSum;

    static int apply(int upd, int val, int len) {
        return val + upd; 
    }
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

    printf("[PASS] Test generic lazy rope int sum sum\n");
}





void test_generic_lazy_rope_int_sum_max()
{
    std::vector<int> ropeValues = std::vector<int> { 1, -3, 8, 2, 5, -6 };
    LazyRope<IntSumMax> rope = LazyRope<IntSumMax>(ropeValues.size());

    // Normalizamos a 0 todos los valores.
    rope.update(0, ropeValues.size(), -INT_MIN);

    for (int i = 0 ; i < ropeValues.size() ; i++)
        rope.update(i, i + 1, ropeValues.at(i));

    for (int i = 0 ; i < ropeValues.size() ; i++)
        assert(rope.query(i, i + 1) == ropeValues.at(i));

    assert(rope.query(0, 2) == 1);
    assert(rope.query(0, ropeValues.size()) == 8);
    assert(rope.query(1, 5) == 8);

    rope.update(4, 6, 10);
    assert(rope.query(0, ropeValues.size()) == 15);

    printf("[PASS] Test generic lazy rope int sum max\n");
}
