#include "./includes/rtv1.h"

static int		get_next_line_2(int const fd, char **line);

static char		*get_line(char *s)
{
	int		length;
	int		i;
	char	*line;

	i = 0;
	length = 0;
	while (s[length] != '\n')
		length++;
	line = (char*)malloc(length);
	while (i < length)
	{
		line[i] = s[i];
		i++;
	}
	return (line);
}

static int		get_next_line_2(int const fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static	char	*result;
	static	int		x;
	int				ret;

	if (result != NULL && (ft_strchr(result, '\n') || x))
	{
		*line = x ? result : get_line(result);
		result = x ? NULL : ft_strdup(ft_strchr(result, '\n') + 1);
		return (1);
	}
	else
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		if ((ret == 0 && (x || result == NULL)) || ret == -1)
			return (ret);
		if (ret == 0)
			x = 1;
		if (result == NULL)
			result = ft_strnew(1);
		result = ft_strjoin(result, buf);
		return (get_next_line(fd, line));
	}
}

int				get_next_line(int const fd, char **line)
{
	if (fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	else
		return (get_next_line_2(fd, line));
}
