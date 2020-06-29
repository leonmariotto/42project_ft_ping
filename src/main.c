/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 17:36:22 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/29 21:20:27 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>

int				print_usage(void)
{
	ft_putendl("ft_ping usage : ft_ping <hostname>");
	return (1);
}

int       main(int ac, char **av)
{
	char			*host;

	(void)ac;
	if (init_myping() < 0)
		return (1);
	if (!(host = ft_getopt(&av[1])))
	{
		print_usage();
		return (1);
	}
	if (init_ping(host) < 0)
		return (1);
	signal_();

	printf("PING %s (%s) %d(%d) bytes of data.\n", myping->dstname,
				 myping->dstaddr,
				 DATALEN + ICMPHDRLEN,
				 DATALEN + ICMPHDRLEN + IPHDRLEN);
	if (pingloop() < 0)
		return (1);
  return (0);
}
