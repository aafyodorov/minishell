/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:13:06 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/04 23:30:51 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

#define	BUF_REDIR 10

int		g_fd[2];
int		g_pipe[2];
int		g_pipe_status[2];

void	read_to_stdin(char ***args);

void	close_stdin_stdout(char *file);
void	open_stdin_stdout(void);

void	redirect_1(char *func);
void	redirect_2(char *func);
void	redirect_3(char *file_name);
void	redirect_4(char *file_name);
void	redirect_5(char *func);

void	redirect_1_close(void);
void	redirect_2_close(void);
void	redirect_3_close(void);
void	redirect_4_close(void);
void	redirect_5_close(void);

#endif
