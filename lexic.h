#ifndef LEXIC_H
#define LEXIC_H
#include <fstream>
#include <string> //����������� ���������
#include <iostream>
#include <vector>
using namespace std;
class Lexic
{
    ifstream cin_code; //���� � �������� ����������
    ifstream cin_mainwords; //���� � ��������� ������� ��������� �����
    ofstream out_code;
    vector <string> Lexems; //������ ������
    string mp; //�������
    bool flagS, flagN, flagO, flagL; //����� ���������� �����, ����� � ��������� ��������������
    char ch; //�������� ������
    struct list1 //������ �������� ���� � �.�.
    {
        string word; //�������������
        int num; //����� � ������
        list1 *next; //������ �� ���������
    } *variables, *constants, *keywords; // ������ ����������, �������� � �������� ����

    struct list2 //������ ��������
    {
        string word; //�������������
        char id; //������ ���� ��������
        int num; //����� �������� ����� �������� ���� �� ����
        list2 *next; //������ �� ��������� �������
    } *operations; //������ ��������
    int numstroke;
public:
    Lexic();
    int add0(list1 *&head, string w); //���������� � ������ 1 ���� ��� ����������� ������
    void add1(list1 *&head, string w, int n); //���������� � ������� 1 ���� ��� ��������� ������
    void add2(list2 *&head, string w, char id, int n); //���������� � ������ 2 ����
    bool sym(); //�������� �� ������ ���������
    string numtostr(int);
    void openfile(char *);
    bool num(); //�������� �� ������ ������
    bool oper(); //�������� �� ������ ������ ��������
    bool separ(); //�������� �� ������ ������������
    void mpclear(); //������� ��������
    void InsertWord(); //���������� ��������� ����� ��� ����������
    void InsertNumber(); //���������� �������� ���������
    void InsertOper(); //���������� ��������
    void Insert(); //���������� ������ � ����������� �� ��� ����
    void Error(); //���������� ������
    void automat(char get); //�������, ����������� �������� ��������
    void printLex();
    bool endfile();
    char getsym();
    int Lexanalys();
    void closefiles();
};


#endif
