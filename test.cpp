#include "libcircularbuffer.h"

int main()
{
	int ret_w = 0;
	int ret_r = 0;
	uint8_t wtest[10]={'0','1','2','3','4','5','6','7','8','9'};
	uint8_t rtest1[10]={"0"};
	uint8_t rtest2[10]={"0"};

	circular_buf_ctx *ctx = circular_buffer_alloc(10);

	ret_w = circular_buffer_push(ctx, wtest, 8);
	ret_r = circular_buffer_pop(ctx, rtest1, 7);

	ret_r = circular_buffer_pop(ctx, rtest1, 5);
	ret_r = circular_buffer_pop(ctx, rtest1, 5);
	//ret_w = circular_buffer_push(ctx, wtest, 3);


	

	ret_w = circular_buffer_push(ctx, wtest, 5);
	ret_r = circular_buffer_pop(ctx, rtest2, 6);


	ret_r = circular_buffer_pop(ctx, rtest2, 4);
	return 0;

}