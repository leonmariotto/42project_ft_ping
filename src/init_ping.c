/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 19:45:06 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/27 16:53:26 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>

int					init_myping(void)
{
	if (!(myping = (t_ping*)ft_memalloc(sizeof(t_ping)))
			|| !(myping->datagram = ft_memalloc(IPHDRLEN + ICMPHDRLEN + DATALEN))
			|| !(myping->dstaddr = ft_strnew(35))
			|| !(myping->fromaddr = ft_strnew(35)))
	{
		ft_putendl_fd("malloc call return an error", 2);
		return (-1);
	}
	myping->content = (char*)(myping->datagram + IPHDRLEN + ICMPHDRLEN);
	myping->icmphdr = (struct icmp*)(myping->datagram + IPHDRLEN);
	myping->iphdr = (struct ip*)myping->datagram;
	gettimeofday(&myping->init_tv, NULL);
	return (0);
}

/*
** Step 1 : Resolv addrs
** Step 2 : Fill headers
** Step 3 : Request socket
** Step 4 : Set socket options.
*/

int					init_ping(char *dsthost)
{
	if (!(myping->dstname = ft_strdup(dsthost)))
		return (-1);
	if (resolv_addrs(dsthost) < 0)
		return (-1);
	if (fill_content() < 0)
		return (-1);
	if (fill_hdrs() < 0)
		return (-1);
	if (request_socket() < 0)
		return (-1);
	return (0);
}
