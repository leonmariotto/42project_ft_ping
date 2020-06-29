/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:43:13 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/29 21:20:13 by lmariott         ###   ########.fr       */
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

//char							*getlocalip(void);
//char							*getip(char *hostname);
unsigned short			checksum(unsigned short *addr, int len);
int									ft_sleep(int second);
int									init_ping(char *dsthost);
int									init_myping(void);
void								stop_ping(void);
void								clear_myping(void);
char								*ft_getopt(char **args);
int									resolv_addrs(char *dsthost);
int									fill_hdrs(void);
int									request_socket(void);
int									fill_content(void);
int									pingloop(void);
void								update_icmp_seq(void);
void								signal_(void);
float								diff_timeval_now(struct timeval first);
int									getip(char *hostname, struct addrinfo **result);

typedef struct				s_option
{
	int								ttl;
	int								f;
	int								ip6;
}											t_option;

typedef struct				s_ping
{
	int								socket; // Mon socket RAW
	struct addrinfo		*dst_ai; // Address de destination obtenu avec getaddrinfo
	void							*datagram; // DATAGRAM TO SEND
	struct ip					*iphdr; // HEADER IP
	struct icmp				*icmphdr; // HEADER ICMP
	char							*content; // DATA
	char							*dstname; // DSTNAME FOR STOP_PING
	char							*dstaddr; // DSTADDR FOR STOP_PING
	struct timeval		init_tv; // TIME au lancement de ping
	int								p_count[3]; // [0] : send ; [1] : rcv ; [2] : error
	t_list						*ltime; // Liste de time pour avg/min/max etc
	t_option					opt; // Option de la cli
	struct timeval		t_send; // timeval before send, for PINGLOOP
	char							*fromaddr; // FROMADDR FOR PINGLOOP
//	void							*rcv_buff; // BUFFER FILLED BY RECVMSG FOR PINGLOOP
	char							rcv_buff[4096]; // BUFFER FILLED BY RECVMSG FOR PINGLOOP
}											t_ping;

/*
** First 32 bits :
**	- Version						4 bits version = 6
**	- Traffic Class			8 bits traffic class field
**	- Flow label				20 bits fields
** Second 32 bits :
**	- Payload lenght		16 bits unsigned integer
**	- Next header				8 bit selector
**	- Hop limit					8 bit unsigned integer
** Then :
** Source address				128 bits
** Destination address	128 bits
*/
struct							s_ip6
{
	int			vtf;
};

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
