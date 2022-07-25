/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_coment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:33:54 by lleiria-          #+#    #+#             */
/*   Updated: 2022/03/08 11:29:58 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char *valid_buffer(char **storage, char **buffer, size_t buflen)
{
//buflen é o tamanho válido de bytes necessário para retornar uma linha
//inteira depois de concatenar a storage com o buffer.
	char	*returner;
	char	*tmp;
	size_t	storlen;

	storlen = ft_strlen(*storage);//Saber o tamanho da storage para quando a copiarmos
	returner = (char *)malloc(sizeof(char) * buflen + storlen + 1);
//Alocamos a memória com o tamanho total do buffer até à quebra de linha para retornar
	if (!returner)
		return (0);//se não houver returner, deu erro
	ft_memcpy(returner, *storage, storlen);//copiamos o conteudo da storage para o returner
	ft_memcpy(returner + storlen, *buffer, buflen);
//Depois copia-se um número buflen de caracteres do buffer 
//para o returner com o tamanho total da storage
	returner[storlen + buflen] = '\0';
//Um nulo para fechar a string da nova linha após os tamanhos do buffer e da storage
	tmp = ft_strdup((*buffer) + buflen);//buffer + buflen pois só vai duplicar após o buflen
//Uma variavel temporaria onde estará o que restou do buffer e que será mandado para a storage
	if (*storage)
		free(*storage);//libertamos a memória alocada na storage
	(*storage) = tmp;//e transferimos o restante conteudo do buffer
	return (returner);//retornamos então a linha
}

static	char *feed_storage(char **storage, char **buffer, size_t valid)
{
	char	*tmp;
	char	*returner;

	returner = NULL;
	if (valid <= 0)// se valid for menor ou igual a 0, então o ficheiro já foi lido ou é inválido
	{
		if (valid == 0 && *storage)//verificamos também se existe algo na storage, pois
//		o ficheiro pode ser válido, mas estar vazio.
		{
			returner = (*storage);//Redireciona-se o ponteiro returner para o conteudo da storage
			*storage = NULL;//enquanto a storage passa a apontar para nulo.
		}
		return (returner);//returnamos o returner com o conteudo da storage
	}
	(*buffer)[valid] = '\0';//o valor de valid vai indicar até onde o fd foi lido
	tmp = ft_strchr(*buffer, '\n');//procurar uma nova linha no buffer
	if (tmp)
		returner = valid_buffer(storage, buffer, (tmp - *buffer) + 1);
/*
	Se existir tmp, ou seja, se existir uma nova linha, usamos a funçāo
	valid_buffer onde enviamos a storage, o buffer e o endereço de tmp
	menos (-) o endereço inicial do buffer (o que será o tamanho da string
	dentro do buffer) + 1 espaço para o nulo no final.
*/
	else
	{
		tmp = ft_strjoin(*storage, *buffer);
//Se não existir tmp, então não encontrou uma nova linha, por isso
//concatenamos a storage e o buffer e enviamos para o tmp
//Assim o returner será nulo e isso vai ativar novamente o while loop da função principal
		if (*storage)
			free(*storage);
		*storage = tmp;
	}
	return (returner);//returnamos a nova linha ou o nulo
}

