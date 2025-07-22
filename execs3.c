/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:53:52 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/21 18:53:53 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_argument_pipe(t_token *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token->value, "|", 2))
		return (0);
	if (is_redirection(token))
		return (0);
	return (1);
}

char	**build_argv(t_token *start)
{
	char	**argv;
	int		n_args;
	int		i;
	char	**aux;
	int		j;

	if (!init_args(start, &n_args, &argv, &i))
		return (NULL);
	while (start && is_argument_pipe(start))
	{
		if (space_in(start->value))
		{
			aux = ft_split(start->value, ' ');
			j = 0;
			while (aux[j])
				argv[i++] = ft_strdup(aux[j++]);
			free_split(aux);
			start = start->next;
			continue ;
		}
		argv[i++] = ft_strdup(start->value);
		start = start->next;
	}
	argv[i] = NULL;
	return (argv);
}

static char	**get_path_array(char **my_envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (my_envp[i] && ft_strncmp(my_envp[i], "PATH=", 5) != 0)
		i++;
	if (!my_envp[i])
		return (NULL);
	paths = ft_split(my_envp[i] + 5, ':');
	return (paths);
}

char	*find_command_path(char *cmd, char **my_envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !my_envp)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_path_array(my_envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_gnl(full_path, cmd,
				ft_strlen(full_path), ft_strlen(cmd));
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
