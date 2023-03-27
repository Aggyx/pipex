/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:26:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/25 23:23:48 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//< file1 cmd1 | cmd2 > file2

#include "./inc/utils.h"

static	void	init(int argc, char **argv, char **envp, struct s_pipex *var)
{	
	if (argc != 5)
		panic("ERROR: Invalid arguments ", -1);
	if (pipe(var->fd) == -1)
		panic("ERROR: failed building pipe ", -1);
	var->env = envp;
	var->incom = ft_split(argv[2], ' ');
	var->outcom = ft_split(argv[3], ' ');
	var->infd = open(argv[1], O_RDONLY);
	if (var->infd == -1)
		panic("ERROR: Invalid input file ", -1);
	var->outfd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (var->outfd == -1)
		panic("ERROR: Invalid output file ", -1);
}

static	void	child(t_pipex *var)
{
	if (find_path(var->env, var->incom) == NULL)
		panic("ERROR: Command not found ", 127);
	var->inpath = find_path(var->env, var->incom);
	close(var->fd[0]);
	dup2(var->fd[1], STDOUT_FILENO);
	close(var->fd[1]);
	dup2(var->infd, STDIN_FILENO);
	close(var->infd);
	if (execve(var->inpath, var->incom, var->env) == -1)
		panic("EXECVE error ", 127);
}

static	void	finalchild(t_pipex *var)
{
	if (find_path(var->env, var->outcom) == NULL)
		panic("ERROR: Command not found ", 127);
	var->outpath = find_path(var->env, var->outcom);
	close(var->fd[1]);
	dup2(var->fd[0], STDIN_FILENO);
	close(var->fd[0]);
	dup2(var->outfd, STDOUT_FILENO);
	close(var->outfd);
	if (execve(var->outpath, var->outcom, var->env) == -1)
		panic("EXECVE error ", 127);
}

static	int	pipes(t_pipex *var)
{
	int	pid;
	int	pid2;

	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process ", 127);
	if (pid == 0)
		child(var);
	pid2 = fork();
	if (pid2 < 0)
		panic("ERROR: failed new process ", 127);
	if (pid2 == 0)
		finalchild(var);
	close(var->fd[0]);
	close(var->fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	var;

	init(argc, argv, envp, &var);
	return (pipes(&var));
}
