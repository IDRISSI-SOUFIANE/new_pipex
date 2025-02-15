/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:56:46 by sidrissi          #+#    #+#             */
/*   Updated: 2025/02/15 22:57:27 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strcat(char *dst, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (s[j])
		dst[i++] = s[j++];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;
	int		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	str = (char *)malloc((s_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	int		len_s1;
	int		len_s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_strcpy(s, s1);
	ft_strcat(s, s2);
	return (s);
}

void	ft_putstr(char *cmd_path, char *error)
{
	int	i;

	i = 0;
	while (error[i])
	{
		write(2, &error[i], 1);
		i++;
	}
	write(2, " ", 1);
	write(2, cmd_path, ft_strlen(cmd_path));
	write(2, "\n", 1);
}
