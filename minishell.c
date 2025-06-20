/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:31:21 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/11 10:31:22 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (int argc, char **argv)
{
	char	*prompt;
	
	if (argc != 1 || argv[1])
		return (1);
	while (1)
	{
		prompt = readline("minishell$ ");
		if (!prompt) // Esto puede suceder en dos casos: si hay un error de reserva con malloc o si se ha pulsado ctrl_d sin escribir nada;
			break;	// Nota: al comparar con bash, si en bash pulsas CTRLD sin escribir nada es equivalente a un exit y te saca de la shell
					// pero si pulsas ctrlD en mitad de un prompt no hace nada. 
		add_history(prompt);
		parse_and_execute_prompt(prompt); 
		free(prompt);
	}
	clear_history();
	return (0);
}

