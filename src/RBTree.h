/*
#pragma once
//Я не знаю что такое темплейт, а у тебя нод через него реализован

class NodeInt {
public:
    int value;
    int height;
    bool color = true;
    NodeInt* l, * r;
    NodeInt* parent;
    NodeInt();
    NodeInt(int value, bool color=true);
    NodeInt(int value, NodeInt* l, NodeInt* r, bool color=true);
    ~NodeInt();
};

class RBTree {
private:
    NodeInt* root;
    int size;

    // получение высоты вершины (с обработкой пустого указателя)
    int getHeight(NodeInt* node);

    int find_by_pos(int index, NodeInt* curr_node);
    void find_floor(int value, NodeInt* curr_node);
    void find_ceiling(int value, NodeInt* curr_node);

    // Внутренняя рекусрвивная вставка
    NodeInt* insertRecursive(NodeInt* node, int val);

    // Обновление высоты узла после вставки или удаления
    void updateHeight(NodeInt* node);

    void flipColors(NodeInt* node);
    void rightRotate(NodeInt* node);
    void leftRotate(NodeInt* node);

    void leftrightRotate(NodeInt* node);
    void rightleftRotate(NodeInt* node);

    void set_parents(NodeInt* curr_node);

public:
    RBTree();
    RBTree(int f_value);
    RBTree(NodeInt* root);
    ~RBTree();

    // получение высоты всего дерева
    int height();

    // true, если получилось вставить! (нерекурсивная)
    bool insert(int value);

    // Публичная функция вставки (рекурсивная)
    void insertRec(int val);

    // true, если получилось удалить! (нерекурсивная)
    bool remove(int value);

    // Возвращает int_max, если не смогли найти такой индекс!
    int select(int index);

    // При реализации поиска floor и ceiling используются строгие неравенства
    // Возвращает int_min, если не смогли найти такой меньший элемент!
    int floor(int value);

    // Возвращает int_max, если не смогли найти такой больший элемент!
    int ceiling(int value);
};
*/