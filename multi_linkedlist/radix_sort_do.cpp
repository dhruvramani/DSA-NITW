#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

struct dnode{
    int data;
    struct dnode *left = NULL;
    struct dnode *nextup = NULL;
    struct dnode *right = NULL;
};

typedef struct dnode* dptr;

dptr addend(dptr l, int type, int k){
    dptr T, L;
    L = l;
    if(L == NULL){
        L = new(dnode);
        (L->data) = k;
        L->nextup = NULL;
        (L->right) = NULL;
        return L;
    }
    else{
        if(type == 1){
            while(L->right != NULL)
                L =L->right;
        }
        else{
            while(L->nextup != NULL)
                L =L->nextup;
        }
        T = new(dnode);
        T->data = k;
        T->right = NULL;
        T->nextup = NULL;
        if(type == 1)
            L->right = T;
        else
            L->nextup = T;
        return L;
    }
}

dptr addfront(dptr l,int type, int k){
    dptr T, L;
    L = l;

    T = new(dnode);
    T->data = k;

    if(L == NULL){
        (T->right) = NULL;
        (T->nextup) = NULL;
        return T;
    }
    else{
        if(type == 1){
            T->right = L;
            T->nextup = NULL;
            L = T;
            return L;
        }
        else{
            T->nextup = L;
            T->right = NULL;
            L = T;
            return L;
        }
    }
}

int srch(dptr l, int type,int k){
    dptr L;
    L= l;
    while(L != NULL){
        if(L->data == k){
            return 1;
        }
        else{
            if(type == 1)
                L = L->right;
            else 
                L = L->nextup;
        }
    }
    return 0;
}


dptr dlt(dptr l, int type, int k){
    dptr T, L;
    L = l;
    if(L != NULL){
        if(L->data == k){
            T = L;
            if(type == 1)
                L = L->right;
            else
                L = L->nextup;
            free(T);
            return L;
        }
        else{
            if(type == 1){
                while(L->right->right != NULL){
                    if(L->right->data == k){
                        T = L->right;
                        L->right = L->right->right;
                        free(T);
                        return l;
                    }
                    else{
                        L = L->right;
                    }
                }
        
            }
            else{
                while(L->nextup->nextup != NULL){
                    if(L->nextup->data == k){
                        T = L->nextup;
                        L->nextup = L->nextup->nextup;
                        free(T);
                        return l;
                    }
                    else{
                        L = L->nextup;
                    }
                }
        
            }
        }
    }
    else{
        T = NULL;
        return T;
    }
}


dptr addafterup(dptr l, int num, int k){
    dptr T, L;
    L = l;
    int flag = 0;
    if(L == NULL){
        cout << "No node with required value";
        T = NULL;
        return T;
    }
    else{
        do{
            if(L->data == num){
                T = new(dnode);
                T->data = k;
                T->nextup = L->nextup;
                L->nextup = T;
                return L;
            }
            else{
                L = L->nextup;
            }
        }while(L->nextup != NULL);

        T = NULL;
        return L->nextup;
    }
}

dptr addaftersd(dptr l, int num, int k){
    dptr T, L;
    L = l;
    int flag = 0;
    if(L == NULL){
        cout << "No node with required value";
        T = NULL;
        return T;
    }
    else{
        do{
            if(L->data == num){
                T = new(dnode);
                T->data = k;
                T->right = L->right;
                L->right = T;
                return L;
            }
            else{
                L = L->right;
            }
        }while(L->right != NULL);

        T = NULL;
        return L->right;
    }
}


void print(dptr head, int type){
    for(int i = 0 ; head != NULL ; i++){
        cout << head->data;
        
        type == 1 ? head = head->right : head = head->nextup ;
    }
}

dptr getPtrAt(dptr l, int  type, int i){
    while(l != NULL && i--){
        if(type == 1)
            l = l->right;
        else
            l = l->nextup;
    }
    return l;
}


int RdxSrt(int base, int num[], int sz){
    dptr l1 = NULL, l2 = NULL, l3 = NULL;
    int flag = 0, temp[2], tmpcntr = 0,  pw =1, counter = 0;
    temp[0] = 0; temp[1] = 0;
    for(int i = base-1 ; i >= 0 ; i--)
        l1 = addfront(l1, 1, i);
        
    for(int i = 0 ; flag != sz ; i++){
        flag = 0;
        
        //elements into lls
        for(int j = 0 ; j < sz ; j++){
            temp[tmpcntr] = (num[j] % (int)pow(10.0,pw)) / pow(10.0,pw-1);
            counter += abs(temp[0] - temp[1]);
            if(temp[tmpcntr] == 0)
                flag++;
            
            l2 = getPtrAt(l1, 1, temp[tmpcntr]);
            addend(l2, 2, num[j]);
            tmpcntr = (tmpcntr+1)%2;
        }
        pw++;
        
        //elements back into array
        int cntr = 0, lsz;
        for(int j = 0 ; j < base ; j++){
            l2 = getPtrAt(l1, 1, j);
            lsz = 0;
            for(int k = 0 ; ; k++){
                l3 = getPtrAt(l2, 2, k+1);
                lsz++;
                if(l3 == NULL){
                    lsz--;
                    break;
                }
                
                num[cntr++] = l3->data;
//                cout << num[cntr-1] << " ";
            }
//            cout << endl;
            
            /*
            for(int k = lsz ; k > 0 ; k--){
                l3 = getPtrAt(l2, 2, k);
                free(l3);
            }
            */
            l2->nextup = NULL;
        }    
        
        /*debugging
        for(int cntrrd = 0 ; cntrrd < sz ; cntrrd++)
            cout << num[cntrrd] << " ";
        cout << endl;
        */
    }
    return counter;
}


int main(){
    int base;
    cout << "Enter base: " ;
    cin >> base;
    
    fstream if2("input2.txt");
    int sz = 0;
    int arr[100];
    
    for(int i = 0 ; !if2.eof(); i++){
        if2 >> arr[i];
        sz++;
    }
    
    cout << "Counter: " << RdxSrt(base, arr, sz) << endl;
    
    for(int i = 0 ; i < sz ; i++){
        cout <<  arr[i] << endl;
    }
    return 0;
}