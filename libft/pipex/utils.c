/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:40:30 by mfornovi          #+#    #+#             */
/*   Updated: 2025/03/10 09:11:58 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_closer(int in_fd, int *pipefd)
{
	close(in_fd);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	ft_errorman(char *mess)
{
	perror(mess);
	exit(0);
}

char	**ft_mkargs(char *av, char	**env)
{
	char const	*bin;
	char		*args;
	char		**split;

	bin = NULL;
	split = NULL;
	args = NULL;
	if (ft_strlen(av) > 0)
	{
		split = ft_split(av, ' ');
		if (access(split[0], R_OK) != -1 || !split)
			return (split);
		ft_freer(split);
		bin = ft_findbin(av, env);
		args = ft_strjoin(bin, av);
		split = ft_split(args, ' ');
		return (free(args), split);
	}
	exit (0);
}
