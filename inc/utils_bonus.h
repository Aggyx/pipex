/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:31:29 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/09 16:27:28 by smagniny         ###   ########.fr       */
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
	int		fd[2];
	int		n_cmds;
	char	**env;cd ..
	char	**cmds;
	int		infd;
	int		outfd;
}				t_pipex;

char	*find_path(char **envp, char	**command);
char	**get_command(char	*argv);
void	doublefree(char	**tmp);
void	panic(char	*str);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *str);
#endif