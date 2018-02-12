/**Description:
* This is a simple ring buffer
* for one write and one read threads
*
* Author:SunYang
* Date: 2017.2.12
 */

#ifndef _INC_LIBCIRCULAR_
#define _INC_LIBCIRCULAR
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct{
	uint8_t* p_buf;
	uint32_t u_buff_size;
	uint64_t u_head;
	uint64_t u_tail;
}circular_buf_ctx;

int circular_buffer_init(circular_buf_ctx *c, int size);

int circular_buffer_reset(circular_buf_ctx *c);

circular_buf_ctx *circular_buffer_alloc(int size);

//return value: the actual write to ring buffer data size
int circular_buffer_push(circular_buf_ctx *c, uint8_t *pdata, int size);

//return value: the actual read from ring buffer data size
int circular_buffer_pop(circular_buf_ctx *c, uint8_t *pdata, int size);

int circular_buffer_len(circular_buf_ctx *c);

void circular_buffer_free(circular_buf_ctx *c);

#ifdef __cplusplus
}
#endif


#endif