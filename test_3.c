#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct disjointset{
    int parent;
}disjointset;

void makeset(int a, disjointset *shop){
    shop[a].parent = a;
    return;
}

int findset(int a, disjointset *shop, int *check_set){
    if(check_set[a] == 0){
        makeset(a, shop);
        check_set[a] = 1;
    }
    int i = a;
    int tmp = i;
    while(shop[i].parent != i){
        i = shop[i].parent;
    }
    while(shop[tmp].parent != i){
        int x = shop[tmp].parent;
        shop[tmp].parent = i;
        tmp = x;
    }
    return i;
}

void group(int a, int b, disjointset *shop, int *check_set){
    int A = findset(a, shop, check_set), B = findset(b, shop, check_set);
    if(A != B){
        shop[B].parent = A;
    }
    return;
}

int sameset(int a, int b, disjointset *shop, int *check_set){
    int A = findset(a, shop, check_set), B = findset(b, shop, check_set);
    if(A == B){
        return 1;
    }
    else{
        return 0;
    }
}


int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    disjointset *shop = malloc(sizeof(disjointset) * (n+1));
    int *check_set = malloc(sizeof(int) * (n+1));
    for(int i = 1; i <= n; i++){
        check_set[i] = 0;
    }
    int total_shops = n;

    for(int i = 1; i <= m; i++){
        char operation[10];
        scanf("%s", operation);
        if(strcmp(operation, "merge") == 0){
            int a, b;
            scanf("%d%d", &a, &b);
            if(!sameset(a, b, shop, check_set)){
                total_shops--;
                group(a, b, shop, check_set);
            }
        }
        else if(strcmp(operation, "query") == 0){
            printf("%d\n", total_shops);
        }
    }

    return 0;
}