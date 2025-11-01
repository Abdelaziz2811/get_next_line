#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int fd = open("big.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	char *line;
	
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	// if (fd != -1 && fd2 != -1)
	// {
	// 	int i = 0;
	// 	while (i < 5)
	// 	{
	// 		line = get_next_line(fd);
	// 		printf("%s", line);
	// 		free(line);
	// 		i++;
	// 	}
	// 	int j = 0;
	// 	while (j < 5)
	// 	{
	// 		line = get_next_line(fd2);
	// 		printf("\033[1;32m%s\033[0m", line);
	// 		free(line);
	// 		j++;
	// 	}
	// 	while (i < 10)
	// 	{
	// 		line = get_next_line(fd);
	// 		printf("%s", line);
	// 		free(line);
	// 		i++;
	// 	}
	// 	while (j < 10)
	// 	{
	// 		line = get_next_line(fd2);
	// 		printf("\033[1;32m%s\033[0m", line);
	// 		free(line);
	// 		j++;
	// 	}
		// while (i < 15)
		// {
		// 	line = get_next_line(fd);
		// 	printf("%s", line);
		// 	free(line);
		// 	i++;
		// }
		// while (j < 15)
		// {
		// 	line = get_next_line(fd2);
		// 	printf("\033[1;32m%s\033[0m", line);
		// 	free(line);
		// 	j++;
		// }
		// while (i < 20)
		// {
		// 	line = get_next_line(fd);
		// 	printf("%s", line);
		// 	free(line);
		// 	i++;
		// }
		// while (j < 20)
		// {
		// 	line = get_next_line(fd2);
		// 	printf("\033[1;32m%s\033[0m", line);
		// 	free(line);
		// 	j++;
		// }
	// }
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);

	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);

	return 0;
}