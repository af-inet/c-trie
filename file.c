#include "file.h"

#define FILE_BUFFER_SIZE 1024

struct file_t {
	int fd;
	unsigned char error;
	char line[FILE_BUFFER_SIZE];
	size_t line_len;
};

struct file_t *
file_alloc(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	struct file_t *file = malloc(sizeof(struct file_t));
	*file = (struct file_t) {
		.fd = fd,
		.error = (fd == -1),
		.line = {0},
		.line_len = 0
	};
	return file;
}

void
file_free(struct file_t *file)
{
	close(file->fd);
	free(file);
}

char *
file_readline(struct file_t *file)
{
	ssize_t ret;
	if (file->error) {
		return NULL;
	}
	file->line_len = 0;
	while (file->line_len < (FILE_BUFFER_SIZE-1)) {
		/* read 1 byte from the file */
		ret = read(
			file->fd,
			file->line + file->line_len,
			1);
		if (ret == 0) {
			/* EOF */
			file->line[file->line_len] = '\0';
			if (file->line_len == 0)
				return NULL;
			return file->line;
		}
		else if (ret == 1) {
			/* read 1 byte */
			file->line_len += 1;
			if (file->line[file->line_len-1] == '\n')  {
				/* nul-terminate the line */
				file->line[file->line_len-1] = '\0';
				return file->line;
			}
		}
		else {
			break;
		}
	}
	/* some kind of error occurred */
	return NULL;
}

char *
file_stream_readline(struct stream_t *self)
{
	struct file_t *file = (struct file_t *)self->src;
	return file_readline(file);
}

void
file_stream_free(struct stream_t *self)
{
	struct file_t *file = (struct file_t *)self->src;
	file_free(file);
	free(self);
}

struct stream_t *
file_stream_alloc(const char *filename)
{
	struct stream_t *stream = malloc(sizeof(struct stream_t));
	*stream = (struct stream_t) {
		.src = file_alloc(filename),
		.readline = &file_stream_readline,
		.free = &file_stream_free,
		.print = &stream_print
	};
	return stream;
}
