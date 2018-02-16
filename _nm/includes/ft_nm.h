#ifndef FT_NM_H
# define FT_NM_H
# include "../../libft/includes/libft.h"
# include <stdio.h>
# include <stdbool.h>

# include <unistd.h>
# include <stdlib.h>

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach/machine.h>


// typedef enum	e_bool
// {
// 	false = 0,
// 	true = 1
// }				t_bool;

# define F_TYPE(type) (type & 0xF)
# define F_MACHO_TYPE(type) (type & 0xF0)
# define F_ARCH(type) (type & 0x300)
# define F_ENDIAN(type) (type & 0xC00)
/*
**	  00 	   00		   0000			  0000
**	endian   32 / 64	macho type		file type
*/
enum	file_flags
{
	F_NONE =		0x0,
	F_ARCHIVE = 	0x1,
	F_FAT = 		0x2,
	F_MACHO = 		0x4,

	F_OBJECT =		0x10,
	F_EXECUTE = 	0x20,
	F_FVMLIB =		0x30,
	F_CORE =		0x40,
	F_PRELOAD =		0x50,
	F_DYLIB =		0x60,
	F_DYLINKER =	0x70,
	F_BUNDLE =		0x80,

	F_32 =			0x100,
	F_64 =			0x200,
	F_LITTLE =		0x400,
	F_BIG =			0x800,
};


typedef struct	s_symbols
{
	//bool		is_32;
	char		*name;
	uint64_t	value;
	uint8_t		type;
	char		type_letter;

	struct s_symbols	*next;
}				t_symbols;

/*
**	tools.c
*/
int			ft_error(char *message);
uint32_t	swap_endian(uint32_t num);
char		section_letter(char *segname);
char		*symbol_type(int type, int sect, int value);
uint32_t	get_file_type(char *file);

/*
**	core_handler.c
*/
void		ft_handle_macho(char *file, uint32_t file_type, t_symbols *symbols);
void		ft_handle_fat(char *file, uint32_t file_type, char *filename);
void		ft_handle_archive(char *file, uint32_t file_type);

/*
**	macho_32_handler.c
*/
void		display_symbols_32(char *file, struct mach_header *header, struct symtab_command *symtab_cmd);
void		ft_handle_macho_32(char *file);

/*
**	macho_64_handler.c
*/
void		display_symbols_64(char *file, struct mach_header_64 *header, struct symtab_command *symtab_cmd);
void		ft_handle_macho_64(char *file);

/*
**	fat_handler.c
*/
struct fat_arch	*find_arch(struct fat_header *fat_header, cpu_type_t arch);

/*
**	print_symbols.c
*/
char		**get_sections_32(struct mach_header *header, struct load_command *load_cmds);
char		**get_sections_64(struct mach_header_64 *header, struct load_command *load_cmds);
char		symbol_32(char *file, char **sections, struct nlist *symbol, char *string_table);
char		symbol_64(char *file, char **sections, struct nlist_64 *symbol, char *string_table);


bool		ft_nm(char *file, char *filename);

#endif
