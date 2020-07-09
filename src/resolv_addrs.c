/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_addrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 19:54:29 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/29 22:52:50 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int					resolv_addrs(char *dsthost)
{
	if (getip(dsthost, &myping->dst_ai) < 0)
		return (-1);

	inet_ntop((myping->opt.ip6 ? AF_INET6 : AF_INET), (const void *)&((struct sockaddr_in*)
						myping->dst_ai->ai_addr)->sin_addr,
						myping->dstaddr, 35);
	return (0);
}
