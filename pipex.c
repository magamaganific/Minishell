/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:51:02 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/19 09:51:04 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **extract_command(t_token *command)
{
	char	**cmd;
	int		count;
	t_token	*node;
	int		i;

	node = command;
	while(ft_strncmp(node->value, "|") && ft_strncmp(node->value, "<") && ft_strncmp(node->value, "<<") && ft_strncmp(node->value, ">") && ft_strncmp(node->value, ">>")) // contar numero de posiciones del array de mi comando. 
		count++;
	cmd = malloc(count*sizeof(char *));
	node = command;
	while (i < count)
	{
		cmd[i] = ft_strdup(node->value);
		i++;
		node = node->next;
	}
	while(ft_strncmp(node->value, "|"))
		node = node->next;
	node = node->next; // Me situo en el siguiente pipe. 
	return (cmd);
}

char	*ft_extract_path(char *cmd, char **envp)
{
	char	**dirs;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	dirs = ft_split(envp[i] + 5, ':');
	if (!dirs)
		return (NULL);
	return (check_path_cmd(dirs, cmd));
}

char	*check_path_cmd(char **dirs, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full;

	if (!dirs || !cmd)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (ft_free_split(dirs), NULL);
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			return (ft_free_split(dirs), NULL);
		if (access(full, X_OK) == 0)
			return (ft_free_split(dirs), full);
		free(full);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

void	exec_cmd(char **cmd, char **envp)
{
	char *path;

	path = ft_extract_path(cmd[0], envp);
	execve(path, cmd, envp);
	error_cmd_exec(cmd1);
	exit(127);
}

void	redirect_and_execute(char *cmd, int fd_in, char **envp)
{	
	int		fd_pipe[2];
	pid_t	hijo;

	pipe (fd_pipe[2])
		if (!fd_pipe)
			return (error_pipe_creation());
	hijo = fork();
	if (hijo > 0)
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);
		waitpid(hijo, NULL, 0);
	}
	else
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		if (fdin == STDIN)
			exit(1);
		else
			exec_cmd(cmd, env);
	}
}

void	exec_pipe(t_token *command, int fd_in, int fd_out, char **envp)
{
	char	**cmd;
	int		i;

	cmd = NULL;
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	cmd = extract_command(command);
	if (!cmd)
		return (NULL);
	while (cmd)
	{
		redirect_and_execute(cmd, env, fd_in);
		free_split(cmd);
		cmd = extract_command(command);
	}
	free_token_list()
}









