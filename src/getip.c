/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:37:52 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:17:21 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <stdio.h>

int				getip(char *hostname, struct addrinfo **result)
{
	struct addrinfo				*hints;

	if (!(hints = (struct addrinfo*)malloc(sizeof(struct addrinfo))))
		return (-1);
	hints->ai_family = (g_myping->opt.ip6 ? AF_INET6 : AF_INET);
	hints->ai_socktype = SOCK_DGRAM;
	hints->ai_flags = 0;
	hints->ai_protocol = 0;
	if (getaddrinfo(hostname, 0, hints, result) != 0)
	{
		ft_putendl_fd("Could not resolv hostname", 2);
		free(hints);
		return (-1);
	}
	free(hints);
	return (0);
}
