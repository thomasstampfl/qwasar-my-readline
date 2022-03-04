#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef READLINE_READ_SIZE
#define READLINE_READ_SIZE 10
#endif

#ifndef MY_DEBUG
#define MY_DEBUG 0
#endif

char* my_readline(int fd);
char* read_from_file(int fd, char* head);
char* split_str_newline(char** ptr_to_string);
char* realloc_str(char* str, size_t factor, size_t offset);
unsigned int my_strlen(const char* str);
unsigned int my_strlenchr(const char* str, int c);
char* my_strcat(char* dest, const char* src);
char* my_strdup(const char *src);
char* my_strndup(const char *src, size_t n);

char* my_readline(int fd)
{
    // one static variable is allowed
    static char* data;
    
    if(READLINE_READ_SIZE < 1)
    {
        #if MY_DEBUG == 1
            printf("READLINE_READ_SIZE must be equal or higher than 1!\n");
        #endif
        return NULL;
    }

    // there is still data in static variable
    if(data != NULL && *data != '\0')
    {
        if(my_strlenchr(data, '\n') > 0)
            return split_str_newline(&data);
    }

    // no data or no newline in buffered data -> read more data from file
    data = read_from_file(fd, data);
    return split_str_newline(&data);
}

char* read_from_file(int fd, char* str)
{
    int i = 1, bytes = 0;
    char buf[READLINE_READ_SIZE + 1] = "\0";

    if( (str = realloc_str(str, 1, 10 * READLINE_READ_SIZE)) == NULL)
        return NULL;

    while( (bytes = read(fd, buf, READLINE_READ_SIZE)) > 0)
    {
        for(int j = bytes; j < READLINE_READ_SIZE; j++)
            buf[j] = '\0';

        my_strcat(str, buf);
        if(my_strlenchr(buf, '\n') > 0U || bytes < READLINE_READ_SIZE)
            return str;

        if(i++ % 10 == 0)
            str = realloc_str(str, 10, 0);
    }

    if(bytes == -1)
    {
        #if MY_DEBUG == 1
            printf("No valid fd provided: %d!\n", fd);
        #endif

        free(str);
        str = NULL;
        return NULL;
    }

    return str;   
}

char* split_str_newline(char** ptr_to_string)
{
    char* string = *ptr_to_string;
    char* ret;
    unsigned int pos_nl = my_strlenchr(string, '\n');

    if(string == NULL || *string == '\0')
        return NULL;
    
    if(pos_nl > 0 && pos_nl <= my_strlen(string) )
    {
        string[pos_nl - 1] = '\0';
        ret = string;
        *ptr_to_string = my_strdup(&string[pos_nl]);
    }
    else
    {
        ret = string;
        *ptr_to_string = NULL;
    }

    return ret;
}

char* realloc_str(char* str, size_t factor, size_t offset)
{
    unsigned int length = factor * my_strlen(str) + offset + 1;
    char* temp = my_strndup("\0", length);

    if(temp == NULL)
        return NULL;
    else
    {
        if(str != NULL)
        {
            my_strcat(temp, str);
            free(str);
            str = temp;
        }
    }
    return temp;
}

unsigned int my_strlen(const char* str)
{
    unsigned int length = 0;

    if(str == NULL)
        return 0;

    while(*str++ != '\0')
        length++;
        
    return length;
}

unsigned int my_strlenchr(const char* str, int c)
{
    unsigned int i = 0;

    if(str == NULL)
        return 0;

    while(str[i] != '\0' && str[i] != c)
        i++;

    return (str[i] == c)? i+1 : 0; 
}

char* my_strcat(char* dest, const char* src)
{
    char* ret = dest;

    if(src == NULL)
        return dest;

    while(*dest != '\0')
        dest++;

    while(*src != '\0')
        *dest++ = *src++;

    *dest = '\0';
    return ret;
}

char* my_strncat(char* dest, const char* src, size_t n)
{
    unsigned int i = 0;
    char* ret = dest;

    while(dest[i] != '\0' && i < n)
        i++;

    while(i < n)
    {
        if(*src == '\0')
            dest[i] = '\0';
        else
            dest[i] = *src++;
        i++;
    }

    dest[i] = '\0';
    return ret;
}

char* my_strdup(const char *src)
{
    int n = my_strlen(src) + 1;
    
    char* dest = malloc(sizeof(char) * (n + 1));
    char* ret = dest;

    if(dest == NULL)
        return NULL;

    while(*src != '\0')
        *dest++ = *src++;

    *dest = '\0';
    return ret;
}

char* my_strndup(const char *src, size_t n)
{
    char* ret = malloc((n + 1) * sizeof(char));

    if(ret == NULL || n == 0)
        return NULL;
    
    ret[n] = '\0';

    for(long unsigned int i = 0; i < n; i++)
    {
        if(*src == '\0')
            ret[i] = '\0';
        else
            ret[i] = *src++;
    }
    return ret;
}

char* my_strncpy(char* dest, const char* src, size_t n)
{
    long unsigned int count = 0;
    char* ret = dest;

    while(count < n)
    {
        *dest++ = (*src == '\0') ? '\0' : *src;
        count++;
        src++;
    }
    return ret;
}
