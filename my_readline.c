#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>

#include <string.h>

// "Number of characters read will be set by the global variable READLINE_READ_SIZE"
int READLINE_READ_SIZE = 100;

// store stuff here? ¯\_(ツ)_/¯
char* storage = NULL;

// init (or reinitialize) global variable
void init_my_readline(){
    if (storage != NULL) free(storage);
    storage = NULL;
}

char* my_readline(int fd) {

    unsigned int total_bytes = 0; // keep track of total size
    char* temp = NULL; // stores stuff
    char* buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char));
    bool end_line = false;
    if (buffer == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    ssize_t read_result; // number of bytes read
    while((read_result = read(fd, buffer, READLINE_READ_SIZE)) > -1 && end_line == false) {
        if (read_result == -1) { // handle errors
            perror("Read error");
            free(buffer);
            return NULL;

        } else if (read_result == 0) {
            // End of file reached
            free(buffer);
            return NULL;
        }

        for (int i = 0; i < read_result; i++) {
            if (buffer[i] == '\n') {
                read_result = i;
                end_line = true;
                break;
            } 
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
        if (end_line == true) break;
    }

    storage[total_bytes] = '\0';
    free(buffer);
    return storage;
}


int main(int ac, char **av)
{
  char *str = NULL;

  int fd = open("test.txt", O_RDONLY);
  while ((str = my_readline(fd)) != NULL)
  {
      printf("%s\n", str);
      init_my_readline();
  }
  close(fd);
  //
  //  Yes it's also working with stdin :-)
  //  printf("%s", my_readline(0));
  //

  return 0;
}