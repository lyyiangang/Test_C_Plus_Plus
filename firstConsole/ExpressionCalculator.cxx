#include "stdafx.h"
#include <vector>
#include <stack>
#include <functional>
#include <sstream>

float ExpressionCalculator(const std::string& exp)
{
    std::unordered_map<char, int> operatorPriority{
        { '(',6 },
        { '*',4 },
        { '/',4 },
        { '+',2 },
        { '-',2 },
        { ')',1 },
        { '#',0 } };
    std::string copiedExp = exp;
    copiedExp.append("#");
    auto opertor2Num = [](float numA, float numB, char opertorToken)->float {
        float result = 0.0;
        switch (opertorToken)
        {
        case '+': result = numA + numB; break;
        case '-':result = numA - numB; break;
        case '*':result = numA*numB; break;
        case '/':result = numA / numB; break;
        default: assert(false); break;
        }
        return result;
    };

    std::stack<float> dataStack;
    std::stack<char> operatorStack;
    std::ostringstream iStream;
    for (int ii = 0; ii < copiedExp.size(); ++ii)
    {
        char curChar = copiedExp[ii];
        if (curChar == ' ')
            continue;
        bool isOperator = operatorPriority.find(curChar) != operatorPriority.end();
        if (!isOperator)
        {
            iStream << curChar;
        }
        if ((isOperator || ii == copiedExp.size() - 1) && !iStream.str().empty())
        {
            dataStack.push(std::atof(iStream.str().c_str()));
            iStream.str("");
        }
        if (isOperator)
        {
            if (operatorStack.empty())
            {
                operatorStack.push(curChar);
            }
            else
            {
                char preOperator = operatorStack.top();
                if (preOperator == '(' && curChar == ')')
                {
                    operatorStack.pop();
                    continue;
                }
                if (operatorPriority[preOperator] >= operatorPriority[curChar] && preOperator != '(')
                {
                    operatorStack.pop();
                    float numA = dataStack.top();
                    dataStack.pop();
                    float numB = dataStack.top();
                    dataStack.pop();
                    float result = opertor2Num(numB, numA, preOperator);
                    dataStack.push(result);
                    --ii;
                    continue;
                }
                else
                {
                    operatorStack.push(curChar);
                }
            }
        }
    }
    assert(dataStack.size() == 1 && operatorStack.size() == 1);
    return dataStack.top();
}

void TestExpression()
{
    const float epsilon = 1e-6;
    auto IsEqual = [&](float valA, float valB)->bool {
        return std::fabs(valA - valB) < epsilon;
    };
    std::vector<std::pair<std::string, float>> testEntries{ 
        { "(2)", 2 },
        { "((2.5))", 2.5 },
        { "(2+5/3)", 3.666666666666667 },
        { "(3*6/5+2)-33/8*9-7", -38.525 },
        { "(233)",233 },
        { "22.5",22.5 }
    };
    for (const auto& curPair : testEntries)
    {
        float result = ExpressionCalculator(curPair.first);
        if (!IsEqual(result, curPair.second))
            std::cout << "Expression:" << curPair.first << "result is:" << result << ",want:" << curPair.second << std::endl;
    }
    std::cout << "all tests pass" << std::endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
    TestExpression();
    getchar();
	return 0;
}


