/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hdrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 20:05:24 by lmariott          #+#    #+#             */
/*   Updated: 2020/07/13 12:49:36 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>

unsigned short			checksum(unsigned short *addr, int len)
{
  int nleft;
  int sum;
  unsigned short *w;
  unsigned short answer;

	answer = 0;
	w = addr;
	sum = 0;
	nleft = len;
  while (nleft > 1)
	{
    sum += *w++;
    nleft -= sizeof (unsigned short);
  }
  if (nleft == 1)
	{
    *(unsigned char *) (&answer) = *(unsigned char *) w;
    sum += answer;
  }
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  answer = ~sum;
  return (answer);
}

int				fill_hdrs(void)
{
	// Todo make IPV6 compatible
	// TODO htons forbidden, remove it
	if (myping->opt.ip6)
	{
		/* IPv6 header */
		//iphdr = (struct ip6_hdr *) &out_packet_buffer[0] ;
		
		/* IPv6 version (4 bits), Traffic class (8 bits), Flow label (20 bits) */
		//iphdr->ip6_flow = htonl ((6 << 28) | (0 << 20) | 0); /* Next header (8 bits): 44 for Frag */ iphdr->ip6_nxt = 44;
		
		/* Hop limit (8 bits): default to maximum value */
		//iphdr->ip6_hops = 255;
		
		/* src address */
		//bcopy(&srcaddr->sin6_addr,&(iphdr->ip6_src), 16) ;
		
		/* dst address */
		//bcopy(&cliaddr->sin6_addr,&(iphdr->ip6_dst), 16);
	}
	((struct ip *)myping->datagram)->ip_v = 4;
	((struct ip *)myping->datagram)->ip_hl = 5;
	((struct ip *)myping->datagram)->ip_tos = 0;
	((struct ip *)myping->datagram)->ip_len = IPHDRLEN + ICMPHDRLEN;
	((struct ip *)myping->datagram)->ip_id = htons(getpid());
	((struct ip *)myping->datagram)->ip_off = htons(1 << 14);
	((struct ip *)myping->datagram)->ip_p = IPHDR_PROTO;
	((struct ip *)myping->datagram)->ip_sum = 0;
	((struct ip *)myping->datagram)->ip_dst = (struct in_addr)
							((struct sockaddr_in*)myping->dst_ai->ai_addr)->sin_addr;
	//myping->iphdr->ip_src = (struct in_addr)
							//((struct sockaddr_in*)myping->dst_ai->ai_addr)->sin_addr;
	!myping->opt.ttl ? (((struct ip *)myping->datagram)->ip_ttl = IPHDR_TTL) :
(((struct ip *)myping->datagram)->ip_ttl = (char)myping->opt.ttl);
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_type = ICMPHDR_TYPE;
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_code = ICMPHDR_CODE;
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_id = htons(getpid());
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_seq= 0;
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_cksum = 0;
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_cksum = checksum((unsigned short*)((struct icmp*)(myping->datagram + IPHDRLEN)),
																ICMPHDRLEN + DATALEN);
	return (0);
}
