#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int storage = 0;
int READLINE_READ_SIZE;

char* my_readline(int fd){
    char* buffer;
    while (read(fd, buffer, 1) > 0 && buffer ) {

    }




    return 0;
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