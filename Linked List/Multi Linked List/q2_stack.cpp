#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

struct mlnode{
    char c;
    struct mlnode *ml = NULL;
    struct mlnode *next = NULL;
};

typedef struct mlnode* mlptr;

int print(mlptr ml, int i, string str){
    mlptr head = ml;
    start:
    ml = head;

    while(ml != NULL){
        if(ml->tag == 1){
            str = str + ml->data.c + " ";
            if(ml->next == NULL){
            }
        }
        else if(ml->tag == 2){
            print(ml->data.ml, i, str);
        }
        ml = ml->next;
    }
    cout << str <<  endl;
}



string rest(string str){
    int cntr = 0;
    string ans = "";
    for(int i = 0 ; i < str.length() ; i++){
        if(str[i] == '('){
            cntr++;
        }
        else if(str[i] == ')'){
            cntr--;
        }
        ans = ans + str[i];
        if(cntr == 0)
            return ans;
    }
}

mlptr create(string str, mlptr ml){
    mlptr t =NULL, head = NULL;
    int cntr = 0
    for(int i = 0 ; i < str.length() ; i++){
        t = new(mlnode);
        if(ml == NULL){
            if(str[i] == '('){
                if(cntr == 0)
                    cntr++;
                else{
                    t->tag = 2;
                    string temp = "";
                    int nt = i;
                    for(int nt = i ; nt < str.length() ; nt++)
                        temp = temp + str[nt];
                    string cur = rest(temp);
                    t->data.ml = create(cur, t->data.ml);
                    i += cur.length();
                    t->next = NULL;
                    ml = t;
                }    
            }
            if('a' <= str[i] && 'z' >= str[i]){
                t->tag =1;
                t->data.c = str[i];
                t->next = NULL;
                ml = t;
                head = ml;
            }
        }
        else{
            if(str[i] == '('){
                t->tag = 2;
                string temp = "";
                int nt = i;
                for(int nt = i ; nt < str.length() ; nt++)
                    temp = temp + str[nt];
                string cur = rest(temp);
                t->data.ml = create(cur, t->data.ml);
                i += cur.length();
                t->next = NULL;
                ml->next = t;
                ml = ml->next;
            }
            else if('a' <= str[i] && 'z' >= str[i]){
                t->tag =1;
                t->data.c = str[i];
                t->next = NULL;
                ml->next = t;
                ml = ml->next;
            }
            else if(str[i] == ')'){
                free(t);
                return head;
            }
        }
    }
}



int main()
{
    mlptr ml = NULL;
    string str;
    cout << "Expression: ";
    cin >> str;
    ml = create(str, ml);
    string str2 = "";
    int i = 0;
    print(ml, i, str2);
    return 0;
}