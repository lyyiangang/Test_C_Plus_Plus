#include "stdafx.h"
#include "TestClass.h"

namespace Test
{
    void Tree::AddData(int val)
    {
        Node* newNode = new Node();
        newNode->lNode = nullptr;
        newNode->rNode = nullptr;
        newNode->value = val;
        AppendNode(&_root,newNode);
    }

    void Tree::AppendNode(Node** parentNode,Node* newNode)
    {
        if (*parentNode == nullptr)
        {
            *parentNode = newNode;
            return;
        }
        if (newNode->value < (*parentNode)->value)
            AppendNode(&((*parentNode)->lNode), newNode);
        else
            AppendNode(&((*parentNode)->rNode), newNode);
    }

    void Tree::FreeAllNodes()
    {
        FreeOneNode(_root);
        _root = nullptr;
    }
    void Tree::FreeOneNode(Node* startNode)
    {
        if (startNode == nullptr)
            return;
        FreeOneNode(startNode->lNode);
        FreeOneNode(startNode->rNode);
        delete startNode;
    }
    void Tree::PrintPreOrder(Node* startNode)const
    {
        if (startNode == nullptr)
            return;
        std::cout << startNode->value <<"  ";
        PrintPreOrder(startNode->lNode);
        PrintPreOrder(startNode->rNode);
    }
    void Tree::PrintMidOrder(Node* startNode)const
    {
        if (startNode == nullptr)
            return;
        PrintMidOrder(startNode->lNode);
        std::cout << startNode->value << "   ";
        PrintMidOrder(startNode->rNode);
    }
    void Tree::PrintAfterOrder(Node* startNode)const
    {
        if (startNode == nullptr)
            return;
        PrintAfterOrder(startNode->lNode);
        PrintAfterOrder(startNode->rNode);
        std::cout << startNode->value << "   ";
    }
    void Tree::PrintLevelOrder()const
    {
    }
    void Tree::PrintStackPreOrder()const
    {
    }
    void Tree::PrintStackAfterOrder()const
    {
    }
    Node* Tree::GetRootNode()const
    {
        return _root;
    }
}