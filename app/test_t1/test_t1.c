#include <hellfire.h>

void thread(void)
{
	int i = 0;
	for(; i < 10; i++){
		printf("t%d\n", hf_selfid());
		delay_ms(1000);
	}
}

void app_main(void){
	int32_t i;
	
	for (i = 0; i < 10; i++)
		hf_spawn(thread, 0, 2, 20, "thread", 1024);
}