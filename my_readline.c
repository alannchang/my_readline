#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include <string.h>

// "Number of characters read will be set by the global variable READLINE_READ_SIZE"
int READLINE_READ_SIZE = 1000;

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
    if (storage != NULL) storage = NULL;
}

char* my_readline(int fd) {

    unsigned int total_bytes = 0; // keep track of total size
    char* temp = NULL; // stores stuff
    char* buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char));
    if (buffer == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    ssize_t read_result; // number of bytes read
    while((read_result = read(fd, buffer, READLINE_READ_SIZE)) > 0) {
        if (read_result == -1) { // handle errors
            perror("Read error");
            free(buffer);
            return NULL;

        } else if (read_result == 0) {
            // End of file reached
            free(buffer);
            return NULL;
        }
        
        total_bytes += read_result;

        // Allocate new memory for temp, which will store the new combined data
        temp = malloc((total_bytes + 1) * sizeof(char));
        if (temp == NULL) {
            perror("Memory allocation failed");
            free(storage);
            free(buffer);
            return NULL;
        }

        // Copy the existing data from storage to temp
        if (storage != NULL) {
            memcpy(temp, storage, total_bytes - read_result);
            free(storage); // Free the old storage memory
        }

        // Copy the new data from buffer to temp
        memcpy(temp + total_bytes - read_result, buffer, read_result);

        // Update storage to point to the new combined data in temp
        storage = temp;
    }

    storage[total_bytes] = '\0';
    free(buffer);
    return storage;
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

 