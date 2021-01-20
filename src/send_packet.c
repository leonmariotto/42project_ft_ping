/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 18:10:32 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:19:15 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <sys/time.h>

/*
** send_packet :
** - Prepare le nouveau packet (nouveau id, checksum, ...)
** - Sauvegarde le icmp_seq, et la timeval
** dans une seule structure dans uneliste chainée.
** - Update p_count[0]
*/

void		send_packet(int sign)
{
	void			*outpack;

	(void)sign;
	update_icmp_seq();
	outpack = g_myping->datagram;
	g_myping->t_count = (int)diff_timeval_now(g_myping->init_tv);
	gettimeofday(&g_myping->t_send, 0);
	g_myping->p_count[0]++;
	sendto(g_myping->socket, outpack, IPHDRLEN + ICMPHDRLEN + DATALEN, 0
		, g_myping->dst_ai->ai_addr, g_myping->dst_ai->ai_addrlen);
	alarm(1);
}

/*
** send_packet6 :
** IPV6 -> j'utilise sendmsg, avec la structure cmsghdr je peux changer le
** hop limit, l'address source est spécifié dans le msghdr.
** On envoie l'icmp + data.
*/

static void	send_packet6end(struct msghdr *msghdr, struct cmsghdr *cmsghdr)
{
	*((int *)CMSG_DATA(cmsghdr)) = (g_myping->opt.ttl ?
		g_myping->opt.ttl : 255);
	g_myping->t_count = (int)diff_timeval_now(g_myping->init_tv);
	gettimeofday(&g_myping->t_send, 0);
	if (sendmsg(g_myping->socket, msghdr, 0) < 0)
	{
		free(msghdr->msg_control);
		ft_putendl_fd("sendmsg return an error", 2);
		alarm(1);
		return ;
	}
	g_myping->p_count[0]++;
	free(msghdr->msg_control);
	alarm(1);
}

void		send_packet6(int sign)
{
	struct msghdr			msghdr;
	struct cmsghdr			*cmsghdr;
	struct iovec			iov[2];
	int						cmsglen;

	(void)sign;
	update_icmp_seq6();
	ft_bzero(&msghdr, sizeof(struct msghdr));
	msghdr.msg_name = (struct sockaddr_in6*)g_myping->dst_ai->ai_addr;
	msghdr.msg_namelen = sizeof(struct sockaddr_in6);
	ft_bzero(&iov, sizeof(iov));
	iov[0].iov_base = (uint8_t *)(g_myping->datagram + IPHDRLEN);
	iov[0].iov_len = ICMPHDRLEN + DATALEN;
	msghdr.msg_iov = iov;
	msghdr.msg_iovlen = 1;
	cmsglen = CMSG_SPACE(sizeof(int));
	if (!(msghdr.msg_control = (struct cmsghdr*)ft_memalloc(cmsglen)))
		return ;
	msghdr.msg_controllen = cmsglen;
	cmsghdr = CMSG_FIRSTHDR(&msghdr);
	cmsghdr->cmsg_level = IPPROTO_IPV6;
	cmsghdr->cmsg_type = IPV6_HOPLIMIT;
	cmsghdr->cmsg_len = CMSG_LEN(sizeof(int));
	send_packet6end(&msghdr, cmsghdr);
}
