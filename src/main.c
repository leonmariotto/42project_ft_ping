/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 17:36:22 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:13:55 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "myping.h"
#include <stdio.h>

int				main(int ac, char **av)
{
	char			*host;

	(void)ac;
	if (init_myping() < 0)
		return (1);
	if (!(host = ft_getopt(&av[1])))
		return (1);
	if (init_ping(host) < 0)
		return (1);
	signal_();
	printf("PING %s (%s) %d(%d) bytes of data.\n", g_myping->dstname,
		g_myping->dstaddr,
		DATALEN + ICMPHDRLEN,
		DATALEN + ICMPHDRLEN + IPHDRLEN);
	if (pingloop() < 0)
		return (1);
	return (0);
}
