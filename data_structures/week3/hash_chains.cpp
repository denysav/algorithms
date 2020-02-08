#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    vector<vector<string>> hash_table;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

    auto find(const vector<string>& haystack, const string& needle) {
        return std::find(haystack.begin(), haystack.end(), needle);
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        hash_table.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            auto& vec = hash_table[query.ind];
            for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        } else {
            if (query.type == "find") {
                auto &chain = hash_table[hash_func(query.s)];
                auto was_found = find(chain, query.s) != chain.end();
                writeSearchResult(was_found);
            }
            else if (query.type == "add") {
                auto &chain = hash_table[hash_func(query.s)];
                auto not_found = find(chain, query.s) == chain.end();
                if (not_found) {
                    chain.push_back(query.s);
                }
            } else if (query.type == "del") {
                auto &chain = hash_table[hash_func(query.s)];
                vector<string>::iterator it = std::find(chain.begin(), chain.end(), query.s);
                if (it != chain.end()) {
                    chain.erase(it);
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
