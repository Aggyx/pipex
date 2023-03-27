/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:31:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/27 15:44:25 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex {
	pid_t	fd[2];
	char	**env;
	char	**incom;
	char	**outcom;
	char	*infd;
	char	*outfd;
	char	*inpath;
	char	*outpath;
}				t_pipex;

char	*find_path(char **envp, char	**command);
char	**get_command(char	*argv);

void	doublefree(char	**tmp);
void	panic(char	*str, int error);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
#endif