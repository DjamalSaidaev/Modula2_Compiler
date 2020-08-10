#include "lexic.h"
#include <fstream>
#include <string> //����������� ���������
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;


Lexic::Lexic()
{
    //cin_code.open("input.mod");
    cin_mainwords.open("mainwords.txt");
    out_code.open("temp.txt");
    variables = NULL;
    operations = NULL;
    constants = NULL;
    numstroke=1;
    keywords = NULL; //��������� ���������� �� ������ �������
    flagL=flagN=flagO=flagS=false; //��������� ��������� ��������� ��������
    int k;
    char q; //������ ���� ��������
    cin_mainwords >> k >> q;
    string s;
    for (int i = 0; i < k; i++) //������ �������� ���� �� ����� � ��������� � ������
    {
        cin_mainwords >> s;
        add1(keywords, s, i);
    }
    //print2(keywords, "k");
    cin_mainwords >> k;
    for (int i = 0; i < k; i++) //������ �������� �� ����� � ��������� � ������
    {
        int n;
        cin_mainwords >> n >> q;
        for (int j = 0; j < n; j++) //������ �������� ���� ch
        {
            cin_mainwords >> s;
            add2(operations, s, q, j);
        }
    }
}
void Lexic::openfile(char *s)
{
    cin_code.open(s);
}
int Lexic::Lexanalys()
{
    while (!endfile()) //���� �� ��������� ����� �����
    {
      automat(getsym()/*������ ������*/); //��������� �������
    }
    automat(' '); //��������� ������� � ���������� �������� ��� ��������� ����������� �������� �� ��������� ����
    printLex(); //����� �������
    closefiles();
    return 1;
}
void Lexic::closefiles()
{
    cin_code.close();
    cin_mainwords.close();
    out_code.close();
}
int Lexic::add0(list1 *&head, string w) //���������� � ������ 1 ���� ��� ����������� ������
{
    list1 *temp = new list1; //�������� ������ ��������
    temp -> next = NULL;
    temp -> word = w; //���������� ������ �������� �������������� w
    if (head) //���� ������ �� ����
    {
        list1 *t;
        for (t=head; t -> next != NULL; t = t -> next);
        temp -> num = t -> num + 1;
        t -> next = temp; //���������� � ����� �������
    }
    else
    {
        temp -> num = 0;
        head = temp;
    }
    return temp -> num; //���������� ����� ������������ ��������
}

void Lexic::add1(list1 *&head, string w, int n) //���������� � ������� 1 ���� ��� ��������� ������
{
    list1 *temp = new list1; //���������� add0
    temp -> word = w;
    temp -> next = NULL;
    temp -> num = n;
    if (head)
    {
        list1 *t;
        for (t=head; t -> next != NULL; t = t -> next);
        t -> next = temp;
    }
    else
    {
        head = temp;
    }
}

void Lexic::add2(list2 *&head, string w, char id, int n) //���������� � ������ 2 ����
{
    list2 *temp = new list2;
    temp -> next = NULL;
    temp -> id = id;
    temp -> word = w;
    temp -> num = n;
    if (head)
    {
        list2 *t;
        for (t=head; t -> next != NULL; t = t -> next);
        t -> next = temp;
    }
    else
    {
        head = temp;
    }
}

bool Lexic::sym() //�������� �� ������ ���������
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == '_')) ? true : false;
}

bool Lexic::num() //�������� �� ������ ������
{
    return (ch >= '0' && ch <= '9') ? true : false;
}

