#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <iomanip>
#include <stack>

using namespace std;

//  存放终结符 非终结符
string Vt[] = {"IDN", "(", ")", "int", "char", "float", "void",
                ",", ";", "{", "}", "init", "continue", "break",
                "return", "while", "for", "if", "else", "&&", "||",
                "++", "--", ">", ">=", "<", "<=", "==", "!=", "=",
                "+=", "-=", "*=", "/=", "%=", "+", "-", "*", "/", "%",
                "FLOAT", "CHAR", "STR", "INT","#","$"};

string Vn[] = {"S", "func", "type", "args", "arg", "func_body", "block",
                "vars", "stmts", "stmt", "assign_stmt", "jump_stmt",
                "iteration_stmt", "branch_stmt", "result",
                "logical_expression", "bool_expression", "lop",
                "isnull_expr", "expression", "operation", "compare_op",
                "equal_op", "value", "value'", "item", "item'",
                "factor", "call_func", "es", "isnull_es", "const",
                "num_const"};   //34



struct node{
    string vt;
    string beside_vt;
    string str[100];    //  分割后的串
    int no; //  记录分割出的数量 
};

int find(string s); //找到终结符对应数字
int find1(string s);//找到非终结符对应数字
int find3(string s);//判断$是否属于first
int find4(string s);
void get_first();
void get_follow();
void func();

node tmp[100];
int num;    //  记录文法条数
string table[50][50] = {}; 
string first[50][50];
string follow[50][50];
int first_size[50];
int follow_size[50];

void init()
{
    ifstream test("D:\\first.txt");
    if(!test.is_open())
        std::cout << "打开文件失败" << endl;
    string s = "";
    int k = 0;
    while(getline(test, s))
    {
        int i;
        for(i = 0; i < s.length() && s[i] != ' '; ++ i)
            tmp[k].vt += s[i];      
        for(int j = i + 4; j < s.length(); ++ j)
            tmp[k].beside_vt += s[j];
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
        for(int j = 0; j < tmp[i].beside_vt.length(); ++ j)
        {
            if(tmp[i].beside_vt[j] == ' ' || j == tmp[i].beside_vt.length() - 1)
            {
                if(j == tmp[i].beside_vt.length() - 1)
                    t += tmp[i].beside_vt[tmp[i].beside_vt.length() - 1];
                tmp[i].str[k] = t;
                tmp[i].no ++;
                t = "";
                k ++;               
                j ++;
            }
            t += tmp[i].beside_vt[j];
        }
    }
}


void creat_table(){
    int flag(0), flag1(0);
    int Vnnum(0);
    int Vtnum(0);
    int VVnum(0);
    for(int i =0;i < num; i ++){
        Vnnum = find1(tmp[i].vt);
        if(find4(tmp[i].str[0]) == 1 && tmp[i].str[0] != "$"){
            table[Vnnum][find(tmp[i].str[0])] =  tmp[i].beside_vt;
        }

        else if(tmp[i].str[0] == "$"){
        flag1 = follow_size[ find1(tmp[i].vt) ];
            for(int j = 0;j < flag1;j ++){
            Vtnum = find(follow[Vnnum][j]);
            table [Vnnum][Vtnum] =  tmp[i].beside_vt;
        }
    }
        else{
        flag = first_size[ find1(tmp[i].str[0]) ];
        for(int j = 0;j < flag;j ++){
            VVnum = find1( tmp[i].str[0]);
            Vtnum = find(first[VVnum][j]);

            table [Vnnum][Vtnum] =  tmp[i].beside_vt;
       //     cout << Vnnum <<" "<< Vtnum <<" "<<table [Vnnum][Vtnum] <<endl;
        }    
        if(find3(tmp[i].str[0]) ){
            flag1 = follow_size[ find1(tmp[i].vt) ];
            for(int j = 0;j < flag1;j ++){
   //         VVnum = find1( tmp[i].str[0]);
            Vtnum = find(follow[Vnnum][j]);
            table [Vnnum][Vtnum] =  tmp[i].beside_vt;
       //     cout << Vnnum <<" "<< Vtnum <<" "<<table [Vnnum][Vtnum] <<endl;
        }    
        }
        flag = 0;
        flag1 = 0;
        Vtnum = 0;
        Vnnum = 0;
        VVnum = 0;
    }
       }
    func();
}

void func()
{
    table[6][13] = "stmts";
    table[6][12] = "stmts";
    table[6][10] = "}";
    table[8][3] = "stmt stmts";
    table[8][14] = "stmt stmts";
    table[8][5] = "stmt stmts";
    table[8][4] = "stmt stmts";
    table[8][0] = "stmt stmts";
    table[8][13] = "jump_stmt";
    table[8][12] = "jump_stmt";
    table[8][15] = "stmt stmts";
    table[8][16] = "stmt stmts";
    table[8][17] = "stmt stmts";
    table[9][0] = "type assign_stmt";
    table[14][10] = "$";
    table[16][2] = "$";
    table[18][3] = "expression";
    table[24][35] = "+ item value'";
    table[24][36] = "- item value'";
    table[26][37] = "* factor item'";
    table[26][38] = "/ factor item'";
    table[26][39] = "% factor item'";
    table[20][8] = "$";
    table[28][8] = "$";
    table[28][21] = "$";
    table[28][22] = "$";
    table[28][23] = "$";
    table[28][24] = "$";
    table[28][26] = "$";
    table[28][25] = "$";
    table[28][27] = "$";
    table[28][28] = "$";
    table[28][29] = "$";
    table[28][30] = "$";
    table[28][31] = "$";
    table[28][32] = "$";
    table[28][33] = "$";
    table[28][34] = "$";
    table[28][35] = "$";
    table[2][0] = "$";    
    table[9][16] = "iteration_stmt";
}

