#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// "Number of characters read will be set by the global variable READLINE_READ_SIZE"
int READLINE_READ_SIZE = 512;

// store stuff here? ¯\_(ツ)_/¯
char* storage;

char *my_strncat(char *dest, const char *src, size_t n) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    char *temp = dest;
    size_t i;

    while (*temp) {
        temp++;
    }

    for (i = 0; i < n && src[i] != '\0'; ++i) {
        temp[i] = src[i];
    }

    temp[i] = '\0';

    return dest;
    
}

void init_my_readline(){

}

char* my_readline(int fd){
    int i = 0;
    char* buffer;
    while (read(fd, &buffer, READLINE_READ_SIZE) == READLINE_READ_SIZE) {

        int j = 0;
        while (j < READLINE_READ_SIZE) {
            // break loop if '\n' found
            if (buffer[j] == '\n') {
                buffer[j] = '\0';
                my_strncat(storage, buffer, j + 1);
                break;
            }
            else {
                my_strncat(storage, buffer, j + 1);
                i++;
                j++;
            }
        }

    }
    return storage;
}


// int main(int ac, char **av)
// {
//   char *str = NULL;

//   if (ac == 2) {
    
//     int fd = open(av[1], O_RDONLY);
//     while ((str = my_readline(fd)) != NULL)
//     {
//       printf("%s\n", str);
//       free(str);
//     }
//     close(fd);
        
//   }


  //
  //  Yes it's also working with stdin :-)
  //  printf("%s", my_readline(0));
  //

//   return 0;
// }