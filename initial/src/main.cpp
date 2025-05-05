#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "test/tc_xmap.h"
#include "test/tc_heap.h"
#include "test/tc_compressor.h"

using namespace std;

void (*func_ptr[17])() = {
    // hashDemo1,
    // hashDemo2,
    // hashDemo3,
    // hashDemo4,
    // hashDemo5,
    // hashDemo6,
    // hashDemo7,
    heapDemo1,
    heapDemo2,
    heapDemo3
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
    if (argc == 1) {
        run(0);  // chạy mặc định
    } else {
        int idx = atoi(argv[1]);  // lấy chỉ số từ argv[1]
        run(idx);
    }

    return 0;
}
