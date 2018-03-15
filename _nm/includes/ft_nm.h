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

# include <ar.h>
# include <mach-o/ranlib.h>


// typedef enum	e_bool
// {
// 	false = 0,
// 	true = 1
// }				t_bool;
# define S_32(num, file_type) rev_uint32(num, file_type)
# define S_64(num, file_type) rev_uint64(num, file_type)

# define SYMBOL_SIZE(is_32) (is_32 ? sizeof(struct nlist) : sizeof(struct nlist_64))
# define SECTION_SIZE(is_32) (is_32 ? sizeof(struct section) : sizeof(struct section_64))
# define MACH_HEADER_SIZE(is_32) (is_32 ? sizeof(struct mach_header) : sizeof(struct mach_header_64))


# define F_TYPE(type) (type & 0xF)
# define F_MACHO_TYPE(type) (type & 0xF0)
# define F_ARCH(type) (type & 0x300)
# define F_ENDIAN(type) (type & 0xC00)

# define F_IS_32(type) (F_ARCH(type) == F_32)
# define F_IS_64(type) (F_ARCH(type) == F_64)
# define F_IS_LITTLE(type) (F_ENDIAN(type) == F_LITTLE)
# define F_IS_BIG(type) (F_ENDIAN(type) == F_BIG)

extern uint64_t	g_maxaddr;

typedef uint32_t	t_filetype_t;

/*
**	File flags	t_filetype_t (uint32_t)
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

enum	check_result
{
	CHECK_BAD,
	CHECK_GOOD
};

enum	status
{
	S_FAILURE,
	S_SUCCESS
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

typedef struct	s_file
{
	char			*ptr;
	size_t			size;

	char			*filename;

	t_filetype_t	file_type;
}				t_file;

/*
**	archive.c
*/
char			*archive_name(char *name);
size_t		*archive_offsets(struct ar_hdr *header);

/*
**	CHECKS
*/
/*
**		archive.c
*/
enum check_result	check_archive(t_file *file);
/*
**		fat.c
*/
enum check_result	check_fat(t_file *file);
/*
**		file.c
*/
enum check_result	filecheck_error(char *filename, char *error);
t_filetype_t		get_file_type(t_file *file);
/*
**		macho.c
*/
enum check_result	check_macho(t_file *file, t_filetype_t ft);
/*
**		swap.c
*/
void				swap_fat_header(struct fat_header *header);
void				swap_fat_arch(struct fat_arch *arch);

/*
**	core.c
*/
void		handle_macho(t_file *file, t_symbols **symbols);
void		handle_fat(char *file, char *filename);
void		handle_archive(char *file, char *filename);

/*
**	fat.c
*/
char			*arch_name(cpu_type_t type);
struct fat_arch	*find_arch(struct fat_header *fat_header, cpu_type_t arch);

/*
**	list.c
*/
void		print_symbols(t_file *file, t_symbols *ptr);
t_symbols	*new_node(t_file *file, void *symbol, char *string_table);

/*
**	macho.c
*/
void		store_symbols(t_file *file, struct symtab_command *symtab_cmd, t_symbols **symbols);

/*
**	sections.c
*/
char		**get_sections(struct mach_header *header, t_filetype_t file_type);

/*
**	sort.c
*/
void		sort_tab(size_t *tab, size_t len);

/*
**	tools.c
*/
void		exit_error(char *error);
enum status	file_error(char *filename);
bool		valid_addr(void *ptr);
uint32_t	swap_uint32(uint32_t num);
uint64_t	swap_uint64(uint64_t num);
uint32_t	rev_uint32(uint32_t num, t_filetype_t file_type);
uint64_t	rev_uint64(uint64_t num, t_filetype_t file_type);
char		section_letter(char *segname);
char		type_letter(char **sections, t_symbols *symbol);

/*
**	main.c
*/
char		*map_file(char *filename, struct stat *file_info);
enum status	nm_if_valid_file(char *filename, bool print_filename);
enum status	ft_nm(char *file, char *filename, size_t file_size, bool print_filename);

#endif
