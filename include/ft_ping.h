/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:43:13 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/19 17:25:50 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <netdb.h>
#	include <unistd.h>
#	include <sys/types.h>
#	include <netinet/ip.h> // struct ip
# include <netinet/in.h>
#	include <netinet/ip_icmp.h> // struct icmp
# include <sys/socket.h>
# include <arpa/inet.h>

char					*getlocalip(void);
char					*getip(char *hostname);
int						fill_icmphdr(struct icmp **icmphdr);
int						fill_iphdr(struct ip **iphdr, struct sockaddr_in dst,
													struct sockaddr_in src);
unsigned short			checksum(unsigned short *addr, int len);

#endif
