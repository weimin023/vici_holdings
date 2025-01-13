#include <vector>
#include <numeric>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <limits>

template<typename T>
inline T mean(const std::vector<T>& v) {
    if (v.empty()) {
        throw std::invalid_argument("Vector is empty.");
    }

    int N = v.size();
    
    int x = 0; 
    int y = 0; 
    for (int i = 0; i < N; i++) { 
        x += v[i] / N; 
        int b = v[i] % N; 
        if (y >= N - b) { 
            x++; 
            y -= N - b; 
        } else { 
            y += b; 
        } 
    } 

    return x + y/N;
}

int main() {
    std::cout<<mean<uint32_t>({std::numeric_limits<uint32_t>::max(),1})<<std::endl;

    return 0;
}