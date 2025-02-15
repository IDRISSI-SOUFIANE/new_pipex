/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:58:48 by sidrissi          #+#    #+#             */
/*   Updated: 2025/02/15 22:49:53 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_check(int ac, char **av, char **env, t_data *data)
{
	if (pipe(data->fds) < 0)
		perror("Error");
	if ((env == NULL || *env == NULL))
		perror("env: ");
	if (ac != 5)
		return (write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40),
			exit(1));
}

char	**split_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path = env[i] + 5;
			break ;
		}
		i++;
	}
	return (ft_split(path, ':'));
}

char	*get_path(t_data *data)
{
	char	*joined_slash;
	char	*path_of_cmd;
	int		i;
	char	*first_cmd;

	i = 0;
	first_cmd = data->cmd[0];
	while (data->path[i])
	{
		joined_slash = ft_strjoin(data->path[i], "/");
		path_of_cmd = ft_strjoin(joined_slash, first_cmd);
		free(joined_slash);
		if (access(path_of_cmd, F_OK) == 0)
			return (path_of_cmd);
		free(path_of_cmd);
		i++;
	}
	return (NULL);
}

int	ft_ok(char **cmd)
{
	char	*cmde;

	cmde = cmd[0];
	if (access(cmde, F_OK) == 0)
		return (0);
	return (1);
}
