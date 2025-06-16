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

	while (line[i]) // Importante: al comparar con bash este no interpreta comillas simples o doble si ya están dentro de otras comillas simples o dobles
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
	if (!ft_strncmp(node->next->value, ">", 2) || !ft_strncmp(node->next->value, ">>", 3) ||
		!ft_strncmp(node->next->value, "<", 2) || !ft_strncmp(node->next->value, "<<", 3) || !ft_strncmp(node->next->value, "|", 2))
	{
		error_syntax(node->next->value);
		return (-1);
	}
	// Apertura válida
	if (!ft_strncmp(node->value, ">", 1))
		fd_out = open(node->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd_out = open(node->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	// Error al abrir el archivo
	if (fd_out < 0)
		perror("minishell");
	return (fd_out);
}

int handle_heredoc(t_token *node)
{
	int		fd_in;
	char	*line;
	const char *filename;
	
	filename = "/tmp/.heredoc_tmp"; // En este fichero temporar voy a guardar las lineas que escriba, porque gracias a eso la funcion puede deolveme en ambs casos un filedesciptor
	fd_in = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_in < 0) // Esto no deberia pasar pero por si acaso. 
	{
		perror("minishell");
		return (-1);
	}
	while (1)
	{
		line = readline("> "); // Volvemos a llamar a la funció realine para que salga por debajo la linea nueva 
		if (!line || !ft_strncmp(line, node->next->value, 1))
		{
			free(line);
			break;
		}
		write(fd_in, line, ft_strlen(line)); // Escribimos en el file temporal las lineas (la idea es que esto luego funcione como un archivo normal para cualquier comando)
		write(fd_in, "\n", 1);
		free(line);
	}
	close(fd_in);
	fd_in = open(filename, O_RDONLY);
	if (fd_in < 0)
		perror("minishell");
	return (fd_in);
}

int save_input(t_token *node)
{
	int	fd_in;

	fd_in = -2;
	if (!node->next)  // Error sintaxis
		return (error_syntax("newline"), -1);

	if (!ft_strncmp(node->next->value, ">", 2) || !ft_strncmp(node->next->value, ">>", 3) ||  //Error sintaxis.
		!ft_strncmp(node->next->value, "<", 2) || !ft_strncmp(node->next->value, "<<", 3) ||
		!ft_strncmp(node->next->value, "|", 2))
		return (error_syntax(node->next->value), -1);

	if (!ft_strncmp(node->value, "<", 2))
	{
		fd_in = open(node->next->value, O_RDONLY); // Abrimos el archivo!!
		if (fd_in < 0) // Si el archivo no existe devolvemos el mismo mensaje de error que bash
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->next->value, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2); 
			ft_putstr_fd("\n", 2);
		}
		return (fd_in);
	}
	else if (!ft_strncmp(node->value, "<<", 3)) // Si hay doble redireccion hay qe abrir el heredoc. 
		return (handle_heredoc(node));

	return (fd_in);
}

void	parse_and_execute_prompt(char *prompt)
{
	char	*cleaned;
	t_token	*command;
	int		fd_in;
	int		fd_out;
	t_token	*node;

	fd_in = -2;
	fd_out = -2;
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
	relativize_zones(command, cleaned);
	free(cleaned);  // :)
	node = command; 
	// A partir de aquí solo está reservada la memoria de la lista de tokens (liberar en pipex o en exec_command con free_token_list).  
	while (node)
	{
		if (!ft_strncmp(node->value, ">", 2) || !ft_strncmp(node->value, ">>", 3))
			fd_out = save_output(node); // Abrimos el archivo de salida en modo truncamiento o append dependiendo del operador
		if (!ft_strncmp(node->value, "<", 2) || !ft_strncmp(node->value, "<<", 3))
			fd_in = save_input(node);  // Tanto < como << crean ficheros !! Super importante. Save_input, una vez parseado lo que viene después de la redirección,
									   // devuelve fd del input. En el caso de << lo que ocurre es que escribimos el contenido en un archivo temporal con nombre aleatorio.
		if (!ft_strncmp(node->value, "|", 2))
			return ; //exec_pipe(command, fd_in, fd_out) ); // Si hay pipe ejecutamos pipex directamente pasando toda la lista
		if (fd_in == -1 || fd_out == -1)
			break;
		node = node->next;
	}
	ft_putnbr_fd(fd_in, 1);
	ft_putnbr_fd(fd_out, 1);
	return ;
	//exec_command(command, fd_in, fd_out); // Si no hay pipe ejecutamos comando normal.
	//ft_error_exec(); // En caso de error durante la ejecución
}

