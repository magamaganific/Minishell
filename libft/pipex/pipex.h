/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:09:47 by mfornovi          #+#    #+#             */
/*   Updated: 2025/03/10 09:10:42 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft.h"
#include "../ft_printf/ft_printf.h"
#include <fcntl.h>

void	ft_closer(int in_fd, int *pipefd);
void	ft_errorman(char *mess);
char	**ft_mkargs(char *av, char **env);
char	*ft_findpath(char **paths, char *cmd);
char	*ft_findbin(char *av, char **env);
void	ft_freer(char **arr);