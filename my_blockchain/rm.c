/*
*
*/

#include "my_blockchain.h"

/*
*
*/


void rm_block(const char *buff, struct nodes **masternode) {
    char *bid = my_trunc_string(buff, 9);
    if (bid == NULL) {
        my_write_string(1, "Command not found\n");
    } else {
        const int bid_len = my_strlen(bid);
        const int str_len = my_strlen(buff) - 1;

        if ((bid_len + 9) != str_len)
        {
            my_write_string(1, "Command not found\n");
        }
        else if (find_block(*masternode, bid) == true)
        {
            rm_found_block(*masternode, bid);
        }
        else
        {
            my_write_string(1, "Block doesn't exist\n");
        }
        free(bid);
    }
}


void rm_node(const char *buff, struct nodes **masternode) {
    const int nid = my_atoi(buff, 8);
    
    if (nid < -1) {
        my_write_string(1, "Command not found\n");
    } else if (nid == -1) {
        rm_all_nodes(*masternode);
        *masternode = NULL;
    } else {
        struct nodes *nid_is_found = find_node(*masternode, nid);
        if (nid_is_found != NULL)
        {

            *masternode = rm_found_node(*masternode, nid);
        }
        else
        {
            my_write_string(1, "Node doesn't exist\n");
        }
    }
}

void rm_found_block(struct nodes *node, char *bid) {
    struct nodes *current = node;
    struct blocks *block_rm = NULL;
    struct blocks *current_block;
    struct blocks *previous;
    while (current != NULL)
    {
        int bidlist_size = current->bidlist_size;
        previous = current->bidlist->head;
        current_block = current->bidlist->head;
        block_rm = NULL;

        while (current_block != NULL)
        {
            if (my_strcmp(current_block->bid, bid) == true)
            {
                block_rm = current_block;
                if (bidlist_size == 1)
                {
                    current->bidlist->head = NULL;
                    current->bidlist_size = 0;
                }
                else if (previous == current_block)
                {
                    current->bidlist->head = current_block->next;
                    current->bidlist_size--;
                }
                else
                {
                    previous->next = current_block->next;
                    current->bidlist_size--;
                }
                break;
            }
            previous = current_block;
            current_block = current_block->next;
        }

        if (block_rm != NULL)
        {
            free(block_rm->bid);
            free(block_rm);
        }

        current = current->next;
    }
}

struct nodes *rm_found_node(struct nodes *masternode, int nid) {
    struct nodes *head = masternode;
    struct nodes *current = masternode;
    struct nodes *previous = current;
    struct nodes *node_rm = NULL;
    struct blocks *tmp_block;
    while (current != NULL)
    {
        if (nid == current->nid)
        {
            node_rm = current;

            if (current == masternode)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            break;
        }
        previous = current;
        current = current->next;
    }

    if (node_rm != NULL)
    {
        while (node_rm->bidlist->head != NULL)
        {
            tmp_block = node_rm->bidlist->head;
            node_rm->bidlist->head = node_rm->bidlist->head->next;
            free(tmp_block->bid);
            free(tmp_block);
        }
        free(node_rm->bidlist);
        free(node_rm);
    }
    return head;
}

bool find_block(struct nodes *node, char *bid) {
    struct nodes *current = node;
    struct blocks *current_block;
    while (current != NULL)
    {
        current_block = current->bidlist->head;
        while (current_block != NULL)
        {
            if (my_strcmp(current_block->bid, bid) == true)
            {
                return true;
            }
            current_block = current_block->next;
        }
        current = current->next;
    }
    return false;
}

void free_blockchain_node(struct nodes *node) {
    struct blocks *tmp_bid;
    struct nodes *tmp;
    struct nodes *current = node;
    while (current != NULL)
    {
        tmp = current;
        while (tmp->bidlist->head != NULL)
        {
            tmp_bid = tmp->bidlist->head;
            tmp->bidlist->head = tmp->bidlist->head->next;
            free(tmp_bid->bid);
            free(tmp_bid);
        }
        current = current->next;
        free(tmp->bidlist);
        free(tmp);
    }
}

void rm_all_nodes(struct nodes *masternode){
    free_blockchain_node(masternode);
}