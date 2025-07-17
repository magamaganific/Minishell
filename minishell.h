/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:22:41 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/11 11:22:43 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include "libft/libft.h"
# include <fcntl.h> 
# include <sys/wait.h>

/*  -------- ESTRUCTURAS --------*/

typedef struct s_signal
{
	int	ret;
	int	ret_exit;
	int	sig;
	int	ff;
}	t_signal;

extern t_signal	g_signal;

typedef struct s_zone
{
	int				start;
	int				end;
	int				expandable;
	struct s_zone	*next;
}	t_zone;

typedef struct s_token
{
	char			*value;
	t_zone			*zones;
	struct s_token	*next;
}	t_token;

typedef struct s_exec_unit
{
	t_token	*start;
	int		fdin;
	int		fdout;
	int		has_pipe_after;
}	t_exec_unit;

/* --------- PARSEO --------- */
int			check_quotes(char *line);
int			is_metachar(char c);
int			is_quote(char c);
t_zone		*create_zone(int start, int end, int expandable);
void		add_zone(t_token *token, t_zone *zone);
char		*extract_token_value(char *str, int start, int end);
t_token		*new_token(char *str, int start, int end);
int			process_quoted_zone(char *str, int *i, t_token *tok);
int			find_token_end(char *str, int i);
void		append_token(t_token **head, t_token *new_tok);
t_token		*tokenizer(char *cleaned);
void		relativize_zones(t_token *tokens, char *cleaned);
int			save_output(t_token *node);
int			save_input(t_token *node);
int			handle_heredoc(t_token *node);
void		clean_tokens(t_token *tokens);
int			is_invalid_redirect(char *value);
char		*ft_strjoin_gnl(char *s1, char *s2, size_t len1, size_t len2);
void		expand_variables(t_token *command, char **my_envp);
char		**copy_env(char **envp);
void		extract_variable_name(t_token *node, char **my_envp);
int			is_in_zones(int i, t_zone *zone);
int			find_variable(t_token *node, int i, char **my_envp);
void		replace_variable(t_token *node, int i, int j, char *replacement);
char		*my_get_envp(char *variable, char **my_envp);
int			add_variables_to_envp(t_token *command, char ***my_envp);
char		**add_variable(char *addition, char **my_envp);
int			not_in_zones(int i, t_zone *zone);
int			in_token(char *value, char s);
int			count_strings(char **envp);
int			is_redirection(t_token *token);

/* -------------- EJECUCIÓN ------------*/
void		parse_and_execute_prompt(char *prompt, char ***envp);
void		execute_units_with_pipes(t_exec_unit *units, char **envp);
void		exec_simple_command(t_token *start, char **envp);
char		*find_command_path(char *cmd, char **envp);
char		**build_argv(t_token *start);
int			count_args(t_token *start);
int			handle_redirections(t_token *start, int *fdin, int *fdout);
t_exec_unit	*split_into_exec_units(t_token *command);
int			count_exec_units(t_token *command);

/* --------- ERRORES ----------*/
void		error_bad_quoting(void);
void		error_syntax(char *unexpected);

/* ---------- LIBERACIÓN DE MEMORIA ---------------*/
void		free_token_list(t_token *command);
void		free_zones(t_zone *zone);
void		free_split(char **split);
void		free_exec_units(t_exec_unit *units);
void		free_env(char **env);

/* -----------BUILT INS -------------------------*/
int			execute_built_in(t_exec_unit *units, char ***my_envp);
int			built_in_unset(t_exec_unit *unit, char ***my_envp);
char		**remove_variable(char **my_envp, const char *varname);
int			built_in_export(t_exec_unit *unit, char ***my_envp);
int			export_variable(char ***my_envp, const char *new_var);
int			built_in_cd(t_exec_unit *unit, char ***my_envp);
int			built_in_env(t_exec_unit *units, char ***my_envp);
int			built_in_echo(t_exec_unit *units);
int			built_in_pwd(t_exec_unit *units);
void		close_fds(t_exec_unit *units);
void		built_in_exit(char *prompt);

/* ----------SIGNALS---------*/

void		ft_handle_int(int sig);
void		handle_signals(void);
void		ft_handle_int_in_p(int sig);
char		*ft_find_ret(void);
void		ft_handle_int_heredoc(int sig);
void		ft_handle_int_empt(int sig);

#endif
