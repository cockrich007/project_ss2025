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

using clocks = std::chrono::high_resolution_clock;
using nanoseconds = std::chrono::nanoseconds;
void test_insert() {
    std::vector<std::string> input_names = {"D:/ss25project/data/inputs/ascend_input.txt",
    "D:/ss25project/data/inputs/random_input1.txt",
    "D:/ss25project/data/inputs/random_input2.txt",
    "D:/ss25project/data/inputs/OddEven_input_frac2_inc.txt",
    "D:/ss25project/data/inputs/OddEven_input_frac5_dic.txt",
    "D:/ss25project/data/inputs/Jump_Input_inc.txt",
    "D:/ss25project/data/inputs/Jump_Input_dic.txt",
    "D:/ss25project/data/inputs/Edge_input.txt",
    "D:/ss25project/data/inputs/Stress_input.txt"};
    size_t length_input_names = input_names.size();


    std::ofstream outFile1("D:/ss25project/data/outputs/inserts/Splay_insert_height.csv");
    std::ofstream outFile2("D:/ss25project/data/outputs/inserts/Splay_insert_time.csv");


    for (size_t i = 0; i < length_input_names; i++) //insert time для Splay
    {
        SplayTree<int> SplayTree;
        std::ifstream inputFile;
        inputFile.open(input_names[i]);
        if (inputFile.is_open()) {
            std::string line;
            outFile1 << "Тестовые данные " << i + 1 << ": ";
            outFile2 << "Тестовые данные " << i + 1 << ": ";

            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    auto start = clocks::now();
                    SplayTree.insert((int)std::stoi(word));
                    auto elapsed = clocks::now() - start;
                    outFile1 << SplayTree.get_tree_height() << " ";
                    outFile2 << std::chrono::duration_cast<nanoseconds>(elapsed).count() << " ";
                }
            }
            std::cout << "Прогруженны данные" << i + 1;
        }
        else {
            std::cout << "Не был открыт поток";
        }
        std::cout << '\n';
        inputFile.close();
        outFile1 << std::endl;
        outFile2 << std::endl;
    }
    outFile1.close();
    outFile2.close();


    std::ofstream outFile3("D:/ss25project/data/outputs/inserts/Simple_insert_height.csv");
    std::ofstream outFile4("D:/ss25project/data/outputs/inserts/Simple_insert_time.csv");


    for (size_t i = 0; i < length_input_names; i++) //insert time для Simple
    {
        SimpleTree<int> SimpleTree1;
        std::ifstream inputFile;
        inputFile.open(input_names[i]);
        if (inputFile.is_open()) {
            std::string line;

            outFile3 << "Тестовые данные " << i + 1 << ": ";
            outFile4 << "Тестовые данные " << i + 1 << ": ";

            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    auto start = clocks::now();
                    SimpleTree1.insert((int)std::stoi(word));
                    auto elapsed = clocks::now() - start;
                    outFile3 << SimpleTree1.get_tree_height() << " ";
                    outFile4 << std::chrono::duration_cast<nanoseconds>(elapsed).count() << " ";
                }
            }
            std::cout << "Прогруженны данные" << i + 1;
        }
        else {
            std::cout << "Не был открыт поток";
        }
        std::cout << '\n';
        inputFile.close();
        outFile3 << std::endl;
        outFile4 << std::endl;
    }
    outFile3.close();
    outFile4.close();


    std::ofstream outFile5("D:/ss25project/data/outputs/inserts/Treap_insert_height.csv");
    std::ofstream outFile6("D:/ss25project/data/outputs/inserts/Treap_insert_time.csv");


    for (size_t i = 0; i < length_input_names; i++) //insert time для Treap
    {
        Treap<int> Treap;
        std::ifstream inputFile;
        inputFile.open(input_names[i]);
        if (inputFile.is_open()) {
            std::string line;

            outFile5 << "Тестовые данные " << i + 1 << ": ";
            outFile6 << "Тестовые данные " << i + 1 << ": ";

            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    auto start = clocks::now();
                    Treap.insert((int)std::stoi(word));
                    auto elapsed = clocks::now() - start;
                    outFile5 << Treap.get_tree_height() << " ";
                    outFile6 << std::chrono::duration_cast<nanoseconds>(elapsed).count() << " ";
                }
            }
            std::cout << "Прогруженны данные" << i + 1;
        }
        else {
            std::cout << "Не был открыт поток";
        }
        std::cout << '\n';
        inputFile.close();
        outFile5 << std::endl;
        outFile6 << std::endl;
    }
    outFile5.close();
    outFile6.close();
}

/*int main() {
    test_insert();
    return 0;
}*/
