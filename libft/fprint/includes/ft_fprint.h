#ifndef FT_FPRINT_H
# define FT_FPRINT_H
# include "../../includes/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

/*
**	FLAGS INDEX
*/

enum	flags {
	PRECISION,
	SPACES,
	SHOW_SIGN,
	ZERO_SPACES,
	HASHTAG,
	LEFT_ALIGN,
	PRECISION_EXISTS,
	A_SPACE,
	CONVERSION
};

enum	conversion {
	H = 1,
	HH,
	L,
	LL,
	J,
	Z
};

int			ft_fprint(int fd, const char *format, ...);


/*
**		CHECKS.C
*/
bool		is_type(char c);
bool		is_modifier(char c);
bool		is_conversion(char c);
char		*check_modifiers(char *ptr, int *flags);
char		*check_conversions(char *ptr, int *flags);

/*
**		PRINT.C
*/
void		print_percent(int *flags);
void		print_char(va_list args, int *flags);
void		print_string(int fd, va_list args, int *flags);
void		print_integer(int fd, va_list args, int *flags);
void		print_hexa(va_list args, char type, int *flags);

/*
**		TOOLS.C
*/
void		print_precision(int *modifiers, int len);
void		right_align(int *modifiers, int len, int force_space);
void		left_align(int *modifiers, int len);
uintmax_t	convert_uvalue(uintmax_t value, int conversions);
intmax_t	convert_svalue(intmax_t value, int conversions);

#endif
