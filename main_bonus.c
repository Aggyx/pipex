/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:26:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/13 18:14:16 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//< file1 cmd1 | cmd2 > file2

#include "./inc/utils_bonus.h"

void	init(int argc, char **argv, char **envp, struct s_pipex *var)
{	
	if (argc < 5)
		panic("ERROR: Invalid arguments");
	if (pipe(var->fd) == -1)
		panic("ERROR: failed building pipe");
	var->env = envp;
	var->n_cmds = argc - 4;
	var->infd = open(argv[1], O_RDONLY);
	if (var->infd == -1)
		panic(" ERROR: Invalid input file.");
	var->outfd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (var->outfd == -1)
		panic(" ERROR: Invalid output file.");
}

void	startchild(t_pipex *var, char *path, char **command)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process");
	if (pid == 0)
	{	
		close(var->fd[0]);
		dup2(var->infd, STDIN_FILENO);
		close(var->infd);
		dup2(var->fd[1], STDOUT_FILENO);
		close(var->fd[1]);
		if (execve(path, command, var->env) == -1)
			panic("EXECVE error");
	}
	waitpid(pid, NULL, 0);
}

void	child(int fdIN, int fdOUT, char **command, t_pipex *var)
{
	int		pid;
	char	*path;

	path = find_path(var->env, command);
	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process");
	if (pid == 0)
	{		
		dup2(fdIN, STDIN_FILENO);
		close(fdIN);
		dup2(fdOUT, STDOUT_FILENO);
		close(fdOUT);
		if (execve(path, command, var->env) == -1)
			panic("EXECVE error");
	}
	waitpid(pid, NULL, 0);
}

void	child_loop(t_pipex *var, char **argv, int i)
{
	char	**command;
	int		fd[2];
	int		fdin;
	int		fdout;

	command = ft_split(argv[i], ' ');
	printf("Path : nose\nCommand: %s", command[0]);
	if (pipe(fd) == -1)
		panic("ERROR: child new process ");
	fdin = var->fd[1];
	fdout = fd[1];
	while (argv[++i] != NULL && --var->n_cmds > 0)
		child(fdin, fdout, command, var);
}


void	finalchild(t_pipex *var, char *path, char **command)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process");
	if (pid == 0)
	{	
		close(var->fd[1]);
		dup2(var->fd[0], STDIN_FILENO);
		close(var->fd[0]);
		dup2(var->outfd, STDOUT_FILENO);
		close(var->outfd);
		if (execve(path, command, var->env) == -1)
			panic("EXECVE error");
	}
	close(var->fd[0]);
	close(var->fd[1]);
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	var;
	int		i;
	char	*path;
	char	**command;

	i = 2;
	init(argc, argv, envp, &var);
	command = ft_split(argv[i], ' ');
	path = find_path(var.env, command);
	startchild(&var, path, command);

	child_loop(&var, argv, i);
	command = ft_split(argv[i], ' ');
	path = find_path(var.env, command);
	finalchild(&var, path, command);
	doublefree(command);
	free(path);
}
