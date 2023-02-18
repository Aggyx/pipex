/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:54:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/02/18 17:07:32 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/utils.h"

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

char	**get_command(char	*argv)
{
	char	**comm;

	comm = ft_split(argv, ' ');
	return (comm);
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
