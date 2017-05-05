// MathLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KDTree.h"
#include <vector>
#include <stack>
#include <functional>
#include <sstream>
#include <unordered_map>

class Operand
{
public:
    Operand(const std::string& aOperator) :_operator(aOperator){
        _str2FunMap["sin"] = (float(*)(float))&std::sin;
        _str2FunMap["cos"] = (float(*)(float))&std::cos;
        _str2FunMap["abs"] = (float(*)(float))&std::abs;
        _isUnaryOperator = _str2FunMap.find(aOperator) != _str2FunMap.end();
    };

    float Eval(float numA, float numB)const
    {
        float result = 0.0;
        if (_operator == "+")
            result = numA + numB;
        else if (_operator == "-")
            result = numA - numB;
        else if (_operator == "*")
            result = numA*numB;
        else if (_operator == "/")
            result = numA / numB;
        else
            assert(false);
        return result;
    }

    //for single param
    float Eval(float valA)const
    {
        return _str2FunMap.at(_operator)(valA);
    }

    const std::string& CmdName()const {
        return _operator;
    }

    bool IsUnaryOperator()const
    {
        return _isUnaryOperator;
    }

private:
    std::string _operator;
    bool _isUnaryOperator;//support single parameter
    std::unordered_map<std::string, std::function<float(float)> > _str2FunMap;
};

float ExpressionCalculator(const std::string& exp)
{
    std::unordered_map<std::string, int> operatorPriority{
        { "(",6 },
        { "*",4 },
        { "/",4 },
        { "sin",4 },
        { "cos",4 },
        { "abs",4 },
        { "+",2 },
        { "-",2 },
        { ")",1 },
        { "#",0 } 
    };

    std::unordered_map<std::string, int> functionPriority{
        { "sin",4 },
        { "cos",4 },
        { "abs",4 }
    };

    std::string copiedExp = exp;
    copiedExp.append("#");
    auto trimStr = [](const std::string& str) {
        if (str.empty())
            return str;
        auto tmpStr = str;
        tmpStr.erase(0, tmpStr.find_first_not_of(' '));
        tmpStr.erase(tmpStr.find_last_not_of(' ') + 1);
        return tmpStr;
    };
    //true for function, and false for number.
    auto isFunctionOrNumber = [&](const std::string& str)->bool {
        assert(!str.empty());
        return functionPriority.find(str) != functionPriority.end();
    };

    std::stack<float> dataStack;
    std::stack<Operand> operatorStack;
    std::ostringstream iStream;
    for (int ii = 0; ii < copiedExp.size(); ++ii)
    {
        std::string curChar;
        curChar.append(1,copiedExp[ii]);
        if (curChar == " ")
            continue;
        bool isBasicOperator = operatorPriority.find(curChar) != operatorPriority.end();
        if (!isBasicOperator)
        {
            iStream << curChar;
        }
        if ((isBasicOperator || ii == copiedExp.size() - 1) && !iStream.str().empty())
        {
            std::string bufferStr = trimStr(iStream.str());
            bool isFunction = isFunctionOrNumber(bufferStr);
            if (isFunction)
                operatorStack.push(bufferStr);
            else
                dataStack.push(std::atof(bufferStr.c_str()));
            iStream.str("");
        }

        if (isBasicOperator)
        {
            if (operatorStack.empty())
            {
                operatorStack.push(curChar);
            }
            else
            {
                Operand preOperator = operatorStack.top();
                if (preOperator.CmdName() == "(" && curChar == ")")
                {
                    operatorStack.pop();
                    continue;
                }
                if (operatorPriority[preOperator.CmdName()] >= operatorPriority[curChar] && preOperator.CmdName() != "(")
                {
                    operatorStack.pop();
                    if (dataStack.size() == 1 &&(preOperator.CmdName() == "-" || preOperator.CmdName() == "+"))//-5??
                    {
                        int sign = preOperator.CmdName() == "-" ? -1 : 1;
                        dataStack.top() *= sign;
                        --ii;
                        continue;
                    }
                    float numA = dataStack.top();
                    dataStack.pop();
                    float result = 0;
                    if (preOperator.IsUnaryOperator())
                    {
                        result = preOperator.Eval(numA);
                    }
                    else
                    {
                        result = preOperator.Eval(dataStack.top(), numA);
                        dataStack.pop();
                    }
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
    const float PI = 3.1415926;
    auto IsEqual = [&](float valA, float valB)->bool {
        return std::fabs(valA - valB) < epsilon;
    };
    std::vector<std::pair<std::string, float>> testEntries{
        { "3*sin(0/2)+7", 7 },
        { "-sin(-PI/2+PI*3/3)+0/5+0.00", 0 },
        { "(-22+(-33))", -55 },
        { "(-22+33)", 11 },
        { "-3", -3 },
        { "(233)",233 },
        { "22.5",22.5 },
        { "((-2.5)*10+5)", -20 },
        { "((-2*3+6)*10+5)", 5 },
        { "(2+5/3)", 3.666666666666667 },
        { "(3*6/5+2)-33/8*9-7", -38.525 },
        {"(2-3)*(3-5)/1.0+2",4}
    };
    for (const auto& curPair : testEntries)
    {
        float result = ExpressionCalculator(curPair.first);
        if (!IsEqual(result, curPair.second))
            std::cout << "Fail. Expression:" << curPair.first << "result is:" << result << ",want:" << curPair.second << std::endl;
    }
    std::cout << "Finish" << std::endl;
}
float testFun(float val)
{
    return val;
}
double testFun(double val)
{
    return val;
}
int _tmain(int argc, _TCHAR* argv[])
{
    TestExpression();
    getchar();
	return 0;
}


