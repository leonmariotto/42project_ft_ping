/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:40:17 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/27 16:37:51 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int					fill_content(void)
{
	int j;

	j = -1;
	while (++j < DATALEN)
	{
		if (!myping->opt.f)
			myping->content[j] = 16 + j;
		else
			myping->content[j] = myping->opt.f;
	}
	return (0);
}
