#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>

#define PIPE 2
#define NON_PIPE 1

typedef struct s_data
{
	char *args[1000];
	int pipe[2];
	int delim;
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

void parse(t_data *data, char **argv)
{
	int i = 1, j = 0, cmd = 0;
	while (argv[i])
	{
		if (!strcmp(argv[i], "|"))
		{
			data[cmd].delim = PIPE;
			cmd++;
			j = 0;
		}
		else if (!strcmp(argv[i], ";"))
		{
			data[cmd].delim = NON_PIPE;
			cmd++;
			j = 0;
		}
		else
		{
			data[cmd].args[j] = argv[i];
			data[cmd].delim = NON_PIPE;
			j++;
		}
		i++;
	}
}
void run(t_data *data, char **env)
{
	int res = 0, i = 0;
	// (void)env;
	while(data[i].delim)
	{
		if (data[i].args[0] && !strcmp(data[i].args[0], "cd"))
		{
			if (data[i].args[2] || !data[i].args[1] || data[i].args[1][0] == '-')
				ft_error(2, "error: cd: bad arguments", NULL);
			else if (chdir(data[i].args[1]) < 0)
				ft_error(2, "error: cd: cannot change directory to ", data[i].args[1]);
		}
		else
		{
			if (data[i].delim == PIPE)
				pipe(data[i].pipe);
			res = fork();
			if (res == 0)
			{
				if (i != 0 && data[i-1].delim == PIPE)
					dup2(data[i-1].pipe[0], 0);
				if (data[i].pipe[1])
					dup2(data[i].pipe[1], 1);
				if (data[i].args[0] && execve(data[i].args[0], data[i].args, env) < 0)
					ft_error(2, "error: cannot execute ", data[i].args[0]);
				exit(1);
			}
			else
			{
				waitpid(res, 0, 0);
				if (i != 0 && data[i-1].delim == PIPE)
					close(data[i].pipe[0]);
				if (data[i].pipe[1])
					close(data[i].pipe[1]);
			}
		}
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	t_data data[1000];
	(void)env;
	if (argc > 1)
	{
		parse(data, argv);
		run(data, env);
	}
	return (0);
}

	// j = 0, i = 0;
	// while(data[i].args[j])
	// {
	// 	while(data[i].args[j])
	// 	{
	// 		printf("data[%d].args[%d]%s\n", i, j, data[i].args[j]);
	// 		j++;
	// 	}
	// 	i++;
	// 	j = 0;
	// }