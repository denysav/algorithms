#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

struct Triplet {
    ull cont, partial;
    size_t idx;
};

ull static constexpr PRIME1 = 1000000003;
ull static constexpr PRIME2 = 1000000007;

ull static X = rand() % (100 - 1) + 1;

ull hash_func(const string& s, ull prime) {
    cout << s << endl;
    ull hash = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
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

ull get_hash(size_t pos, size_t k, vector<ull> powers, vector<pair<ull, size_t>> hashes, ull prime) {
    auto hash = (hashes[pos + k] .first- powers[k] * hashes[pos].first) % prime;
    while (hash < 0) {
        hash += prime;
    }
    return hash % prime;
}

vector<pair<ull, size_t>> compute_prefix_hashes(const string& s, ull prime) {
    ll hash = 0;
    vector<pair<ull, size_t>> result = {};
    for (size_t i = 0; i < s.size(); i++) {
        hash = (hash * X + s[i]) % prime;
        while (hash < 0) {
            hash += prime;
        }
        hash %= prime;
        result.push_back(make_pair(hash, i));
    }
    return result;
}

int find_mismatch(vector<pair<ull, size_t>>& text, vector<pair<ull, size_t>>& pattern, vector<ull> powers, ull prime) {
    int lo = 0, hi =  text.size() - 1;
    int mismatch = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        auto text_hash = get_hash(mid, powers, text, prime);
        auto pattern_hash = get_hash()
        if (v1[mid] != v2[mid]) {
            mismatch = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return mismatch;
}

vector<int> solve(int k, const string &text, const string &pattern) {
    vector<int> pos;
    auto powers = compute_powers(k, PRIME1);
    auto text_hashes = compute_prefix_hashes(text, PRIME1);
    auto pattern_hashes = compute_prefix_hashes(pattern, PRIME1);
    for (int i = 0; i < text.size() - pattern.size() + 1; i++) {
        int counter = 0;
        size_t text_idx = i;
        size_t pattern_idx = 0;
        while (counter < k) {
            auto mismatch = find_mismatch(text_hashes, pattern_hashes, powers, text_idx, pattern_idx, i + k, PRIME1);
            if (mismatch == -1) {
                counter++;
            }
            text_idx =
        }
    }
    return pos;
}
int main() {
//    ios_base::sync_with_stdio(false), cin.tie(0);
//    int k;
//    string t, p;
//    while (cin >> k >> t >> p) {
//        auto a = solve(k, t, p);
//        cout << a.size();
//        for (int x : a)
//            cout << " " << x;
//        cout << "\n";
//    }
    string s1 = "abcd";
    string s2 = "abbd";
    auto hashes0 = compute_prefix_hashes(s2, PRIME1);
    auto cvs = compute_prefix_hashes(s1, PRIME1);
    for (int i = 0; i <cvs.size(); i++) {
        cout << hashes0[i].first << " " << cvs[i].first << endl;
    }
}
