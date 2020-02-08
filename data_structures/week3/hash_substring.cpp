#include <iostream>
#include <string>
#include <vector>
#include <random>

using std::string;
typedef unsigned long long ull;
typedef long long ll;

struct Data {
    string pattern, text;
};

ull static constexpr PRIME = 1000000007;

ull static X = std::rand() % (PRIME - 1) + 1;

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (auto it = output.rbegin(); it != output.rend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}

ull hash_func(const string& s) {
    ull hash = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        hash = (hash * X + *it) % PRIME;
    }
    return hash;
}

ull re_hash_func(char begin, char end, ull prev_hash, ull x_power_pattern_mult) {
    ll hash = X * prev_hash + begin - end * x_power_pattern_mult;
    while (hash < 0) {
        hash += PRIME;
    }
    return hash % PRIME;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    auto t_hash = hash_func(t.substr(t.size() - s.size(), t.size()));
    auto s_hash = hash_func(s);
    ull x_power_pattern_mult = 1;
    for (size_t i = 0; i < s.size(); i++) {
        x_power_pattern_mult = (x_power_pattern_mult * X) % PRIME;
    }
    std::vector<int> ans;
    for (int i = t.size() - s.size(); i >= 0; --i) {
        if (i < t.size() - s.size()) {
            t_hash = re_hash_func(t[i], t[i + s.size()], t_hash, x_power_pattern_mult);
        }
        if (s_hash == t_hash) {
            if (t.substr(i, s.size()) == s) {
                ans.push_back(i);
            }
        }
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
