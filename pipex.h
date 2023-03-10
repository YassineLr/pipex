/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:59:31 by ylarhris          #+#    #+#             */
/*   Updated: 2023/02/10 20:05:31 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<stdio.h>
# include<unistd.h>
# include<fcntl.h>
# include<stdlib.h>

size_t	ft_strlen(const char *str);
int		ft_wdcount(char *str, char c);
int		ft_lcount(int i, char *str, char sep);
char	*ft_filling(char *t__t, char *str, char sep, int i);
void	ft_free(char **str);
char	**ft_split(char *str, char sep);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *src, const char *to_find, size_t n);
char	*ft_paths(char **env);
char	*ft_path(char *cmd, char **env);
void	firstchild(char **av, int *T, char **env);
void	secondchild(char **av, int *T, char **env);
void	exit_status(int status);

#endif