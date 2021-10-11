/*
*
*/

#include "my_blockchain.h"

/*
*
*/

int blockchain_size(struct nodes *node)
{
    int count = 0;
    while (node != NULL)
    {
        ++count;
        node = node->next;
    }
    return count;
}



void my_blockchain(struct nodes **masternode)
{
    while (true)
    {
        const int size = blockchain_size(*masternode);
        const bool synced = is_synced(*masternode);
        display_prompt(synced, size);
        const int prompt_status = prompt_action(0, masternode);
        if (prompt_status == -1)
        {
            break;
        }
    }
}

int display_prompt(const bool synced, const int node_size)
{
    int chars_printed = my_write_string(1, "[");
    if (chars_printed < 0)
    {
        return -1;
    }
   
    chars_printed = (synced == true) ? my_write_string(1, "s") : my_write_string(1, "-");
    if (chars_printed < 0)
    {
        return -1;
    }
    
    chars_printed = my_write_integer(1, node_size);
    if (chars_printed < 0)
    {
        return -1;
    }
    
    chars_printed = my_write_string(1, "]> ");
    if (chars_printed < 0)
    {
        return -1;
    }
    
    return 0;
}

int prompt_action(const int fd, struct nodes **masternode)
{
    char buff[256];
    if (read_command(fd, buff) < 0)
    {
        return 0;
    }

    if (my_strncmp(buff, "add node", 0, 8) == true)
    {
        add_node(buff, masternode);
        
    }   
    else if (my_strncmp(buff, "add block", 0, 9) == true)
    {
        add_block(buff, masternode);
     
    }
    else if (my_strncmp(buff, "rm node", 0, 7) == true)
    {
        rm_node(buff, masternode);
      
    }
    else if (my_strncmp(buff, "rm block", 0, 8) == true)
    {
        rm_block(buff, masternode);
      
    }
    else if (my_strncmp(buff, "sync", 0, 4) == true)
    {
        sync_blockchain(*masternode);
      
    }
    else if (my_strncmp(buff, "ls", 0, 2) == true)
    {
        ls(*masternode, ls_l(buff));
        
    }
    else if (my_strncmp(buff, "quit", 0, 4) == true)
    {
        return -1;
        
    }
    else
    {
        my_write_string(1, "Command not found\n");
        
    }

   return 0;  
}

int read_command(const int fd, char *buff)
{
    for (int i = 0; i < 256; ++i)
    {
        buff[i] = 0;
    }
    const int chars_read = read(fd, buff, 256);
    if (chars_read < 2)
    {
        my_write_string(1, "Command not found\n");
        return -1;
    }
    return 0;
}

