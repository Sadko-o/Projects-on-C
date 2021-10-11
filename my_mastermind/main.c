#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
   
int check_input(char input[]){
    int val = atoi(input); 
    if( val == 0 && (input[0] != 0)) { //if input was not numbers
        return 1;
    }else{
        int digit=0;
        int out_of_range=0;
        for(int i=0; i<4; i++){ //checking if input contains 8 or 9
            digit=val%10;
            val=val/10;
            if(digit==9 || digit==8){
                out_of_range++;
                break; 
            }
        }   
        return out_of_range; 
    }
}


int len(char input[]){
    int a=0;
    while(input[a]!='\n'){ 
        a++;
    }
    return a;
}
  

void read_input(char input[]){
    read(0, input, 5); 
    input[5]='\0';
}

int check_places(char secret_code[], char input[]){
            int wellplaced=0, misplaced=0, input_left_size=0, secret_left_size=0;
            char input_left[4], secret_left[4];
            for (int i=0; i<4; i++){ 
                if(secret_code[i]==input[i]){    
                wellplaced++;
                }
                else{     
                    input_left[input_left_size++] = input[i];
                    secret_left[secret_left_size++] = secret_code[i];
                }
            }
            
            for (int i=0; i<input_left_size; i++){ 
                for (int j=0; j<secret_left_size; j++){
                    if(secret_left[i]==input_left[j]){
                        misplaced++; secret_left_size--;
                        secret_left[j]=secret_left[secret_left_size];
                        break;
                    }
                }
            }
            
            if(wellplaced==4){  
                printf("Congratz! You did it!\n"); 
                return 1;
            }else{
                printf("Wellplaced pieces: %d\n", wellplaced);
                printf("Misplaced pieces: %d\n", misplaced);
                return 0;
            }
}
 
  
int main(int ac, char** av) {
    char secret_code[4]; 
    int digits = 4;
    if(ac > 2 && av[1][0] == '-' && av[1][1]=='c'){
        for(int i=0; i<4; i++){
           secret_code[i]=av[2][i]; 
        }
    } else {
        srand(time(NULL));
        for(int i = 0 ; i < digits ; i++ ) {
           int random_number = (rand() % 8); 
           secret_code[i] = (random_number+'0'); 
        }
    }
    secret_code[4]='\0';   
    //To print out secret code
    //printf("%s\n\n", secret_code);
    
    printf("Will you find the secret code?\n");
      
    for(int attempt = 0; attempt < 10; attempt++){
        printf("---\n");
        printf("Round %d\n", attempt);
        char input[6]={0};
        
        read_input(input);
            
        while (len(input)!=4 || check_input(input)!=0){ 
            printf("Wrong input!\n");
            read_input(input);
        } 
        if ( check_places(secret_code, input)){
            return 0;
        } 
    }
    return 0; 
}