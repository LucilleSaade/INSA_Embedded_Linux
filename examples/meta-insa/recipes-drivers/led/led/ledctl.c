#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main( int argc, char ** argv)
{
	int fd = open( "/dev/led", O_RDWR );
	if (fd < 0 )
	{
		printf ( "Fail to open %s \n", strerror(errno));
		return  -1;
	}

	sleep(100);

	close(fd);

	return 0;
}
