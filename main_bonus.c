/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:26:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/27 11:12:16 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//< file1 cmd1 | cmd2 > file2

#include "./inc/utils_bonus.h"

void	init(int argc, char **argv, char **envp, struct s_pipex *var)
{	
	if (argc <= 5)
		panic("ERROR: Invalid arguments, this is bonus", -1);
	var->env = envp;
	var->infd = open(argv[1], O_RDONLY);
	if (var->infd == -1)
		panic("ERROR: Invalid input file ", -1);
	var->outfd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (var->outfd == -1)
		panic(" ERROR: Invalid output file ", -1);
}

void	child(char **command, t_pipex *var)
{
	pid_t	pid;
	int		fd[2];
	char 	*path;

	if (pipe(fd) == -1)
		panic("Pipe error", 127);
	path = find_path(var->env, command);
	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process ", 127);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(path, command, var->env) == -1)
			panic("EXECVE error1 ", 127);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, 0, 0);
	}
	close(fd[1]);
	close(fd[0]);
}

void	finalchild(char **command, t_pipex *var)
{
	pid_t	pid;
	char	*path;

	path = find_path(var->env, command);
	if (!path)
		panic("Command not found ", -1);
	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process ", 127);
	if (pid == 0)
	{
		if (execve(path, command, var->env) == -1)
			panic("EXECVE error2 ", 127);
	}
	waitpid(pid, 0, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	var;
	int		i;

	i = 1;
	init(argc, argv, envp, &var);
	dup2(var.infd, STDIN_FILENO);
	close(var.infd);
	while (++i < argc - 2)
		child(ft_split(argv[i], ' '), &var);
	dup2(var.outfd, STDOUT_FILENO);
	close(var.outfd);
	finalchild(ft_split(argv[i], ' '), &var);
}
