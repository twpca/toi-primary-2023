#include "testlib.h"
#include <bits/stdc++.h>

typedef std::pair<int, int> Edge;
typedef std::vector<Edge> Edges;

/*
O(n)
*/
void shuffle_edges(Edges &edges, int base = 0) {
    shuffle(edges.begin(), edges.end());
    for (auto &e : edges) {
        if (rnd.next(0, 1))
            std::swap(e.first, e.second);
        e.first += base;
        e.second += base;
    }
}

/*
O(nlogn)
*/
void relabel_edges(Edges &edges, int base = 0) {
    std::vector<int> label;
    for (auto &e : edges) {
        label.push_back(e.first);
        label.push_back(e.second);
    }
    std::sort(label.begin(), label.end());
    label.resize(std::unique(label.begin(), label.end()) - label.begin());
    for (auto &e : edges) {
        e.first = std::lower_bound(label.begin(), label.end(), e.first) - label.begin() + base;
        e.second = std::lower_bound(label.begin(), label.end(), e.second) - label.begin() + base;
    }
}

/*
convert from Prüfer sequence
O(nlogn)
*/
Edges uniform_tree(int size, int base = 0) {
    if (size <= 0)
        __testlib_fail("uniform_tree: size must greater then 0");
    if (size == 1)
        return {};
    Edges rt;
    std::vector<int> seq(size - 2), cnt(size, 0);
    std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;
    Edge lst;
    for (int i = 0; i < size - 2; ++i) {
        seq[i] = rnd.next(0, size - 1);
        ++cnt[seq[i]];
    }
    for (int i = 0; i < size; ++i)
        if (!cnt[i])
            leaves.push(i);
    for (int i : seq) {
        rt.push_back(std::make_pair(leaves.top(), i));
        leaves.pop();
        if (!--cnt[i])
            leaves.push(i);
    }
    lst.first = leaves.top();
    leaves.pop();
    lst.second = leaves.top();
    rt.push_back(lst);
    shuffle_edges(rt, base);
    return rt;
}

/*
shuffle the nodes and connect one from prefix for each node, for each node:
type0: no restriction
type1: connect with rnd.next(std::max(0, i - dis), i - 1)
type2: connect with rnd.next(0, std::min(dis - 1, i - 1))
Note that when type not equal to 1 and 2, it is regraded as 0
O(n)
*/
Edges custom_tree(int size, int type, int dis = 1, int base = 0) {
    if (size <= 0)
        __testlib_fail("custom_tree: size must greater then 0");
    if ((type == 1 || type == 2) && dis <= 0)
        __testlib_fail("custom_tree: dis must greater then 0 when type is 1 or 2");
    if (size == 1)
        return {};
    Edges rt;
    std::vector<int> idx(size);
    std::iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());
    for (int i = 1; i < size; ++i)
        if (type == 1)
            rt.push_back(std::make_pair(idx[rnd.next(std::max(0, i - dis), i - 1)], idx[i]));
        else if (type == 2)
            rt.push_back(std::make_pair(idx[rnd.next(0, std::min(dis - 1, i - 1))], idx[i]));
        else
            rt.push_back(std::make_pair(idx[rnd.next(0, i - 1)], idx[i]));
    shuffle_edges(rt, base);
    return rt;
}

/* Returns random permutation of the given size (values are between `first` and `first`+size-1)*/
template<typename T, typename E>
std::vector<E> perm(T size, E first) {
    if (size < 0)
        __testlib_fail("random_t::perm(T size, E first = 0): size must non-negative");
    else if (size == 0)
        return std::vector<E>();
    std::vector<E> p(size);
    E current = first;
    for (T i = 0; i < size; i++)
        p[i] = current++;
    if (size > 1)
        for (T i = 1; i < size; i++)
            std::swap(p[i], p[rnd.next(i + 1)]);
    return p;
}

/* Returns random permutation of the given size (values are between 0 and size-1)*/
template<typename T>
std::vector<T> perm(T size) {
    return perm(size, T(0));
}

