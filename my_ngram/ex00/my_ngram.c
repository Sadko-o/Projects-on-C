#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    char current = ' ';
    int count = 0;
    while(current){
        if(current == '"') current++;
        for(int i = 1; i < argc; i++){
            for(int j =0 ; argv[i][j] != '\0'; j++){
                if(current == argv[i][j]) count++;
            }
        }
        if(count != 0){
            printf("%c:%d\n", current, count);
            count =0;
        }   
        current++;
    }
    return 0;
}