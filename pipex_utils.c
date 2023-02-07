/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:58:38 by ylarhris          #+#    #+#             */
/*   Updated: 2023/02/06 06:59:18 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/ylarhris/Desktop/pipex/Libft/libft.h"
#include <stdio.h>
#include<unistd.h>
#include<fcntl.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


static int	ft_wdcount(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i + 1] == '\0' || (str[i] == c && str[i + 1] != c))
			count++;
		i++;
	}
	return (count);
}

static int	ft_lcount(int i, char *str, char sep)
{
	int	count;

	count = 0;
	while (str[i] == sep)
		i++;
	while (str[i] && str[i] != sep)
	{
		count++;
		i++;
	}
	return (count);
}

static char	*ft_filling(char *t__t, char *str, char sep, int i)
{
	int	j;
	int	k;
	int	n;

	j = 0;
	k = 0;
	n = ft_lcount(i, str, sep);
	t__t = (char *) malloc ((n + 1) * sizeof(char));
	if (!t__t)
		return (NULL);
	while (str[i] && k < n)
	{
		t__t [k] = str [i];
		i++;
		k++;
	}
	t__t [k] = '\0';
	return (t__t);
}

void ft_free(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(char *str, char sep)
{
	int		i;
	int		j;
	char	**s_str;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	s_str = (char **) malloc ((ft_wdcount(str, sep) + 1) * sizeof(char *));
	if (!s_str)
		return (NULL);
	while (str[i] && j < ft_wdcount(str, sep))
	{
		while (str[i] == sep)
			i++;
		if (str[i] != sep)
		{
			s_str[j] = ft_filling(s_str[j], str, sep, i);
			if(!s_str[j])
				ft_free(s_str);
			j++;
		}
		i += ft_lcount(i, str, sep);
	}
	s_str[j] = NULL;
	return (s_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*j_str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	j_str = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!j_str)
		return (NULL);
	while (s1[i])
	{
		j_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		j_str[i + j] = s2[j];
		j++;
	}
	j_str[i + j] = '\0';
	return (j_str);
}

char *path(char *cmd, char **env)
{
    int		i;
	char	*tmp;
	char	*str;
	char	**spliit;
	char	*t__t;

	i = 0;
	while(env[i])
	{
		if(strnstr(env[i],"PATH=",5))
			str = env[i] + 5;
		i++;
	}
	spliit = ft_split(str, ':');
	i = 0;
	while (spliit[i])
	{
		tmp = ft_strjoin(spliit[i],"/");
		t__t = ft_strjoin(tmp ,cmd);
		if(access(t__t,X_OK) == 0)
			return (t__t);
		i++;
	}
	return (NULL);
}
void child1(int fd, char **av, char **env)
{
	char **args;
	
	dup2(fd,1);
	args = ft_split(av[1],' ');
	execve(av[1],args,env);
	execve(path(args[0], env),args,env);
}

void child2(int to_close,int fd, char **av, char **env)
{
	char **args;
		
	close(to_close);
	dup2(fd,0);
	args = ft_split(av[2], ' ');
	execve(av[2],args,env);
	execve(path(args[0], env),args,env);
	path(args[0], env);
}

int main(int ac, char **av, char **env)
{
	int 	T[2];
	char	**args;
	pid_t 	pid[2];
	int		fd[2];

	pipe(T);
	pid[0] = fork();
	if(!pid[0])
		child1(T[1], av, env);
	else
		pid[1] = fork();
		if(pid[1])
			child2(T[1], T[0], av, env);
}

