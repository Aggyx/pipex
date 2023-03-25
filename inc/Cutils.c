/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:54:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/25 15:48:11 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

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
	{
		printf("%s", command[0]);
		return (command[0]);
	}
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

void	panic(char	*str)
{
	perror(str);
	exit(127);
}
