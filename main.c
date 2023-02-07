/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:26:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/02/07 19:26:13 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//< file1 cmd1 | cmd2 > file2

#include "inc/utils.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_command {
	int		argc;
	char	**argv;
}				t_cmd;

typedef struct s_pipex {
	char	**env;
	char	*incom;
	char	*outcom;
	int		infd;
	int		outfd;
	char	*inpath;
	char	*outpath;
}				t_pipex;

char	*find_path(char **envp, char	*command)
{
	char	*path;
	char	**tmp;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", envp[i++], 4) != 0)
		;
	tmp = ft_split(envp[--i], ':');
	path = ft_strjoin(tmp[3], "/");
	free(tmp);
	path = ft_strjoin(path, command);
	ft_printf("%s\n",path);
	if (access(path, F_OK) != 0)
		perror("ERROR: command not found.");
	return (path);
}

void	init(int argc, char **argv, char **envp, struct s_pipex *var)
{	
	var->env = envp;
	var->incom = argv[2];
//	var->outcom = argv[3];
	var->infd = open(argv[1], O_RDONLY);
//	var->outfd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	var->inpath = find_path(envp, var->incom);
//	var->outpath = find_path(envp, var->outcom);
	ft_printf("Infile:%s\nOutfile: \nlen: %d\n", argv[1], argc);
}

void	pipes(t_pipex *var)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) != 0)
		perror("ERROR: failed building pipe");
	pid = fork();
	if (pid < 0)
		perror("ERROR: failed new process");
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);
		execve(var->inpath, &var->incom, var->env);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	var;

	if (argc != 3)
		perror("ERROR: Invalid arguments");
	init(argc, argv, envp, &var);
	pipes(&var);
}
