#include <iostream>
#include "lexic.h"
#include "syntax.h"
using namespace std;

int main(int argc, char* argv[])
{
    Lexic L;
    Syntax S;
    int a;
    setlocale(0, "rus");
    cout << "����� ��������� �������������(1 ��� 2)?\n";
    cin >> a;
    if (a == 1)// ���� �������� ���������, �� argc ����� ������ 1(� ����������� �� ���-�� ����������)
    {
        L.openfile("input.mod");// ����� ������ ������ �� ������� ���������� �� ������(��������� � ������� ���������� � 0 )
    }
    else if(a==2)
    {
        L.openfile("input2.mod");
    }
    if(L.Lexanalys())
    {
        if(S.Synanalys())
        {
            if(S.GenerCode())
            {
                cout << "���������� ���������!!!" << endl;
            }
        }
    }
    return 0;
}
