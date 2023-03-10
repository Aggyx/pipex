/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:26:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/03/13 18:25:35 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//< file1 cmd1 | cmd2 > file2

#include "./inc/utils.h"

void	init(int argc, char **argv, char **envp, struct s_pipex *var)
{	
	if (argc != 5)
		panic("ERROR: Invalid arguments");
	if (pipe(var->fd) == -1)
		panic("ERROR: failed building pipe");
	var->env = envp;
	var->incom = get_command(argv[2]);
	var->outcom = get_command(argv[3]);
	var->infd = open(argv[1], O_RDONLY);
	if (var->infd == -1)
		panic("ERROR: Invalid input file.");
	var->outfd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (var->outfd == -1)
		panic("ERROR: Invalid output file.");
}

void	child(t_pipex *var)
{
	if (find_path(var->env, var->incom) == NULL)
		panic("ERROR: Command not found");
	var->inpath = find_path(var->env, var->incom);
	close(var->fd[0]);
	dup2(var->fd[1], STDOUT_FILENO);
	close(var->fd[1]);
	dup2(var->infd, STDIN_FILENO);
	close(var->infd);
	if (execve(var->inpath, var->incom, var->env) == -1)
		panic("EXECVE");
}

void	finalchild(t_pipex *var)
{
	if (find_path(var->env, var->outcom) == NULL)
		panic("ERROR: Command not found");
	var->outpath = find_path(var->env, var->outcom);
	close(var->fd[1]);
	dup2(var->fd[0], STDIN_FILENO);
	close(var->fd[0]);
	dup2(var->outfd, STDOUT_FILENO);
	close(var->outfd);
	if (execve(var->outpath, var->outcom, var->env) == -1)
		panic("EXECVE");
}

int	pipes(t_pipex *var)
{
	int	pid;
	int	pid2;

	pid = fork();
	if (pid < 0)
		panic("ERROR: failed new process");
	if (pid == 0)
		child(var);

	pid2 = fork();
	if (pid2 < 0)
		panic("ERROR: failed new process");
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
	pipes(&var);
}
