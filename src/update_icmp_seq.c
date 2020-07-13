/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_icmp_seq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:20:51 by lmariott          #+#    #+#             */
/*   Updated: 2020/07/13 12:51:30 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>

void					update_icmp_seq(void)
{
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_seq += 1;
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_cksum = 0;
	((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_cksum = checksum((unsigned short*)((struct icmp*)(myping->datagram + IPHDRLEN)),
																ICMPHDRLEN + DATALEN);
}
