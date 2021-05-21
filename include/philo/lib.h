#ifndef LIB_H
# define LIB_H
# include <stddef.h>
# include <stdbool.h>

size_t	ft_strlen(const char *s);
bool	parse_uint(const char *s, unsigned long long *n);
int		dputs(const char *s, int fd);
int		error_out(const char *msg, int exit_code);

#endif
