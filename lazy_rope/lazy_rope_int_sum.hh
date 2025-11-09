#include <stdlib.h>
#include <vector>


class LazyRopeIntSum {
public:
    LazyRopeIntSum(int n);
    int query(int l, int r);
    void update(int l, int r, int upd);
private:
    std::vector<int> value; 
    std::vector<int> lazy;
    int size;

    int query_impl(int node, int l_, int r_, int l, int r);
    void update_impl(int node, int l_, int r_, int l, int r, int upd);
    void propagate(int node, int l_, int r_);   
};