int find(string s)  //  找终结符
{
    for(int i = 0; i < 46; ++ i)
    {
        if(s == Vt[i])
            return i;
    }
    return -1;
}

int find1(string s) //  找非终结符
{
    for(int i = 0; i < 43; ++ i)
    {
        if(s == Vn[i])
            return i;
    }
    return 0;
}

int find3(string s)
{
    int flag(0);
        for (int i = 0; i < first_size[find1(s)]; ++i)
        {
            if(first[find1(s)][i] == "$")
            flag = 1;
        }
        return flag;
}

int find4(string s){
    if(find(s) == -1)
        return 0;
    else
        return 1;
}

void get_first()
{   
    string s = "";
    ifstream test("D:\\first_ans.txt");
    int k = 0;
    while(getline(test, s))
    {
        int j = 0;
        for(int  i = 0; i < s.length() ; ++ i)
        {
            if(s[i] == ' ' )
                j ++;
            else if(i == s.length() - 1)
            {
                first[k][j] += s[i];
                j ++;
            }
            else
                first[k][j] += s[i];
        }
        first_size[k]=j;
        k ++;
    }
    test.close();
}

void get_follow()
{   
    string s = "";
    ifstream test("D:\\follow_ans.txt");
    int k = 0;
    while(getline(test, s))
    {
        int j = 0;
        for(int i = 0; i < s.length() ; ++ i)
        {
            if(s[i] == ' ' )
                j ++;
            else if(i == s.length() - 1)
            {
                follow[k][j] += s[i];
                j ++;
            }
            else
                follow[k][j] += s[i];                         
        }
        follow_size[k]=j;
        k ++;
    }
    test.close();
}

void print_stack(stack<string> s)   
{
    while(!s.empty())
    {
        std::cout << s.top();
        s.pop();
    }
}

stack<string> sign; //  符号串
stack<string> input;    //  输入串
stack<string> tmp_input;

void predict()
{   
    sign.push("#");
    // input.push("#");
    ifstream token("D:\\token.txt");
    string s;
    while(!token.eof())
    {
        token >> s;
        tmp_input.push(s);
    }
    tmp_input.pop();
    tmp_input.push("#");
    while(!tmp_input.empty())
    {
        input.push(tmp_input.top());
        tmp_input.pop();
    }
    sign.push("S");
    print_stack(sign);
    std::cout << "\t";
    print_stack(input);
    std::cout << "\t";
    if(table[find1(sign.top())][find(input.top())] != "" && sign.top() != input.top())
        std::cout << "\t" << sign.top() << " -> " << table[find1(sign.top())][find(input.top())];
    std::cout << endl;
    while(!sign.empty())
    {
        string x = sign.top();
        string a = input.top();
        if(find4(x) || x == "#")
        {
            if(x == "#" && a == "#")
            {
                std::cout << "accept!" << endl;
                break;
            }
            else if(x == a && x != "#" && a != "#")
            {
                sign.pop();
                input.pop();
            }
        }
        else
        {
            if(table[find1(x)][find(a)] != "")
            {   
                string tmp_str = table[find1(x)][find(a)];
                sign.pop();
                if(table[find1(x)][find(a)] != "$")
                {
                    stack<string> tmp_stack;
                    string t = "";
                    for(int i = 0; i < tmp_str.length(); ++ i)
                    {
                        if(i == tmp_str.length() - 1)
                        {
                            t += tmp_str[i];
                            tmp_stack.push(t);
                            break;
                        }
                        if(tmp_str[i] != ' ')
                        {
                            t += tmp_str[i];
                            if(i == tmp_str.length() - 1)
                                t += tmp_str[i];            
                        }
                        else
                        {
                            tmp_stack.push(t);
                            t = "";              
                        }
                    }
                    while(!tmp_stack.empty())
                    {
                        sign.push(tmp_stack.top());
                        tmp_stack.pop();
                    }
                }
                
            }
        }
        print_stack(sign);
        std::cout << "\t";
        print_stack(input);
        std::cout << "\t";
        if(table[find1(sign.top())][find(input.top())] != "" && sign.top() != input.top())
            std::cout << "\t" << sign.top() << " -> " << table[find1(sign.top())][find(input.top())];
        std::cout << endl;
        if(x == "#")
        break;
    }
}

int main()
{
    ofstream test("D:\\table.txt");
    init();
    divide();
    get_first();
    get_follow();
    creat_table();
    predict();
    return 0;
}