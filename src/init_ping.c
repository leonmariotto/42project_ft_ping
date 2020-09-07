/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 19:45:06 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/07 11:59:51 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <stdio.h>

/*
** Step 1 : Resolv addrs
** Step 2 : Fill headers
** Step 3 : Request socket
** Step 4 : Set socket options.
*/

int					init_ping(char *dsthost)
{
	if (!(g_myping->dstname = ft_strdup(dsthost)))
		return (-1);
	if (resolv_addrs(dsthost) < 0)
		return (-1);
	if (fill_content() < 0)
		return (-1);
	if (g_myping->opt.ip6)
	{
		if (fill_hdrs6() < 0)
			return (-1);
		if (request_socket6() < 0)
			return (-1);
	}
	else
	{
		if (fill_hdrs4() < 0)
			return (-1);
		if (request_socket4() < 0)
			return (-1);
	}
	return (0);
}

int					init_myping(void)
{
	if (!(g_myping = (t_ping*)ft_memalloc(sizeof(t_ping)))
			|| !(g_myping->datagram = ft_memalloc(IPHDRLEN + ICMPHDRLEN
					+ DATALEN))
			|| !(g_myping->dstaddr = ft_strnew(INET6_ADDRSTRLEN))
			|| !(g_myping->fromaddr = ft_strnew(INET6_ADDRSTRLEN)))
	{
		ft_putendl_fd("malloc call return an error", 2);
		return (-1);
	}
	gettimeofday(&g_myping->init_tv, NULL);
	return (0);
}
