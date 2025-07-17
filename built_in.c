/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:37:56 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/26 16:37:57 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_variable(char ***my_envp, const char *new_var)
{
	char	*var_name;
	char	*equal_sign;
	int		i;

	equal_sign = ft_strchr(new_var, '=');
	if (!equal_sign)
		return (1);
	var_name = ft_substr(new_var, 0, equal_sign - new_var);
	if (!var_name)
		return (1);
	i = 0;
	while ((*my_envp)[i])
	{
		if (!ft_strncmp((*my_envp)[i], var_name, ft_strlen(var_name)) &&
			(*my_envp)[i][ft_strlen(var_name)] == '=')
		{
			free((*my_envp)[i]);
			(*my_envp)[i] = ft_strdup(new_var);
			free(var_name);
			return (0);
		}
		i++;
	}
	*my_envp = add_variable((char *)new_var, *my_envp);
	return (free(var_name), 0);
}

int	built_in_export(t_exec_unit *unit, char ***my_envp)
{
	t_token	*curr;

	curr = unit->start;
	if (curr && curr->value && !ft_strncmp(curr->value, "export", 7))
		curr = curr->next;
	if (!curr)
		return (0);
	while (curr)
	{
		if (ft_strchr(curr->value, '='))
		{
			if (export_variable(my_envp, curr->value) != 0)
			{
				ft_putstr_fd("minishell: export: memory error\n", 2);
				return (1);
			}
		}
		curr = curr->next;
	}
	g_signal.ret = 0;
	return (1);
}

static	char	**copy_env_excluding_var(char **src, char **dst,
					const char *varname)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (!(ft_strncmp(src[i], varname, ft_strlen(varname)) == 0
				&& src[i][ft_strlen(varname)] == '='))
		{
			dst[j] = ft_strdup(src[i]);
			if (!dst[j])
			{
				free_env(dst);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	dst[j] = NULL;
	return (dst);
}

char	**remove_variable(char **my_envp, const char *varname)
{
	int		count;
	char	**new_envp;

	count = 0;
	while (my_envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	if (copy_env_excluding_var(my_envp, new_envp, varname) == NULL)
		return (NULL);
	free_env(my_envp);
	return (new_envp);
}

int	execute_built_in(t_exec_unit *units, char ***my_envp)
{
	if (units->has_pipe_after == 1)
		return (0);
	if (in_token(units->start->value, '='))
		units->start = units->start->next;
	while (units->start && is_redirection(units->start)
		&& units->start->next->next)
		units->start = units->start->next->next;
	if (!ft_strncmp(units->start->value, "pwd", 4))
		return (built_in_pwd(units));
	else if (!ft_strncmp(units->start->value, "echo", 5))
		return (built_in_echo(units));
	else if (!ft_strncmp(units->start->value, "env", 4))
		return (built_in_env(units, my_envp));
	else if (!ft_strncmp(units->start->value, "cd", 3))
		return (built_in_cd (units, my_envp));
	else if (!ft_strncmp(units->start->value, "unset", 6))
		return (built_in_unset(units, my_envp));
	else if (!ft_strncmp(units->start->value, "export", 7))
		return (built_in_export(units, my_envp));
	else
		return (0);
}
