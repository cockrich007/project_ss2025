#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <climits>
#include "TestGenerator.h"


// заполняет вектор элементами по возрастанию от begin до num
void TestGenerator::DataAscend(int begin, int num) {
    Data.clear();

    for (int i = begin; i < num; i += 1) {
        Data.push_back(i);
    }
}

// заполняет вектор num случайными элементами, в диапазоне от low до high
void TestGenerator::DataRandom(int num, int low, int high) {
    Data.clear();
    std::mt19937 TestGenerator(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(low, high);
    for (int i = 0; i < num; i += 1) {
        int number = distribution(TestGenerator);
        Data.push_back(number);
    }
}

// разбивает вектор размером num на fract частей и заполняет их четными\нечетными числами (чередуя части). increase выбирает идут они
// по возрастанию или по убыванию
void TestGenerator::DataOddEven(int num, int fract, bool increase) {
    Data.clear();
    for (int x = 0; x < fract; x += 1) {
        if (increase) {
            if (x % 2 == 0) {
                for (int i = 0; i < ((num / fract)); i += 2)
                    Data.push_back(i);
            }
            else {
                for (int i = 1; i < ((num / fract)); i += 2)
                    Data.push_back(i);
            }
        }
        else {
            if (x % 2 == 0) {
                for (int i = ((num / fract)); i > 0; i -= 2)
                    Data.push_back(i);
            }
            else {
                for (int i = ((num / fract) + 1); i > 0; i -= 2)
                    Data.push_back(i);
            }
        }
    }
}

// заполняет вектор прыгающими данными (increase выбирает уменьшается разрыв или увеличивается(изначально уменьшается))
void TestGenerator::DataJump(int num, bool increase) {
    Data.clear();

    int low_num = 0;
    int high_num = 10000;
    if (increase) {
        int low_num = 5000;
        int high_num = 4999;
    }

    for (int i = 0; i < num; i += 1) {
        if (i % 2 == 0) {
            Data.push_back(low_num);
            low_num++;
        }
        else {
            Data.push_back(high_num);
            high_num--;
        }
    }
}

// Заполняет вектор граничными значениями
void TestGenerator::DataEdge() {
    Data.clear();
    for (int i = 0; i < 10; i++) {
        Data.push_back(INT32_MAX);
        Data.push_back(INT32_MIN);
    }
}

// Заполняет вектор возрастающими значениями в количестве десять в степени power_of_ten
void TestGenerator::DataStress(int power_of_ten) {
    Data.clear();
    for (int i = 0; i < pow(10, power_of_ten); i++) {
        Data.push_back(i);
    }
}