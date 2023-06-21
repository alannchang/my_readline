#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// "Number of characters read will be set by the global variable READLINE_READ_SIZE"
int READLINE_READ_SIZE = 10;

// store stuff here? ¯\_(ツ)_/¯
char* storage = NULL;

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

// init (or reinitialize) global variable
void init_my_readline(){

}

char* my_readline(int fd) {

    unsigned int count = 0;
    char* buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char));
    if (buffer == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    ssize_t read_result;
    while((read_result = read(fd, buffer, READLINE_READ_SIZE)) == READLINE_READ_SIZE) {
        if (read_result == -1) { // handle errors
            perror("Read error");
            free(buffer);
            return NULL;

        } else if (read_result == 0) {
            // End of file reached
            free(buffer);
            return NULL;
        }
        count += read_result;
        printf("%s", buffer);
        free(buffer);
        char* buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char));



    }

    buffer[READLINE_READ_SIZE] = '\0';
    return buffer;
}


int main(int ac, char **av) {
    char *str = NULL;
    int fd = open("test.txt", O_RDONLY);
    str = my_readline(fd);
    printf("%s\n", str);
    free(str);

//   while ((str = my_readline(fd)) != NULL) {
//         printf("%s\n", str);
//         free(str);
//     }
//     close(fd);
    return 0;
} 

  //
  //  Yes it's also working with stdin :-)
  //  printf("%s", my_readline(0));
  //

 