#include <stdio.h>


int main(){

    int dig;

    while(scanf("%d",&dig) != EOF){
        printf("%d\n",dig);
        if(dig == 0)
            break;
    }

    return 0;
}