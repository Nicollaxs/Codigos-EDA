#include <stdio.h>

int main(){

    int a = 5;
    int *p = &a;
    int **pp = &p;

    printf("%d \n",*pp);

}