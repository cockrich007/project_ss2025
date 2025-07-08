#pragma once
//Я не знаю что такое темплейт, а у тебя нод через него реализован

class NodeInt {
public:
    int value;
    int height;
    NodeInt* l, * r;
    NodeInt();
    NodeInt(int value);
    NodeInt(int value, NodeInt* l, NodeInt* r);
    ~NodeInt();
};

class RBTree() {
private:
	NodeInt* root;
    int size;


}