/* Returns `size` unordered (unsorted) distinct numbers between `from` and `to`. */
template<typename T>
std::vector<T> distinct(int size, T from, T to) {
    std::vector<T> result;
    if (size == 0)
        return result;

    if (from > to)
        __testlib_fail("random_t::distinct expected from <= to");

    if (size < 0)
        __testlib_fail("random_t::distinct expected size >= 0");

    uint64_t n = to - from + 1;
    if (uint64_t(size) > n)
        __testlib_fail("random_t::distinct expected size <= to - from + 1");

    double expected = 0.0;
    for (int i = 1; i <= size; i++)
        expected += double(n) / double(n - i + 1);

    if (expected < double(n)) {
        std::set<T> vals;
        while (int(vals.size()) < size) {
            T x = T(rnd.next(from, to));
            if (vals.insert(x).second)
                result.push_back(x);
        }
    } else {
        if (n > 1000000000)
            __testlib_fail("random_t::distinct here expected to - from + 1 <= 1000000000");
        std::vector<T> p(perm(int(n), from));
        result.insert(result.end(), p.begin(), p.begin() + size);
    }

    return result;
}

/* Returns `size` unordered (unsorted) distinct numbers between `0` and `upper`-1. */
template<typename T>
std::vector<T> distinct(int size, T upper) {
    if (size < 0)
        __testlib_fail("random_t::distinct expected size >= 0");
    if (size == 0)
        return std::vector<T>();

    if (upper <= 0)
        __testlib_fail("random_t::distinct expected upper > 0");
    if (size > upper)
        __testlib_fail("random_t::distinct expected size <= upper");

    return distinct(size, T(0), upper - 1);
}

/* Returns random (unsorted) partition which is a representation of sum as a sum of integers not less than min_part. */
template<typename T>
std::vector<T> partition(int size, T sum, T min_part) {
    if (size < 0)
        __testlib_fail("random_t::partition: size < 0");
    if (size == 0 && sum != 0)
        __testlib_fail("random_t::partition: size == 0 && sum != 0");
    if (min_part * size > sum)
        __testlib_fail("random_t::partition: min_part * size > sum");
    if (size == 0 && sum == 0)
        return std::vector<T>();

    T sum_ = sum;
    sum -= min_part * size;

    std::vector<T> septums(size);
    std::vector<T> d = distinct(size - 1, T(1), T(sum + size - 1));
    for (int i = 0; i + 1 < size; i++)
        septums[i + 1] = d[i];
    std::sort(septums.begin(), septums.end());

    std::vector<T> result(size);
    for (int i = 0; i + 1 < size; i++)
        result[i] = septums[i + 1] - septums[i] - 1;
    result[size - 1] = sum + size - 1 - septums.back();

    for (std::size_t i = 0; i < result.size(); i++)
        result[i] += min_part;

    T result_sum = 0;
    for (std::size_t i = 0; i < result.size(); i++)
        result_sum += result[i];
    if (result_sum != sum_)
        __testlib_fail("random_t::partition: partition sum is expected to be the given sum");

    if (*std::min_element(result.begin(), result.end()) < min_part)
        __testlib_fail("random_t::partition: partition min is expected to be no less than the given min_part");

    if (int(result.size()) != size || result.size() != (size_t) size)
        __testlib_fail("random_t::partition: partition size is expected to be equal to the given size");

    return result;
}

