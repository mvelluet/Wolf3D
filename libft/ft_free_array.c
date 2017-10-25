/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 11:41:12 by pribault          #+#    #+#             */
/*   Updated: 2017/10/17 22:18:11 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(void **array, size_t len)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (i < len)
		free(array[i++]);
	free(array);
}
