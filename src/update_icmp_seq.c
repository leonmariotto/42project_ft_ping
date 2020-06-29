/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_icmp_seq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 21:20:51 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/23 08:37:18 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>

void					update_icmp_seq(void)
{
	myping->icmphdr->icmp_seq += 1;
	myping->icmphdr->icmp_cksum = 0;
	myping->icmphdr->icmp_cksum = checksum((unsigned short*)myping->icmphdr,
																ICMPHDRLEN + DATALEN);
}
