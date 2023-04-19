#include "shell.h"

/**
 * get_history_file - gets the history
 * @info: parameter structure
 *
 * Return: string allocated containing the file
 */

char *get_history_file(info_t *info)
{
	char *reg, *cd;

	cd = _getenv(info, "HOME=");
	if (!cd)
		return (NULL);
	reg = malloc(sizeof(char) * (_strlen(cd) + _strlen(HIST_FILE) + 2));
	if (!reg)
		return (NULL);
	reg[0] = 0;
	_strcpy(reg, cd);
	_strcat(reg, "/");
	_strcat(reg, HIST_FILE);
	return (reg);
}

/**
 * write_history - writes to an existing file
 * @info: the parameter structure
 *
 * Return: 1 on success, otherwise -1
 */
int write_history(info_t *info)
{
	ssize_t sz;
	char *fname = get_history_file(info);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	sz = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (sz == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, sz);
		_putfd('\n', sz);
	}
	_putfd(BUF_FLUSH, sz);
	close(sz);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: history count, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, fin = 0, count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *reg = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	reg = malloc(sizeof(char) * (fsize + 1));
	if (!reg)
		return (0);
	rdlen = read(fd, reg, fsize);
	reg[fsize] = 0;
	if (rdlen <= 0)
		return (free(reg), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (reg[i] == '\n')
		{
			reg[i] = 0;
			build_history_list(info, reg + fin, count++);
			fin = i + 1;
		}
	if (fin != i)
		build_history_list(info, reg + fin, count++);
	free(reg);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @reg: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *reg, int linecount)
{
	list_t *ptr = NULL;

	if (info->history)
		ptr = info->history;
	add_node_end(&ptr, reg, linecount);

	if (!info->history)
		info->history = ptr;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *ptr = info->history;
	int i = 0;

	while (ptr)
	{
		ptr->num = i++;
		ptr = ptr->next;
	}
	return (info->histcount = i);
}
