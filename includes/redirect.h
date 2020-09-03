/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:13:06 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/03 22:13:18 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

int		g_fd[5];
int		g_pipe[2];
int		g_pipe_status[2];


void	close_stdin_stdout(char *file);
void	open_stdin_stdout(void);

void	redirect_1(void);
void	redirect_2(void);
void	redirect_3(void);
void	redirect_4(void);
void	redirect_5(void);

void	redirect_1_close(void);
void	redirect_2_close(void);
void	redirect_3_close(void);
void	redirect_4_close(void);
void	redirect_5_close(void);

#endif
