#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <chrono>

void worker(int id, int start, int end, int target, const std::vector<int> &data, std::vector<int> &seg_map) {
    int N = data.size();

    for (int task = start; task < end; ++task) {
        int sum_ = 0;
        for (int i = task; i < N; ++i) {
            sum_ += data[i];
            if (sum_ >= target) {
                seg_map[task] = i;
                break;
            }
        }
    }
    
}

void calc_opt(int num, const std::vector<int> &in) {
    int N = in.size();
    int maxThreads = std::thread::hardware_concurrency();
    int numThreads = (N > maxThreads)? maxThreads:N; // Number of threads

    std::vector<int> seg_map(N, -1);

    std::vector<std::thread> threads;
    int chunkSize = (N + numThreads - 1) / numThreads;

    std::cout << "numThreads: " << numThreads << std::endl;
    std::cout << "chunkSize: " << chunkSize << std::endl;

    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = std::min(start + chunkSize, N);
        //std::cout<<start<<" "<<end<<std::endl;
        threads.emplace_back(worker, i, start, end, num, std::ref(in), std::ref(seg_map));
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    /*for (auto i:seg_map) {
        std::cout<<i<<std::endl;
    }*/

    std::vector<std::pair<int, int>> collect;
    for (int i = 0; i < N; ++i) {
        int start = i;
        int end = seg_map[i];

        if (end == -1) continue;

        if (collect.empty()) {
            collect.emplace_back(start, end);
        } else {
            if (collect.back().second == end) {
                collect.back().first = start;
            } else {
                collect.emplace_back(start, end);
            }
        }
    }

    for (auto &i:collect) {
        for (int p = i.first; p <= i.second; ++p) {
            std::cout<<in[p]<<" ";
        }
        std::cout<<std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <sum> <filename>\n";
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
    calc_opt(target_val, data_in);
    auto end = std::chrono::high_resolution_clock::now();

    return 0;
}