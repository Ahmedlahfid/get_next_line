#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "get_next_line.h"


int main(void)
{
  //  int c = open("txt.txt", O_RDONLY );
    printf("%s",get_next_line(0));
   // printf("%s",get_next_line(c));

}

