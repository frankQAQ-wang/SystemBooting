#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int i, len, size, totalsize, x, y;
	FILE *ifp, *ofp;
	struct stat filestat;
	unsigned char *buff;
	char sector[512];
	i = 0;
	len = 0;
	size = 0;
	totalsize = 0;
	ifp = NULL;
	ofp = NULL;
	buff = NULL;
	if(argc < 4)
	{
		printf("%s: ofile size ifile...\n", argv[0]);
		return 1;
	}
	ofp = fopen(argv[1], "w");
	if(!ofp)
	{
		printf("ofile(%s) error: %s\n", argv[1], strerror(errno));
		return 2;
	}
	totalsize = atoi(argv[2]);
	for(i = 3; i < argc; i++)
	{
		if(stat(argv[i], &filestat))
		{
			printf("ifile(%s) error: %s\n", argv[i], strerror(errno));
			unlink(argv[1]);
			return 3;
		}
		if(len < filestat.st_size)
		{
			free(buff);
			buff = malloc(filestat.st_size);
		}
		len = filestat.st_size;
		size += len;
		if(size > totalsize)
		{
			printf("ifile(%s) error: %s\n", argv[i], strerror(errno));
			unlink(argv[1]);
			return 4;
		}
		ifp = fopen(argv[i], "r");
		if(!ifp)
		{
			printf("ifile(%s) error: %s\n", argv[i], strerror(errno));
			return 5;
		}
		fread(buff, 1, len, ifp);
		fwrite(buff, 1, len, ofp);
		fclose(ifp);
	}
	memset(sector, 0, 512);
	x = (totalsize - size) % 512;
	y = (totalsize - size) / 512;
	fwrite(sector, 1, x, ofp);
	for(i = 0; i < y; i++)
	       fwrite(sector, 1, 512, ofp);	
	free(buff);
	fclose(ofp);
	return 0;
}