void pure_random(int argc, char *argv[]) { // n m q cl cr
    assert(argc >= 5);
    int n = atoi(argv[0]);
    int m = atoi(argv[1]);
    int q = atoi(argv[2]);
    int cl = atoi(argv[3]);
    int cr = atoi(argv[4]);
    assert(m >= n - 1);
    Edges edges = uniform_tree(n, 1);
    std::set<Edge> vis;
    for (auto e : edges) 
    {
        if (e.first > e.second) 
        {
            std::swap(e.first, e.second);
        }
        vis.insert(e);
    }
    Edges choice;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (vis.find(Edge(i, j)) == vis.end())
            {
                choice.push_back(Edge(i, j));
            }
        }
    }
    shuffle_edges(choice);
    for (int i = 0; i < m - (n - 1) && i < int(choice.size()); i++)
    {
        edges.push_back(choice[i]);
    }
    shuffle_edges(edges);
    printf("%d %d\n", n, int(edges.size()));
    for (auto e : edges)
    {
        printf("%d %d %d\n", e.first, e.second, rnd.next(cl, cr));
    }
    printf("%d\n", q);
    for (int i = 1; i <= q; i++) 
    {
        int u, v;
        do 
        {
            u = rnd.next(1, n);
            v = rnd.next(1, n);
        } while (u == v);
        printf("%d %d\n", u, v);
    }
}


