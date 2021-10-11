#ifndef MY_BLOCKCHAIN_H
#define MY_BLOCKCHAIN_H

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>


struct blocks {
    char *bid;
    struct blocks *next;
};

struct list_of_blocks {
    struct blocks *head;
    struct blocks *tail;
};

struct nodes {
    int nid;
    int bidlist_size;
    struct list_of_blocks *bidlist;
    bool sync;
    struct nodes *next;
};


//my_readline.c
#define  READLINE_READ_SIZE 11
char* my_readline(int fd);
char* my_string(char* string, char* BUFFER);

// my_helper.c
char* my_strchr(char* param_1, int c);
char* my_strcpy(char* param_1, char* param_2);
char* my_strncpy(char* param_1, char* param_2, int i);
char* my_strcat(char* param_1, char* param_2);
int   my_strlen(const char *str);
int   my_write_string(const int fd, const char *str);
bool  my_strcmp(const char *param_1, const char *param_2);
bool  my_strncmp(const char *param_1, const char *param_2, const int index, const int len);
char  *my_strcpy1(const char *str);
char  *my_trunc_string(const char *str, const int index);
int   my_atoi(const char *str, const int index);
int   my_atoi2(const char *str);
int   my_write_integer(const int fd, const int param);

//my_blockchain.c
int read_command(const int fd, char *buff);
int blockchain_size(struct nodes *node);
int prompt_action(const int fd, struct nodes **masternode);
int display_prompt(const bool synced, const int node_size);
void my_blockchain(struct nodes **masternode);
void read_backup_file(struct nodes **masternode, const char *backup_file);
bool is_synced(struct nodes *node);

//add.c
struct blocks *create_block(char *bid);
struct nodes *create_node(int nid);
void add_block(const char *buff, struct nodes **masternode);
void add_node(const char *buff, struct nodes **masternode);
int add_new_block(struct nodes *node, int nid, char *bid);
void add_new_node(struct nodes *node, int nid);

//rm.c
void rm_block(const char *buff, struct nodes **masternode);
void rm_node(const char *buff, struct nodes **masternode);
void rm_found_block(struct nodes *node, char *bid);
struct nodes *rm_found_node(struct nodes *masternode, int nid);
bool find_block(struct nodes *node, char *bid); 
void free_blockchain_node(struct nodes *node);
void rm_all_nodes(struct nodes *masternode);

//other.c
struct nodes *find_node(struct nodes *node, int nid);
void ls(struct nodes *node, const bool is_l);
bool ls_l(const char *buff);
void sync_blockchain(struct nodes *node);

char **find_blocks_to_sync(struct nodes *node, int *block_numb);
//char **find_blocks_to_sync(struct nodes *node, int *blocks_to_sync)
void quit_and_save(struct nodes *masternode, const char *save_file);



#endif