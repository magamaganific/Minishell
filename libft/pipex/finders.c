/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:04:32 by mfornovi          #+#    #+#             */
/*   Updated: 2025/03/11 13:04:40 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_findpath(char **paths, char *cmd)
{
	char	*pth;
	char	*res;
	char	*box;

	pth = NULL;
	res = NULL;
	box = NULL;
	while (*paths)
	{
		pth = ft_strjoin(*paths, "/");
		box = ft_strjoin(pth, cmd);
		if (access(box, R_OK) != -1)
		{
			res = ft_strdup(pth);
			return (free(pth), free(box), res);
		}
		free(pth);
		free(box);
		pth = NULL;
		box = NULL;
		paths++;
	}
	return ("");
}

char	*ft_findbin(char *av, char **env)
{
	char	**split;
	char	**paths;
	char	*bin;

	bin = NULL;
	paths = NULL;
	split = ft_split(av, ' ');
	while (*env != NULL)
	{
		if (ft_strncmp("PATH", *env, 4) == 0)
		{
			paths = ft_split(*env, ':');
			bin = ft_findpath(paths, split[0]);
			ft_freer(paths);
			ft_freer(split);
			return (bin);
		}
		env++;
	}
	return (bin);
}
