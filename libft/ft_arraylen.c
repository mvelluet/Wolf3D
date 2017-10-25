/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 12:30:44 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/25 16:36:29 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraylen(char **array)
{
	int		len;

	len = 0;
	if (!array)
		return (0);
	while (array[len])
		len++;
	return (len);
}
