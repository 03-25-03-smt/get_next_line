#include "get_next_line.h"

static char	*get_current_buffer(int fd, char *buffer)
{
	char	*current;
	ssize_t  bytes_read;

  bytes_read = 1;																// 1 потому что нужно войти в цыкл 
  current = (char *)malloc(BUFFER_SIZE + 1);
  if (!current)
    return (NULL);
  while (bytes_read > 0 && !find_chr(buffer, '\n'))                            // Нам нужно читать, пока в buffer нет \n
  {
    bytes_read = read(fd, current, BUFFER_SIZE);
    if (bytes_read == 0)
      break;
    if (bytes_read == -1)
      return (free(current),NULL);
    current[bytes_read] = '\0';
    buffer = merge_previous_and_current(buffer, current);
    if (!buffer)
      return (free(current),NULL);
  }
  free(current);
  if (strlen_at(buffer, '\0') > 0)
		return (buffer);
  return (NULL);
}

static char	*get_line(char **buffer)
{
	char	*line;                                                         // Строка, которую мы вернём пользователю.
	char	*keep;                                                         // Остаток, который сохраним для следующего вызова 
	size_t	til_null_len;                                                 // Длина всей строки
	size_t	til_new;                                                     // Позиция \n

	if (!buffer || !*buffer)
		return (NULL);
	til_new = strlen_at(*buffer, '\n');                                   // Ищем \n 
	if ((*buffer)[til_new] == '\n')                                      // Проверяем, действительно ли там \n
		til_new++;														// ф-я возвращает позицию \n но не включает в себя этот же \n
	line = cpy_buffer(*buffer, 0, til_new);                             // Создаём line
	if (!line)
		return (NULL);
	til_null_len = strlen_at(*buffer, '\0');                             // Находим конец всей строки
	keep = cpy_buffer(*buffer, til_new, til_null_len - til_new );   	// Копируем остаток /  til_null_len - til_new  нужно узнать сколько символов осталось после \n, чтобы скопировать именно остаток в keep.
	if (!keep)
		return (free (line), NULL);
	free(*buffer);
	*buffer = keep;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer; // переменная сохраняет своё значение между вызовами функции. Она живёт всё время работы программы, а не удаляется при выходе из функции. Её область видимости при этом ограничена только этой функцией.
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_current_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(&buffer);
	if (!buffer[0])
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
