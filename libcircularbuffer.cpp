#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libcircularbuffer.h"

#define MIN(a, b) (((a) > (b)) ? (b) : (a))

int circular_buffer_init(circular_buf_ctx *c, int size)
{
	int ret = 0;
	uint8_t *p_data = NULL;
		
	p_data = (uint8_t *)malloc(size);
	if(!p_data)
		return -1;

	c->p_buf  = p_data;
	c->u_buff_size = size;
	c->u_head = c->u_tail = 0;

	return 0;
}

int circular_buffer_reset(circular_buf_ctx *c)
{
	int ret = -1;
	if(c)
	{
		c->u_head = 0;
		c->u_tail = 0;
		ret = 0;
	}
	
	return ret;
}

circular_buf_ctx *circular_buffer_alloc(int size)
{
	circular_buf_ctx *p	= NULL;
	int ret				= 0;

	p = (circular_buf_ctx *)malloc(sizeof(circular_buf_ctx));
	if(!p)
		return p;

	ret = circular_buffer_init(p, size);

	if(ret < 0){
		free(p);
		return p;
	}
	
	return p;
}

int circular_buffer_push(circular_buf_ctx *c, uint8_t *pdata, int size)
{
	uint64_t head = c->u_head;
	uint64_t tail = c->u_tail;
	int len = 0;

	assert( (int)(head > tail)>=0 );

	if(!pdata || !size)
		return -1;

	size = MIN(size, c->u_buff_size - head + tail);	
	len  = MIN(size, c->u_buff_size - head % c->u_buff_size);
	memcpy(c->p_buf + (head % c->u_buff_size), pdata, len);
	memcpy(c->p_buf, pdata+len, size-len);

	c->u_head = head + size;

	return size;
}

int circular_buffer_pop(circular_buf_ctx *c, uint8_t *pdata, int size)
{
	uint64_t head = c->u_head;
	uint64_t tail = c->u_tail;
	int len = 0;

	assert( (int)(head -tail) >= 0 );
	
	if(!pdata || !size)
		return -1;

	size = MIN(size, head - tail);
	len  = MIN(size, c->u_buff_size - (tail % c->u_buff_size));
	memcpy(pdata, c->p_buf + (tail % c->u_buff_size), len );
	memcpy(pdata + len, c->p_buf, size-len );

	c->u_tail = tail + size;

	return size;
}

int circular_buffer_len(circular_buf_ctx *c)
{
	return (c->u_head - c->u_tail);
}

void circular_buffer_free(circular_buf_ctx *c)
{
	if(c){
		if(c->p_buf){
			free(c->p_buf);
			c->p_buf = NULL;
		}
		free(c);
	}
}