#ifndef FT_NM_H
# define FT_NM_H
# include "../../libft/includes/libft.h"
# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# include <mach-o/loader.h>
# include <mach-o/nlist.h>


// TO IMPLEMENT
//     00           0000
//  32 or 64     file type
enum	file_flags
{
	F_NONE =	0x0,
	F_OBJECT =	0x1,
	F_EXECUTE = 0x2,
	F_ARCHIVE =	0x4,

	F_32 =		0x10,
	F_64 =		0x20
};

/*
**	tools.c
*/
int			ft_error(char *message);
uint8_t		get_file_type(char *file);

/*
**	core_handler.c
*/
void		ft_handle_object(char *file, uint8_t file_type);
void		ft_handle_execute(char *file, uint8_t file_type);
void		ft_handle_archive(char *file, uint8_t file_type);

/*
**	object_handler.c
*/
void		ft_handle_object_32(char *file);
void		ft_handle_object_64(char *file);


#endif
