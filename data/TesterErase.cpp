#include "TestGenerator.h"
#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <random>
#include <set>

#include "../src/SimpleTree.h"
#include "../src/SplayTree.h"
#include "../src/Treap.h"

using clocks = std::chrono::high_resolution_clock;
using nanoseconds = std::chrono::nanoseconds;

std::random_device rd;
std::mt19937 gen(rd());

void test_erase() {
    std::vector<std::string> input_names = { "D:/ss25project/data/inputs/ascend_input.txt",
    "D:/ss25project/data/inputs/random_input1.txt",
    "D:/ss25project/data/inputs/random_input2.txt",
    "D:/ss25project/data/inputs/OddEven_input_frac2_inc.txt",
    "D:/ss25project/data/inputs/OddEven_input_frac5_dic.txt",
    "D:/ss25project/data/inputs/Jump_Input_inc.txt",
    "D:/ss25project/data/inputs/Jump_Input_dic.txt",
    "D:/ss25project/data/inputs/Edge_input.txt",
    "D:/ss25project/data/inputs/Stress_input.txt" };

    size_t length_input_names = input_names.size();


    std::ofstream outFile1("D:/ss25project/data/outputs/erases/Splay_erase_height.csv");
    std::ofstream outFile2("D:/ss25project/data/outputs/erases/Splay_erase_time.csv");


    for (size_t i = 0; i < length_input_names; i++) //erase time для Splay
    {
        SplayTree<int> SplayTree1;

        std::ifstream inputFile;
        inputFile.open(input_names[i]);

        std::vector<int> Data_for_erase;

        outFile1 << "Тестовые данные " << i + 1 << ": ";
        outFile2 << "Тестовые данные " << i + 1 << ": ";

        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    Data_for_erase.push_back(std::stoi(word));
                    SplayTree1.insert((int)std::stoi(word));
                }
            }
            std::shuffle(Data_for_erase.begin(), Data_for_erase.end(), gen);

            for (int x = 0; x < Data_for_erase.size(); x++) {
                auto start = clocks::now();
                SplayTree1.erase(Data_for_erase[x]);
                auto elapsed = clocks::now() - start;
                outFile1 << SplayTree1.get_tree_height() << " ";
                outFile2 << std::chrono::duration_cast<nanoseconds>(elapsed).count() << " ";
                outFile1.flush();
                outFile2.flush();
            }
            outFile1 << std::endl;
            outFile2 << std::endl;
            outFile1.flush();
            outFile2.flush();
        }
        inputFile.close();
    }
    outFile1.close();
    outFile2.close();


    std::ofstream outFile3("D:/ss25project/data/outputs/erases/Simple_erase_height.csv");
    std::ofstream outFile4("D:/ss25project/data/outputs/erases/Simple_erase_time.csv");

    for (size_t i = 0; i < length_input_names; i++) //erase time для Simple
    {
        SimpleTree<int> SimpleTree1;

        std::ifstream inputFile;
        inputFile.open(input_names[i]);

        std::vector<int> Data_for_erase;

        outFile3 << "Тестовые данные " << i + 1 << ": ";
        outFile4 << "Тестовые данные " << i + 1 << ": ";

        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    Data_for_erase.push_back(std::stoi(word));
                    SimpleTree1.insert((int)std::stoi(word));
                }
            }
            std::shuffle(Data_for_erase.begin(), Data_for_erase.end(), gen);

            for (int x = 0; x < Data_for_erase.size(); x++) {
                auto start = clocks::now();
                SimpleTree1.erase(Data_for_erase[x]);
                auto elapsed = clocks::now() - start;
                outFile4 << std::chrono::duration_cast<nanoseconds>(elapsed).count() << " ";
                outFile3 << SimpleTree1.get_tree_height() << " ";
                outFile3.flush();
                outFile4.flush();
            }
            outFile3 << std::endl;
            outFile3.flush();
            outFile4 << std::endl;
            outFile4.flush();
        }
        inputFile.close();
    }
    outFile3.close();
    outFile4.close();


    std::ofstream outFile5("D:/ss25project/data/outputs/erases/Treap_erase_height.csv");
    std::ofstream outFile6("D:/ss25project/data/outputs/erases/Treap_erase_time.csv");

    for (size_t i = 0; i < length_input_names; i++) //erase time для Treap
    {
        Treap<int> Treap1;

        std::ifstream inputFile;
        inputFile.open(input_names[i]);

        std::vector<int> Data_for_erase;

        outFile5 << "Тестовые данные " << i + 1 << ": ";
        outFile6 << "Тестовые данные " << i + 1 << ": ";

        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    Data_for_erase.push_back(std::stoi(word));
                    Treap1.insert((int)std::stoi(word));
                }
            }
            std::shuffle(Data_for_erase.begin(), Data_for_erase.end(), gen);

            for (int x = 0; x < Data_for_erase.size(); x++) {
                auto start = clocks::now();
                Treap1.erase(Data_for_erase[x]);
                auto elapsed = clocks::now() - start;
                outFile5 << Treap1.get_tree_height() << " ";
                outFile6 << std::chrono::duration_cast<nanoseconds>(elapsed).count() << " ";
                outFile5.flush();
                outFile6.flush();
            }
            outFile5 << std::endl;
            outFile6 << std::endl;
            outFile5.flush();
            outFile6.flush();
        }
        inputFile.close();
    }
    outFile5.close();
    outFile6.close();
    
    std::ofstream outFile7("D:/ss25project/data/outputs/erases/Set_erase_time.csv");

    for (size_t i = 0; i < length_input_names; i++) //erase time для Set
    {
        std::set<int> set_test;

        std::ifstream inputFile;
        inputFile.open(input_names[i]);

        std::vector<int> Data_for_erase;

        outFile7 << "Тестовые данные " << i + 1 << ": ";

        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    Data_for_erase.push_back(std::stoi(word));
                    set_test.insert((int)std::stoi(word));
                }
            }
            std::shuffle(Data_for_erase.begin(), Data_for_erase.end(), gen);

            for (int x = 0; x < Data_for_erase.size(); x++) {
                auto start = clocks::now();
                set_test.erase(Data_for_erase[x]);
                auto elapsed = clocks::now() - start;
                outFile7 << std::chrono::duration_cast<nanoseconds>(elapsed).count() << " ";
                outFile7.flush();
            }
            outFile7 << std::endl;
            outFile7.flush();
        }
        inputFile.close();
    }
    outFile7.close();


}

int main() {
    test_erase();
    return 0;
}
