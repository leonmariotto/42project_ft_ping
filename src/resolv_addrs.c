/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_addrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 19:54:29 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/04 23:05:31 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int					resolv_addrs(char *dsthost)
{
	if (getip(dsthost, &g_myping->dst_ai) < 0)
		return (-1);
	inet_ntop((g_myping->opt.ip6 ? AF_INET6 : AF_INET),
						(const void *)&((struct sockaddr_in*)
						g_myping->dst_ai->ai_addr)->sin_addr,
						g_myping->dstaddr, 35);
	return (0);
}
