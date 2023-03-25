/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:26:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/25 15:42:46 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//< file1 cmd1 | cmd2 > file2

#include "./inc/utils_bonus.h"

void	init(int argc, char **argv, char **envp, struct s_pipex *var)
{	
	if (argc <= 5)
		panic("ERROR: Invalid arguments ");
	var->env = envp;
	var->infd = open(argv[1], O_RDONLY);
	if (var->infd == -1)
		panic("ERROR: Invalid input file ");
	var->outfd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (var->outfd == -1)
		panic(" ERROR: Invalid output file ");
}

void	child(char **command, t_pipex *var)
{
	pid_t	pid;
	int		fd[2];
	char	*path;

	if (pipe(fd) == -1)
		panic("Pipe error");
	path = find_path(var->env, command);
	if (!path)
		panic("Command not found ");
	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process ");
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(path, command, var->env) == -1)
			panic("EXECVE error1 ");
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
		panic("Command not found ");
	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process ");
	if (pid == 0)
	{
		if (execve(path, command, var->env) == -1)
			panic("EXECVE error2 ");
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
