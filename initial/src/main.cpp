#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "test/tc_xmap.cpp"
#include "test/tc_heap.cpp"
#include "test/tc_compressor.cpp"


using namespace std;

void (*func_ptr[7])() = {
    hashDemo1,
    hashDemo2,
    hashDemo3,
    hashDemo4,
    hashDemo5,
    hashDemo6,
    hashDemo7
    // heapDemo1,
    // heapDemo2,
    // heapDemo3,
    // tc_huffman1001,
    // tc_huffman1002,
    // tc_huffman1003,
    // tc_huffman1004,
    // tc_huffman1005,
    // tc_compressor1001,
    // tc_compressor1002
};

void run(int func_idx)
{
    func_ptr[func_idx]();
}

int main(int argc, char **argv)
{
    // cout << "Assignment-2" << endl;
    if (argc == 1) {
        // Không có tham số, mặc định chạy testcase 0
        run(0);
    } else {
        // Có tham số, lấy argv[1] làm số testcase
        int idx = atoi(argv[1]);  // chuyển argv[1] (chuỗi) thành số nguyên
        run(idx);
    }

    return 0;
}