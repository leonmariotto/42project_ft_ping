/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_addrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 19:54:29 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/25 20:14:34 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int					resolv_addrs(char *dsthost)
{
	if (getip(dsthost, &myping->dst_ai) < 0)
		return (-1);
	if (!(myping->dstaddr = ft_strnew(35)))
		return (-1);
	/*
	** IPV6 ?
	*/
	inet_ntop(AF_INET, (const void *)&((struct sockaddr_in*)
						myping->dst_ai->ai_addr)->sin_addr,
						myping->dstaddr, 35);
	return (0);
}
