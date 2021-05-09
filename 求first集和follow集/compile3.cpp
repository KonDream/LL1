#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;

//  存放终结符
string Vt[] = {"IDN", "(", ")", "int", "char", "float", "void",
                ",", ";", "{", "}", "init", "continue", "break",
                "return", "while", "for", "if", "else", "&&", "||",
                "++", "--", ">", ">=", "<", "<=", "==", "!=", "=",
                "+=", "-=", "*=", "/=", "%=", "+", "-", "*", "/", "%",
                "FLOAT", "CHAR", "STR", "INT", "$", "#"};    //44

string Vn[] = {"S", "func", "type", "args", "arg", "func_body", "block",
                "vars", "stmts", "stmt", "assign_stmt", "jump_stmt",
                "iteration_stmt", "branch_stmt", "result",
                "logical_expression", "bool_expression", "lop",
                "isnull_expr", "expression", "operation", "compare_op",
                "equal_op", "value", "value'", "item", "item'",
                "factor", "call_func", "es", "isnull_es", "const",
                "num_const"};   //34

struct node{
    string vn;
    string beside_vn;
    string str[100];    //  分割后的串
    int no; //  记录分割出的数量
};

node tmp[100];

// struct node2{
//     string vn;
//     string vt;
// };

// node2 first[100];
set<string> first[100];
set<string> follow[100];
int num;    //  记录文法条数

void init()
{
    ifstream test("D:\\first.txt");
    if(!test.is_open())
        cout << "打开文件失败！" << endl;
    string s = "";
    int k = 0;
    while(getline(test, s))
    {
        int i;
        for(i = 0; i < s.length() && s[i] != ' '; ++ i)
            tmp[k].vn += s[i];      
        for(int j = i + 4; j < s.length(); ++ j)
            tmp[k].beside_vn += s[j];
        k ++;
    }
    num = k;
    test.close();
}

void divide()
{
    for(int i = 0; i < num; ++ i)
    {
        string t = "";
        int k = 0;
        for(int j = 0; j < tmp[i].beside_vn.length(); ++ j)
        {
            if(j == tmp[i].beside_vn.length() - 1)
            {
                t += tmp[i].beside_vn[j];
                tmp[i].str[k] = t;
                tmp[i].no ++;
                break;
            }
            if(tmp[i].beside_vn[j] != ' ')
            {
                t += tmp[i].beside_vn[j];
                if(j == tmp[i].beside_vn.length() - 1)
                    t += tmp[i].beside_vn[tmp[i].beside_vn.length() - 1];            
            }
            else
            {
                tmp[i].str[k] = t;
                tmp[i].no ++;
                t = "";
                k ++;               
            }
        }
    }
}

int find(string s)  //  找终结符
{
    for(int i = 0; i < 46; ++ i)
    {
        if(s == Vt[i])
            return 1;
    }
    return 0;
}

int find1(string s) //  找非终结符
{
    for(int i = 0; i < 34; ++ i)
    {
        if(s == Vn[i])
            return i;
    }
    return -1;
}

void get_first(string s)
{
    int tag = 0;
    int flag = 0;
    for(int i = 0; i < num; ++ i)
    {   
        if(tmp[i].vn == s)
        {
            for(int j = 0; j < tmp[i].no; ++ j)
            {
                if(find(tmp[i].str[j])) //  可以找到，说明是终结符
                {
                    first[find1(s)].insert(tmp[i].str[j]);
                    break;
                }
                else
                {
                    get_first(tmp[i].str[j]);
                    set<string>::iterator it;
                    for(it = first[find1(tmp[i].str[j])].begin(); it != first[find1(tmp[i].str[j])].end(); it++)
                    {
                        if(*it == "#")
                            flag = 1;
                        else
                            first[find1(s)].insert(*it);
                    }
                    //cout << flag << endl;
                    if(flag == 0)
                        break;
                    else
                    {
                        tag += flag;
                        flag = 0;
                    }
                }
            }
           // cout << tag << endl;
            if(tag == tmp[i].no)
                first[find1(s)].insert("#");
        }       
    }
}

void get_follow(string s)
{
    for(int i = 0; i < num; ++ i)
    {
        if(tmp[0].vn == s)
            follow[find1(tmp[0].vn)].insert("#");
        int index = -1;
        int l = tmp[i].no;
        for(int j = 0; j < l; ++ j)
        {
            if(tmp[i].str[j] == s)
                index = j;
        }

        if(index != -1 && index < l - 1)
        {
            string next = tmp[i].str[index + 1];
            if(find(next))
                follow[find1(s)].insert(next);
            else
            {
                int flag = 0;
                set<string>::iterator it;
                for(it = first[find1(next)].begin(); it != first[find1(next)].end(); it ++)
                {
                    if(*it=="$")
                        flag = 1;
                    else
                        follow[find1(s)].insert(*it);
                }
                if(flag && tmp[i].vn != s)
                {
                    get_follow(tmp[i].vn);
                    set<string>::iterator it;
                    for(it = follow[find1(tmp[i].vn)].begin(); it != follow[find1(tmp[i].vn)].end(); it ++)
                    {
                        follow[find1(s)].insert(*it);
                    }
                }
            }
        }
        else if(index != -1 && index == l - 1 && s != tmp[i].vn)
        {
            get_follow(tmp[i].vn);
            set<string>::iterator it;
            string kk = tmp[i].vn;
            for(it = follow[find1(kk)].begin(); it != follow[find1(kk)].end(); it ++)
                follow[find1(s)].insert(*it);
        }
    }
}

int main()
{
    init();
    divide();
    for(int i = 0; i < 33; ++ i)
    {
        get_first(Vn[i]);
    }

    for(int i = 0; i < 33; ++ i)
        get_follow(Vn[i]);
    
    // ofstream fout;
    // fout.open("D:\\first_ans.txt");
    for(int i = 0; i < 33; ++ i)
    {
        cout << Vn[i] << ":";
        set<string>::iterator it;
        for(it = first[i].begin(); it != first[i].end(); it++)
            cout << *it << " ";
        cout << endl;
    }
    return 0;
}
