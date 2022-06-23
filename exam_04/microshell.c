#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

#define PIPE 2
#define NON_PIPE 1
typedef struct s_data
{
	char *args[1000];
	int delim;
	int pipe[2];
} t_data;
int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}
void ft_error(int fd, char *str1, char *str2)
{
	if (str1)
		write(fd, str1, ft_strlen(str1));
	if (str2)
		write(fd, str2, ft_strlen(str2));
	write(fd, "\n", 1);
}
void parse(t_data *data, char **argc)
{
	int i = 1, j = 0, cmd = 0;
	while (argc[i])
	{
		if (!strcmp(argc[i], "|"))
		{
			data[cmd].delim = PIPE;
			cmd++;
			j = 0;
		}
		else if (!strcmp(argc[i], ";"))
		{
			data[cmd].delim = NON_PIPE;
			cmd++;
			j = 0;
		}
		else
		{
			data[cmd].args[j] = argc[i];
			data[cmd].delim = NON_PIPE;
			j++;
		}
		i++;
	}
	// j = 0, i = 0, cmd = 0;
	// while (data[cmd].args[j])
	// {
	// 	while(data[cmd].args[j])
	// 	{
	// 		printf("data[%d].args[%d] - %s\n", cmd, j, data[cmd].args[j]);
	// 		j++;
	// 	}
	// 	printf("data[%d] delim: %d\n", cmd, data[cmd].delim);
	// 	j = 0;
	// 	cmd++;
	// }
}
void run(t_data *data, char **env)
{
	int res = 0;
	int i = 0;
	while (data[i].delim)
	{
		if (data[i].args[0] && !strcmp(data[i].args[0], "cd")) //if CD
		{
			if (data[i].args[2] || !data[i].args[1] || data[i].args[1][0] == '-')
				ft_error(2, "error: cd: bad arguments", NULL);
			else if (chdir(data[i].args[1]) < 0)
				ft_error(2, "error: cd: cannot change directory to ", data[i].args[1]);
		}
		else // not CD
		{
			if (data[i].delim == PIPE)
				pipe(data[i].pipe);
			res = fork();
			if (res == 0) // if child process
			{
				if (i != 0 && data[i-1].delim == PIPE) // если это команда следующая после пайпа
					dup2(data[i-1].pipe[0], 0); // то для предыдущей команды устанавливаем фд - 0ж
				if (data[i].pipe[1] != 0) // если был создан пайп
					dup2(data[i].pipe[1], 1); // устанавливаем его в 1.
				if (data[i].args[0] && execve(data[i].args[0], data[i].args, env) < 0)
					ft_error(2, "error: cannot execute ", data[i].args[0]);
				exit(1);
			}
			else // parent process
			{
				waitpid(res, NULL, 0);
				if (i != 0 && data[i-1].delim == PIPE)
					close(data[i-1].pipe[0]); // закрывает фв команды перед пайпом
				if (data[i].pipe[1])
					close(data[i].pipe[1]); //закрывает фд команды после пайпа
			}
		}
		i++;
	}
}

int	main(int argv, char **argc, char **envp)
{
	t_data data[1000];
	if (argv > 1)
	{
		parse(data, argc);
		run(data, envp);
		// printf("%s\n", getcwd(NULL, 0));
	}
	return (0);
}