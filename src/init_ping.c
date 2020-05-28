/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 19:45:06 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/26 17:36:15 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>

static int	init_myping(void)
{
	struct timeval ts;

	if (!(myping = (t_ping*)ft_memalloc(sizeof(t_ping))))
	{
		ft_putendl_fd("malloc call return an error", 2);
		return (-1);
	}
	if (!(myping->datagram = ft_memalloc(IPHDRLEN + ICMPHDRLEN + DATALEN)))
	{
		ft_putendl_fd("malloc call return an error", 2);
		return (-1);
	}
	myping->content = (char*)(myping->datagram + IPHDRLEN + ICMPHDRLEN);
	myping->icmphdr = (struct icmp*)(myping->datagram + IPHDRLEN);
	myping->iphdr = (struct ip*)myping->datagram;
	myping->npsend = 0;
	myping->nprcv = 0;
	gettimeofday(&ts, NULL);
	myping->init_tv = ts.tv_usec;
	return (0);
}

int					init_ping(char *dsthost)
{
	// Step 1 : Resolv addrs
	// Step 2 : Fill headers
	// Step 3 : Request socket
	// Step 4 : Set socket options.

	if (init_myping() < 0)
		return (-1);
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
