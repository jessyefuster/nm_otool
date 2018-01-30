
#include "../includes/ft_nm.h"

void	ft_nm(char *file)
{
	uint8_t		file_type;

	file_type = get_file_type(file);
	if (file_type & F_OBJECT)
	{
		ft_putendl("File type:   OBJECT FILE");
		ft_handle_object(file, file_type);
	}
	else if (file_type & F_EXECUTE)
	{
		ft_putendl("File type:   EXECUTABLE");
		ft_handle_execute(file, file_type);
	}
	else if (file_type & F_ARCHIVE)
	{
		ft_putendl("File type:   ARCHIVE");
		ft_handle_archive(file, file_type);
	}
	else
		ft_putendl("File type:   NONE");
}

int		main(int argc, char **argv)
{
	int				fd;
	char			*file;
	struct stat		file_info;

	if (argc != 2)
		return (ft_error("Error\n"));

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error("Open error\n"));

	if (fstat(fd, &file_info) < 0 || file_info.st_mode & S_IFDIR)
		return (ft_error("Fstat error\n"));

	if ((file = mmap(0, file_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error("Mmap error\n"));

	ft_nm(file);

	return (0);
}
