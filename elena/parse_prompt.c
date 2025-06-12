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

void	parse_and_execute_prompt(char *prompt)
{
	char	*cleaned;
	t_token	*command;
	int		fd_in;
	int		fd_out;
	t_token	*node;

	cleaned = ft_strtrim(prompt, "\t\n\v\f\r");  // RESERVA MEMORIA CUIDADO !!!!
	if (!cleaned || cleaned[0] == '\0')
	{
		if (cleaned)
			free(cleaned);
		return;
	}
	check_quotes(cleaned); //Checkea que las comillas estén bien cerradas (tanto simples como dobles), si no lo están lanza la siguiente línea para que se cierren
	command = tokenizer(cleaned); // RESERVA MEMORIA, CUIDADO !!!: Rellena los tokens como nodos de la lista
	free(cleaned);
	node = command;
	while (*node)
	{
		if (!ft_strcmp (command->value, ">") || !ft_strcmp(command->value ">>"))
			fd_out = save_output(command); // Abrimos el archivo de salida en modo truncamiento o append dependiendo de la comilla 
		if (!ft_strcmp (command->value, "<") || !ft_strcmp (command->value, "<<"))
			fd_in = save_input(command); // Tanto < como << crean ficheros !! Super importante. Save_input una vez parseado lo que viene después de la redirección 
		 									//devuelve fd del input. 
		if (!ft_strcmp (command->value, "|"))
			return (exec_pipe(command, fd_in, fd_out)) // Si hay pipe ejecutamos pipex
		*node = node->next;
	}
	exec_command(command, fd_in, fd_out); // Si no hay pipe ejecutamos comando normal. 
	ft_error_exec();
}