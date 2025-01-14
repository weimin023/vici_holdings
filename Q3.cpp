#include <vector>
#include <queue>
#include <iostream>
#include <chrono>

void calc(int num, const std::vector<int> &in) {
    std::vector<std::queue<int>> res;
    std::queue<int> seg;

    int n = in.size();
    int curr_sum = 0;
    int p1 = 0;
    for (int p2 = 0; p2 < n; ++p2) {

        curr_sum += in[p2];
        seg.push(in[p2]);

        while (curr_sum >= num) {
            if (curr_sum - in[p1] < num) {
                res.push_back(seg);
            }
            curr_sum -= in[p1];
            seg.pop();
            p1++;
        }
    }

    for (auto &q:res) {
        while (!q.empty()) {
            std::cout<<q.front()<<" ";
            q.pop();
        }
        std::cout<<std::endl;
    }
}

int main() {
    std::vector<int> in{3, 17, 42, 1, 26, 8, 0, 63, 90, 1, 6, 53, 60};

    auto start = std::chrono::high_resolution_clock::now();
    calc(80, in);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "duration: " << elapsed.count() / 1e9 << " ns\n";
    return 0;
}