void kruskal(int argc, char* argv[]) { // n m q cl cr bcc_cnt bcc_min_part bcc_tree_type bcc_tree_dis cyc_type cyc_dis spn_tree_type spn_tree_dis nosol_num
    assert(argc >= 14);
    int n = atoi(argv[0]);
    int m = atoi(argv[1]);
    int q = atoi(argv[2]);
    int cl = atoi(argv[3]);
    int cr = atoi(argv[4]);
    int bcc_cnt = atoi(argv[5]);
    int bcc_min_part = atoi(argv[6]);
    int bcc_tree_type = atoi(argv[7]);
    int bcc_tree_dis = atoi(argv[8]);
    int cyc_type = atoi(argv[9]);
    int cyc_dis = atoi(argv[10]);
    int spn_tree_type = atoi(argv[11]);
    int spn_tree_dis = atoi(argv[12]);
    int nosol_num = atoi(argv[13]);
    assert(m >= n - 1 + (n - 1 - (bcc_cnt - 1)));
    Edges edges;
    std::vector<int> bcc_sz = partition(bcc_cnt, n, bcc_min_part);
    { // prevent multiple edges
        std::vector<int> tmp;
        for (int sz : bcc_sz)
        {
            if (sz == 2) 
            {
                tmp.push_back(1), tmp.push_back(1);
            }
            else
            {
                tmp.push_back(sz);
            }
        }
        bcc_sz.swap(tmp);
    }
    Edges nosol;
    std::vector<std::pair<int, int>> intervals; 
    int base = 0;
    for (int sz : bcc_sz)
    {
        Edges tmp;
        if (bcc_tree_type == -1)
        {
            tmp = uniform_tree(sz, base);
        }
        else
        {
            tmp = custom_tree(sz, bcc_tree_type, bcc_tree_dis, base);
        }
        for (auto e : tmp)
        {
            edges.push_back(e);
        }
        for (int i = 0; i < base; i++)
        {
            for (int j = base; j < base + sz; j++)
            {
                nosol.push_back(Edge(i, j));
            }
        }
        intervals.push_back(std::make_pair(base, base + sz - 1));
        base += sz;
    }
    std::vector<int> boss(n);
    std::vector<std::vector<int>> group(n);
    std::vector<std::vector<int>> answer(n, std::vector<int>(n, -1));
    std::vector<std::pair<Edge, int>> graph;
    std::iota(boss.begin(), boss.end(), 0);
    for (int i = 0; i < n; i++)
    {
        group[i].resize(1, i);
    }
    shuffle_edges(edges);
    for (auto e : edges)
    {
        int a = boss[e.first];
        int b = boss[e.second];

        if (group[a].size() >= 2 || group[b].size() >= 2)
        {
            int first_pl = rnd.next(0, int(graph.size()));
            if (cyc_type == 1)
            {
                first_pl = rnd.next(std::max(0, int(graph.size()) - cyc_dis), int(graph.size()));
            }
            else if (cyc_type == 2)
            {
                first_pl = rnd.next(0, std::min(cyc_dis - 1, int(graph.size())));
            }

            int u, v;
            do 
            {
                u = group[a][rnd.next(0, int(group[a].size()) - 1)];
                v = group[b][rnd.next(0, int(group[b].size()) - 1)];  
            } while (Edge(u, v) == e);
            if (rnd.next(0, 1)) 
            {
                std::swap(u, v);
            }

            graph.insert(graph.begin() + first_pl, std::make_pair(Edge(u, v), 0));
        }

        for (int i : group[b])
        {
            for (int j : group[a])
            {
                answer[i][j] = answer[j][i] = graph.size();
            }
        }
        graph.emplace_back(e, 0);

        if (group[a].size() < group[b].size())
        {   
            std::swap(a, b);
        }
        for (int i : group[b])
        {
            group[a].push_back(i), boss[i] = a;
        }
        group[b].clear();
    }
    std::vector<int> lengths(graph.size());
    for (int &i : lengths)
    {
        i = rnd.next(cl, cr);
    }
    std::sort(lengths.begin(), lengths.end());
    for (int i = 0; i < int(graph.size()); i++)
    {
        graph[i].second = lengths[i];
    }

    Edges spn_tree;
    if (spn_tree_type == -1)
    {
        spn_tree = uniform_tree(int(bcc_sz.size()));
    }
    else 
    {
        spn_tree = custom_tree(int(bcc_sz.size()), spn_tree_type, spn_tree_dis);
    }
    for (auto e : spn_tree)
    {
        int u, v;
        u = rnd.next(intervals[e.first].first, intervals[e.first].second);
        v = rnd.next(intervals[e.second].first, intervals[e.second].second);
        graph.emplace_back(Edge(u, v), rnd.next(cl, cr));
    }

    Edges addition; 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (answer[i][j] > 0)
            {
                answer[i][j] = graph[answer[i][j]].second;
            }
        }
    }
    for (auto e : graph)
    {
        answer[e.first.first][e.first.second] = answer[e.first.second][e.first.first] = -2;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (answer[i][j] > 0)
            {
                addition.emplace_back(i, j);
            }
        }
    }
    shuffle_edges(addition);
    while (int(graph.size()) < m && !addition.empty())
    {
        graph.emplace_back(addition.back(), rnd.next(answer[addition.back().first][addition.back().second], cr));
        addition.pop_back();
    }

    Edges querys;
    shuffle_edges(nosol);
    for (int i = 0; i < int(intervals.size());) 
    {
        if (intervals[i].first == intervals[i].second) 
        {
            std::swap(intervals[i], intervals.back());
            intervals.pop_back();
        }
        else
        {
            i++;
        }
    }
    
    nosol_num = std::min(nosol_num, q);
    if (intervals.empty()) 
    {
        nosol_num = q;
    }
    if (nosol.empty())
    {
        nosol_num = 0;
    }
    for (int i = 0; i < q - nosol_num; i++) 
    {
        auto itv = intervals[rnd.next(0, int(intervals.size()) - 1)];
        int u, v;
        do 
        {
            u = rnd.next(itv.first, itv.second);
            v = rnd.next(itv.first, itv.second);
        } while (u == v);
        querys.emplace_back(u, v);
    }
    for (int i = 0; i < nosol_num; i++) 
    {
        querys.push_back(nosol[rnd.next(0, int(nosol.size()) - 1)]);
    }

    shuffle(graph.begin(), graph.end());
    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 1);
    shuffle(idx.begin(), idx.end());
    printf("%d %d\n", n, int(graph.size()));
    for (auto e : graph)
    {
        printf("%d %d %d\n", idx[e.first.first], idx[e.first.second], e.second);
    }
    shuffle_edges(querys);
    printf("%d\n", int(querys.size())); 
    for (auto e : querys)
    {
        printf("%d %d\n", idx[e.first], idx[e.second]);
    }
}

#define register_generator(name) if (gname == #name) return name(argc - 2, argv + 2), 0

int main(int argc, char* argv[])
{
    if (argc < 2)
    {   
        return std::cerr << "Arguments should not be empty.\n", 1;
    }
    registerGen(argc, argv, 1);
    std::string gname(argv[1]);
    register_generator(pure_random);
    register_generator(kruskal);
    return 0;
}
