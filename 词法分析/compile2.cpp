#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;
//  key words
char key_words[11][100] = {"while", "for", "continue", "break", "if", "else",
                    "float", "int", "char", "void", "return"};

char token[200];
int is_float = 0;

bool is_num(char x) //数字
{
    if(x >= '0' && x <= '9')
        return true;
    return false;
}

bool is_letter(char x) //字母
{
    if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'z'))
        return true;
    return false;
}

int is_key(char x[]) //关键字
{
    for(int i = 0; i < 11; ++ i)
    {
        if(!strcmp(x, key_words[i]))
            return i + 1;
    }
    return -1;
}

void scan(int &flag, int &p, char s[]) //遍历
{
    token[200] = {0};
    int cnt = 0;
    if(s[p] == ' ')
        p ++;
    
    if(is_letter(s[p]))
    {
        while(is_num(s[p]) || is_letter(s[p]))
        {
            token[cnt ++] = s[p];
            p ++;
        }
        token[cnt] = '\0';
        flag = is_key(token);
        if(flag == -1)
            flag = 41;  //  41为标识符
    }
    else if(is_num(s[p]))
    {
        while(is_num(s[p]))
        {   
            if(s[p + 1] == '.'){
                is_float = 1;
                token[cnt ++] = s[p];
                token[cnt ++] = '.';
                p += 2;
            }
            else{
            token[cnt ++] = s[p];
            p ++;
        }
        }
        if(is_float == 0){
        token[cnt] = '\0';
        flag = 42; //   42为整数
    }
        if(is_float == 1){
            token[cnt] = '\0';
            flag = 43; //43为浮点数
            is_float = 0;
        }
    }
    else
    {
        switch(s[p])
        {
            case '(' : flag = 33; token[0] = s[p]; token[1]='\0'; break;
            case ')' : flag = 34; token[0] = s[p]; token[1]='\0'; break;
            case '{' : flag = 35; token[0] = s[p]; token[1]='\0'; break;
            case '}' : flag = 36; token[0] = s[p]; token[1]='\0'; break;
            case ';' : flag = 37; token[0] = s[p]; token[1]='\0'; break;
            case ',' : flag = 38; token[0] = s[p]; token[1]='\0'; break;
            case '[' : flag = 39; token[0] = s[p]; token[1]='\0'; break;
            case ']' : flag = 40; token[0] = s[p]; token[1]='\0'; break;
        }
        if(s[p] == '+')
        {
            token[cnt ++] = s[p];
            if(s[p + 1] == '+')
            {
                token[cnt ++] = s[++ p];
                flag = 24; //   ++
            }
            else if(s[p + 1] == '=')
            {
                token[cnt ++] = s[++ p];
                flag = 28; //   +=
            }
            else
                flag = 12; //   +
            token[cnt] = '\0';
        }

        else if(s[p] == '-')
        {
            token[cnt ++] = s[p];
            if(s[p + 1] == '-')
            {
                token[cnt ++] = s[++ p];
                flag = 25; //   --
            }
            else if(s[p + 1] == '=')
            {
                token[cnt ++] = s[++ p];
                flag = 29; //   -=
            }
            else
                flag = 13; //   -
            token[cnt] = '\0';
        }

        else if(s[p] == '*')
        {
            token[cnt ++] = s[p];
            if(s[p + 1] == '=')
            {
                token[cnt ++] = s[++ p];
                flag = 30; //   *=
            }
            else
                flag = 14; //   *
            token[cnt] = '\0';
        }        

        else if(s[p] == '/')
        {
            token[cnt ++] = s[p];
            if(s[p + 1] == '=')
            {
                token[cnt ++] = s[++ p];
                flag = 31; //   /=
            }
            else
                flag = 15; //   /
            token[cnt] = '\0';
        } 

        else if(s[p] == '%')
        {
            token[cnt ++] = s[p];
            if(s[p + 1] == '=')
            {
                token[cnt ++] = s[++ p];
                flag = 32; //   %=
            }
            else
                flag = 16; //   %
            token[cnt] = '\0';
        }

        else if(s[p] == '=')
        {
            token[cnt ++] = s[p];
            if(s[p + 1] == '=')
            {
                token[cnt ++] = s[++ p];
                flag = 20; //   ==
            }
            else
                flag = 17; //   =
            token[cnt] = '\0';
        }

        else if(s[p] == '>')
        {
            token[cnt ++] = s[p];
            if(s[p + 1] == '=')
            {
                token[cnt ++] = s[++ p];
                flag = 22; //   >=
            }
            else
                flag = 18; //   >
            token[cnt] = '\0';
        }

        else if(s[p] == '<')
        {
            token[cnt ++] = s[p];
            if(s[p + 1] == '=')
            {
                token[cnt ++] = s[++ p];
                flag = 21; //   <=
            }
            else
                flag = 19; //   <
            token[cnt] = '\0';
        }

        if(s[p] == '!' && s[p + 1] == '=')
        {
            token[cnt ++] = s[p];
            token[cnt ++] = s[++ p];
            flag = 23; //   !=
            token[cnt] = '\0';
        }
        if(s[p] == '&' && s[p + 1] == '&')
        {
            token[cnt ++] = s[p];
            token[cnt ++] = s[++ p];
            flag = 26; //   &&
            token[cnt] = '\0';
        }
        if(s[p] == '|' && s[p + 1] == '|')
        {
            token[cnt ++] = s[p];
            token[cnt ++] = s[++ p];
            flag = 27; //   ||
            token[cnt] = '\0';
        }
        if(s[p] == '\'' && s[p + 2] == '\'')
        {
            token[cnt ++] = 'C';
            token[cnt ++] = 'H';
            token[cnt ++] = 'A';
            token[cnt ++] = 'R';
            flag = 44;
            token[cnt] = '\0';
            p += 2;
        }         
        p ++;

    }
}
//输出的是token序列
int main()
{
    char s[100] = {0};
    freopen("D:\\test.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ofstream fout("D:\\token.txt");
    while(cin>>s)
    {
        int p = 0;
        int flag;
        int x = strlen(s);
        while(p < x)    //循环条件 ,p还未指到字符串最后  
        {
            scan(flag,p,s);
            /* 输出token序列 */
            if(flag == 44)
                fout << "CHAR" << " ";
            else if(flag == 43)
                fout << "FLOAT" << " ";
            else if(flag == 42)
                fout << "INT" << " ";
            else if(flag == 41)
                fout << "IDN" << " ";
            else 
                fout << token << " ";

            // /* 输出符号表 */   
            // if(flag == 43)  //  浮点数
            //     cout << token << "  " << "<FLOAT," << token << ">" << endl;
            // else if(flag == 42)  //  常数
            //     cout << token << "  " << "<CONST," << token << ">" << endl;
            // else if(flag >= 1 && flag <= 11)    // 关键字
            // {
            //     cout << token << " ";
            //     for(int i = 0; i < strlen(token); ++ i)
            //         token[i] -= 'a' - 'A';
            //     cout << "<" << token << ",_>" << endl;
            // }
            // else if(flag >= 33 && flag <= 40)   // 界符
            //     cout << token << "  " << "<SE,_>" << endl;
            // else if(flag >= 12 && flag <= 32)   // 运算符
            //     cout << token << "  " << "<OP,_>" << endl;
            // else if(flag == 41) // 标识符
            //     cout << token << "  " << "<IDN," << token << ">" << endl;
        }
    }
    return 0;
}