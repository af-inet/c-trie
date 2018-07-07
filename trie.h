#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>

struct trie_t {
	char value;
	unsigned char word;
	struct trie_t *next;
	struct trie_t *child;
};

struct trie_t *trie_alloc(char value);
void trie_free(struct trie_t *trie);
void trie_insert(struct trie_t *node, char *key);
struct trie_t *trie_find(struct trie_t *node, char *key);

#endif /* TRIE_H */
