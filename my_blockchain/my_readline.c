/*
*
*/

#include "my_blockchain.h"

/*
*
*/

char* my_string(char* string, char* BUFFER) {
    int len = 0, i = 0;
    char* tmp;
    if (BUFFER[0] == '\0') {
        return NULL;
    }

    if (BUFFER[0] == '\n' && (BUFFER[1] != '\0' || BUFFER[0] != '\0')) {
        string = malloc(2);
        my_strncpy(string, BUFFER, 1);
        string[1] = '\0';
        len = 0;
    } else {
        while (BUFFER[len] != '\n' && BUFFER[len] != '\0') {
            len++;
        }

        string = malloc(len + 1);

        if (BUFFER[len] == '\n') {
            my_strncpy(string, BUFFER, len);
        } else {
            my_strcpy(string, BUFFER);
        }

        string[len] = '\0';
    }

    tmp = malloc(strlen(BUFFER) + 1);

    for (int j = len + 1; BUFFER[j] != '\0'; j++) {
        tmp[i] = BUFFER[j];
        i++;
    }

    tmp[i] = '\0';
    my_strcpy(BUFFER, tmp);
    free(tmp);

    return string;
}

char* my_readline(int fd) {
    
    char buffer[READLINE_READ_SIZE + 1];
    char* string = NULL;
    int s = 0;
    static char BUFFER[1023];
    
    while ((s = read(fd, buffer, READLINE_READ_SIZE)) > 0) {     
        buffer[s] = '\0';
        my_strcat(BUFFER, buffer);
        if (my_strchr(BUFFER, '\n')) break;
    }
    if (s ==-1){
        return NULL;
    }
    string = my_string(string, BUFFER);

    if (string == NULL) {
        return NULL;
    }

    int len = strlen(string);

    if (s == 0 && len == 0) {
        free(string);
        BUFFER[0] = '\0';
        return NULL;      
    }

    return string;
}