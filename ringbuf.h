#include <stddef.h>

typedef struct ringbuf {
	char* start;
	char* write;
	char* read;	
	size_t size;
	size_t capacity;
} ringbuf_t;

ringbuf_t* ringbuf_create(size_t size);

void ringbuf_delete(ringbuf_t *buf);

int ringbuf_append(ringbuf_t *buf, char *data, size_t size);

int ringbuf_pop(ringbuf_t *buf, size_t size, char* target);

int ringbuf_pop_delimited(ringbuf_t* buf, char d, char* target, size_t target_size);

