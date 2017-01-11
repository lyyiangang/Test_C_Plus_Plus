#include "stdafx.h"
#include "TestClass.h"
#include <queue>
#include <stack>

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
        std::cout << startNode->value <<" ";
        PrintPreOrder(startNode->lNode);
        PrintPreOrder(startNode->rNode);
    }
    void Tree::PrintPreOrderByStack(Node* startNode)const
    {
        if (startNode == nullptr)
            return;
        std::stack<Node*> allNodes;
        while (startNode != nullptr || !allNodes.empty())
        {
            while (startNode!= nullptr)
            {
                std::cout << startNode->value << " ";
                allNodes.push(startNode);
                startNode = startNode->lNode;
            }
            if (!allNodes.empty())
            {
                startNode = allNodes.top()->rNode;
                allNodes.pop();
            }
        }
    }
    void Tree::PrintMidOrder(Node* startNode)const
    {
        if (startNode == nullptr)
            return;
        PrintMidOrder(startNode->lNode);
        std::cout << startNode->value << " ";
        PrintMidOrder(startNode->rNode);
    }
    void Tree::PrintMidOrderByStack(Node* startNode)const
    {
        if (startNode == nullptr)
            return;
        std::stack<Node*> allNodes;
        while (startNode != nullptr || !allNodes.empty())
        {
            while (startNode != nullptr)
            {
                allNodes.push(startNode);
                startNode = startNode->lNode;
            }
            if (!allNodes.empty())
            {
                std::cout << allNodes.top()->value << " ";
                startNode = allNodes.top()->rNode;
                allNodes.pop();
            }
        }
    }
    void Tree::PrintAfterOrder(Node* startNode)const
    {
        if (startNode == nullptr)
            return;
        PrintAfterOrder(startNode->lNode);
        PrintAfterOrder(startNode->rNode);
        std::cout << startNode->value << " ";
    }

    void Tree::PrintLevelOrder(Node* startNode)const
    {
        if (startNode == nullptr)
            return;
        std::queue<Node*> allNodes;
        allNodes.push(startNode);
        while (!allNodes.empty())
        {
            Node* frontNode = allNodes.front();
            std::cout << frontNode->value << " ";
            if(frontNode->lNode!=nullptr)
                allNodes.push(frontNode->lNode);
            if(frontNode->rNode!=nullptr)
                allNodes.push(frontNode->rNode);
            allNodes.pop();
        }
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