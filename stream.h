#ifndef STREAM_H
#define STREAM_H

struct stream_t {
	void *src;
	char *(*readline) (struct stream_t *);
	void (*free) (struct stream_t *);
	void (*print) (struct stream_t *);
};

#define stream_lines(fs, line) \
	for (char *line = fs->readline(fs); line != NULL; line = fs->readline(fs))

static void stream_print(struct stream_t *self) {
	stream_lines(self, line) {
		printf("%s\n", line);
	}
}


#endif /* STREAM_H */
