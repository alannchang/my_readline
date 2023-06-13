#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


// Number of characters read will be set by the global variable READLINE_READ_SIZE
int READLINE_READ_SIZE = 512;

// store stuff here ¯\_(ツ)_/¯
int storage;

void my_strcat(char* dest, const char* src){

    while(*dest) dest++;

    while(*src) {
        *dest = *src;
        src++;
        dest++;
    }

    *dest = '\0';
}

void init_my_readline() {
    
}

char* my_readline(int fd){
    char* result = "";
    char* buffer;
    while (read(fd, &buffer, READLINE_READ_SIZE) == READLINE_READ_SIZE) {
        // check for newline character
        while (*buffer) {
            if (*buffer == '\n') {
                *buffer = '\0';
                my_strcat(result, buffer);
                break;
            }
        }

    }

    return result;
}


int main(int ac, char **av)
{
  char *str = NULL;

  if (ac == 2) {
    
    int fd = open(av[1], O_RDONLY);
    while ((str = my_readline(fd)) != NULL)
    {
      printf("%s\n", str);
      free(str);
    }
    close(fd);
        
  }


  //
  //  Yes it's also working with stdin :-)
  //  printf("%s", my_readline(0));
  //

  return 0;
}