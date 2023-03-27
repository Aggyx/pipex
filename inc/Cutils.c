/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:54:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/27 11:11:35 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static	int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i]) && (s2[i]) && (s1[i] == s2[i]) && (i < n - 1))
		i++;
	if (n == 0)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static	char	**find_path_env(char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	tmp = ft_split(envp[i] + 5, ':');
	return (tmp);
}

char	*find_path(char **envp, char	**command)
{
	char	*path;
	char	*ppath;
	char	**tmp;
	int		i;

	i = 0;
	if (access(command[0], X_OK) == 0)
		return (command[0]);
	tmp = find_path_env(envp);
	i = -1;
	while (tmp[++i])
	{	
		ppath = ft_strjoin(tmp[i], "/");
		path = ft_strjoin(ppath, command[0]);
		free(ppath);
		if (access(path, X_OK) == 0)
		{
			doublefree(tmp);
			return (path);
		}
		free(path);
	}
	doublefree(tmp);
	return (NULL);
}

void	doublefree(char	**tmp)
{
	int	i;

	i = 0;
	if (tmp != NULL)
	{
		while (tmp[i])
			free(tmp[i++]);
	}
	free(tmp);
}

void	panic(char	*str, int error)
{
	perror(str);
	exit(error);
}
