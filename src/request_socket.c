/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_socket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:33:56 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:18:48 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <stdio.h>

/*
** Ouverture du socket raw
** need root privilege
** Setsockopt pour que le noyau n'ajoute pas de header IP, falcultatif
** avec IPPROTO_ICMP
** Optval non-zero for enable boolean option. (man)
*/

static int				socketerror(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (-1);
}

int						request_socket6(void)
{
	if ((g_myping->socket = socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6)) < 0)
		return (socketerror("socket raw v6 return an error\nAre you root ?\n"));
	return (0);
}

int						request_socket4(void)
{
	int			optval;
	int			filt;
	struct timeval		tv;

	filt = ~((1 << ICMP_SOURCE_QUENCH) |
		(1 << ICMP_DEST_UNREACH) |
		(1 << ICMP_TIME_EXCEEDED) |
		(1 << ICMP_PARAMETERPROB) |
		(1 << ICMP_REDIRECT) |
		(1 << ICMP_ECHOREPLY));
	if ((g_myping->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		return (socketerror("socket raw return an error\nAre you root ?\n"));
	optval = 1;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (setsockopt(g_myping->socket, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int))
		|| setsockopt(g_myping->socket, SOL_RAW, 1, &filt, sizeof(filt)) == -1
		|| setsockopt(g_myping->socket, (g_myping->opt.ip6 ?
			IPPROTO_IPV6 : IPPROTO_IP), SO_RCVTIMEO, (void*)&tv,
			sizeof(struct timeval)))
		return (socketerror("setsockopt return an error"));
	return (0);
}
