/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:58:57 by sidrissi          #+#    #+#             */
/*   Updated: 2025/02/15 22:57:06 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strlen_p(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (!s1 || !s2 || n <= 0)
		return (0);
	i = 0;
	while (i < n && (s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_find(char *s, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == s[0])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dst, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
