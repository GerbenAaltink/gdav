/*
 * =====================================================================================
 *
 *       Filename:  return_var.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07-12-21 19:58:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char * return_var(int d){
    static char result[1024];
    sprintf(result, "%d",d);
    return result;
}



int main() {
    char first[100];
    strcpy(first, return_var(10));
    char * next = return_var(20);
    printf("%s : %s\n", first, next);

}
