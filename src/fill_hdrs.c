/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hdrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 20:05:24 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/25 20:23:47 by lmariott         ###   ########.fr       */
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
	myping->iphdr->ip_v = IPHDR_VERSION;
	myping->iphdr->ip_hl = IPHDR_HL;
	myping->iphdr->ip_tos = IPHDR_TOS;
	myping->iphdr->ip_len = IPHDRLEN + ICMPHDRLEN;
	myping->iphdr->ip_id = htons(getuid());
	myping->iphdr->ip_ttl = IPHDR_TTL;
	myping->iphdr->ip_off = htons(1 << 14);
	myping->iphdr->ip_p = IPHDR_PROTO;
	myping->iphdr->ip_sum = 0;
	//myping->iphdr->ip_src = myping->src_ai->ai_addr;
	myping->iphdr->ip_dst = (struct in_addr)
							((struct sockaddr_in*)myping->dst_ai->ai_addr)->sin_addr;
	//myping->iphdr->ip_src = (struct in_addr)
							//((struct sockaddr_in*)myping->dst_ai->ai_addr)->sin_addr;
	//myping->icmphdr->type = 255;// ICMPHDR_TYPE;
	//myping->icmphdr->code = ICMPHDR_CODE;
	//myping->icmphdr->un.echo.id = ICMPHDR_ID;
	//myping->icmphdr->un.echo.sequence = ICMPHDR_SEQ;
	//myping->icmphdr->checksum = 0;
	//myping->icmphdr->checksum = checksum((unsigned short*)myping->icmphdr,
	//															ICMPHDRLEN + DATALEN);
	// struct icmp version
	myping->icmphdr->icmp_type = ICMPHDR_TYPE;
	myping->icmphdr->icmp_code = ICMPHDR_CODE;
	myping->icmphdr->icmp_id = htons(ICMPHDR_ID);
	myping->icmphdr->icmp_seq= htons(ICMPHDR_SEQ);
	myping->icmphdr->icmp_cksum = 0;
	myping->icmphdr->icmp_cksum = checksum((unsigned short*)myping->icmphdr,
																ICMPHDRLEN + DATALEN);
	//myping->iphdr->ip_sum = checksum((unsigned short*)myping->iphdr,
//															IPHDRLEN + ICMPHDRLEN + DATALEN);
	return (0);
}
