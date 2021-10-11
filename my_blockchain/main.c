/*
*
*/

#include "my_blockchain.h"

/*
*
*/

int main(int argc, const char *argv[]){
    struct nodes **masternode = (struct nodes **)malloc(sizeof(struct nodes *));
    *masternode = NULL;
    const char *backup_file;
    const char *save_file;

    if (argc > 1) {
        backup_file = argv[1];	
    } else  {
        backup_file = NULL;
    }
    
    if (argc > 2){
        save_file = argv[2];	
    } else  {
        save_file = NULL;
    }

    read_backup_file(masternode, backup_file); 
    my_blockchain(masternode);   
    quit_and_save(*masternode, save_file);
    
    free_blockchain_node(*masternode);   
    free(masternode);

    return 0;
}


void read_backup_file(struct nodes **masternode, const char *backup_file)
{
    if (backup_file == NULL)
    {
        my_write_string(1, "No backup is provided\n");
        return;
    }
    const int fd = open(backup_file, O_RDONLY);
  
    bool next_node = false;
    bool next_block = false;
    int current_nid = 0;

    char *str = NULL;
    while ((str = my_readline(fd)) != NULL)
    {
        if (my_strcmp(str, "nid") == true)
        {
            next_node = true;
            next_block = false;
            free(str);
            continue;
        }

        if (my_strcmp(str, "bid") == true)
        {
            next_node = false;
            next_block = true;
            free(str);
            continue;
        }
       
        if ((next_node == true) && (next_block == false))
        {
            const int nid = my_atoi2(str);
            current_nid = nid;

            if (*masternode == NULL)
            {
                *masternode = create_node(nid);
            }
            else
            {
                add_new_node(*masternode, nid);
            }
        }

        if ((next_node == false) && (next_block == true))
        {          
            add_new_block(*masternode, current_nid, my_strcpy1(str));
        }
        
        free(str);
    }
    close(fd);
}


bool is_synced(struct nodes *node)
{
    int count_blocks_to_sync = 0;
    struct nodes *current = node;
    struct blocks *current_head;
    char **bid_array = find_blocks_to_sync(current, &count_blocks_to_sync);

    const int my_blockchain_size = blockchain_size(current);
    if (my_blockchain_size < 2)
    {
        for (int i = 0; i < count_blocks_to_sync; ++i)
        {
            free(bid_array[i]);
        }
        free(bid_array);
        return false;
    }
    if (count_blocks_to_sync < 1)
    {
        for (int i = 0; i < count_blocks_to_sync; ++i)
        {
            free(bid_array[i]);
        }
        free(bid_array);
        return false;
    }
   
    for (int i = 0; i < count_blocks_to_sync; ++i)
    {
        current = node;
        bool block_found = false;
        while (current != NULL)
        {
            block_found = false;
            current_head = current->bidlist->head;
            while (current_head != NULL)
            {
                if (my_strcmp(bid_array[i], current_head->bid) == true)
                {
                    block_found = true;
                    break;
                }
                current_head = current_head->next;
            }

            if (block_found == false)
            {
                for (int i = 0; i < count_blocks_to_sync; ++i)
                {
                    free(bid_array[i]);
                }
                free(bid_array);
                return false;
            }

            current = current->next;
        }
    }

    for (int i = 0; i < count_blocks_to_sync; ++i)
    {
        free(bid_array[i]);
    }
    free(bid_array);

    return true;
}