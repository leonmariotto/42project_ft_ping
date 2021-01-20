/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 00:21:07 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:17:33 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <stdio.h>

static int		isargvalid(char **args, int i, char opt)
{
	if (ft_isdigit(*args[i]) && ft_atoi(args[i]) > 0
			&& ft_atoi(args[i]) < 256)
	{
		if (opt == 't')
			g_myping->opt.ttl = ft_atoi(args[i]);
		else if (opt == 'p')
			g_myping->opt.f = ft_atoi(args[i]);
		return (1);
	}
	else
	{
		ft_putendl_fd("ft_ping: Invalid argument", 2);
		return (0);
	}
}

static int		ping_help(void)
{
	ft_putendl("Usage: ft_ping [-vh] [-t ttl] [-p pattern] destination");
	ft_putendl("Usage: ft_ping -6 [-vh] [-t ttl] [-p pattern] destination");
	return (0);
}

static int		whicharg(char **args, int i)
{
	if (args[i][1] == 't')
		return (isargvalid(args, ++i, 't'));
	else if (args[i][1] == '6')
		return ((g_myping->opt.ip6 = 1));
	else if (args[i][1] == 'v')
		return ((g_myping->opt.v = 1));
	else if (args[i][1] == 'p')
		return (isargvalid(args, ++i, 'p'));
	else if (args[i][1] == 'h')
		return (ping_help());
	else
	{
		printf("ft_ping: Unknown opt : %c\n", args[i][1]);
		return (0);
	}
}

char			*ft_getopt(char **args)
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
		if (!whicharg(args, i))
			return (NULL);
	}
	return (NULL);
}
