/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hdr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 01:07:55 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/19 18:28:14 by lmariott         ###   ########.fr       */
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
	fprintf(stderr, "answer(int) = %d\n", (int)answer);
  return (answer);
}

int						fill_iphdr(struct ip **iphdr, struct sockaddr_in dst,
													struct sockaddr_in src)
{
	(*iphdr)->ip_v = 4;
	(*iphdr)->ip_hl = 5;
	(*iphdr)->ip_tos = 0;
	(*iphdr)->ip_len = sizeof(struct ip) + sizeof(struct icmp);
	(*iphdr)->ip_id = htons(getuid());
	(*iphdr)->ip_ttl = 255;
	(*iphdr)->ip_p = IPPROTO_ICMP;
	(*iphdr)->ip_sum = 0;
	(*iphdr)->ip_src = src.sin_addr;
	(*iphdr)->ip_dst = dst.sin_addr;
	return (0);
}

int						fill_icmphdr(struct icmp **icmphdr)
{
	(*icmphdr)->icmp_type = ICMP_ECHO;
	(*icmphdr)->icmp_code = 2;
	(*icmphdr)->icmp_id = 20;
	(*icmphdr)->icmp_seq = htons(42);
	(*icmphdr)->icmp_cksum = 0;
	(*icmphdr)->icmp_cksum = checksum((unsigned short*)*icmphdr,
															sizeof(struct icmp) + 38);
	return (0);
}
