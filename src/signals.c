/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:29:39 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/10 08:27:10 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Captures the sigint and correctly displays a new prompt but need to handle the display of ^C which should not appear
void handle_sigint(int sig)
{
	// if (data->waitpid_res == 0)
	// {
	// write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// }
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

	// return prompt on a new line
}
/*
void handle_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_replace_line("", 0);
		rl_on_new_line();
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
*/

// CTRL + C sends SIGINT
// CTRL + \ sends SIGQUIT
int	handle_sigs(t_data *data)
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
	term.c_lflag &= ~ ECHOCTL;
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
