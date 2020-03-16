// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <queue>
#include <regex>
#include<stdlib.h>
using namespace std;

// 运算符优先级
int op_pri(string op) {
    if (op == "+" || op == "-") {
        return 1;
    }
    else if (op == "*" || op == "/") {
        return 2;
    }
    else if (op == "(" || op == ")") {
        return 0;
    }
    else {
        return -1;
    }
}

bool get_math(string str, queue<string>& save_match) {
    vector<string> save_stack;
    save_stack.push_back("#");
    //regex reg_all("^(((?<o>\()[-+]?([0-9]+[-+*/])*)+[0-9]+((?<-o>\))([-+*/][0-9]+)*)+($|[-+*/]))*(?(o)(?!))$");
    regex reg_all("(([0-9]+)[.]*([0-9]*))(([0-9]+)[.]*([0-9]*)|[+*/)(-])*(([0-9]+)[.]*([0-9]*))");
    if (regex_match(str, reg_all)) {
        regex reg("((([0-9]+)([.]*)([0-9]*))|[+*/)(-])");
        smatch str_match;
        auto pos = str.cbegin();
        auto end = str.cend();
        for (; regex_search(pos, end, str_match, reg); pos = str_match.suffix().first) {
            regex reg_number("([0-9]+)([.]*)([0-9]*)");
            if (regex_match(str_match.str(0), reg_number)) {
                save_match.push(str_match.str(0));
            }
            else {
                while (op_pri(save_stack.back()) >= op_pri(str_match.str(0))) {
                    save_match.push(save_stack.back());
                    save_stack.pop_back();
                }
                save_stack.push_back(str_match.str(0));
            }
        }
        for (; save_stack.begin() != save_stack.end(); save_stack.pop_back()) {
            save_match.push(save_stack.back());
        }
        return true;
    }
    else {
        return false;
    }
}

double cal_math(queue<string>& save_math) {
    double res = 0;
    vector<double> save_stack;
    for (; !save_math.empty(); save_math.pop()) {
        string str = save_math.front();
        cout << str << endl;
        regex reg_number("([0-9]+)[.]*([0-9]*)");
        if (regex_match(str, reg_number)) {
            save_stack.push_back(atof(str.c_str()));
        }
        else {
            if (str == "#")
                return res;
            double number1 = save_stack.back();
            save_stack.pop_back();
            double number2 = save_stack.back();
            save_stack.pop_back();
            if (str == "+") {
                res = number2 + number1;
                save_stack.push_back(res);
            }
            else if (str == "-") {
                res = number2 - number1;
                save_stack.push_back(res);
            }
            else if (str == "*") {
                res = number2 * number1;
                save_stack.push_back(res);
            }
            else if (str == "/") {
                res = number2 / number1;
                save_stack.push_back(res);
            }
            else {
                return res;
            }
        }
    }
    return res;
}

int main()
{
    // 输入值
    string math = "";
    // 后缀表达式
    queue<string> save_math;
    cout << "请输入计算表达式(不支持括号)" << endl;
    cin >> math;
    if (get_math(math, save_math)) {
        cout << "结果为: " << cal_math(save_math) << endl;
    }
    else {
        cout << "输入计算式格式有误" << endl;
    }

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
