/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:03:21 by fcil              #+#    #+#             */
/*   Updated: 2022/08/16 15:19:50 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

void	signalint_func(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

//ilk olarak alt satıra geçer.
//rl replace line ile şu anki satırı temizler
//rl_on_new_line genellikle satır koyduktan sonra yeni satıra geçtiğimizi söyler.
// rl_redisplay() ile buffer da kalanlar sıfırlanır
