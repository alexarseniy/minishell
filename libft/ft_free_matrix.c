/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:33:05 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/09 02:30:27 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_free_matrix(void **matrix, void (ft_special_free)(void **var))
{
	int	i;

	if (!matrix)
		return (-1);
	if (ft_special_free)
		ft_special_free(matrix);
	else
	{
		i = 0;
		while (matrix[i])
		{
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
	}
	return (0);
}
