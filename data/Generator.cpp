#include "TestGenerator.h"
#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>
#include <sstream>
#include <iostream>

#include "../src/SimpleTree.h"
#include "../src/SplayTree.h"
#include "../src/Treap.h"


void generate_tests() {
    TestGenerator gen;
    //    freopen("inputs/ascend_input.txt", "w", stdout);
    std::ofstream outfile;

    outfile.open("D:/ss25project/data/inputs/ascend_input.txt");
    gen.DataAscend(0, 1000);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/random_input1.txt");
    gen.DataRandom(1000, 0, 1000);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/random_input2.txt");
    gen.DataRandom(1000, 0, 1000);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/OddEven_input_frac2_inc.txt");
    gen.DataOddEven(1000, 2, true);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/OddEven_input_frac5_dic.txt");
    gen.DataOddEven(1000, 5, false);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/Jump_Input_inc.txt");
    gen.DataJump(1000, true);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/Jump_Input_dic.txt");
    gen.DataJump(1000, false);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/Edge_input.txt");
    gen.DataEdge();
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();

    outfile.open("D:/ss25project/data/inputs/Stress_input.txt");
    gen.DataStress(3);
    for (auto element : gen.Data) {
        outfile << element << ' ';
    }
    outfile.close();
}

void main() {
    generate_tests();
    return;
}
