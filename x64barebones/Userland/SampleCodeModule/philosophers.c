#include <philosophers.h>

int state[MAXPHILO]; 
int forkState[MAXPHILO];
int semaphores[MAXPHILO];
static int ph_count;
static int ph_id;
static int ph_mutex;
char c;


void createPhilosopher(){
	        ph_count++;
		    semaphores[ph_count] = sys_sem_open((void*) (long) ph_id);
		    state[ph_id] = THINKING;
            argumentsPointer arg=sys_my_malloc(sizeof(arguments));
            arg->ph_id=ph_id;
            ph_id++;
		    sys_create_args_process(philosopher,"mmimi",BACKGROUND,1,(void**)arg);
            //sys_create_process(philosopher,"mimi",BACKGROUND);
    
	//exit?
}

void philosopher(int argc,argumentsPointer arg) {
        sys_sleep(1); 
        take_fork(arg->ph_id); 
        sys_sleep(1); 
        put_fork(arg->ph_id); 

    
}

void deletePhilosopher(){
       
		    if(ph_count > 1){
			    sys_sem_close(semaphores[ph_count-1]);
			    ph_count--;
			    ph_id--;
                //terminar proceso?
		    }
	//exit?
}

void test(int id) { 
    if (state[id] == HUNGRY && ph_count>1
        && state[left(id)] != EATING //agarro comensal izquiero
        && state[right(id)] != EATING) { //agarro comensal derecho
        // state that eating 

        state[id] = EATING; 
        forkState[left(id)]=id;
        forkState[id]=id;
        
  
        sys_sleep(2); 
  
        print_ph_state();
  
        // sem_post(&S[phnum]) has no effect 
        // during takefork 
        // used to wake up hungry philosophers 
        // during putfork 
        sys_sem_post(semaphores[id]); 
    } 
}

void take_fork(int id) 
{ 

    sys_lock(&ph_mutex); 

    // state that hungry 
    state[id] = HUNGRY;  
    print_ph_state();

    // eat if neighbours are not eating 
    test(id); 
  
    sys_unlock(&ph_mutex); 
  
    // if unable to eat wait to be signalled 
    sys_sem_wait(semaphores[id]); 
  
    sys_sleep(1); 
} 

void put_fork(int id) 
{ 
   sys_lock(&ph_mutex); 
  
    // state that thinking 
    state[id] = THINKING; 
    forkState[left(id)]=MAXPHILO;
    forkState[id]=MAXPHILO;
    
    print_ph_state();
    test(left(id));
    test(right(id));
    sys_unlock(&ph_mutex);
    
} 


void print_ph_state() {
	for(int i = 0; i < ph_count; i++) {
		print_f("\nPhilosopher %d: ",i);
        if( state[i]==THINKING){
            print_f("THINKING\n");
        }
        else if(state[i]==HUNGRY){
            print_f("HUNGRY\n");
        }
        else{
            print_f("EATING\n");
        }
		print_f("Forks: ");
		if (forkState[left(i)] == MAXPHILO)
			print_f("Left Free , ");
		else
			print_f("Left Owner %d , ", forkState[left(i)]);
        if(forkState[i]==MAXPHILO){
            print_f("Right Free\n\n");
        }
        else{
            print_f("Right Owner %d\n\n",forkState[i]);
        }
	}

}

int left(int id){
    return (id + ph_count - 1) % ph_count;
}
int right(int id){
    return (id+1)%ph_count;
}

void philosophers() {
    //Setup
	ph_count = 0;
	ph_id = 0; 
    ph_mutex=0;
    int running=1;
    
    for(int i=0;i<MAXPHILO;i++){
        forkState[i]=MAXPHILO;
    }
        sys_clear_console();

    
	print_f("Press 'c' to create a new philosopher.\n");
    print_f("Press 'd' to delete one philosopher.\n");

    while(running){
        
        c=get_char();
        switch (c){
            case 'c':
		        sys_create_process(createPhilosopher,"mmimi",BACKGROUND);            
                break;

            case 'd':
                sys_create_process(deletePhilosopher,(void*)(long)ph_id,BACKGROUND);
            break;
            
        }
        {
        
        }
    }

	

}