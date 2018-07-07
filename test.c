#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trie.h"
#include "file.h"

void
trie_dump(struct trie_t *n, size_t indent)
{
	if (!n)
		return;
	for (size_t i=0; i<indent; i++)
		printf("  ");
	printf("%c\n", n->value);
	trie_dump(n->child, indent+1);
	trie_dump(n->next, indent);
}

void
test_dump()
{
	struct trie_t *r = trie_alloc('@');
	trie_insert(r, "hello");
	trie_insert(r, "hi");
	trie_insert(r, "help");
	trie_insert(r, "diamonds");
	trie_dump(r, 0);
}

void
test_trie()
{
	struct trie_t *r = trie_alloc('@');
	trie_insert(r, "hello");
	trie_insert(r, "hi");
	trie_insert(r, "help");
	trie_insert(r, "diamonds");
	printf("PASS test_trie\n");
}

void
test_file()
{
	struct file_t file;
	file = file_init("test.txt");
	assert(strcmp(file_readline(&file), "a") == 0);
	assert(strcmp(file_readline(&file), "b") == 0);
	assert(strcmp(file_readline(&file), "c") == 0);
	assert(file_readline(&file) == NULL);
	file_close(&file);
	printf("PASS test_file\n");
}

int
main(int argc, char *argv[])
{
	test_dump();
	test_file();
	test_trie();
}
