#include "stdafx.h"
#include "TestClass.h"
#include <queue>
#include <stack>
#include <algorithm>

namespace Test
{
    void Tree::AddData(int val)
    {
        Node* newNode = new Node();
        newNode->lNode = nullptr;
        newNode->rNode = nullptr;
        newNode->value = val;
        AppendNode(&_root, newNode);
    }

    void Tree::AppendNode(Node** parentNode, Node* newNode)
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
        std::cout << startNode->value << " ";
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
            while (startNode != nullptr)
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
    void Tree::PrintAfterOrderByStack(Node* startNode)const
    {
        if (startNode == nullptr)
            return;

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
            if (frontNode->lNode != nullptr)
                allNodes.push(frontNode->lNode);
            if (frontNode->rNode != nullptr)
                allNodes.push(frontNode->rNode);
            allNodes.pop();
        }
    }

    int Tree::Height(Node* startNode)const
    {
        if (startNode == nullptr)
            return 0;
        int left = Height(startNode->lNode);
        int right = Height(startNode->rNode);
        return std::max(left, right) + 1;
    }
    Node* Tree::GetRootNode()const
    {
        return _root;
    }

    void KDTree::ConstructTree(const StlPoint2Vector& pts)
    {
        if (pts.empty())
            return;
        StlPoint2Vector copiedPts = pts;
        float variance[2] = { 0 };
        Variance(copiedPts, variance);
        int split = variance[0] > variance[1] ? 0 : 1;
        CreateNode(_root, split, &copiedPts);
    }
    void KDTree::CreateNode(KDNode* startNode, int split, StlPoint2Vector* pts)
    {
        assert(startNode == nullptr && (split == 1 || split == 0));
        int tmpSplit = split;
        std::sort(pts->begin(),pts->end(), 
                  [tmpSplit ](const Point2 & ptA, const Point2 & ptB){return ptA[tmpSplit] > ptB[tmpSplit]; });
        int mid = (int)(pts->size() / 2);
        startNode = new KDNode();
        startNode->data = pts->at(mid)[split];
        startNode->left = nullptr;
        startNode->right = nullptr;
        startNode->range[0] = pts->front()[split];
        startNode->range[1] = pts->back()[split];
        pts->erase(pts->begin() + mid);
        
        split = (split == 0) ? 1 : 0;

    }

    void Variance(const StlPoint2Vector& pts, float variance[2])
    {
        assert(!pts.empty() && variance != nullptr);
        float Ex = 0, Ey = 0;
        for (auto& curPt : pts)
        {
            Ex += curPt[0];
            Ey += curPt[1];
        }
        Ex /= pts.size();
        Ey /= pts.size();

        float sumDeltaX = 0, sumDeltaY = 0;
        for (auto& curPt : pts)
        {
            sumDeltaX += (curPt[0] - Ex)*(curPt[0] - Ex);
            sumDeltaY += (curPt[1] - Ey)*(curPt[1] - Ey);
        }
        variance[0] = sumDeltaX / pts.size();
        variance[1] = sumDeltaY / pts.size();
    }

}