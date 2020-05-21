/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:37:52 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/16 15:40:41 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>

char			*getlocalip(void)
{
	struct hostent	*host;
	char						*hostname;
	char						**addr;

	if (!(hostname = getenv("HOSTNAME")))
	{
		ft_putendl_fd("Error: HOSTNAME not set", 2);
		return (0);
	}
	if (!(host = gethostbyname(hostname)))
	{
		ft_putendl_fd("Error: gethostbyname cant resolv HOSTNAME", 2);
		return (0);
	}
	addr = host->h_addr_list;
	int i = -1;
	while(addr[++i])
		fprintf(stderr, "addr[%d] = [%s]\n", i,inet_ntoa(*(struct in_addr*)addr[i]));
	return (inet_ntoa(*(struct in_addr*)*addr));
}

char			*getip(char *hostname)
{
	struct hostent	*host;
	char						**addr;

	if (!(host = gethostbyname(hostname)))
	{
		ft_putendl_fd("Error: gethostbyname cant resolv HOSTNAME", 2);
		return (0);
	}
	addr = host->h_addr_list;
	int i = -1;
	while(addr[++i])
		fprintf(stderr, "addr[%d] = [%s]\n", i,inet_ntoa(*(struct in_addr*)addr[i]));
	return (inet_ntoa(*(struct in_addr*)*addr));
}
