/* A Simple calculator - By. MQJ */
/* Beta 0.02: add support of quote */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

double solve(string& q);
vector<double> getTerm(string& q);
double getValue(string& q);

int main()
{
    string input;
    for (;;)
    {
        cin >> input;
        cout << solve(input) << endl;
        input.clear();
    }
    return 0;
}

double solve(string& q)
{
    double sum = 0;
    for (auto term: getTerm(q)) // ��ÿ�����ֵ, Ȼ���ۼ�
        sum += term;

    return sum;
}

vector<double> getTerm(string& q)
{
    vector<double> term;
    string thisTerm;        // ��ǰ��
    string temp;

    int quote = 0;          // ����

    bool numStart = false;
    bool simple = false;    // �Ƿ�ֻ��ȡ

    for (auto each: q)
    {
        switch (each)
        {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
            // ��ʼ
            if (!simple)
                if (!numStart)
                    numStart = true;
            thisTerm += each;
            break;
        case '+': case '-':
            // ��ʼ
            if (!simple)
            {
                if (!numStart)
                {
                    numStart = true;
                }
                // ����
                else
                {
                    numStart = false;
                    thisTerm += ' ';    // ������
                    term.push_back(getValue(thisTerm));
                    thisTerm.clear();
                }
            }
            thisTerm += each;
            break;
        case '*': case '/':
            if (!simple)
            {
                numStart = false;
                thisTerm += ' ';
            }
            thisTerm += each;
            break;
        case '(':
            if (!simple)
            {
                simple = true;
                temp = thisTerm;
                thisTerm.clear();
            }
            else
                thisTerm += each;
            ++quote;
            break;
        case ')':
            --quote;
            if (quote == 0)
            {
                simple = false;
                thisTerm = temp + to_string(solve(thisTerm));   // �ݹ�
            }
            else
                thisTerm += each;
            break;
        }
    }
    thisTerm += " ";
    term.push_back(getValue(thisTerm));
    return term;
}

double getValue(string& q)  // �������ֵ
{
    string rightStr;
    double rightNum;
    double leftNum;
    bool token;
    char sym;

    for (auto c: q)
    {
        switch (c)
        {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.': case '+': case '-':
            rightStr += c;
            break;
        case '*': case '/':
            leftNum = rightNum;
            token = true;
            sym = c;
            break;
        case ' ':
            rightNum = atof(rightStr.c_str());
            rightStr.clear();
            if (token)
            {
                switch(sym)
                {
                case '*':
                    rightNum *= leftNum;
                    break;
                case '/':
                    rightNum = leftNum / rightNum;
                    break;
                }
            }
            break;
        }
    }
    return rightNum;
}

