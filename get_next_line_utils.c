#include "get_next_line.h"

size_t strlen_at(const char *s, int end)             // str lenght 
{
  size_t  i;

  i = 0;
  if (!s)
    return (0);
  while (s[i] != '\0' && s[i] != end)
    i++;
  return (i);
}

char *find_chr(const char *s, int c)                  // looking for specific character, that we are sending for example "/n" 
{
  if (!s)
    return (NULL);
  while (*s != '\0')
    {
      if (*(unsigned char *)s == (unsigned char)c)
        return ((char *)s);
      s++;
    }
  if ((unsigned char)c == '\0')
	  return ((char *)s);
  return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)    // копирует одну стр в другую
{
	const unsigned char	*str_ptr;
	unsigned char		*dest_ptr;

	str_ptr = src;
	dest_ptr = dest;
	while (n > 0)
	{
		*dest_ptr = *str_ptr;
		dest_ptr++;
		str_ptr++;
		n--;
	}
	return (dest);
}

char	*cpy_buffer(const char *buffer, size_t start, size_t len)      // копирует ф-ю в новую ф-ю
{
  size_t  num;
  char    *res;
  
  num = 0;
  res = (char *)malloc(len + 1);
  if (!res)
    return (NULL);
  while (num < len)
    {
      res[num] = buffer[start + num];
      num++;
    }
  res[num] = '\0';
  return (res);
}

char	*merge_previous_and_current(char *previous, const char *current) // соединяет 2 фи-я в одну 
{
	size_t	prev_len;
	size_t	curr_len;
	char	*result;

	prev_len = 0;
	if (previous)
		prev_len = strlen_at(previous, '\0');
	curr_len = strlen_at(current, '\0');
	result = (char *)malloc(prev_len + curr_len + 1);
	if (!result)
		return (NULL);
	if (previous)
		ft_memcpy(result, previous, prev_len);
	ft_memcpy(result + prev_len, current, curr_len);
	result[prev_len + curr_len] = '\0';
	free(previous);
	return (result);
}

char	*get_current_buffer(int fd, char *buffer)
{

}
