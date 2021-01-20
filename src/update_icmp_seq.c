/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_icmp_seq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:20:51 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:19:52 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <stdio.h>

void					update_icmp_seq(void)
{
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_seq += 1;
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_cksum = 0;
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_cksum =
		checksum((unsigned short*)((struct icmp*)(g_myping->datagram +
		IPHDRLEN)), ICMPHDRLEN + DATALEN);
}

void					update_icmp_seq6(void)
{
	((struct icmp6_hdr*)(g_myping->datagram + IPHDRLEN))->icmp6_seq += 1;
	((struct icmp6_hdr*)(g_myping->datagram + IPHDRLEN))->icmp6_cksum = 0;
	((struct icmp6_hdr*)(g_myping->datagram + IPHDRLEN))->icmp6_cksum =
					checksum((unsigned short*)((struct icmp6_hdr*)
					(g_myping->datagram + IPHDRLEN)), ICMPHDRLEN + DATALEN);
}
