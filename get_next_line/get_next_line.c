/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:38:38 by ytabia            #+#    #+#             */
/*   Updated: 2024/11/12 11:56:19 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
char *ft_read_save(int fd, char *save)
{
	int read_bytes;
	char *buff;
	char *tmp;

	buff = malloc(BUFFER_SIZE + 1);
	if(!buff)
		return(NULL);
	read_bytes = 1;
	while(!ft_strchr(save, '\n'))     //opposit , the func return null = false thats mean its true  
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1) // read errors
    	{
        	free(buff);
        	free(save);
        	return (NULL);
    	}
		if(read_bytes == 0)          // file is empty   buff =  Hell          save =  Hello\nWo                     save  =      Hello\nWorld 						he\0
			break;
		buff[read_bytes] = '\0';
		tmp = save;                // put save to tmp to free save allocation  
		save = ft_strjoin(save, buff);
		free(tmp);
	}
	if(read_bytes == 0 && (!save || *save == '\0'))     // EOF and no content
	{
		free(buff);
		free(save);
		return(NULL);
	}	
	free(buff);
	return(save);
}

char *ft_get_the_line(char *save)
{
	int i;
	char *s;

	if(!save)      //if save is empty
		return(NULL);
	i = 0;
	while(save[i] && save[i] != '\n')
		i++;
	s = malloc(sizeof(char) * (i + 2));   // allocate size line + \n + \0
	if(!s)
		return(NULL);
	i = 0;
	while(save[i] && save[i] != '\n')   // copy save into s 
	{
		s[i] = save[i];
		i++;
	}
	if(save[i] == '\n')            // put the new line and ancrment to put null terminator  
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0';
	return(s);	
}

char *ft_update_save(char *save)
{
	char *s;
	int i;
	int j;

	if (!save)
		return NULL;
	i = 0;
	while(save[i] && save[i] != '\n')     // Hello\nqe
		i++;
	if(!save[i])           //  if No newline found free save and return NULL
	{
		free(save);      
		return(NULL);
	}
	s = malloc(sizeof(char) * (ft_strlen(save) - i) + 1);  // allcat rimander after \n ex: Hello\nwo   strlen save = 8 , i = 5 
	if(!s)
		return(NULL);
	i++;
	j = 0;
	while(save[i])
	{
		s[j] = save[i];                // keep index of save and copy from it to s
		i++;
		j++;
	} 
	s[j] = '\0';
	free(save);						   // free old allocation of save 
	return(s);                        // return updated str
}

char *get_next_line(int fd)
{
	static char *save;
	char *line;

	if(fd < 0 || BUFFER_SIZE < 0)
		return(NULL);
	save = ft_read_save(fd, save);            // give the adrress return to save
	if(!save)
		return(NULL);
	line = ft_get_the_line(save);   
	save = ft_update_save(save);
	return(line);
}

// #include <stdio.h>
// int main()
// {
// 	int fd;
// 	fd = open("test.txt", O_RDONLY);

// 	printf("%s", get_next_line(fd));
//  	printf("%s", get_next_line(fd));
// }