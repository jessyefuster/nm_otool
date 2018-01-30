#include "../includes/ft_nm.h"

void	ft_handle_object(char *file, uint8_t file_type)
{
	if (file_type & F_32)
		ft_handle_object_64(file);
	else
		ft_handle_object_32(file);
}

void	ft_handle_execute(char *file, uint8_t file_type)
{
	
}

void	ft_handle_archive(char *file, uint8_t file_type)
{
	
}
