#include <hellfire.h>

#define N	20
#define N_WRITERS	1


sem_t enchendo, mutex, cheia;
int32_t contaPostIt;

void user() {
	while(1) {
        hf_semwait(&enchendo);
        hf_semwait(&mutex);
        //colaPostIt_na_mochila();
        contaPostIt++;
		printf("cola postit na mochila %d\n", contaPostIt);
        if (contaPostIt==N)
            hf_sempost(&cheia);
        hf_sempost(&mutex);
    }
}

void pigeon() {
	while(1){
        hf_semwait(&cheia);
        hf_semwait(&mutex);
        // leva_mochila_ate_B_e_volta();
		printf("Levando mochila \n");
        contaPostIt=0;
		int i;
        for(i=0;i<N;i++)
            hf_sempost(&enchendo);
        hf_sempost(&mutex);
    }
}


void app_main(void){
	int32_t i;

	hf_seminit(&enchendo, N);
	hf_seminit(&mutex, 1);	
	hf_seminit(&cheia, 1);
	

	for(i = 0; i < 5; i++)
		hf_spawn(user, 0, 0, 0, "user", 2048);

	for(i = 0; i < 1; i++)
		hf_spawn(pigeon, 0, 0, 0, "pigeon", 2048);

}




















/*

sem_t mtx_rc, mtx_wc, mtx, w_db, r_db;
int32_t rc = 0, wc = 0, reads = 0, writes = 0;




void reader(void){
	int32_t i;

	i = hf_selfid();
	while(1){
		hf_semwait(&mtx);
		hf_semwait(&r_db);
		hf_semwait(&mtx_rc);
		rc++;
		if (rc == 1) hf_semwait(&w_db);
		hf_sempost(&mtx_rc);
		hf_sempost(&r_db);
		hf_sempost(&mtx);
		reads++;
		printf("(R) thread %d reading the database... (%d readers, %d reads, %d writes)\n", i, rc, reads, writes);
		hf_semwait(&mtx_rc);
		rc--;
		if (rc == 0) hf_sempost(&w_db);
		hf_sempost(&mtx_rc);
		printf("(R) thread void app_main(void){
	int32_t i;

	
	hf_seminit(&mtx_rc, 1);
	hf_seminit(&mtx_wc, 1);	
	hf_seminit(&mtx, 1);
	hf_seminit(&w_db, 1);
	hf_seminit(&r_db, 1);
	
	hf_seminit(&mtx, 1);
	hf_seminit(&w_db, 1);
	hf_seminit(&r_db, 1);

	for(i = 0; i < N_READERS; i++)
		hf_spawn(reader, 0, 0, 0, "reader", 2048);

	for(i = 0; i < N_WRITERS; i++)
		hf_spawn(writer, 0, 0, 0, "writer", 2048);

}%d using data...\n", i);
	}
}

void writer(void){
	int32_t i;
	hf_seminit(&mtx, 1);
	hf_seminit(&w_db, 1);
	hf_seminit(&r_db, 1);

	i = hf_selfid();
	while(1){
		hf_semwait(&mtx_wc);
		wc++;
		if (wc == 1) hf_semwait(&r_db);
		hf_sempost(&mtx_wc);
		printf("(W) thread %d preparing data...\n", i);
		hf_semwait(&w_db);
		writes++;
		printf("(W) thread %d writing to the database... (%d reads, %d writes)\n", i, reads, writes);
		hf_sempost(&w_db);
		hf_semwait(&mtx_wc);
		wc--;
		if (wc == 0) hf_sempost(&r_db);
		hf_sempost(&mtx_wc);
	}up
}
void app_main(void){
	int32_t i;

	
	hf_seminit(&mtx_rc, 1);
	hf_seminit(&mtx_wc, 1);	
	hf_seminit(&mtx, 1);
	hf_seminit(&w_db, 1);
	hf_seminit(&r_db, 1);
	
	hf_seminit(&mtx, 1);
	hf_seminit(&w_db, 1);
	hf_seminit(&r_db, 1);

	for(i = 0; i < N_READERS; i++)
		hf_spawn(reader, 0, 0, 0, "reader", 2048);

	for(i = 0; i < N_WRITERS; i++)
		hf_spawn(writer, 0, 0, 0, "writer", 2048);

}

*/
