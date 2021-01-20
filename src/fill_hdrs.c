/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hdrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 20:05:24 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:17:09 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <stdio.h>

unsigned short			checksum(unsigned short *addr, int len)
{
	int							nleft;
	int							sum;
	unsigned short				*w;
	unsigned short				answer;

	answer = 0;
	w = addr;
	sum = 0;
	nleft = len;
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= sizeof(unsigned short);
	}
	if (nleft == 1)
	{
		*(unsigned char*)(&answer) = *(unsigned char*)w;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}

int						fill_hdrs6(void)
{
	struct ip6_hdr		*iphdr;
	struct icmp6_hdr	*icmphdr;

	iphdr = (struct ip6_hdr *)(g_myping->datagram);
	icmphdr = (struct icmp6_hdr*)(g_myping->datagram + IPHDRLEN);
	iphdr->ip6_flow = 0;
	iphdr->ip6_plen = 0;
	iphdr->ip6_nxt = 0;
	!g_myping->opt.ttl ? (iphdr->ip6_hops = IPHDR_TTL) :
		(iphdr->ip6_hops = (char)g_myping->opt.ttl);
	iphdr->ip6_src = (struct in6_addr)
		((struct sockaddr_in6*)g_myping->dst_ai->ai_addr)->sin6_addr;
	iphdr->ip6_dst = (struct in6_addr)
		((struct sockaddr_in6*)g_myping->dst_ai->ai_addr)->sin6_addr;
	icmphdr->icmp6_type = ICMP6_ECHO_REQUEST;
	icmphdr->icmp6_code = 0;
	icmphdr->icmp6_id = getpid();
	icmphdr->icmp6_seq = 0;
	icmphdr->icmp6_cksum = icmp6_checksum(*iphdr, *icmphdr,
			(uint8_t*)(g_myping->datagram + ICMPHDRLEN), ICMPHDRLEN + DATALEN);
	return (0);
}

int						fill_hdrs4(void)
{
	((struct ip *)g_myping->datagram)->ip_v = 4;
	((struct ip *)g_myping->datagram)->ip_hl = 5;
	((struct ip *)g_myping->datagram)->ip_tos = 0;
	((struct ip *)g_myping->datagram)->ip_len = IPHDRLEN + ICMPHDRLEN;
	((struct ip *)g_myping->datagram)->ip_id = getpid();
	((struct ip *)g_myping->datagram)->ip_off = 64;
	((struct ip *)g_myping->datagram)->ip_p = IPHDR_PROTO;
	((struct ip *)g_myping->datagram)->ip_sum = 0;
	((struct ip *)g_myping->datagram)->ip_dst = (struct in_addr)
		((struct sockaddr_in*)g_myping->dst_ai->ai_addr)->sin_addr;
	(((struct ip *)g_myping->datagram)->ip_ttl =
		(g_myping->opt.ttl ? (char)g_myping->opt.ttl : IPHDR_TTL));
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_type = ICMPHDR_TYPE;
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_code = ICMPHDR_CODE;
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_id = getpid();
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_seq = 0;
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_cksum = 0;
	((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_cksum =
		checksum((unsigned short*)((struct icmp*)(g_myping->datagram
				+ IPHDRLEN)), ICMPHDRLEN + DATALEN);
	return (0);
}
