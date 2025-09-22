/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:39:28 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/15 01:31:52 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char	*nptr)
{
	int		result;
	int		sign;
	char	*ptr_aux;

	result = 0;
	sign = 1;
	ptr_aux = (char *)nptr;
	while (ft_isspace(*ptr_aux))
		ptr_aux++;
	if (*ptr_aux == '-')
		sign = -1;
	if (*ptr_aux == '-' || *ptr_aux == '+')
		ptr_aux++;
	while (*ptr_aux && ft_isdigit(*ptr_aux))
		result = result * 10 + (*ptr_aux++ - '0');
	return (result * sign);
}
