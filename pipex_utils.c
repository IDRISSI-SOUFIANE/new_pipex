#include "../include/pipex.h"

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
char    *get_path(t_data *data)
{
    char    *joined_slash;
    char    *path_of_cmd;
    int     i;

    i = 0;
    while (data->path[i])
    {
        joined_slash = ft_strjoin(data->path[i], "/");
        path_of_cmd = ft_strjoin(joined_slash, data->cmd[0]);
        free(joined_slash);
        if (access(path_of_cmd, F_OK) == 0)
            return (path_of_cmd);
        free(path_of_cmd);
        i++;
    }
    return (NULL);
}

