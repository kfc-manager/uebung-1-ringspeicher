#include "ringbuf.h"
#include <stdlib.h>

ringbuf_t* ringbuf_create(size_t size) {
	ringbuf_t *buf = malloc(sizeof(ringbuf_t));
	if (!buf) return NULL;
	buf->size = 0;
	buf->capacity = size;
	buf->start = malloc(size);
	if (!buf->start) return NULL;
	buf->write = buf->start;
	buf->read = buf->start;
	return buf;
}

void ringbuf_delete(ringbuf_t *buf) {
	free(buf->start);
	free(buf);
}

int ringbuf_append(ringbuf_t *buf, char *data, size_t size) {
	if (buf->size + size/sizeof(char) > buf->capacity)  return -1; //not enough space in the ringbuffer
	if (size == 0UL) return 0; //empty sequence of char's, so we do nothing
	for (long unsigned int i = 0; i < size/sizeof(char); i++) {
		*buf->write = *data;
		data++;
		buf->size++;
		if ((long unsigned int) (buf->write - buf->start + 1) >= buf->capacity) {
			buf->write = buf->start; //write pointer is at the end of allocated storage and needs to be set to the start
			continue;
		}
		buf->write++; 
	}
	return 0;
}

int ringbuf_pop(ringbuf_t *buf, size_t size, char* target) {
	if (buf->size < size/sizeof(char)) return -1; //not enough characters in the ringbuffer
	if (size == 0UL) return 0;
	for (long unsigned int i = 0; i < size/sizeof(char); i++) {
		*target = *buf->read;
		target++;
		buf->size--;
		if ((long unsigned int) (buf->read - buf->start + 1) >= buf->capacity) {
			buf->read = buf->start;
			continue;
		}
		buf->read++;
	}
	return 0;
}

int ringbuf_pop_delimited(ringbuf_t* buf, char d, char* target, size_t target_size) {
	if (buf->size < target_size/sizeof(char)) return -1;
	if (target_size == 0UL) return 0;
	for (long unsigned int i = 0; i < target_size/sizeof(char); i++) {
		*target = *buf->read;
		buf->size--;
		if ((long unsigned int) (buf->read - buf->start + 1) >= buf->capacity) {
			buf->read = buf->start;
		} else {
			buf->read++;
		}
		if (*target == d) break; 
		target++;
	}
	return 0;
}

