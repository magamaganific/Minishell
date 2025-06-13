/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:22:30 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/11 11:22:32 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
--------WORKFLOW---------

1. Elimino espacios al inicio y al final 
2. Checkeo que las comillas simples y dobles están bien cerradas. 
3. Tokenizamos: Hacemos una lista en la que cada nodo es el comando, sus argumentos, y cualquier cosa introducida en el prompt
-> Se tienen en cuenta las comillas dobles y las comillas simples (no cortar en espacios si aparecen)
4. Abrimos fichero de salida 8es lo primero que gestiona bash, lo aprendí en el pipex
5. Abrimos fichero de entrada, incluyendo la posibilidad de que lo ponga como una lista por pantalla hasta EOF (<<)
6. Si hay pipe ejecutamos pipex
7. Si no hay pipe ejecutamos como comando simple 

*/

#include "minishell.h"

int	check_quotes(char *line)
{
	int	squote = 0;
	int	dquote = 0;
	int	i = 0;

	while (line[i]) // Importante: al comparar con bash este no interpreta comillas simples o doble ssi ya están dentro de otras comillas simples o dobles
					// Por eso en los ifs se tiene en cuenta que " no esté en comilla simple y ' no esté en comilla doble (&& squote, &&dquote)
	{
		if (line[i] == '"' && squote == 0)
		{
			if (dquote == 0)
				dquote = 1;
			else
				dquote = 0;
		}
		else if (line[i] == '\'' && dquote == 0)
		{
			if (squote == 0)
				squote = 1;
			else
				squote = 0;
		}
		i++;
	}
	if (squote == 1 || dquote == 1)
		return (0);
	return (1);
}

int	save_output(t_token *node)
{
	int	fd_out;
	// Error: no hay nada después del operador de redirección
	if (!node->next)
	{
		error_syntax("newline");
		return (-1);
	}
	// Error: lo que viene después es otro operador no válido
	if (!ft_strcmp(node->next->value, ">") || !ft_strcmp(node->next->value, ">>") ||
		!ft_strcmp(node->next->value, "<") || !ft_strcmp(node->next->value, "<<") || !ft_strcmp(node->next->value, "|"))
	{
		error_syntax(node->next->value);
		return (-1);
	}
	// Apertura válida
	if (!ft_strcmp(node->value, ">"))
		fd_out = open(node->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd_out = open(node->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	// Error al abrir el archivo
	if (fd_out < 0)
		perror("minishell");
	return (fd_out);
}

int		save_input (t_token *node)
{
	int	fd_in;

	if (!ft_strcmp(node->value, ">"))
		fd_in = 
}

void	parse_and_execute_prompt(char *prompt)
{
	char	*cleaned;
	t_token	*command;
	int		fd_in = STDIN_FILENO;
	int		fd_out = STDOUT_FILENO;
	t_token	*node;

	cleaned = ft_strtrim(prompt, "\t\n\v\f\r"); // RESERVA MEMORIA CUIDADO !!!! :)
	if (!cleaned || cleaned[0] == '\0')
	{
		if (cleaned)
			free(cleaned);
		return;
	}
	if (!check_quotes(cleaned))
		return (error_bad_quoting()); // Checkea que las comillas estén bien cerradas (tanto simples como dobles), si no lo están lanza la siguiente línea para que se cierren
	command = tokenizer(cleaned); // RESERVA MEMORIA, CUIDADO !!!: Rellena los tokens como nodos de la lista
	relativize_zones(command);
	free(cleaned);  // :)
	node = command; 
	// A partir de aquí solo está reservada la memoria de la lista de tokens (liberar en pipex o en exec_command con free_token_list).  
	while (node)
	{
		if (!ft_strcmp(node->value, ">") || !ft_strcmp(node->value, ">>"))
			fd_out = save_output(node); // Abrimos el archivo de salida en modo truncamiento o append dependiendo del operador
		if (!ft_strcmp(node->value, "<") || !ft_strcmp(node->value, "<<"))
			fd_in = save_input(node);  // Tanto < como << crean ficheros !! Super importante. Save_input, una vez parseado lo que viene después de la redirección,
									   // devuelve fd del input. En el caso de << lo que ocurre es que escribimos el contenido en un archivo temporal con nombre aleatorio.
		if (!ft_strcmp(node->value, "|"))
			return (exec_pipe(command, fd_in, fd_out)); // Si hay pipe ejecutamos pipex directamente pasando toda la lista
		node = node->next;
	}
	exec_command(command, fd_in, fd_out); // Si no hay pipe ejecutamos comando normal.
	ft_error_exec(); // En caso de error durante la ejecución
}

