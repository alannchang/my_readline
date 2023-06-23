#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>

#include <string.h>

// "Number of characters read will be set by the global variable READLINE_READ_SIZE"
int READLINE_READ_SIZE = 2;

// store stuff here? ¯\_(ツ)_/¯
char* leftovers = NULL;

// init (or reinitialize) global variable
void init_my_readline(){
    // code leftovers to hold whatever comes after '\n'.  That's why things are cutting off.
    // not sure why the last line is not printing though.
}

char* my_readline(int fd) {

    unsigned int total_bytes = 0; // keep track of total size
    char* rd_line_buffer = NULL;  // stores 'line' to be returned by my_readline
    char* rd_buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char)); // buffer used for read()
    bool end_line = false; // set to 'true' when '\n' encountered
    if (rd_buffer == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    ssize_t read_result; // number of bytes read
    while ((read_result = read(fd, rd_buffer, READLINE_READ_SIZE)) > -1 && end_line == false) {
        if (read_result == -1) { // handle errors
            perror("Read error");
            free(rd_buffer);
            return NULL;

        } else if (read_result == 0) { // End of file reached
            free(rd_buffer);
            return NULL;
        }

        for (int i = 0; i < read_result; i++) { // check for '\n'
            if (rd_buffer[i] == '\n') {
                read_result = i;
                end_line = true;
                break;
            }
        }
        
        total_bytes += read_result;

        // Allocate new memory for temp, which will store the new combined data
        char* temp = malloc((total_bytes + 1) * sizeof(char));
        if (temp == NULL) {
            perror("Memory allocation failed");
            free(rd_line_buffer);
            free(rd_buffer);
            return NULL;
        }

        // Copy the existing data from storage to temp
        if (rd_line_buffer != NULL)
        {
            memcpy(temp, rd_line_buffer, total_bytes - read_result);
            free(rd_line_buffer);  // Free the old storage memory
        }

        // Copy the new data from buffer to temp
        memcpy(temp + total_bytes - read_result, rd_buffer, read_result);

        // Update storage to point to the new combined data in temp
        rd_line_buffer = temp;
        if (end_line == true) break;
        // code memcpy to leftover here 
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