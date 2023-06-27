#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>

#include <string.h>

// "Number of characters read will be set by the global variable READLINE_READ_SIZE"
int READLINE_READ_SIZE = 1024;

// global variable to store stuff that comes after '\n' encountered
char* leftovers = NULL;

// used to "init (or reinitialize) global variable"
void init_my_readline() {
    if (leftovers != NULL) {
        free(leftovers);
        leftovers = NULL;
    }
}

// add everything after '\n' from read buffer to leftovers variable
void store_leftovers(char* buffer, ssize_t read_result) {
    size_t leftover_length = strlen(buffer) - read_result - 1;
    leftovers = malloc((leftover_length + 1) * sizeof(char));
    memcpy(leftovers, buffer + read_result + 1, strlen(buffer) - read_result);
    leftovers[leftover_length] = '\0';
}

char* my_readline(int fd) {

    char* rd_line_buffer = NULL;  // 'line' to be returned by my_readline
    size_t total_bytes = 0; // keep track of total

    if (leftovers != NULL) { // if we got leftovers, add them to readline buffer
        rd_line_buffer = leftovers;
        total_bytes = strlen(leftovers);
        leftovers = NULL;
    }
    
    char* rd_buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char)); // buffer used for read()
    bool end_line = false; // 'true' when '\n' encountered
    if (rd_buffer == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    ssize_t bytes_read;
    while ((bytes_read = read(fd, rd_buffer, READLINE_READ_SIZE)) > 0) { // read in READLINE_READ_SIZE chunks

        rd_buffer[bytes_read] = '\0';

        for (int i = 0; i < bytes_read; i++) {  // check for '\n' in read buffer
            if (rd_buffer[i] == '\n') {
                bytes_read = i;
                end_line = true;
                break;
            }
        }

        total_bytes += bytes_read;

        // Allocate new memory for temp, which will store the new combined data
        char* temp = malloc((total_bytes + 1) * sizeof(char));
        if (temp == NULL) {
            perror("Memory allocation failed");
            free(rd_line_buffer);
            free(rd_buffer);
            return NULL;
        }

        if (rd_line_buffer != NULL) { // Copy the existing data from storage to temp
            memcpy(temp, rd_line_buffer, total_bytes - bytes_read);
            free(rd_line_buffer);  // Free the old storage memory
        }

        memcpy(temp + total_bytes - bytes_read, rd_buffer, bytes_read); // Copy the new data from buffer to temp

        rd_line_buffer = temp; // Update storage to point to the new combined data in temp

        if (end_line) { // if '\n' was found, store the rest of the buffer in leftovers
            store_leftovers(rd_buffer, bytes_read);
            break;
        }
    }

    if (bytes_read == 0 && total_bytes == 0) {  // End of file reached
        free(rd_buffer);
        return NULL;

    } else if (bytes_read == -1) {  // handle invalid file descriptor
        perror("Read error");
        free(rd_buffer);
        return NULL;
    }

    rd_line_buffer[total_bytes] = '\0';
    free(rd_buffer);
    return rd_line_buffer;
}


int main(int ac, char **av)
{
  char *str = NULL;

  int fd = open("test.txt", O_RDONLY);
  while ((str = my_readline(fd)) != NULL)
  {
      printf("%s\n", str);
      free(str);
  }
  close(fd);
  //
  //  Yes it's also working with stdin :-)
  //  printf("%s", my_readline(0));
  //

  return 0;
}