#pragma once
#include <iostream>
#include <vector>

namespace Test
{
    //------------------------binary tree------------------------
    typedef struct Node_t
    {
        double value;
        Node_t* lNode;
        Node_t* rNode;
    } Node;
    //http://blog.csdn.net/fansongy/article/details/6798278/
    class Tree
    {
    public:
        Tree():_root(nullptr){};
        void AddData(int val);
        void FreeAllNodes();

        void PrintPreOrder(Node* startNode)const;
        void PrintPreOrderByStack(Node* startNode)const;

        void PrintMidOrder(Node* startNode)const;
        void PrintMidOrderByStack(Node* startNode)const;

        void PrintAfterOrder(Node* startNode)const;
        void PrintAfterOrderByStack(Node* startNode)const;

        void PrintLevelOrder(Node* startNode)const;//层序遍历

        int Height(Node* startNode)const;
        Node* GetRootNode()const;

    private:
        Node* _root;
        void AppendNode(Node** parentNode,Node* newNode);
        void FreeOneNode(Node* startNode);
    };
    //------------------------kd tree------------------------
    typedef struct Point2_t
    {
    public:
        float& operator[](int index){
            return pos[index];
        }
        const float& operator[](int index)const{
            return pos[index];
        }
    private:
        float pos[2];

    } Point2;

    typedef std::vector<Point2> StlPoint2Vector;

    typedef struct KDNode_t
    {
        float data;
        float range[2];
        KDNode_t* parent;
        KDNode_t* left;
        KDNode_t* right;
    } KDNode;

    //http://blog.csdn.net/qll125596718/article/details/8426458
    class KDTree
    {
    public:
        KDTree() :_root(nullptr),
                  _dim(2){};
        void ConstructTree(const StlPoint2Vector& pts);

    private:
        void CreateNode(KDNode* startNode, int split, StlPoint2Vector* pts);

        KDNode* _root;
        int _dim;
    };

    //两个不同维度的方差
    void Variance(const StlPoint2Vector& pts, float variance[2]);

}
