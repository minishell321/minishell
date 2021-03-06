/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:29:39 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/21 16:20:24 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sig_child(int sig)
{	
	if (sig == SIGINT)
	{
		ft_putstr_fd("^C\n", 2);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: 3\n", 2);
		rl_redisplay();
	}
}

int	handle_sigs_child(void)
{
	struct sigaction	sa_sigint_ch;
	struct sigaction	sa_sigquit_ch;

	sa_sigint_ch.sa_handler = &handle_sig_child;
	sa_sigquit_ch.sa_handler = &handle_sig_child;
	sigaction(SIGINT, &sa_sigint_ch, NULL);
	sigaction(SIGQUIT, &sa_sigquit_ch, NULL);
	return (0);
}

// CTRL + C sends SIGINT
// CTRL + \ sends SIGQUIT
int	handle_sigs(void)
{
	struct termios		term;
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	if (isatty(STDIN_FILENO) != 1 || isatty(STDOUT_FILENO) != 1)
	{
		printf("Error: isatty\n");
		return (1);
	}
	if (tcgetattr(STDIN_FILENO, &term) != 0)
	{
		printf("Error: tcgetattr\n");
		return (1);
	}
	term.c_lflag &= ~ECHOCTL ;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
	{
		printf("Error: tcsetattr\n");
		return (1);
	}
	sa_sigint.sa_handler = &handle_sigint;
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
	return (0);
}
