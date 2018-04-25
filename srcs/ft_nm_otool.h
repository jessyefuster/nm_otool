/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:07:29 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/25 16:32:06 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H
# include "../libft/includes/libft.h"
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

typedef uint32_t					t_filetype_t;
typedef struct load_command			t_lc;
typedef struct symtab_command		t_sym;
typedef struct nlist				t_nlist;
typedef struct nlist_64				t_nlist_64;
typedef struct section				t_sect;
typedef struct section_64			t_sect_64;
typedef struct segment_command		t_seg;
typedef struct segment_command_64	t_seg_64;

# define MIN(a, b)	(a <= b ? a : b)

# define S_32(num, file_type) rev_uint32(num, file_type)
# define S_64(num, file_type) rev_uint64(num, file_type)

# define SYMBOL_SIZE(is_32) (is_32 ? sizeof(t_nlist) : sizeof(t_nlist_64))
# define SECTION_SIZE(is_32) (is_32 ? sizeof(t_sect) : sizeof(t_sect_64))

# define F_TYPE(type) (type & 0xF)
# define F_MACHO_TYPE(type) (type & 0xF0)
# define F_ARCH(type) (type & 0x300)
# define F_ENDIAN(type) (type & 0xC00)

# define F_IS_32(type) (F_ARCH(type) == F_32)
# define F_IS_64(type) (F_ARCH(type) == F_64)
# define F_IS_LITTLE(type) (F_ENDIAN(type) == F_LITTLE)
# define F_IS_BIG(type) (F_ENDIAN(type) == F_BIG)

/*
**	File flags	t_filetype_t (uint32_t)
**
**	  00 	   00		   0000			  0000
**	endian   32 / 64	macho type		file type
*/
enum				e_file_flags
{
	F_NONE = 0x0,
	F_ARCHIVE = 0x1,
	F_FAT = 0x2,
	F_MACHO = 0x4,

	F_OBJECT = 0x10,
	F_EXECUTE = 0x20,
	F_FVMLIB = 0x30,
	F_CORE = 0x40,
	F_PRELOAD = 0x50,
	F_DYLIB = 0x60,
	F_DYLINKER = 0x70,
	F_BUNDLE = 0x80,

	F_32 = 0x100,
	F_64 = 0x200,
	F_LITTLE = 0x400,
	F_BIG = 0x800,
};

enum				e_function
{
	NM,
	OTOOL
};

/*
**	Parse functions return values
*/
enum				e_check_result
{
	CHECK_BAD,
	CHECK_GOOD
};

/*
**	Function status return values
*/
enum				e_status
{
	S_FAILURE,
	S_SUCCESS
};

/*
**	Archive member name structure
*/
typedef struct		s_ar_member {
	char				*name;
	size_t				name_size;
}					t_ar_member;

/*
**	Symbol chained-list structure
*/
typedef struct		s_symbols
{
	char				*name;
	uint64_t			value;
	uint8_t				type;
	uint8_t				sect;

	struct s_symbols	*next;
}					t_symbols;

/*
**	Main structure
*/
typedef struct		s_file
{
	char				*ptr;
	size_t				size;

	char				*name;

	t_filetype_t		type;
}					t_file;

/*
**	archive.c
*/
char				*format_archive_name(char *archive_name, char *member_name,
					size_t member_name_len);

/*
**	CHECKS
*/
/*
**		archive.c
*/
size_t				size_ar_name(struct ar_hdr *header);
bool				is_extended(struct ar_hdr *header);
enum e_check_result	check_archive(t_file *file);
/*
**		fat.c
*/
enum e_check_result	check_fat(t_file *file);
/*
**		file.c
*/
t_filetype_t		get_file_type(t_file *file);
/*
**		macho.c
*/
enum e_check_result	check_symtab_command(t_file *file,
					struct symtab_command *st);
enum e_check_result	check_macho(t_file *file);
/*
**		macho_32.c
*/
enum e_check_result	check_load_commands_32(t_file *file,
					struct mach_header *mh, struct load_command *lc);
/*
**		macho_64.c
*/
enum e_check_result	check_load_commands_64(t_file *file,
					struct mach_header_64 *mh, struct load_command *lc);
/*
**		swap.c
*/
void				swap_fat_header(struct fat_header *header);
void				swap_fat_arch(struct fat_arch *arch);
void				swap_mach_header(struct mach_header *header);
void				swap_mach_header_64(struct mach_header_64 *header);
void				swap_load_command(struct load_command *command);
void				swap_segment(struct segment_command *segment);
void				swap_segment_64(struct segment_command_64 *segment);
void				swap_section(struct section *section);
void				swap_section_64(struct section_64 *section);
void				swap_symtab(struct symtab_command *symtab);
void				swap_nlist(struct nlist *symbol);
void				swap_nlist_64(struct nlist_64 *symbol);

/*
**	fat.c
*/
char				*arch_name(cpu_type_t type);
char				*arch_name_short(cpu_type_t type);
struct fat_arch		*find_arch(struct fat_header *fat_header, cpu_type_t arch);

/*
**	tools.c
*/
void				exit_error(char *error);
enum e_check_result	filecheck_error(char *filename, char *error);
uint32_t			swap_uint32(uint32_t num);
uint64_t			swap_uint64(uint64_t num);
uint32_t			rev_uint32(uint32_t num, t_filetype_t file_type);
uint64_t			rev_uint64(uint64_t num, t_filetype_t file_type);

#endif
