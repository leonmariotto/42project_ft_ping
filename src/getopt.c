/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 00:21:07 by lmariott          #+#    #+#             */
/*   Updated: 2020/07/02 12:01:36 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char				*ft_getopt(char **args)
{
	int i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] != '-')
		{
			if (args[i + 1])
				return (NULL);
			return (args[i]);
		}
		else if (args[i][1] == 't')
		{
			if (ft_isdigit(*args[++i]) && ft_atoi(args[i]) > 0
					&& ft_atoi(args[i]) < 256)
				myping->opt.ttl = ft_atoi(args[i]);
			else
			{
				ft_putendl_fd("ft_ping: can't set unicast time-to-live: \
Invalid argument", 2);
				return (NULL);
			}
		}
		else if (args[i][1] == '6')
		{
			myping->opt.ip6 = 1;
		}
		else if (args[i][1] == 'v')
		{
			myping->opt.v = 1;
		}
		else if (args[i][1] == 'p')
		{
			if (ft_isdigit(*args[++i]) && ft_atoi(args[i]) > 0
					&& ft_atoi(args[i]) < 256)
				myping->opt.f = ft_atoi(args[i]);
			else
			{
				ft_putendl_fd("ft_ping: can't set unicast time-to-live: \
Invalid argument", 2);
				return (NULL);
			}
		}
	}
	return (NULL);
}
