/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:43:13 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/05 01:34:43 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <netdb.h>
# include <unistd.h>
# include <sys/types.h>
# include <netinet/ip.h>
# include <netinet/ip6.h>
# include <netinet/icmp6.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h>
# include <sys/socket.h>
# include <arpa/inet.h>

unsigned short						checksum(unsigned short *addr, int len);
void								update_icmp_seq6(void);
int									ft_sleep(int second);
int									init_ping(char *dsthost);
void								send_packet(int sign);
void								send_packet6(int sign);
int									init_myping(void);
void								stop_ping(void);
void								clear_myping(void);
char								*ft_getopt(char **args);
int									resolv_addrs(char *dsthost);
int									fill_hdrs4(void);
int									fill_hdrs6(void);
int									request_socket4(void);
int									request_socket6(void);
int									fill_content(void);
int									pingloop(void);
void								update_icmp_seq(void);
void								signal_(void);
float								diff_timeval_now(struct timeval first);
void								print_ping(float time_diff);
void								print_ping6(float time_diff);
int									getip(char *hostname,
			struct addrinfo **result);
uint16_t							icmp6_checksum (struct ip6_hdr iphdr,
			struct icmp6_hdr icmp6hdr, uint8_t *payload, int payloadlen);

typedef struct								s_option
{
	int								ttl;
	int								f;
	int								ip6;
	int								v;
}											t_option;

/*
** int						socket; // My socket
** struct addrin*dst_ai; // Destination address get with getaddrinfo
** void					*datagram; // DATAGRAM TO SEND
** char					*dstname; // DSTNAME FOR STOP_PING
** char					*dstaddr; // DSTADDR FOR STOP_PING
** struct timevainit_tv; // TIME at the start of ping
** int						p_count[3]; // [0] : send ;
** [1] : rcv ; [2] : error
** t_list				*ltime; // Liste de time pour avg/min/max etc
** t_option			opt; // Option de la cli
** struct timevat_send; // timeval before send, for PINGLOOP
** int						t_count; // timeval for stop_ping
** char					*fromaddr; // FROMADDR FOR PINGLOOP
** char							rcv_buff[4096]; // BUFFER
** FILLED BY RECVMSG FOR PINGLOOP
*/

typedef struct								s_ping
{
	int								socket;
	struct addrinfo					*dst_ai;
	void							*datagram;
	char							*dstname;
	char							*dstaddr;
	struct timeval					init_tv;
	double							p_count[3];
	t_list							*ltime;
	t_option						opt;
	struct timeval					t_send;
	int								t_count;
	char							*fromaddr;
	char							rcv_buff[4096];
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
//struct							s_ip6
//{
//	int			vtf;
//};

/*
** ICMP (ipv4) HEADER DEFINE
** For modify icmp for ipv4 header easily.
*/

# define ICMPHDR_TYPE				ICMP_ECHO
# define ICMPHDR_CODE				0
# define ICMPHDR_ID					42
# define ICMPHDR_SEQ				1

/*
** IPv4 HEADER DEFINE
** For modify ipv4 header easily.
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
# define PACKETLEN				84

# define PACKET6LEN				44

# ifndef MYPING
#  define MYPING

t_ping 			*g_myping;

# endif

#endif
