/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:13:00 by ylarhris          #+#    #+#             */
/*   Updated: 2023/02/10 20:05:17 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_paths(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*ft_path(char *cmd, char **env)
{
	char	*path;
	char	*paths;
	char	**splited;
	int		i;

	i = 0;
	paths = ft_paths(env);
	if (!paths)
	{
		write (2, "No such file or directory\n", 27);
		exit (127);
	}
	splited = ft_split(paths, ':');
	while (splited[i])
	{
		path = ft_strjoin(ft_strjoin(splited[i], "/"), cmd);
		if (access(path, X_OK | F_OK) == 0)
			return (path);
		i++;
	}
	write(2, "command not found\n", 19);
	exit(127);
	return (NULL);
}

void	firstchild(char **av, int *T, char **env)
{
	int		fd;
	char	*path;
	char	**args;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("");
		exit(127);
	}
	dup2(fd, STDIN_FILENO);
	dup2(T[1], STDOUT_FILENO);
	args = ft_split(av[2], ' ');
	execve(args[0], args, env);
	path = ft_path(args[0], env);
	if (!path)
		exit(127);
	if (execve(path, args, env) == -1)
	{
		write(2, "could not execve", 17);
		exit(127);
	}
	exit(1);
}

void	secondchild(char **av, int *T, char **env)
{
	int		fd;
	char	*path;
	char	**args;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	dup2(T[0], STDIN_FILENO);
	close(T[1]);
	args = ft_split(av[3], ' ');
	execve(args[0], args, env);
	path = ft_path(args[0], env);
	if (!path)
		exit(127);
	if (execve(path, args, env) == -1)
	{
		write(2, "could not execve", 17);
		exit(127);
	}
	exit(0);
}

void	exit_status(int status)
{
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(WTERMSIG(status) + 128);
	exit(0);
}
