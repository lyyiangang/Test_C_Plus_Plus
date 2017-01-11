// firstConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <numeric>
#include "TestClass.h"

void TestBinaryTree()
{

    //                                      8
    //                              5                15
    //                           3      7        12       18
    //                          1  4  6   _    11   13  16   19 
    //                                  
    Test::Tree tree;
    tree.AddData(8);
    tree.AddData(5);
    tree.AddData(15);
    tree.AddData(3);
    tree.AddData(7);
    tree.AddData(12);
    tree.AddData(18);
    tree.AddData(1);
    tree.AddData(4);
    tree.AddData(6);
    tree.AddData(11);
    tree.AddData(13);
    tree.AddData(16);
    tree.AddData(19);
    
    std::cout << "\n------------pre order-----------" << std::endl;
    tree.PrintPreOrder(tree.GetRootNode());
    std::cout << "\n--------------pre order by stack----\n" << std::endl;
    tree.PrintPreOrderByStack(tree.GetRootNode());

    std::cout << "\n---------------mid order----------" << std::endl;
    tree.PrintMidOrder(tree.GetRootNode());
    std::cout << "\n-------------- mid order by stack--\n" << std::endl;
    tree.PrintMidOrderByStack(tree.GetRootNode());

    std::cout << "\n---------------after order----------" << std::endl;
    tree.PrintAfterOrder(tree.GetRootNode());
    std::cout << "\n-----------------lever order----------" << std::endl;
    tree.PrintLevelOrder(tree.GetRootNode());
    tree.FreeAllNodes();
}


int main()
{
    TestBinaryTree();
    system("pause");
}