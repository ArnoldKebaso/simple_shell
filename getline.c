#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @reg: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **reg, size_t *l)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*reg) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*reg);
		*reg = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(reg, &len_p, stdin);
#else
		r = _getline(info, reg, &len_p);
#endif
		if (r > 0)
		{
			if ((*reg)[r - 1] == '\n')
			{
				(*reg)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*reg);
			build_history_list(info, *reg, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*l = r;
				info->cmd_buf = reg;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *reg; /* the ';' command chain buffer */
	static size_t i, j, l;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &reg, &l);
	if (r == -1) /* EOF */
		return (-1);
	if (l)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = reg + i; /* get pointer for return */

		check_chain(info, reg, &j, i, l);
		while (j < l) /* iterate to semicolon or end */
		{
			if (is_chain(info, reg, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= l) /* reached end of buffer? */
		{
			i = l = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = reg; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @reg: buffer
 * @s: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *reg, size_t *s)
{
	ssize_t r = 0;

	if (*s)
		return (0);
	r = read(info->readfd, reg, READ_BUF_SIZE);
	if (r >= 0)
		*s = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @lgt: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *lgt)
{
	static char reg[READ_BUF_SIZE];
	static size_t i, l;
	size_t k;
	ssize_t r = 0, s = 0;
	char *ch = NULL, *new_p = NULL, *c;

	ch = *ptr;
	if (ch && lgt)
		s = *lgt;
	if (i == l)
		i = l = 0;

	r = read_buf(info, reg, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = _strchr(reg + i, '\n');
	k = c ? 1 + (unsigned int)(c - reg) : l;
	new_p = _realloc(ch, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (ch ? free(ch), -1 : -1);

	if (s)
		_strncat(new_p, reg + i, k - i);
	else
		_strncpy(new_p, reg + i, k - i + 1);

	s += k - i;
	i = k;
	ch = new_p;

	if (lgt)
		*lgt = s;
	*ptr = ch;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
