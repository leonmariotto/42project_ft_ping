/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_addrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 19:54:29 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:19:01 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"

int					resolv_addrs(char *dsthost)
{
	if (getip(dsthost, &g_myping->dst_ai) < 0)
		return (-1);
	if (!g_myping->opt.ip6)
		inet_ntop(AF_INET,
			(const void *)&((struct sockaddr_in*)g_myping->
				dst_ai->ai_addr)->sin_addr,
			g_myping->dstaddr, INET_ADDRSTRLEN);
	else
		inet_ntop(AF_INET6,
			(const void *)&((struct sockaddr_in6*)g_myping->
				dst_ai->ai_addr)->sin6_addr,
			g_myping->dstaddr, INET6_ADDRSTRLEN);
	return (0);
}
