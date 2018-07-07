#include <stdlib.h>
#include <stdio.h>

#include "stream.h"
#include "file.h"
#include "trie.h"

void
trie_load(struct trie_t *node, char *filename)
{
	struct stream_t *fs;

	fs = file_stream_alloc(filename);
	stream_lines(fs, line) {
		trie_insert(node, line);
	}
	fs->free(fs);
}

int
main(int argc, char *argv[])
{
	struct trie_t *root = trie_alloc('@');
	struct trie_t *ret;
	trie_load(root, "words.txt");

	ret = trie_find(root, "africa");
	printf("ret: %p %u\n", ret, ret->word);

	ret = trie_find(root, "ciaowhdiaowd");
	printf("ret: %p\n", ret);

	trie_free(root);
}
