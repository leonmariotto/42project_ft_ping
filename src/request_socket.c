/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_socket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:33:56 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/27 22:11:08 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>

/*
** Ouverture du socket raw
** need root privilege
*/

/*
** Setsockopt pour que le noyau n'ajoute pas de header IP, falcultatif
** avec IPPROTO_ICMP
** Optval non-zero for enable boolean option. (man)
*/

int						request_socket(void)
{
	int										optval;
	int										filt;
	struct timeval				tv;

	filt = ~((1<<ICMP_SOURCE_QUENCH)|
			      (1<<ICMP_DEST_UNREACH)|
			      (1<<ICMP_TIME_EXCEEDED)|
			      (1<<ICMP_PARAMETERPROB)|
			      (1<<ICMP_REDIRECT)|
			      (1<<ICMP_ECHOREPLY));
	if ((myping->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		ft_putendl_fd("socket return an error\nAre you root ?\n", 2);
		return (-1);
	}
	optval = 1;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
  if (setsockopt(myping->socket, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int))
			|| setsockopt(myping->socket, SOL_RAW, 1, &filt, sizeof filt) == -1
			|| setsockopt(myping->socket, IPPROTO_IP, SO_RCVTIMEO, (void*)&tv, sizeof(struct timeval)))
	{
		ft_putendl_fd("setsockopt return an error", 2);
		return (-1);
	}
	return (0);
}
