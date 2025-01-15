#include <vector>
#include <queue>
#include <iostream>
#include <chrono>
#include <fstream>

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

void worker(int id, int start, int target, const std::vector<int> &data, int &out) {
    int N = data.size();

    int sum_ = 0;
    for (int i = start; i < N; ++i) {
        sum_ += data[i];
        if (sum_ >= target) out = i;
    }
}

void calc_opt(int num, const std::vector<int> &in) {
    int N = in.size();

    std::vector<int> bucket(N, -1);

    // multithreads call workers
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <sum>" << " <filename>\n";
        return 1;
    }

    int target_val = std::stoi(std::string(argv[1]));
    std::string fileName = argv[2];
    std::ifstream inputFile(fileName);
    std::vector<int> data_in;

    int row;

    if (inputFile.is_open()) {
        while (inputFile >> row) {
            data_in.push_back(row);
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file: " << fileName << "\n";
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    calc(target_val, data_in);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "duration: " << elapsed.count() / 1e9 << " ns\n";
    return 0;
}