/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:42:33 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/12 10:42:34 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//// TODOS LOS VALUES DEL TOKEN LLEVAN ASOCIADAS RESERVAS DE MEMORIA !!!! CUIDADO !!!!

int is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int is_quote(char c)
{
	return (c == '"' || c == '\'');
}

t_zone *create_zone(int start, int end, int expandable) // Creo el nodo con la zona 
{
	t_zone *zone;

	zone = malloc(sizeof(t_zone));
	if (!zone)
		return (NULL);
	zone->start = start+1; // Para saltarme la comilla del principio (ya he indicado si era expandible o no)
	zone->end = end-1; // Para saltarme la comilla del final
	zone->expandable = expandable;
	zone->next = NULL;
	return (zone);
}

void add_zone(t_token *token, t_zone *zone) // Añado el nodo al final de la lista 
{
	t_zone *curr;

	if (!token->zones)
		token->zones = zone;
	else
	{
		curr = token->zones;
		while (curr->next)
			curr = curr->next;
		curr->next = zone;
	}
}

char *extract_token_value(char *str, int start, int end) /*importante*/
{
	char *substr;

	substr = ft_substr(str, start, end - start);
	return (substr);
}

t_token *new_token(char *str, int start, int end) /*importante*/
{
	t_token *tok;

	tok = malloc(sizeof(t_token)); //Creo nodo 
	if (!tok)
		return (NULL);
	tok->value = extract_token_value(str, start, end); //Extraigo subcaden
	tok->zones = NULL;
	tok->next = NULL;
	return (tok);
}

int process_quoted_zone(char *str, int *i, t_token *tok) //Hay que pasar i como puntero para que se conserve su valor tras el paso por la función. 
{
	char quote;
	int start;
	int expandable;

	quote = str[*i];  //Guardo el tipo de comilla 
	start = *i; //Posición inicial de la zona entrecomillada
	expandable = 0;
	if (quote == '"')
		expandable = 1; //Así indico que en esa zona debo expandir variables si las encuentro. 
	(*i)++;
	while (str[*i] && str[*i] != quote) // Avanzo hasta cierre de comilla.
		(*i)++;
	if (str[*i] == quote)
	{
		add_zone(tok, create_zone(start, *i, expandable)); //Añado la zona (la región entrecomillada)
		(*i)++;
	}
	return (*i);
}

int find_token_end(char *str, int i)
{
	char quote;

	while (str[i] && str[i] != ' ' && !is_metachar(str[i]))
	{
		if (is_quote(str[i])) //Tengo que tener en cuenta si está entre comillas o no. Si está entre comillas sigo avanzando hasta que se cierren. 
		{
			quote = str[i]; // Con esto indico si es comilla simple o comilla doble (me ahorro tener que declarar una variable para cada)
			i++;
			while (str[i] && str[i] != quote) //Avanzo hasta encontrar la comilla de cierre. 
				i++;
			if (str[i]) // Una posición más porque me interesa mantener la comilla de cierrre (siempre que no haya un '\0' despúes de ella)
				i++;
		}
		else  // Si no hay coillas simplemente avanzo hasta espacio o metacaracter
			i++;
	}
	return (i); //Ahora sé la posición donde terminar el token, ya puedo extraer la subcaena. 
}

void append_token(t_token **head, t_token *new_tok)
{
	t_token *curr;

	if (!*head) //Para el caso en el que la lista no está inicializada y es el primer nodo. 
		*head = new_tok;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_tok;
	}
}

t_token *tokenizer(char *cleaned) /*importante*/
{
	t_token *tokens;
	t_token *tok;
	int i;
	int start;

	i = 0;
	tokens = NULL;
	while (cleaned[i])
	{
		while (cleaned[i] == ' ') // Me salto los espacios iniciales y si hay varios espacios juntos entre medias
			i++;
		if (!cleaned[i]) //Para el caso en el que sólo haya espacios
			break;
		if (is_metachar(cleaned[i])) // Este if es para crear un token que sea solo el metacaracter
		{
			start = i;
			i++;   // Me voy a la posición siguiente
			if ((cleaned[start] == '<' || cleaned[start] == '>') && cleaned[i] == cleaned[start]) // Si es << >> salto dos posiciones
				i++;
			tok = new_token(cleaned, start, i); //Creo el token: start = posicion del metachar, i siguiente posición (o siguiente siguiente si >> o <<)
			append_token(&tokens, tok); // lo pongo al final de la lista
			continue; // Paso a siguiente iteración
		}
		start = i;
		tok = new_token(cleaned, start, find_token_end(cleaned, i)); //con find token end voy a avanzar hasta encontras espacio o metacaracter
		if (!tok) //Por si falla el malloc
			return (NULL);
		while (i < find_token_end(cleaned, start)) //Este bucle es para extraer zonas en caso de que haya comillas. 
		{
			if (is_quote(cleaned[i]))
				process_quoted_zone(cleaned, &i, tok);
			else
				i++;
		}
		append_token(&tokens, tok); // Añado el token al final de la lista. 
	}
	return (tokens);
}



