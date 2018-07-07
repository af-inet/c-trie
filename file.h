#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "stream.h"

struct stream_t *file_stream_alloc(const char *filename);

#endif /* FILE_H */
