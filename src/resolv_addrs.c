/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_addrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 19:54:29 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/27 23:09:20 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int					resolv_addrs(char *dsthost)
{
	if (getip(dsthost, &myping->dst_ai) < 0)
		return (-1);
	/*
	** IPV6 ?
	** Parcourir dst_ai s'arreter sur la bonne (la premiere si aucun forcage est spécifié.)
	** Ne plus utiliser AF_INET mais myping->dst_ai->ai_family
	*/
	inet_ntop(AF_INET, (const void *)&((struct sockaddr_in*)
						myping->dst_ai->ai_addr)->sin_addr,
						myping->dstaddr, 35);
	return (0);
}
