/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:28:59 by ylarhris          #+#    #+#             */
/*   Updated: 2023/02/08 09:23:21 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// searching the path

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
	return(NULL);
}

char	*ft_path(char *cmd, char **env)
{
	char	*path;
	char	*paths;
	char	**splited;
	int		i = 0;
	int		acce;

	paths = ft_paths(env);
	if (!paths)
		exit (127);
	splited = ft_split(paths, ':');
	while (splited[i])
	{
		path = ft_strjoin(ft_strjoin(splited[i],"/") ,cmd);
		if(access(path,X_OK) == 0)
			return (path);
		i++;		
	}
	write(2, "command not found\n",19);
	exit(127);
}

void	execution(char *cmd, char *path)
{
	
}
