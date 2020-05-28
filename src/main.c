/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 17:36:22 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/26 15:13:07 by lmariott         ###   ########.fr       */
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
	//struct ip							*iphdr;
	//struct icmp						*icmphdr;
	//char									*packet;
	//char									*buffer;
	//char									*content;
	//int										sock;
	//char									*addrdst;
	//char									*addrsrc;
	//struct sockaddr_in		dst;
	//struct sockaddr_in		src;
	//int optval;
	int r;

	//fprintf(stderr, "sizeof unigned short int : %d\n", (int)sizeof(unsigned short int));
	//fprintf(stderr, "sizeof struct ip : %d\n", (int)sizeof(struct ip));
	//fprintf(stderr, "sizeof struct icmp : %d\n", (int)sizeof(struct icmp));
	//fprintf(stderr, "sizeof struct icmphdr : %d\n", (int)sizeof(struct icmphdr));
  if (ac != 2)
		return (print_usage());
	if (init_ping(av[1]) < 0)
		return (1);
	signal_();

	//// Initialisation des structures.
  //packet  = (char*)ft_memalloc(sizeof(struct ip) + sizeof(struct icmp) + 36);
  //buffer  = (char*)ft_memalloc(sizeof(struct ip) + sizeof(struct icmp) + 36);
  //iphdr = (struct ip*)packet;
  //icmphdr = (struct icmp*)(packet + sizeof(struct ip));
	//content = (char*)(packet + sizeof(struct ip) + sizeof(struct icmp));

	//// Obtenir les adresses
	//if (!(addrdst = ft_strdup(getip(av[1])))
	//		|| !(addrsrc = ft_strdup(getlocalip())))
	//		return (1);
	//// fprintf(stderr, "addrdst = [%s]\naddrsrc = [%s]\n", addrdst, addrsrc);

	//// Initialisation de dst (TO) pour sendTO
	//dst.sin_family = AF_INET;
	//if (!(dst.sin_addr.s_addr = inet_addr(addrdst)))	
	//	return (1);
	//// Initialisation de src (TO) pour sendTO
	//src.sin_family = AF_INET;
	//if (!(src.sin_addr.s_addr = inet_addr(addrsrc)))	
	//	return (1);

//// On remplis content
	//int j = -1;
	//while (++j < 36)
	//	content[j] = 'B';
	//// On remplit les structures.
	//if (fill_iphdr(&iphdr, dst, src)
	//	|| fill_icmphdr(&icmphdr))
	//	return (1);
	//iphdr->ip_sum = checksum((unsigned short*)iphdr,
	//														sizeof(struct ip) + 36);

	//// Ouverture du socket, need root id
	//if ((sock = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP)) < 0)
	//{
	//	ft_putendl_fd("socket return an error", 2);
	//	perror("socket");
	//	return (1);
	//}
	//// Setsockopt, pourquoi ????
  //setsockopt(sock,IPPROTO_IP,IP_HDRINCL,&optval,sizeof(int)); 

	//// Print les valeurs de packet
	//// Pourquoi ces valeurs sont differentes de celle de tcpdump ?
	//printf("len = %d\n", iphdr->ip_len);
	//int i;
  //for ( i=0; i < IPHDRLEN+ICMPHDRLEN+DATALEN;i++)
	//	printf("%.2X ",*((char*)myping->datagram + i));
	//printf("\n");

	// send le packet echo request
	printf("PING %s (%s) %d(%d) bytes of data.\n", myping->dstname,
				 myping->dstaddr,
				 DATALEN + ICMPHDRLEN,
				 DATALEN + ICMPHDRLEN + IPHDRLEN);
	if (pingloop() < 0)
		return (1);
	r = sendto(myping->socket,myping->datagram, IPHDRLEN + ICMPHDRLEN + DATALEN, 0,
						 myping->dst_ai->ai_addr, myping->dst_ai->ai_addrlen);
  if (r <= 0)
    ft_putendl_fd("sendto call return an error", 2);

	// recv echo response
	//socklen_t sizerecvfrom;
	//sizerecvfrom = htons(sizeof(struct sockaddr));
	//r = recvfrom(sock, buffer, sizeof(struct ip) + sizeof(struct icmp) + 36,
	//						 0 , dst_ai->ai_addr, dst_ai->ai_addrlen);
  //if (r <= 0)
  //  ft_putendl_fd("recvfrom call return an error", 2);

  //for ( i=0; i < (int)(sizeof(struct ip)+sizeof(struct icmp));i++)
	//	printf("%.2X ",*(buffer+i));
	//printf("\n");
  return (0);
}
