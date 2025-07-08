#include "TestGenerator.h"
#include <fstream>

#include "../src/SimpleTree.h"
#include "../src/SplayTree.h"
#include "../src/Treap.h"

using namespace std;

void generate_tests() {
    TestGenerator gen;
//    freopen("inputs/ascend_input.txt", "w", stdout);
    std::ofstream outfile;

    outfile.open("D:/ss25project/data/inputs/ascend_input.txt");
    gen.DataAscend(0, 10000);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/random_input1.txt");
    gen.DataRandom(10000, 0, 10000);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/random_input2.txt");
    gen.DataRandom(10000, 0, 10000);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/OddEven_input_frac2_inc.txt");
    gen.DataOddEven(10000, 2, true);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/OddEven_input_frac5_dic.txt");
    gen.DataOddEven(10000, 5, false);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();
}

int main() {
    generate_tests();
    return 0;
}
