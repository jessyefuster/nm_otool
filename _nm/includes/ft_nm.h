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

# define SYMBOL_SIZE(is_32) (is_32 ? sizeof(struct nlist) : sizeof(struct nlist_64))
# define SECTION_SIZE(is_32) (is_32 ? sizeof(struct section) : sizeof(struct section_64))


# define F_TYPE(type) (type & 0xF)
# define F_MACHO_TYPE(type) (type & 0xF0)
# define F_ARCH(type) (type & 0x300)
# define F_ENDIAN(type) (type & 0xC00)

# define F_IS_32(type) (F_ARCH(type) == F_32)
# define F_IS_64(type) (F_ARCH(type) == F_64)

extern uint64_t	g_maxaddr;

/*
**	File flags	(uint8_t)
**
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

/*
**	Symbol chained-list structure
*/
typedef struct	s_symbols
{
	//bool		is_32;
	char		*name;
	uint64_t	value;
	uint8_t		type;
	uint8_t		sect;
	// char		type_letter;

	struct s_symbols	*next;
}				t_symbols;


/*
**	archive.c
*/


/*
**	core.c
*/
void		handle_macho(char *file, uint32_t file_type, t_symbols **symbols);
void		handle_fat(char *file, char *filename);
void		handle_archive(char *file, uint32_t file_type);

/*
**	fat.c
*/
struct fat_arch	*find_arch(struct fat_header *fat_header, cpu_type_t arch);

/*
**	list.c
*/
void		print_symbols(char *file, t_symbols	*ptr, uint32_t file_type);
t_symbols	*new_node(uint32_t file_type, void *symbol, char *string_table);

/*
**	macho.c
*/
void		store_symbols(char *file, uint32_t file_type, struct symtab_command *symtab_cmd, t_symbols **symbols);

/*
**	sections.c
*/
char		**get_sections(struct mach_header *header, uint32_t file_type);

/*
**	tools.c
*/
// int			ft_error(char *message);
bool		file_error(char *filename);
bool		valid_addr(void *ptr);
uint32_t	swap_endian(uint32_t num);
char		section_letter(char *segname);
char		type_letter(char **sections, t_symbols *symbol);
char		*symbol_type(int type, int sect, int value);
uint32_t	get_file_type(char *file);

/*
**	main.c
*/
char		*valid_file(char *filename, struct stat *file_info);
void		nm_if_valid(char *filename);
bool		ft_nm(char *file, char *filename);



/*
**	_macho_32.c
**	_macho_64.c
**	DEPRECATED
*/
// void		display_symbols_32(char *file, struct mach_header *header, struct symtab_command *symtab_cmd);
// void		ft_handle_macho_32(char *file);
// void		display_symbols_64(char *file, struct mach_header_64 *header, struct symtab_command *symtab_cmd);
// void		ft_handle_macho_64(char *file);


/*
**	_print.c
**	DEPRECATED
*/
// char		**get_sections_32(struct mach_header *header, struct load_command *load_cmds);
// char		**get_sections_64(struct mach_header_64 *header, struct load_command *load_cmds);
// char		symbol_32(char *file, char **sections, struct nlist *symbol, char *string_table);
// char		symbol_64(char *file, char **sections, struct nlist_64 *symbol, char *string_table);



#endif
