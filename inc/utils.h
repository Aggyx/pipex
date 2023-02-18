/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:31:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/02/18 17:13:19 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include "./libft.h"
# include <unistd.h>

typedef struct s_pipex {
	int		fd[2];
	char	**env;
	char	**incom;
	char	**outcom;
	int		infd;
	int		outfd;
	char	*inpath;
	char	*outpath;
}				t_pipex;

char	*find_path(char **envp, char	**command);
char	**get_command(char	*argv);
void	doublefree(char	**tmp);
#endif