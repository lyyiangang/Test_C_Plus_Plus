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

    //-------------------------------------------------------------kdtree----------------------------------------------------------
    void KDTree::ConstructTree(const StlPoint2Vector& pts)
    {
        StlPoint2Vector copiedPt = pts;
        ConstructTreePrivate(&_root, copiedPt.begin(), copiedPt.end(), 1);
    }

    void KDTree::ConstructTreePrivate(KDNode** parentNode,StlPoint2Vector::iterator startIt, StlPoint2Vector::iterator endIt, int level)
    {
        int count = std::distance(startIt, endIt);
        if (count<1)
            return;
       // float variance[2] = { 0 };
       // Variance(startIt, endIt, variance);
        //int split = variance[0] > variance[1] ? 0 : 1;
        int split = level%_dim;
        std::sort(startIt, endIt, [&split](const Point2& ptA, const Point2& ptB){
            return ptA[split] < ptB[split];
        });
        auto midIt = startIt + (int)(count / 2);
        float range[2] = { (*startIt)[split], (*(--endIt))[split] };
        AppendPoint(parentNode, *midIt, range, level);
        ConstructTreePrivate(parentNode,startIt, midIt,level+1);
        ConstructTreePrivate(parentNode,midIt + 1, endIt,level+1);
    }
    
    void KDTree::AppendPoint(KDNode** parentNode,const Point2& pt,float range[2],int level)
    {
        KDNode* newNode= NewNode(pt);
        newNode->range[0] = range[0];
        newNode->range[1] = range[1];
        newNode->level = level;
        if (*parentNode == nullptr)
        {
            *parentNode= newNode;
            return;
        }
        int index = (*parentNode)->level%_dim;
        if (pt[index] < (*parentNode)->pt[index])
            AppendPoint(&(*parentNode)->left, pt, range, level);
        else
            AppendPoint(&(*parentNode)->right, pt, range, level);
    }

    KDNode* KDTree::NewNode(const Point2& pt)
    {
        KDNode* resultNode = new KDNode();
        resultNode->left = nullptr;
        resultNode->right = nullptr;
        resultNode->parent = nullptr;
        resultNode->level = 0;
        resultNode->pt = pt;
        resultNode->range[0] = 0;
        resultNode->range[1] = 0;
        return resultNode;
    }

    void Variance(StlPoint2Vector::iterator startIt, StlPoint2Vector::iterator endIt, float variance[2])
    {
        int count = std::distance(startIt, endIt);
        assert(count > 0 && variance != nullptr);
        float Ex = 0, Ey = 0;
        std::for_each(startIt,endIt,[&Ex,&Ey](const Point2& curPt)
        {
            Ex += curPt[0];
            Ey += curPt[1];
        });
        Ex /= count;
        Ey /= count;

        float sumDeltaX = 0, sumDeltaY = 0;
        std::for_each(startIt,endIt,[&](const Point2 & curPt)
        {
            sumDeltaX += (curPt[0] - Ex)*(curPt[0] - Ex);
            sumDeltaY += (curPt[1] - Ey)*(curPt[1] - Ey);
        });
        variance[0] = sumDeltaX / count;
        variance[1] = sumDeltaY / count;
    }

}