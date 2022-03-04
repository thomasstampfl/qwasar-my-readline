# my_readline

***

Project for Students @ [Qwasar Silicon Valley](https://qwasar.io/)

![Qwasar Silicon Valley Logo](https://qwasar.io/wp-content/uploads/2019/07/Qwasar-Logo-09.png "Qwasar Silicon Valley Logo")

### Team members:
* Thomas Stampfl

***
## Task

Recreation of **readline** functionality with some limitations.

Read until newline character `\n` or end-of-file.

***
## Usage

Set READLINE_READ_SIZE to define how many bytes shall be read each time. (Value must be `>1`, otherwise error & `NULL` pointer)

Call the function `char *my_readline(int fd);` in your application.

Provide a valid file descriptor.
Reading from `stdin` is possible.

On **success** the function returns the pointer to the read string. Don't forget to free!

On **failure** the function return a `NULL` pointer.

***
## Simple main for testing

Create a *sample_file* with some content. 

Create a file *main.c* with the following content:

```
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define READLINE_READ_SIZE 10

char* my_readline(int fd);

int main(int argc, char** argv)
{
    int fd;
    char* path = "sample_file";
    char* str;

    if(argc != 1)
        path = argv[1];

    if( (fd = open(path, O_RDONLY)) )
    {
        // reading from stdin
        // while( (str = my_readline(STDIN_FILENO)) != NULL)

        // simulate fd error
        // while( (str = my_readline(-1)) != NULL)

        // read from file
        while( (str = my_readline(fd)) )
        {
            // print allocated string
            printf("%s\n", str);

            // do not forget to free allocated string
            free(str);
        }
    }
    else
        printf("Error opening file!\n");      
    close(fd);    
    return 0;
}

```

Compile with

`gcc -o out main.c my_readline.c -Wall -Wextra -Werror`

Run with
* `./out` to use the path set in the main.c file e.g. **sample_file**
* `./out filename` to output the content of the file **filename**


***
## Limitations
* only one static variable
* only allowed functions: `read`, `open`, `close`, `malloc`, `free`
***

## Have fun!
