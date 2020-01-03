#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void GenerateSwaps() {
        swaps_.clear();
        for (int i = data_.size() / 2 - 1; i >= 0; i--) {
            sift_down(i);
        }
    }

    void sift_down(int index) {
        int min = index;
        int N = data_.size();
        while(min < N) {
            int left = min * 2 + 1;
            int right = min * 2 + 2;
            if (left < N && data_[min] > data_[left]) {
                min = left;
            }
            if (right < N && data_[min] > data_[right]) {
                min = right;
            }
            if (index != min) {
                swap(data_[index], data_[min]);
                swaps_.emplace_back(make_pair(index, min));
                index = min;
            } else {
                break;
            }
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
