/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 18:07:19 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:18:35 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <stdio.h>

void							print_ping(float time_diff)
{
	int type;

	type = (int)((struct icmp*)(g_myping->rcv_buff + IPHDRLEN))->icmp_type;
	if (type != ICMP_ECHOREPLY)
		g_myping->p_count[2]++;
	else
		g_myping->p_count[1]++;
	if (type != ICMP_ECHOREPLY || g_myping->opt.v)
	{
		printf("From %s: icmp_seq=%-3d type=%d code=%d\n",
			g_myping->fromaddr,
			((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_seq,
			type,
			(int)((struct icmp*)(g_myping->rcv_buff + IPHDRLEN))->icmp_code);
	}
	else
	{
		printf("%d bytes from %s: icmp_seq=%-3d ttl=%d time=%f ms\n",
			DATALEN + ICMPHDRLEN,
			g_myping->fromaddr,
			((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_seq,
			((struct ip*)g_myping->rcv_buff)->ip_ttl,
			time_diff);
	}
}

void							print_ping6(float time_diff)
{
	struct icmp6_hdr *icmphdr;

	icmphdr = (struct icmp6_hdr*)(g_myping->rcv_buff);
	if (icmphdr->icmp6_type != ICMP6_ECHO_REPLY)
		g_myping->p_count[2]++;
	else
		g_myping->p_count[1]++;
	if (icmphdr->icmp6_type != ICMP6_ECHO_REPLY || g_myping->opt.v)
	{
		printf("From %s: icmp_seq=%-3d type=%d code=%d\n",
				g_myping->fromaddr,
				((struct icmp6_hdr*)(g_myping->datagram + IPHDRLEN))->icmp6_seq,
				icmphdr->icmp6_type,
				icmphdr->icmp6_code);
	}
	else
	{
		printf("%d bytes from %s: icmp_seq=%-3d time=%f ms\n",
				DATALEN + ICMPHDRLEN,
				g_myping->fromaddr,
				icmphdr->icmp6_seq,
				time_diff);
	}
}
