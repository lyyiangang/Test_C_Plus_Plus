#pragma once
#include <iostream>
namespace Test
{
    typedef struct Node_t
    {
        double value;
        Node_t* lNode;
        Node_t* rNode;
    } Node;

    class Tree
    {
    public:
        Tree():_root(nullptr){};
        void AddData(int val);
        void FreeAllNodes();
        void PrintPreOrder(Node* startNode)const;
        void PrintMidOrder(Node* startNode)const;
        void PrintAfterOrder(Node* startNode)const;
        void PrintLevelOrder()const;
        void PrintStackPreOrder()const;
        void PrintStackAfterOrder()const;
        Node* GetRootNode()const;

    private:
        Node* _root;
        void AppendNode(Node** parentNode,Node* newNode);
        void FreeOneNode(Node* startNode);
    };
}
