#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <stdio.h>
// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	*line = NULL;
// 	int	fd = open(av[1], O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
// #include <stdio.h>
// #include <string.h>
// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	int	fd = open(av[1], O_RDONLY);
// 	char *line = get_next_line(fd);
// 	printf("1char.txt\nstrcmp -> %i\n", strcmp(line, "0"));
// 	free(line);
// 	close(fd);
// 	return (0);
// }

#include <stdio.h>
int	main(int ac, char **av)
{
	(void)ac;
	char	*line = NULL;
	// (void)av;
	// int	fd = -1;/*open(av[1], O_RDONLY);*/
	int	fd = open(av[1], O_RDONLY);
	printf("1 -> %s\n", line = get_next_line(fd));
	free(line);
	printf("2 -> %s\n", line = get_next_line(fd));
	free(line);
	close(fd);
	printf("3 -> %s\n", line = get_next_line(-1));
	free(line);
	fd = open(av[1], O_RDONLY);
	printf("4 -> %s\n", line = get_next_line(fd));
	free(line);
	printf("5 -> %s\n", line = get_next_line(fd));
	free(line);
	printf("6 -> %s\n", line = get_next_line(fd));
	free(line);
	printf("7 -> %s\n", line = get_next_line(fd));
	free(line);
	printf("8 -> %s\n", line = get_next_line(fd));
	free(line);
}
//
//
// #include <stdio.h>
// #include <unistd.h>
// void	ft_putstr(char *line)
// {
// 	write(1, line, ft_strclen(line, 0));
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	*line = NULL;
// 	int	fd = open(av[1], O_RDONLY);
// 	line = get_next_line(fd);
// 		ft_putstr(line);
// 	free(line);
// 	close(fd);
// 	open(av[1], O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		ft_putstr(line);
// 		free(line);
// 	}
// 	//line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// }
