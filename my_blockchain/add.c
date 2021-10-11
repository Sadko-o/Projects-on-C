/*
*
*/

#include "my_blockchain.h"

/*
*
*/

struct blocks *create_block(char *bid) {
    struct blocks *new = (struct blocks *)malloc(sizeof(struct blocks));
    new->bid = bid;
    new->next = NULL;
    return new;
}

struct nodes *create_node(int nid) {
    struct nodes *new = (struct nodes *)malloc(sizeof(struct nodes));
    new->nid = nid;
    new->bidlist_size = 0;
    new->bidlist = (struct list_of_blocks *)malloc(sizeof(struct list_of_blocks));
    new->bidlist->head = NULL;
    new->bidlist->tail = NULL;
    new->next = NULL;
    return new;
}

void add_block(const char *buff, struct nodes **masternode) {
    char *bid = my_trunc_string(buff, 10);
    if (bid == NULL)
    {
        my_write_string(1, "Command not found\n");
    }
    else
    {
        const int bid_len = my_strlen(bid);
        const int nid = my_atoi(buff, 10 + bid_len + 1);

        if (nid < -1)
        {
            my_write_string(1, "Command not found\n");
            free(bid);
        }
        else if (nid == -1)
        {
            
            struct nodes *node = *masternode;
            while (node != NULL)
            {
               
                char *bid_cpy = my_strcpy1(bid);
                const int add_block_status = add_new_block(*masternode, node->nid, bid_cpy);
                if (add_block_status == 2)
                {
                    my_write_string(1, "This block already exists\n");
                    free(bid_cpy);
                    return;
                }
                if (add_block_status == 3)
                {
                    my_write_string(1, "Node doesn't exist\n");
                    free(bid_cpy);
                    return;
                }
                
                node = node->next;
            }
            free(bid);
        }
        else
        {
            
            const int add_block_status = add_new_block(*masternode, nid, bid);
            if (add_block_status == 2)
            {
                my_write_string(1, "This block already exists\n");
                free(bid);
                return;
            }
            if (add_block_status == 3)
            {
                my_write_string(1, "Node doesn't exist\n");
                free(bid);
                return;
            }
            
        }
    }
}

void add_node(const char *buff, struct nodes **masternode) {
    const int nid = my_atoi(buff, 9);

    if (nid < 0)
    {
        my_write_string(1, "Command not found\n");
    }
    else
    {
        if (*masternode == NULL)
        {
            *masternode = create_node(nid);
        }
        else if (find_node(*masternode, nid) != NULL)
        {
            my_write_string(1, "This node already exists\n");
        }
        else
        {
            add_new_node(*masternode, nid);
        }
    }
}

int add_new_block(struct nodes *node, int nid, char *bid) {
    struct nodes *current = node;
    bool node_exist = false;

    while (current != NULL)
    {
        if (nid == current->nid)
        {
            struct blocks *new_block = create_block(bid);
            if (current->bidlist->head == NULL)
            {
                current->bidlist->head = new_block;
                current->bidlist->tail = current->bidlist->head;
                current->bidlist_size++;
            }
            else
            {
                struct blocks *current_block = current->bidlist->head;
                while (current_block != NULL)
                {
                    if (my_strcmp(current_block->bid, bid) == true)
                    {
                        free(new_block);
                        return 2;
                    }
                    else if (current_block->next == NULL)
                    {
                        break;
                    }
                    else
                    {
                        current_block = current_block->next;
                    }
                }
                current_block->next = new_block;
                current->bidlist->tail = new_block;
                current->bidlist_size++;
                
            }
            node_exist = true;
        }
        current = current->next;
    }
    if (node_exist == false)
    {   
        return 3;
    }
    else
    {   
        return 1;
    }
}

void add_new_node(struct nodes *node, int nid) {
    struct nodes *current = node;
    
    while (current != NULL && current->next != NULL)
    {
        current = current->next;
    }
    
    struct nodes *new = create_node(nid);
    current->next = new;
}