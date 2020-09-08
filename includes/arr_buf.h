#ifndef ARR_BUF_H
# define ARR_BUF_H

# include "libft.h"

# define BUF_SIZE 256

typedef struct {
	int		i;
	char	buf[BUF_SIZE + 1];
}			t_buf;

void		init_buf(t_buf *buf);
int			add_to_buf(t_buf *buf, char chr, char **str);
int			flush_buf(t_buf *buf, char **str);

#endif
