#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# include "../ft_nm_otool.h"

/*
**	core.c
*/
void		handle_macho(t_file *file);
void		handle_fat(t_file *file);
void		handle_archive(t_file *file);

/*
**	section.c
*/
void		*get_text_section(t_file *file, void *segment);
void		print_text_section(void *section);

/*
**	main.c
*/
// char				*map_file(char *filename, struct stat *file_info);
// enum status			nm_if_valid_file(char *filename, bool print_filename);
enum status		ft_otool(char *ptr, char *filename, size_t file_size, bool print_filename);

#endif