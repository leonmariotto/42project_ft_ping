/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_socket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:33:56 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/26 17:10:36 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>

int						request_socket(void)
{
	int optval;
	/*
	** Ouverture du socket raw
	** need root privilege
	*/
	if ((myping->socket = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP)) < 0)
	{
		ft_putendl_fd("socket return an error", 2);
		return (1);
	}
	/*
	** Setsockopt pour que le noyau n'ajoute pas de header IP, falcultatif
	** avec IPPROTO_ICMP
	*/
  if (setsockopt(myping->socket,IPPROTO_IP,IP_HDRINCL,&optval,sizeof(int)))
	{
		ft_putendl_fd("setsockopt return an error", 2);
		return (-1);
	}
	return (0);
}
