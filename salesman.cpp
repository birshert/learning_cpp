#include <algorithm>
#include <ctime>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <set>

int n;
const int msek = CLOCKS_PER_SEC / 1000;
std::vector<std::pair<long long, long long>> p(3100);
std::vector<std::vector<double>> dista;
std::vector<std::vector<int>> G;
std::vector<int> ans, ans1;
std::vector<std::pair<int, int>> sets(3100);
std::vector<int> cy;

inline double dist(std::pair<long long, long long>& f, std::pair<long long, long long>& s) {
    return std::sqrt((f.first - s.first) * (f.first - s.first)
                     + (f.second - s.second) * (f.second - s.second));
}

void greedy() {
    ans.resize(n + 1);
    ans[0] = 0;
    ans[n] = 0;
    std::vector<int> used(n, 0);
    used[0] = 1;
    for (int i = 0; i != n - 1; ++i) {
        std::pair<long double, int> curr = {1e10, -1};
        for (int j = 0; j != n; ++j) {
            if (!used[j]) {
                long double c = dista[ans[i]][j];
                if (c < curr.first) {
                    curr.first = c;
                    curr.second = j;
                }
            }
        }
        ans[i + 1] = curr.second;
        used[curr.second] = 1;
    }
}

void rando(int k) {
    std::default_random_engine generator(time(nullptr));
    std::uniform_int_distribution<int> mix(1, n - 1);
    clock_t end_time = clock() + k * msek;
    while (clock() < end_time) {
        int i = mix(generator), j = mix(generator);
        if (i != j) {
            if (i > j) {
                std::swap(i, j);
            }
            if (dista[ans[i - 1]][ans[i]] + dista[ans[j]][ans[j + 1]]
                > dista[ans[i - 1]][ans[j]] + dista[ans[i]][ans[j + 1]]) {
                std::reverse(ans.begin() + i, ans.begin() + j + 1);
            }
        }
    }
}

void opti(int i) {
    clock_t end_time = clock() + i * msek;
    while (clock() < end_time) {
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (dista[ans[i - 1]][ans[i]] + dista[ans[j]][ans[j + 1]]
                    > dista[ans[i - 1]][ans[j]] + dista[ans[i]][ans[j + 1]]) {
                    std::reverse(ans.begin() + i, ans.begin() + j + 1);
                }
            }
        }
    }
}

int set(int p) {
    if (p == sets[p].first) {
        return p;
    }
    return sets[p].first = set(sets[p].first);
}

void union_(int f, int s) {
    int f_set = set(f), s_set = set(s);
    if (f_set != s_set) {
        if (sets[f_set].second < sets[s_set].second) {
            sets[f_set].first = s_set;
            sets[s_set].second += sets[f_set].second;
        } else {
            sets[s_set].first = f_set;
            sets[f_set].second += sets[s_set].second;
        }
    }
}

void cycle(int v) {
    for (int i = 0; i != n; ++i) {
        if (G[v][i] != 0) {
            --G[v][i];
            --G[i][v];
            cycle(i);
        }
    }
    cy.push_back(v);
}

void mst() {
    std::vector<std::pair<double, std::pair<int, int>>> edges, ost;
    for (int i = 0; i != n; ++i) {
        for (int j = i + 1; j != n; ++j) {
            edges.push_back({dista[i][j], {i, j}});
        }
    }
    std::sort(edges.begin(), edges.end());
    std::vector<int> used(n, 0);
    for (int i = 0; i != n; ++i) {
        sets[i].first = i;
        sets[i].second = 1;
    }
    for (auto edge : edges) {
        if (set(edge.second.first) != set(edge.second.second)) {
            ost.push_back(edge);
            union_(edge.second.first, edge.second.second);
        }
    }
    G.resize(n, std::vector<int>(n, 0));
    for (auto elem : ost) {
        G[elem.second.second][elem.second.first] += 2;
        G[elem.second.first][elem.second.second] += 2;
    }
    cycle(0);
    std::vector<int> true_path;
    for (int i = 0; i != cy.size(); ++i) {
        if (!used[cy[i]]) {
            true_path.push_back(cy[i]);
            used[cy[i]] = 1;
        }
    }
    true_path.push_back(0);
    ans = true_path;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    for (int i = 0; i != n; ++i) {
        std::cin >> p[i].first >> p[i].second;
    }
    dista.resize(n, std::vector<double>(n, 0));
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            if (i != j) {
                dista[i][j] = dist(p[i], p[j]);
            }
        }
    }
    if (n < 100) {
        mst();
    } else {
        greedy();
    }
    if (n <= 25) {
        std::reverse(ans.begin() + 1, ans.end() - 1);
        opti(9800);
    } else if (n < 200) {
        opti(2000);
        rando(6000);
    } else if (n <= 600) {
        opti(3000);
        rando(6600);
    } else if (n > 600) {
        rando(4700);
        opti(5000);
    }
    for (auto elem : ans) {
        std::cout << elem + 1 << ' ';
    }
}
