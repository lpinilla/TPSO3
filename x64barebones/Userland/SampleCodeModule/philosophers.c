#include <philosophers.h>


int state[MAXPHILO]; 
int forkState[MAXPHILO];
int semaphores[MAXPHILO];
int ph_count;
int static ph_id;
int ph_mutex;
char c;


void createPhilosopher(){
	while(1){
        if((c=get_char())=='c'){
		semaphores[ph_count] = sys_sem_open((void*) (long) ph_id);
		//philosopherId[ph_count] = id;
		state[ph_count] = 2;
		ph_id++;
		ph_count++;
		sys_create_process(philosopher,(void*)(long)ph_id,BACKGROUND);
        }
	}
	//exit?
}

void deletePhilosopher(){
	while(1){
        if((c=get_char())=='d'){
		    if(ph_count > 1){
			    sys_sem_close(semaphores[ph_count-1]);
			    ph_count--;
			    ph_id--;
                //terminar proceso?
		    }
        }
	}

	//exit?
}

void test(int ph_id) 
{ 
    if (state[ph_id] == 1
        && state[(ph_id + ph_count - 1) % ph_count] != 0 //agarro comensal izquiero
        && state[(ph_id + 1) % ph_count] != 0) { //agarro comensal derecho
        // state that eating 
        state[ph_id] = 0; 
  
        sys_sleep(2); 
  
        print_ph_state();
  
        // sem_post(&S[phnum]) has no effect 
        // during takefork 
        // used to wake up hungry philosophers 
        // during putfork 
        sys_sem_post(semaphores[ph_id]); 
    } 
}

void take_fork(int ph_id) 
{ 
  
    sys_lock(&ph_mutex); 
  
    // state that hungry 
    state[ph_id] = 1;  
  
    print_ph_state();

    // eat if neighbours are not eating 
    test(ph_id); 
  
    sys_unlock(&ph_mutex); 
  
    // if unable to eat wait to be signalled 
    sys_sem_wait(semaphores[ph_id]); 
  
    sys_sleep(1); 
} 

void put_fork(int ph_id) 
{ 
  
   sys_lock(&ph_mutex); 
  
    // state that thinking 
    state[ph_id] = 2; 
  
    print_ph_state();
  
    test((ph_id + ph_count - 1) % ph_count); //izquierdo
    test((ph_id + 1) % ph_count); //derecho
  
    sys_unlock(&ph_mutex); 
} 




void philosopher(void* id) {
        int* i = id; 
        sys_sleep(1); 
        take_fork(*i); 
        sys_sleep(0); 
        put_fork(*i); 
    
}

void print_ph_state() {
	for(int i = 0; i < ph_count; i++) {
		print_f("Philosopher %d: %d \n", i, state[i]);
		print_f("Fork - ");

		if (forkState[i] == -1)
			print_f("Free\n\n");
		else
			print_f("Owner %d\n\n", forkState[i]);
	}

}



void dining_philosophers() {
    //Setup
	ph_count = 0;
	ph_id = 0; 

	
    sys_clear_console();
	print_f("Press 'c' to create a new philosopher.\n");
    print_f("Press 'd' to delete one philosopher.\n");

    sys_create_process(createPhilosopher,(void*)(long) ph_id,BACKGROUND);
    sys_create_process(deletePhilosopher,(void*)(long)ph_id,BACKGROUND);

	
	while(1);
	
}