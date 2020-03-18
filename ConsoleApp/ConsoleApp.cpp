// ConsoleApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 10000;

int n;
char expression[maxn + 5];

int read_pos;    //read()读入时最后一个字符的位置+1 
inline int getNumber(int s) {    //获取s位置起的第一个数字 
    int number = 0;
    for (; (expression[s] >= '0' && expression[s] <= '9'); s++)
        number = number * 10 + expression[s] - '0';
    read_pos = s;
    return number;
}

int solve(int pos, int length) {    
    int stack[2][maxn + 5], len = 0;    
    switch (expression[pos]) {
        case '-': stack[0][++len] = 1, stack[1][len] = getNumber(pos);
        default: stack[0][++len] = -1, stack[1][len] = getNumber(pos + 1);
    }
    pos = read_pos;
    int temp;
    while (pos <= length) {
        switch (expression[pos]) {
        case '+': stack[0][++len] = 1, stack[1][len] = getNumber(pos + 1); break;
        case '-': stack[0][++len] = -1, stack[1][len] = getNumber(pos + 1); break;
        case '*': temp = getNumber(pos + 1), stack[1][len] *= temp; break;
        case '/': temp = getNumber(pos + 1), stack[1][len] /= temp; break;
        default:  break;
        }
        pos = read_pos;
    }
    int result = 0;
    for (int i = 1; i <= len; i++)    //计算数据
        result += (stack[0][i] * stack[1][i]);
    return result;
}

int main() {
    std::cout << "请输入算式：";
    std::cin >> expression;
    int length = strlen(expression);
    std::cout << "运算结果为：" << expression << "=" << solve(0, length - 1) << '\n';
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