bool Lexic::oper() //�������� �� ������ ������ ��������
{
    return (ch =='"' || ch==':' || ch== ',' || ch=='.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '&' || ch == '|' || ch == '=' || ch == ';' || /*ch == '(' || ch == ')' ||*/ ch == '{' || ch == '}') ? true : false;
}

bool Lexic::separ() //�������� �� ������ ������������
{
    return (ch == '"' || ch=='[' || ch==']' || ch== ',' || ch=='.' ||  ch == ' ' || ch == '\n' || ch == ')' || ch == '(' || ch == ';' || ch == '}' || ch == '{' || (!flagO && mp != "" && oper())) ? true : false;
}

void Lexic::mpclear() //������� ��������
{
    mp = "";
}

void Lexic::InsertWord() //���������� ��������� ����� ��� ����������
{
    //char ch1;
    string w;
    list1 *temp;
    for (temp=keywords; temp!=NULL; temp = temp -> next) //����� � ������ ��������
    {
        if (temp -> word == mp)
        {
            w = "k";
            /*ch1 = '0' + temp -> num;
            w += ch1;*/
            w += " " + temp -> word + " " + numtostr(numstroke);
            Lexems.push_back(w);
            return;
        }
    }
    for (temp=variables; temp!=NULL; temp = temp -> next) //����� � ������ ����������
    {
        if (temp -> word == mp)
        {
            w = "j";
            w += " " + temp -> word + " " + numtostr(numstroke);
            Lexems.push_back(w);
            return;
        }
    }
    //int nnum = add0(variables, mp); //���������� ����� ����������
    w = "j";
    w += " " + mp + " " + numtostr(numstroke);
    Lexems.push_back(w);
    //cout << w << endl;
}

void Lexic::InsertNumber() //���������� �������� ���������
{
    //char ch1;
    string w;
    list1 *temp;
    for (temp=constants; temp!=NULL; temp = temp -> next) //����� � ������ ��������
        if (temp -> word == mp)
        {
            w = "c";
            w += " " + temp -> word + " " + numtostr(numstroke);
            Lexems.push_back(w);
            return;
        }

    //int nnum = add0(constants, mp); //���������� ����� ���������
    w = "c";
    w += " " + mp + " " + numtostr(numstroke);
    Lexems.push_back(w);
}

void Lexic::InsertOper() //���������� ��������
{
    //char ch1;
    string w;
    list2 *temp;
    for (temp=operations; temp != NULL; temp = temp -> next)
//����� � ������ ��������
        if (temp -> word == mp)
        {
            w = temp -> id;
            w += " " + temp -> word + " " + numtostr(numstroke);
            Lexems.push_back(w);
            return;
        }
}

string Lexic::numtostr(int num)
{
    char buf[5];
    string temp="";
    itoa(num, buf, 10);
    for(int i=0 ; i<5 && buf[i]!='\0'; i++) temp+=buf[i];
    //temp+="\0";
    return temp;
}
void Lexic::Insert() //���������� ������ � ����������� �� ��� ����
{
    string w="";
    if (flagS) //���� ����� � �������� ����� ��� ��� ����������
        InsertWord();

    if (flagN) //���� ����� � �������� ���������
        InsertNumber();

    if (flagO) //���� ����� - ��������
        InsertOper();

    if(flagL)
    {
        w = "l";
        w += " " + mp + " " + numtostr(numstroke);
        Lexems.push_back(w);
    }
    mpclear(); //������� ��������
}

void Lexic::Error() //���������� ������
{
    Lexems.push_back("Error"); //����� ��������� �� ������
    while (!separ() && cin_code.peek()!=EOF) //������� �������� �� ���������� �����������
        cin_code >> ch;
    mpclear();
}

void Lexic::automat(char get) //�������, ����������� �������� ��������
{
    string w;
    static char last=' ';
    ch=get;
    int h=0;
    static int q=0;
    if(q==1)
    {
        numstroke++;
        q=0;
    }
    if(ch=='\n')
    {
        q=1;
    }
    if(ch=='"')
    {
        //Insert();
        ch=getsym();
        mp="\"";
        while(ch!='"')
        {
            mp+=ch;
            ch=getsym();
        }
        mp+=ch;
        flagL=true;
        flagS = flagN = flagO = false;
        Insert();
        flagL=false;
        mp=")";
        flagO=true;
        Insert();
        return;
    }
    if (mp.length() == 0) //���� ������� ����
    {
        last=ch;
        if (!(ch == ' ' || ch == '\n')) //���� ������ �� ������ � �� ������ ����� ������
        {
            flagS = sym();
            flagN = num();
            flagO = oper(); //���������� ��� �������
            mp += ch; //��������� ������ � �������
            return;
        }
        else return;
    }
    if(ch=='*' && last=='(')
    {
        while(h!=1)
        {
            do
            {
                ch=getsym();
            }while(ch!='*');
            if(getsym()!=')') continue;
            else h=1;
        }
        h=0;
        return;
    }
    if (!separ() || (flagN && ch=='.')) //���� ������ - �� �����������
    {
        if ((sym() || num()) && flagS)
//���� ����������� ������ � ������� ������ � ������� ��� �����
            mp += ch;
        else if ((num() || ch=='.') && flagN)
            mp += ch;
//���� ����������� ����� � ������� ������ - ����� ��� �����
        else if (oper() && flagO)
//���� ����������� �������� � ������� ������ � ������ ��������
            mp += ch;
        else if (flagN && sym())
//���� ����������� �����, � ������� ������ � �������, �� ������
            Error();
        else
        {
            if(mp=="[")
            {
                w="i ";
                w += mp + " " + numtostr(numstroke);
                Lexems.push_back(w);
            }
            Insert();
            flagS = sym();
            flagN = num();
            flagO = oper();
            mp += ch; //��������� ������ � �������
        }
        last = ch;
        return;
    }
    if (separ())
    {
        if (oper()) //���� ����������� � ������ ��������
        {
            Insert();
            flagS = sym();
            flagN = num();
            flagO = oper();
            mp = ch;
        }
        else
        {
            Insert();
            if(ch=='(' || ch==')')
            {
                w="s ";
                w += ch;
                w+= " " + numtostr(numstroke);
                Lexems.push_back(w);
            }
            else if(ch=='[' || ch==']')
            {
                w="i ";
                w += ch;
                w+= " " + numtostr(numstroke);
                Lexems.push_back(w);
            }
        }
        last = ch;
    }
}

void Lexic::printLex()
{
    for(int i=0 ; i<(int)Lexems.size() ; i++)
        out_code << Lexems[i] << endl;
}
bool Lexic::endfile()
{
    return cin_code.peek()==EOF ? true : false;
}

char Lexic::getsym()
{
    char q;
    q=cin_code.get();
    return q;
}
