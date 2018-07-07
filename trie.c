#include "trie.h"

struct trie_t *
trie_alloc(char value)
{
	struct trie_t *node = malloc(sizeof(struct trie_t));
	*node = (struct trie_t) {
		.value = value,
		.next = NULL,
		.child = NULL
	};
	return node;
}

void
trie_free(struct trie_t *node)
{
	if (!node)
		return;
	trie_free(node->child);
	trie_free(node->next);
	free(node);
}

void
trie_insert(struct trie_t *node, char *key)
{
	do {
		// find the nearest match, or the last node in the chain
		while (node->value != key[0] && node->next)
			node = node->next;

		// if there was no match, add a new node at the end of the chain
		if (node->value != key[0])
			node = node->next = trie_alloc(key[0]);

		// if we've reached the end of string, we're done
		if (key[1] == '\0') {
			node->word = 1;
			return;
		}

		// if the matching node has no child node, add one
		if (node->child == NULL)
			node->child = trie_alloc(key[1]);

		node = node->child;
		key++;

	} while (1);
}

struct trie_t *
trie_find(struct trie_t *node, char *key)
{
	do {
		// find the nearest match, or the last node in the chain
		while (node->value != key[0] && node->next)
			node = node->next;

		// if there was no match, we're done
		if (node->value != key[0])
			return NULL;

		// if we've reached the end of string, we're done
		if (key[1] == '\0')
			return node;

		// if the matching node has no child node, no match
		if (node->child == NULL)
			return NULL;

		node = node->child;
		key++;

	} while(1);
}

