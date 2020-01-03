#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;
using std::pair;
using std::make_pair;

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        auto cmp = [](pair<int, long long> left, pair<int, long long> right) {
            return left.second == right.second ? left.first > right.first : left.second > right.second;
        };

        priority_queue<pair<int, long long>, vector<pair<int, long long>>, decltype(cmp)> pq(cmp);

        for (auto i = 0; i < num_workers_; i++) {
            pq.push(make_pair(i, 0));
        }

        for (int i = 0; i < jobs_.size(); ++i) {
            int duration = jobs_[i];
            auto thread = pq.top();
            pq.pop();

            assigned_workers_.push_back(thread.first);
            start_times_.push_back(thread.second);
            thread.second += duration;
            pq.push(thread);
        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
