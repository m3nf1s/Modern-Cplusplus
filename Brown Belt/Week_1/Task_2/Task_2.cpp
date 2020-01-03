/*
    На лекциях вам было рассказано о внутреннем устройстве контейнеров map и set.
    Обычно map и set реализованы как двоичные деревья поиска.
    
    Также вы узнали о том, как производится обход дерева с помощью итераторов.
    
    В данной задаче мы будем работать не с контейнером set,
    но с аналогичным двоичным деревом поиска, состоящим из следующих вершин:
    
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node* parent;
    };

    Где:    
    *   value - значение, хранящееся в вершине;
    *   left и right - указатели на дочерние вершины (оба равны nullptr для листьев дерева);
    *   parent - указатель на родительскую вершину (равен nullptr для корня дерева).
    Допустим, что для обхода дерева мы используем не специальный итератор, а просто указатель на вершину Node*.
    
    Вам требуется реализовать функцию
    , возвращающую указатель на следующую по возрастанию значения вершину.
    
    Функция должна вернуть nullptr в случае, если текущая вершина - последняя в дереве.
*/

#include "test_runner.h"

#include <cassert>
#include <deque>
#include <iostream>

struct Node 
{
    Node(int v, Node* p)
        : value(v)
        , parent(p)
    {}

    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent;
};


class NodeBuilder 
{
public:
    Node* CreateRoot(int value)
    {
        nodes.emplace_back(value, nullptr);
        return &nodes.back();
    }

    Node* CreateLeftSon(Node* me, int value)
    {
        assert(me->left == nullptr);
        nodes.emplace_back(value, me);
        me->left = &nodes.back();
        return me->left;
    }

    Node* CreateRightSon(Node* me, int value) 
    {
        assert(me->right == nullptr);
        nodes.emplace_back(value, me);
        me->right = &nodes.back();
        return me->right;
    }

private:
    std::deque<Node> nodes;
};


Node* Next(Node* me) 
{
    if (me->right)
    {
        Node* ptr = me->right;
        while (ptr->left)
        {
            ptr = ptr->left;
        }
        return ptr;
    }

    Node* ptr = me->parent;
    while (ptr && me->value > ptr->value)
    {
        ptr = ptr->parent;
    }
    return ptr;
}


void Test1()
{
    NodeBuilder nb;

    Node* root = nb.CreateRoot(50);
    ASSERT_EQUAL(root->value, 50);

    Node* l = nb.CreateLeftSon(root, 2);
    Node* min = nb.CreateLeftSon(l, 1);
    Node* r = nb.CreateRightSon(l, 4);
    ASSERT_EQUAL(min->value, 1);
    ASSERT_EQUAL(r->parent->value, 2);

    nb.CreateLeftSon(r, 3);
    nb.CreateRightSon(r, 5);

    r = nb.CreateRightSon(root, 100);
    l = nb.CreateLeftSon(r, 90);
    nb.CreateRightSon(r, 101);

    nb.CreateLeftSon(l, 89);
    r = nb.CreateRightSon(l, 91);

    ASSERT_EQUAL(Next(l)->value, 91);
    ASSERT_EQUAL(Next(root)->value, 89);
    ASSERT_EQUAL(Next(min)->value, 2);
    ASSERT_EQUAL(Next(r)->value, 100);

    while (min)
    {
        std::cout << min->value << '\n';
        min = Next(min);
    }
}

void Test2()
{
    Next(nullptr);
}

void TestRootOnly() 
{
    NodeBuilder nb;
    Node* root = nb.CreateRoot(42);
    ASSERT(Next(root) == nullptr);
};


int main() 
{
    TestRunner tr;
    RUN_TEST(tr, Test1);
    RUN_TEST(tr, TestRootOnly);
    //RUN_TEST(tr, Test2);
    return 0;
}
