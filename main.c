/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:18:13 by ylarhris          #+#    #+#             */
/*   Updated: 2023/02/10 20:04:06 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	pid_t	child[2];
	int		t[2];
	int		status;

	pipe(t);
	if (ac != 5)
		write(1, "Bad Arguments", 14);
	else
	{
		child[0] = fork();
		if (!child[0])
			firstchild(av, t, env);
		else
		{
			child[1] = fork();
			if (!child[1])
				secondchild(av, t, env);
		}
	}
	close(t[1]);
	close(t[0]);
	waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
	exit_status(status);
}
