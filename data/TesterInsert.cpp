#include "TestGenerator.h"

#include "../src/SimpleTree.h"
#include "../src/SplayTree.h"
#include "../src/Treap.h"

using namespace std;

void generate_tests() {
    TestGenerator gen;
    freopen("inputs/ascend_input.txt", "w", stdout);
    gen.DataAscend(0, 10000);
    for (auto element : gen.Data) {
        cout << element << '\n';
    }
}

int main() {
    generate_tests();
    return 0;
}