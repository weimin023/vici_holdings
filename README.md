# vici_holdings

## Environment
OS: Ubuntu 22.04 (WSL)

Arch: x86_64

## Build Steps
```
git clone
cd vici_holdings
mkdir build
cd build
cmake ..
make -j16
```

## Comments
### Q3
1. `Q3_data.txt` is a simple testcase contains 10^6 integers range from 1~70. 
2. Options for showing results
>#define SHOW_V1_RESULT 0
>
>#define SHOW_V2_RESULT 0

3. Will show the duration of two versions
>1. Single Thread Duration: 1.13723e-09 ns
>
>2. Multiple Threads Duration: 1.43559e-10 ns