static char	*valid_storage(char **storage, size_t size)
{
/*
	Se houver uma nova linha dentro da storage, significa que não precisamos
	encher o buffer com o conteudo do ficheiro.
	Só precisamos de marcar o endereço da nova linha dentro da storage.
	Então pegamos em tudo da storage até à quebra de linha, passar para o
	returner, limpar a storage e mandá-la de volta.
*/
	char	*tmp;
	char	*returner;
	size_t	n;

	if (size < 0)//Se o size (endereço da nova linha - o endereço inicial da storage)
		return (0);//for menor que 0, então deu erro
	returner = malloc(sizeof(char) * (size + 1));
	if (!returner)
		return (0);
	n = -1;//incializa-se a variavel com -1 em vez de zero, pois vamos
	while (++n != size)//incrimentá-la durante a comparação, antes de compará-la com o size
		returner[n] = (*storage)[n];//Enquanto este loop for válido, colocamos no returner
//o conteudo da storage.
	returner[n] = '\0';
	tmp = ft_strdup(*storage + n);
//	Então colocamos uma string duplicada da storage na variavel temporaria,
//	porém apenas o endereço após a quebra de linha (+ n).
	free (*storage);//limpamos a memória alucada na storage
	(*storage) = tmp;///E fazemos a storage apontar para o conteudo duplicado
	return (returner);//returnamos a linha agora com o nulo no final da string
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*returner;
	size_t		valid;

//casos de erro
	if ((read(fd, NULL, 0) == -1) || (fd < 0 || fd > 1024) || BUFFER_SIZE <= 0)
		return (0);
/* |||||||||||||||||||-Primeira Condição-||||||||||||||||||||

	size_t read (int fd, void* buf, size_t cnt);
	fd (primeiro slot) - File Descriptor
	buf (segundo slot) - buffer de onde os dados serão lidos
	cnt (terceiro slot) - tamanho do buffer
	
	Usa-se o read para para ver se existe ficheiro (fd) ou se é válido.
	File Descriptor (fd) é um int que identifica exclusivamente um arquivo aberto.
	O nulo (NULL) no segundo slot significa que tudo o que foi lido
	não será copiado para nada, ou seja, um buffer nulo. O zero (0) no terceiro slot
	indica que o buffer tem tamanho zero (0), ou seja, nada será lido.
	
	O retorno normal deveria ser 0, ou seja, que nada foi lido.
	Se o retorno for -1 então deu erro, o que significa que a função
	não conseguiu ler nada por ser inválida.

|||||||||||||||||||-Segunda Condição-||||||||||||||||||||

	O fd só pode ter valores entre 0 e 1024, qualquer valor
	menor ou maior é invalido.

|||||||||||||||||||-Terceira Condição-||||||||||||||||||||
	
	O BUFFER_SIZE, que será dado pela flag do compilador, näo pode
	ser menor ou igual a zero, pois assim nada será lido.
*/
	valid = 1;
	returner = NULL;
	buffer = ft_strchr(storage, '\n');
/*	com o ft_strchr verificamos se existe algo no armazenamento (storage) e se caso
	exista enviamos o seu conteudo até à primeira quebra de linha (\n) encontrada
	para o buffer
*/
//caso o buffer esteja vazio ou não haja quebra de linha, é necessário enchê-lo
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
//Alocamos a memória necessária para o buffer + 1 espaço para o nulo do final da string
		if (!buffer)//Se mesmo assim não existir nada no buffer, então deu erro
			return (0);
/*  /////////////////-Condições do While-//////////////
	Devido à função feed_storage, o returner só deixará de ser nulo se o
	buffer encontrar uma nova linha.

	Enquanto valid for maior que 0, significa que ainda há conteudo para ser
	lido no ficheiro.
	Se valid chegar a 0 também significa que o buffer está vazio e que tudo o
	que restava retornar já está na storage.
	Desse modo, o returner já não será nulo e o while loop para.
*/
		while (returner == NULL && valid > 0)
		{
			valid = read(fd, buffer, BUFFER_SIZE);
//Lemos (read) um número BUFFER_SIZE de caracteres e
//armazenamos no ponteiro buffer
			returner = feed_storage(&storage, &buffer, valid);
//Enchemos entāo a storage com tudo o que o buffer encontrar e
//colocamos no returner a storage ou o buffer
		}
		free (buffer);
//libertamos a memória do buffer após tê-lo transportado para a storage,
//preparando o buffer para o próximo loop
		return (returner);//retornamos a linha
	}
	returner = valid_storage(&storage, (buffer - storage) + 1);
//Se houver uma quebra de linha dentro da storage, colocamos tudo
//até essa quebra de linha no returner e limpamos o conteudo usado
//da storage, deixando apenas o que está depois da quebra de linha
	return (returner);
}