#include <stdio.h>
#include <stdlib.h>

void	relativize_zones(t_token *tokens, char *cleaned) // Esta función pone el start y el end de las zonas en función del token, no del prompt. 
{
	t_token	*curr;
	char	*base;
	t_zone	*zone;
	char	*pos;
	int		diff;

	curr = tokens;
	base = cleaned;
	while (curr)
	{
		zone = curr->zones; // Apunto al primer nodo de la lista de zonas. 
		pos = ft_strnstr(cleaned, curr->value, ft_strlen(base)); // Apunto a donde empiezan las comillas en mi prompt
		if (!pos) // Si no hubiera zonas, porque no ha comillas. 
		{
			curr = curr->next; 
			continue;
		}
		diff = pos - base; // Posición en la frase (se la tengo que restar para expresarla respecto a 0.)
		while (zone)
		{
			zone->start = zone->start - diff;
			zone->end = zone->end - diff;
			zone = zone->next;
		}
		curr = curr->next;
	}
}


void	print_zones(t_zone *zones, char *token_value)
{
	while (zones)
	{
		printf("\t[ZONE] start: %d, end: %d, expandable: %d\n",
			zones->start, zones->end, zones->expandable);
		printf("\t       --> content: \"");
		for (int i = zones->start; i < zones->end+1; i++)
			putchar(token_value[i]);
		printf("\"\n");
		zones = zones->next;
	}
}

void	print_tokens(t_token *tokens)
{
	int index = 0;
	while (tokens)
	{
		printf("[TOKEN %d] value: \"%s\"\n", index, tokens->value);
		if (tokens->zones)
			print_zones(tokens->zones, tokens->value);
		tokens = tokens->next;
		index++;
	}
}

void	free_zones(t_zone *zone)
{
	t_zone	*tmp;

	while (zone)
	{
		tmp = zone->next;
		free(zone);
		zone = tmp;
	}
}

void	free_token_list(t_token *command)
{
	t_token	*tmp;

	while (command)
	{
		tmp = command->next;
		free(command->value);
		free_zones(command->zones);
		free(command);
		command = tmp;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*p1;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	p1 = malloc(len + 1);
	if (!p1)
		return (NULL);
	while (i < len)
	{
		p1[i] = s[i];
		i++;
	}
	p1[i] = '\0';
	return (p1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && j < len)
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}


char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < n)
	{
		j = 0;
		while (little[j] && (i + j) < n && big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

int main(void)
{
	char *test_cases[] = {
		// Caso de prueba original complejo
		"echo \"Hola que tal\"$USER'$USER' | grep 'Ele' > outfile >>hola \"lets'gooo' >ahora no redirige\" > \"pero ahora sii\"",

		// Casos más complicados
		"echo \"$USER's profile\" >>file | cat <'data input'",
		"echo \"Inicio\"$MIDDLE'Fin'|grep \"pattern>'a'\" >> salida",
		"cmd1 < input1 | cmd2 \"text$VAR>'a'\" > 'output final'",
		"echo \"double'quoted'word\" 'single\"quoted\"part' | tee result",
		"echo 'quote>\"test\"' \"quote<'test'\" | sort > file",
		"ls -l | grep \"Jan 01\" >> log$DATE'tmp'",
		"echo \"$USER\"\"'$USER'\"'$HOME'",
		"echo \"start'$VAR'end\">file",
		"cmd arg1 \">>\" '<<' | another > 'file name with spaces.txt'",
		"echo 'Unmatched quote test > still counts' >>file"
	};

	int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
	for (int i = 0; i < num_cases; i++)
	{
		printf("=======================================================================\n");
		printf("CASO %d:\n%s\n", i + 1, test_cases[i]);
		printf("=======================================================================\n");
		printf ("\n");
		t_token *tokens = tokenizer(test_cases);
		if (!tokens)
		{
			fprintf(stderr, "Error al tokenizar el input");
			continue;
		}
		relativize_zones(tokens, test_cases);
		print_tokens(tokens);
		free_token_list(tokens);
		printf ("\n\n");
	}
	return (0);
}
