/*
*
*/

#include "my_blockchain.h"

/*
*
*/ 

void sync_blockchain(struct nodes *node) {
    int count_blocks_to_sync;
    struct nodes *current = node;
    struct blocks *current_head, *block_rm;
    char **bid_array = find_blocks_to_sync(current, &count_blocks_to_sync);
    while (current != NULL)
    {
        current_head = current->bidlist->head;
        if (current_head != NULL)
        {
            while (current_head != NULL)
            {
                block_rm = current_head;
                current_head = current_head->next;
                free(block_rm->bid);
                free(block_rm);
            }
            current->bidlist->head = NULL;
            current->bidlist_size = 0;
            for (int i = 0; i < count_blocks_to_sync; i++)
            {
                add_new_block(node, current->nid, my_strcpy1(bid_array[i]));
            }
        }
        else
        {
            for (int i = 0; i < count_blocks_to_sync; i++)
            {
                add_new_block(node, current->nid, my_strcpy1(bid_array[i]));
            }
        }
        current = current->next;
    }

    for (int i = 0; i < count_blocks_to_sync; ++i)
    {
        free(bid_array[i]);
    }
    free(bid_array);
}


char **find_blocks_to_sync(struct nodes *node, int *blocks_to_sync) {
    char **blocks = malloc(100 * sizeof(char *));
    int count = 0;
    struct nodes *current = node;
    struct blocks *current_head;
    bool unique = true;
    while (current != NULL)
    {
        current_head = current->bidlist->head;
        while (current_head != NULL)
        {
            if (count == 0)
            {
                blocks[count] = my_strcpy1(current_head->bid);
                count++;
            }
            else
            {
                unique = true;
                for (int i = 0; i < count; i++)
                {
                    if (my_strcmp(blocks[i], current_head->bid) == true)
                    {
                        unique = false;
                    }
                }

                if (unique == true)
                {
                    blocks[count] = my_strcpy1(current_head->bid);
                    count++;
                }
            }
            current_head = current_head->next;
        }
        current = current->next;
    }
    *blocks_to_sync = count;
    return blocks;
}


void ls(struct nodes *node, const bool is_l) {
    struct nodes *head = node;
    while (head != NULL)
    {
        my_write_integer(1, head->nid);
        if (is_l == true)
        {
            struct blocks *current_block = head->bidlist->head;
            while (current_block != NULL)
            {
                if (current_block == head->bidlist->head)
                {
                    my_write_string(1, ": ");
                }
                my_write_string(1, current_block->bid);
                if (current_block->next != NULL)
                {
                    my_write_string(1, ", ");
                }

                current_block = current_block->next;
            }
        }

        my_write_string(1, "\n");
        head = head->next;
    }
}

bool ls_l(const char *buff) {
    if (my_strncmp(buff, "-l", 3, 2) == true)
    {
        return true;
    }
    return false;
}

struct nodes *find_node(struct nodes *node, int nid) {
    struct nodes *current = node;
    while (current)
    {
        if (nid == current->nid)
        {
            return current;
        }
        current = current->next;
    }
    return current;
}

void quit_and_save(struct nodes *masternode, const char *save_file) {
    if (save_file == NULL)
    {
        my_write_string(1, "Save backup file is not provided\n");
        return;
    }
    const int fd = open(save_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    struct nodes *current = masternode;
    struct blocks *current_block;
    while (current != NULL)
    {
        my_write_string(fd, "nid\n");
        my_write_integer(fd, current->nid);
        my_write_string(fd, "\n");
        current_block = current->bidlist->head;
        while (current_block != NULL)
        {
            if (current_block == current->bidlist->head)
            {
                my_write_string(fd, "bid\n");
            }
            my_write_string(fd, current_block->bid);
            my_write_string(fd, "\n");          
            current_block = current_block->next;
        }

        current = current->next;
    }

    close(fd);
}