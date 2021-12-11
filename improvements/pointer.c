#include <stdio.h>
#include <stdlib.h>

int main(){
    char * pref = "ABCDE";
    char * data = "123456789";
    char * pdata = data;
    pdata += 3;
    printf("%s\n", data);
    printf("%s\n", pdata);
    pdata[2] = 0;

    printf("%s\n", data);
    printf("%s\n", pdata);

    pdata -= 3;

    printf("%s\n", data);
    printf("%s\n", pdata);

    pdata -= 3;

    printf("%s\n", data);
    printf("'%s'\n", pdata);

    *pdata = 5;
    
     printf("%s\n", data);
    printf("'%s'\n", pdata);

    char * t = malloc(1);
    int max = (int *)t;
   //max = t*;
    printf("%d\n",max); 
  
    for(int i = 0; i < max; i++){
   // int i = 0;    
        *t = i;
       printf("%s", t);
    } 

    return 0;

}
