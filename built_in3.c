/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:57:09 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/26 18:57:10 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_unset(t_exec_unit *unit, char ***my_envp)
{
	t_token	*curr;

	curr = unit->start;
	if (curr && curr->value && !ft_strncmp(curr->value, "unset", 6))
		curr = curr->next;
	while (curr)
	{
		if (!ft_strchr(curr->value, '='))
			*my_envp = remove_variable(*my_envp, curr->value);
		curr = curr->next;
	}
	g_signal.ret = 0;
	return (1);
}

int	validate_cd_args(t_token *arg)
{
	t_token	*tmp;
	int		arg_count;

	tmp = arg;
	arg_count = 0;
	while (tmp)
	{
		arg_count++;
		tmp = tmp->next;
	}
	if (arg_count == 0)
	{
		ft_putstr_fd("minishell: cd: missing argument\n", 2);
		return (1);
	}
	if (arg_count > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	built_in_cd(t_exec_unit *unit, char ***my_envp)
{
	t_token	*arg;
	char	*new_path;
	char	*pwd_var;

	arg = unit->start;
	if (arg && arg->value && !strcmp(arg->value, "cd"))
		arg = arg->next;
	if (validate_cd_args(arg) != 0)
		return (1);
	if (chdir(arg->value) != 0)
		return (perror("minishell: cd"), 1);
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (perror("cd (getcwd)"), 1);
	pwd_var = ft_strjoin("PWD=", new_path);
	free(new_path);
	if (!pwd_var)
		return (1);
	export_variable(my_envp, pwd_var);
	free(pwd_var);
	g_signal.ret = 0;
	return (1);
}
