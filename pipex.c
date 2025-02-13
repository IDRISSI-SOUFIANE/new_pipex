#include "../include/pipex.h"

void	ft_close(t_data *data)
{
	close(data->fds[0]);
	close(data->fds[1]);
}

void	ft_clean(t_data *data)
{
	if (data->cmd)
		ft_free(data->cmd, ft_strlen_p(data->cmd));
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->path)
		ft_free(data->path, ft_strlen_p(data->path));
	close(data->fds[0]);
	close(data->fds[1]);
	exit(1);
}



// here will be leaks if execeve faile
void	child_process1(char **av, char **env, t_data *data)
{
	data->infile = open(av[1], O_RDONLY, 0777);
	if (data->infile < 0)
		(close(data->infile), ft_clean(data), perror("Error:"));
	if (dup2(data->infile, STDIN_FILENO) < 0 || dup2(data->fds[1], STDOUT_FILENO) < 0)
		(ft_clean(data), perror("Error:"));
	(close(data->infile), ft_close(data));
	data->cmd = ft_split(av[2], ' ');
	if (NULL == data->cmd)
		(perror("Error:"), ft_clean(data));
	data->cmd_path = get_path(data);
	// if (execve(data->cmd_path, data->cmd, env) < 0)
	// {
	// 	return (ft_clean(data),
	// 		ft_free(data->cmd, ft_strlen_p(data->cmd)),
	// 		free(data->cmd_path));
	// 		perror("Error: ");
	// 		exit(1);
	// }

	if (execve(data->cmd_path, data->cmd, env) < 0)
	{
		perror("Error: ");
		ft_clean(data);
	}
}
/*in child process1 he write so the child process2 should read!!*/
void	child_process2(char **av, char **env, t_data *data)
{
	data->outfile = open(av[4], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (data->outfile < 0)
		(close(data->outfile), ft_clean(data), perror("Error:"));
	if (dup2(data->outfile, STDOUT_FILENO) < 0 || dup2(data->fds[0], STDIN_FILENO) < 0)
		(ft_clean(data), perror("Error:"));
	(close(data->outfile), ft_close(data));
	data->cmd = ft_split(av[3], ' ');
	if (NULL == data->cmd)
		(perror("Error:"), ft_clean(data));
	data->cmd_path = get_path(data);
	// if (execve(data->cmd_path, data->cmd, env) < 0)
	// {
	// 	return (ft_clean(data),
	// 		ft_free(data->cmd, ft_strlen_p(data->cmd)),
	// 		free(data->cmd_path));
	// 		perror("Error: ");
	// 		exit(1);
	// }

	if (execve(data->cmd_path, data->cmd, env) < 0)
	{
		perror("Error: ");
		ft_clean(data);
	}

}
// There is no leaks in this function
// void	ft_check(int ac, char **av, char **env, t_data *data)
// {
// 	if (pipe(data->fds) < 0)
// 		perror("Error(pipe): ");
// 	if ((env == NULL || *env == NULL) )
// 		perror("env: ");
// 	if (ac != 5)
// 		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), exit(1));
// 	if (ft_find(av[2], "/*.-") || ft_find(av[3], "/*.-"))
// 		return (write(2, "zsh: no such file or dierectory\n", 32), exit(1));
// }


void	ft_check(int ac, char **av, char **env, t_data *data)
{
	if (ac != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), exit(1));
	if (pipe(data->fds) < 0)
		return (perror("Error(pipe): "), exit(1));
	if (env == NULL || *env == NULL)
		return (perror("Error(env): "), exit(1));
	if (ft_find(av[2], "/*.-") || ft_find(av[3], "/*.-"))
		return (write(2, "zsh: no such file or directory\n", 32), exit(1));
}


void	f()
{
	system("leaks a.out");
}
// // stuct in my mind
// int main(int ac, char **av, char **env)
// {
// 	atexit(f);
// 	t_data	data;

// 	ft_check(ac, av, env, &data); // no free here
// 	data.path = split_path(env);
// 	if (NULL == data.path)
// 		ft_free(data.path, ft_strlen_p(data.path)); // this line hold the pointer come from split so should free them when failer or when you finish
// 	data.pid1 = fork();
// 	if (data.pid1 < 0)
// 		ft_clean(&data); // this line hold the pointer come from split so should free them when failer or when you finish
// 	if(data.pid1 == 0)
// 		child_process1(av, env, &data);
// 	data.pid2 = fork();
// 	if (data.pid2 < 0)
// 		ft_clean(&data); // this line hold the pointer come from split so should free them when failer or when you finish
// 	if(data.pid2 == 0)
// 		child_process2(av, env, &data);
// 	ft_clean(&data);
// 	return (0);
// }

int main(int ac, char **av, char **env)
{
	atexit(f);
	t_data	data;

	ft_check(ac, av, env, &data);
	data.path = split_path(env);
	if (NULL == data.path)
		ft_clean(&data);
	data.pid1 = fork();
	if (data.pid1 < 0)
		ft_clean(&data);
	if (data.pid1 == 0)
		child_process1(av, env, &data);
	data.pid2 = fork();
	if (data.pid2 < 0)
		ft_clean(&data);
	if (data.pid2 == 0)
		child_process2(av, env, &data);

	// Wait for both processes to finish
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	ft_clean(&data);
	return (0);
}

