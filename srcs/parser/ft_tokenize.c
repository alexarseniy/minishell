/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:04:29 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/01 19:52:41 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*ft_tokenize(char *cmd)
{
	// 1 separar la entrada en palabras
		//cada palabra esta delimitada por espacios, operaciones de redireccion, pipes. Los espacios dentro de las comillas se debe de ignorar
		// EJEMPLOS:
		//	WORD1 WORD2 WORD3
		// WORD1<WORD2 o WORD1 < WORD2
		// WORD1>WORD2 o WORD1 > WORD2
		// WORD1<<del WORD2
		// WORD1 << del WORD2
		// WORD1>>WORD2
		// WORD1 >> WORD2
	// comprobar el tipo de cada palabra
		// Si es espacio, no se tiene en cuennta, solo separa tokens
		// si es comilla, todo lo que haya dentro, sera una unica palabra
		// las redirecciones tambien son separadores
	// clasificar cada palabra
		// e_tkn_type enum
	
	// Para realizar todo lo anterior, se revisara la entrada caracter por caracter hasta encontrar 
	t_token	*tkn;
	int		i;

	if (!cmd)
		return (NULL);
	tkn = NULL;
	while (cmd[i])
	{
		if (ft_is_not_sep(cmd[i]))
			i++;
		else
		{
			
		}
	}
}

void	ft_free_tokens(t_tokens *tokens)
{
	t_token	*aux;
	while (token)
	{
		aux = tokens;
		tokens = tokens->next;
		aux->next = NULL;
		free(aux->token);
		free(aux);
		aux = NULL;
	}
}
