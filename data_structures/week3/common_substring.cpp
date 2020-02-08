#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

struct Answer {
    size_t i, j, len;
};

ull static constexpr PRIME1 = 1000000003;
ull static constexpr PRIME2 = 1000000007;

ull static X = rand() % (100 - 1) + 1;

ull hash_func(const string& s, ull prime) {
    ull hash = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        hash = (hash * X + *it) % prime;
    }
    return hash;
}

ull re_hash_func(char begin, char end, ull prev_hash, ull prime, ull mult) {
    ll hash = X * prev_hash + begin - end * mult;
    while (hash < 0) {
        hash += prime;
    }
    return hash % prime;
}

vector<ull> compute_powers(size_t k, ull mod) {
    vector<ull> powers = {1};
    for (size_t i = 0; i < k; i++) {
        powers.push_back((powers.back() * X) % mod);
    }
    return powers;
}

vector<pair<ull, size_t>> compute_substr_hashes(const string& s, const vector<ull> powers, size_t k, ull prime) {
    vector<pair<ull, size_t>> result = {make_pair(hash_func(s.substr(s.size() - k, k), prime), s.size() - k)};
    for (int i = s.size() - k - 1; i >= 0; i--) {
        result.push_back(make_pair(re_hash_func(s[i], s[i + k], result.back().first, prime, powers[k]), i));
    }
    return result;
}

Answer get_common_substring(const string& s1, const string& s2, size_t k) {
    auto x1 = compute_powers(k, PRIME1);
    auto x2 = compute_powers(k, PRIME2);

    auto s1_x1_hashes = compute_substr_hashes(s1, x1, k, PRIME1);
    auto s1_x2_hashes = compute_substr_hashes(s1, x2, k, PRIME2);

    auto s2_x1_hashes = compute_substr_hashes(s2, x1, k, PRIME1);
    auto s2_x2_hashes = compute_substr_hashes(s2, x2, k, PRIME2);

   unordered_map<ull, size_t> map_s1_x1, map_s1_x2;
   for (auto hash_pair : s1_x1_hashes) {
       map_s1_x1.emplace(hash_pair);
   }
   for (auto hash_pair : s1_x2_hashes) {
       map_s1_x2.emplace(hash_pair);
   }

   for (size_t i = 0; i < s2_x1_hashes.size(); i++) {
       auto hash1 = s2_x1_hashes[i];
       auto hash2 = s2_x2_hashes[i];

       if (map_s1_x1.find(hash1.first) != map_s1_x1.end() && map_s1_x2.find(hash2.first) != map_s1_x2.end()) {
           return {map_s1_x1[hash1.first], hash1.second, k};
       }
   }

   return {0,0,0};
}

/* Traditional DP approach to find longest common substring of 2 strings but it exceeds max allowed memory threshold
 * auto n = s.size();
    auto m = t.size();
    std::vector<std::vector<size_t>> dp(m + 1, std::vector<size_t>(n + 1));
    size_t s_idx = 0;
    size_t t_idx = 0;
    size_t max = 0;

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (t[i - 1] == s[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max) {
                    max = dp[i][j];
                    s_idx = j - 1;
                    t_idx = i - 1;
                }
            }
        }
    }

    return {s_idx - (max - 1), t_idx - (max - 1), max};
 */

Answer solve(const string &s, const string &t) {
    int lo = 1;
    int hi = min(s.size(), t.size());
    Answer sol = {0, 0, 0};
    while (lo <= hi) {
        size_t mid = (lo + hi) / 2;
        auto ans = get_common_substring(s, t, mid);
        if (sol.len < ans.len) {
            sol = ans;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
   return sol;
}


int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    string t, s;
    while (cin >> s >> t) {
        Answer ans = solve(s, t);
        cout << ans.i << " " << ans.j << " " << ans.len << "\n";
    }
}
