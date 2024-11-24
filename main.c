#include "get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	//  int c = open("txt.txt", O_RDONLY );
	printf("%s", get_next_line(0));
	// printf("%s",get_next_line(c));
}
