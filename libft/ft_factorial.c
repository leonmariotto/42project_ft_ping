/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llenotre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:33:46 by llenotre          #+#    #+#             */
/*   Updated: 2018/11/13 20:20:36 by llenotre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_factorial(int n)
{
	if (n < 0 || n > 12)
		return (0);
	if (n == 0 || n == 1)
		return (1);
	return (n * ft_factorial(n - 1));
}
