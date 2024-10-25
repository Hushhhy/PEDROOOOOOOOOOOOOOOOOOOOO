/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:53:51 by codespace         #+#    #+#             */
/*   Updated: 2024/10/20 18:54:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_and_close(int fd, int std_fd)
{
	if (fd != -1)
	{
		if (dup2(fd, std_fd) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(fd);
	}
}

void	_maybe_fd_closing(int fd)
{
	if (fd != -1)
		close(fd);
}
