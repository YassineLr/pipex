#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

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

int main(int ac, char **av, char **env)
{
    int P[2];
    pid_t   pid;
    char **ar = ft_split(av[1],' ');
    char **ars1 = ft_split(av[2],' ');
    int m;
    printf("%s",ars1[0]);
    printf("%s",ars1[1]);

    pipe(P);
    pid = fork();
    if (pid)
    {
        dup2(P[1],1);
        execve("/bin/ls", ar, env);
    }
    else
    {
        close(P[1]);
        printf("hello");
        dup2(P[0], 0);
        execve("/usr/bin/wc",ars1, env);
        close(P[0]);
    }
}