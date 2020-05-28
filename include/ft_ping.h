/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:43:13 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/26 17:32:15 by lmariott         ###   ########.fr       */
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

//char					*getlocalip(void);
//char					*getip(char *hostname);
unsigned short			checksum(unsigned short *addr, int len);

int				init_ping(char *dsthost);
void			stop_ping(void);
void			clear_myping(void);
int				resolv_addrs(char *dsthost);
int				fill_hdrs(void);
int				request_socket(void);
int				fill_content(void);
int				pingloop(void);
void			update_icmp_seq(void);
void			signal_(void);

int				getip(char *hostname, struct addrinfo **result);

typedef struct				s_ping
{
	int								socket;
	struct addrinfo		*dst_ai;
	void							*datagram;
	struct ip					*iphdr;
	struct icmp				*icmphdr;
	char							*content;
	char							*dstname;
	char							*dstaddr;
	unsigned long int	npsend;
	unsigned long int nprcv;
	long int					init_tv;
}											t_ping;

# ifndef MYPING
#  define MYPING

t_ping *myping;

# endif

/*
** ICMP HEADER DEFINE
** TO MODIFY THE HEADER ICMP
*/

# define ICMPHDR_TYPE				ICMP_ECHO
# define ICMPHDR_CODE				0
# define ICMPHDR_ID					42
# define ICMPHDR_SEQ				1

/*
** IP HEADER DEFINE
** TO MODIFY THE HEADER ICMP
*/

# define IPHDR_VERSION		4
# define IPHDR_HL					5
# define IPHDR_OFF				IP_DF
# define IPHDR_TOS				0
# define IPHDR_SEQ				0
# define IPHDR_TTL				64
# define IPHDR_PROTO			IPPROTO_ICMP

/*
** PACKET SIZE
*/

# define IPHDRLEN					20
# define ICMPHDRLEN				24
# define DATALEN					40

//int				getip(struct addrinfo **result)
//int						fill_icmphdr(struct icmp **icmphdr);
//int						fill_iphdr(struct ip **iphdr, struct sockaddr_in dst,
//													struct sockaddr_in src);
//unsigned short			checksum(unsigned short *addr, int len);

#endif
