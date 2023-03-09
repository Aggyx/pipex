/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:54:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/02/28 06:45:16 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

char	*find_path(char **envp, char	**command)
{
	char	*path;
	char	*ppath;
	char	**tmp;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	tmp = ft_split(envp[i] + 5, ':');
	i = -1;
	while (tmp[++i])
	{	
		ppath = ft_strjoin(tmp[i], "/");
		path = ft_strjoin(ppath, command[0]);
		free(ppath);
		if (access(path, F_OK) == 0)
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
	exit(0);
}