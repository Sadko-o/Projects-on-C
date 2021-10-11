/*
*
*/

#include "my_blockchain.h"

/*
*
*/

char* my_strchr(char* param_1, int c) {
    while (*param_1) {
        if (*param_1 == c) return param_1;
        param_1++;
    }

    return NULL;
}

char* my_strcpy(char* param_1, char* param_2) {
    if (!param_1) return NULL;

    while (*param_2 != '\0') {
        *param_1 = *param_2;
        param_1++;
        param_2++;
    }

    *param_1 = '\0';

    return param_1;
}

char* my_strncpy(char* param_1, char* param_2, int i) {
    if (!param_1) return NULL;

    while (i > 0) {
        if (*param_2 == '\0') break;
        *param_1 = *param_2;
        param_1++;
        param_2++;
        i--;
    }

    *param_1 = '\0';

    return param_1;
}

char* my_strcat(char* param_1, char* param_2) {
    while (*param_1 != '\0') {
        param_1++;
    }

    while (*param_2 != '\0') {
        *param_1 = *param_2;
        param_1++;
        param_2++;
    }

    *param_1 = '\0';

    return param_1;
}

int my_strlen(const char *str)
{
    int count = 0;
    while (str[count] != 0) 
    {
        count++;
    }
    return count;
}

int my_write_string(const int fd, const char *str)
{
    return write(fd, str, my_strlen(str));
}

bool my_strcmp(const char *param_1, const char *param_2)
{
    const int len1 = my_strlen(param_1);
    const int len2 = my_strlen(param_2);

    if (len1 != len2)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < len1; ++i)
        {
            if (param_1[i] != param_2[i])
            {
                return false;
            }
        }
        return true;
    }
}

bool my_strncmp(const char *param_1, const char *param_2, const int index, const int len)
{
    const int len1 = my_strlen(param_1);
    const int len2 = my_strlen(param_2);

    if (len < 0)
    {
        return false;
    }
    else if (len1 < index + len)
    {
        return false;
    }
    else if (len2 < len)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < len; ++i)
        {
            if (param_1[index + i] != param_2[i])
            {
                return false;
            }
        }
        return true;
    }
}

char *my_strcpy1(const char *str)
{
    const int len = my_strlen(str);
    char *str_copy = (char *)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; ++i)
    {
        str_copy[i] = str[i];
    }
    str_copy[len] = 0;
    return str_copy;
}

char *my_trunc_string(const char *str, const int index)
{
    const int len = my_strlen(str) - 1;

    char *new_str = NULL;
    int new_len = 0;
    if (len < index)
    {
        return new_str;
    }
    else
    {

        for (int i = index; i < len; ++i)
        {
            if (str[i] != ' ')
            {
                ++new_len;
            }
            else
            {
                break;
            }
        }
        if (new_len == 0)
        {
            return new_str;
        }
        else
        {
            new_str = (char *)malloc((new_len + 1) * sizeof(char));
        }
        for (int i = index; i < new_len + index; ++i)
        {
            new_str[i - index] = str[i];
        }
        new_str[new_len] = 0;
        return new_str;
    }
}

int my_atoi(const char *str, const int index)
{
    const int str_len = my_strlen(str) - 1;

    if ((str_len - index) == 1 && str[index] == '*')
    {
        return -1;
    }
    else if (str_len <= index)
    {
        return -2;
    }
    else
    { 
        for (int i = index; i < str_len; ++i)
        {
            if (str[i] < 48 || str[i] > 57)
            {
                return -2;
            }
        }

        int int_from_str = 0;
        for (int i = index; i < str_len; ++i)
        {
            int len = str_len - i;
            int pow_10 = 1;
            while (len > 1)
            {
                pow_10 *= 10;
                --len;
            }

            int_from_str += (str[i] - 48) * pow_10;
        }
        return int_from_str;
    }
}

int my_atoi2(const char *str)
{
    const int str_len = my_strlen(str);

    if (str_len == 1 && str[0] == '*')
    {
        return -1;
    }
    else if (str_len <= 0)
    {
        return -2;
    }
    else
    {
        for (int i = 0; i < str_len; ++i)
        {
            if (str[i] < 48 || str[i] > 57)
            {
                return -2;
            }
        }

        int int_from_str = 0;
        for (int i = 0; i < str_len; ++i)
        {
            int len = str_len - i;
            int pow_10 = 1;
            while (len > 1)
            {
                pow_10 *= 10;
                --len;
            }

            int_from_str += (str[i] - 48) * pow_10;
        }
        return int_from_str;
    }
}

int my_write_integer(const int fd, const int param)
{
    if (param < 0)
    {
        return -1;
    }
    else if (param == 0)
    {
        const int digit = 48;
        return write(fd, &digit, 1);
    }
    else
    {
        int chars_printed = 0;
        int len = 1;
        int tmp = param;
        tmp /= 10;
        while (tmp > 0)
        {
            ++len;
            tmp /= 10;
        }

        int digit = 48;
        while (len > 0)
        {
            int pow_10 = 1;
            for (int j = 1; j < len; ++j)
            {
                pow_10 *= 10;
            }

            digit = (param / pow_10) % 10 + 48;
            chars_printed += write(fd, &digit, 1);
            --len;
        }
        return chars_printed;
    }
}