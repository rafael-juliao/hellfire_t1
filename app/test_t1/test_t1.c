#include <hellfire.h>

#define DELAY_APERIODIC 5
#define RANDOM_MIN 300
#define RANDOM_MAX 1000

void aperiodic_task_2(void){
	printf("\nRUNNING APERIODIC 2 | RC: %d | ID: %d", _readcounter(), hf_selfid());
	delay_ms(DELAY_APERIODIC); // FAKE DELAY PROCESSING
}

void aperiodic_task(void){
	printf("\nRUNNING APERIODIC   | RC: %d | ID: %d", _readcounter(), hf_selfid());
	delay_ms(DELAY_APERIODIC); // FAKE DELAY PROCESSING
}

void realtime_worker(void){
	for(; ;){
		printf("\nRUNNING REAL TIME | RC: %d | ID: %d", _readcounter(), hf_selfid());
		delay_ms(1000); // FAKE DELAY WORKER DOING JOB
	}
}

void aperiodic_generator(void){

	for(; ;){
		int32_t time = RANDOM_MIN + ( random() % RANDOM_MAX );
		printf("\nCREATING APERIODIC | RC: %d | NEXT IN => %d", _readcounter(), time);
		hf_spawn(aperiodic_task, 0, 1, 0, "aperiodic_task", 1024);
		delay_ms(time);

		time = RANDOM_MIN + ( random() % RANDOM_MAX );
		printf("\nCREATING APERIODIC 2 | RC: %d | NEXT IN => %d", _readcounter(), time);
		hf_spawn(aperiodic_task_2, 0, 1, 0, "aperiodic_task_2", 1024);
		delay_ms(time);
	}
}

void app_main(void){
	int32_t i;
	printf("\n~~>APP STARTED<~~ | RC: %d ", _readcounter());

	
	hf_spawn(realtime_worker, 20, 10, 20, "worker 1", 1024);
	hf_spawn(realtime_worker, 20, 4, 20, "worker 2", 1024);
	hf_spawn(realtime_worker, 20, 5, 20, "worker 3", 1024);

	hf_spawn(aperiodic_generator, 0, 0, 0, "aperiodic_gen", 1024);

}