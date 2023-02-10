/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:18:13 by ylarhris          #+#    #+#             */
/*   Updated: 2023/02/08 08:18:55 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **env)
{
    pid_t child[2];
    int    T[2];

    pipe(T);
    if (ac != 5)
        write(1, "Bad Arguments", 14);
    else
    {
        child[0] = fork();
        if (!child[0])
            firstchild(av,T,env);
        else
        {
            child[1] = fork();
            if (!child[1])
                secondchild(av,T,env);
        }
    }
    close(T[1]);
    close(T[0]);
    waitpid(child[0], NULL, 0);
    waitpid(child[1], NULL, 0);
}