#include "../includes/ft_nm.h"

int			ft_error(char *message)
{
	ft_putstr(message);
	return (1);
}

// https://code.woboq.org/llvm/include/ar.h.html
// https://upload.wikimedia.org/wikipedia/commons/6/67/Deb_File_Structure.svg
uint8_t		get_file_type(char *file)
{
	uint8_t				file_type;
	struct mach_header	*header;

	header = (struct mach_header *)file;
	if (header->magic == MH_MAGIC)
		file_type |= F_32;
	else if (header->magic == MH_MAGIC_64)
		file_type |= F_64;
	else
		return (0);

	if (header->filetype == MH_OBJECT)
		file_type |= F_OBJECT;
	else if (header->filetype == MH_EXECUTE)
		file_type |= F_EXECUTE;
	
	printf("arch: %d\n", (file_type & F_32) ? 32 : 64);

	return (file_type);
}
