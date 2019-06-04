#include <philosophers.h>

int state[MAXPHILO]; 
int forkState[MAXPHILO];
int semaphores[MAXPHILO];
static int philo_process[MAXPHILO];
 int ph_count;
static int ph_id;
static int ph_mutex;
char c;
static char * philo_name="Philosopher N";



void create_philosopher(){
    argumentsPointer arg = sys_my_malloc(sizeof(arguments));
    if(arg==NULL){
        print_f("Malloc Error, cant create more philosophers\n");
    }
    else{
        philo_name[12]=(char)(ph_id + '0');
	    semaphores[ph_count] = sys_sem_open((void*) (long) ph_id);
	    state[ph_id] = THINKING;
        ph_count++;
        arg->ph_id=ph_id;
	    philo_process[ph_id]=sys_create_args_process(philosopher,philo_name,BACKGROUND,1,(void**)arg);
        ph_id++;
        // print_f("ID: ");
        // for(int i=0;i<MAXPHILO;i++){
        //     print_f("%d, ",philo_process[i]);
        // }
        // print_f("\n");
    }
}

void philosopher(int argc,argumentsPointer arg) {
    while(1){
        sys_sleep(5); 
        take_fork(arg->ph_id); 
        sys_sleep(5); 
        put_fork(arg->ph_id); 
    }
    
}

void delete_philosopher(){
		sys_sem_close(semaphores[ph_count-1]);
	    ph_count--;
        ph_id--;

        //print_f("Delete:\nID:%d PhiloProcess: %d\n",ph_id,philo_process[ph_id]);


        sys_kill_process(philo_process[ph_id]);

        // print_f("ID: ");
        // for(int i=0;i<MAXPHILO;i++){
        //     print_f("%d, ",philo_process[i]);
        // }
        // print_f("\n");

        // sys_print_all_procceses();
        // print_f("\n");
}

void test(int id) { 
    if (state[id] == HUNGRY && ph_count>1
        && state[left(id)] != EATING //agarro comensal izquiero
        && state[right(id)] != EATING) { //agarro comensal derecho
        // state that eating 

        state[id] = EATING; 
        forkState[left(id)]=id;
        forkState[id]=id;
        
  
        sys_sleep(5); 
        //print_ph_state();
  
        //sem_post(semaphores[id]) has no effect during takefork 
        // used to wake up hungry philosophers during putfork 
        sys_sem_post(semaphores[id]); 
    } 
}

void take_fork(int id) 
{ 

    sys_lock(&ph_mutex); 

    // state that hungry 
    state[id] = HUNGRY;  

    //print_ph_state();

    // eat if neighbours are not eating 
    test(id); 
  
    sys_unlock(&ph_mutex); 
  
    // if unable to eat wait to be signalled 
    sys_sem_wait(semaphores[id]); 
  
    sys_sleep(5); 
} 

void put_fork(int id) 
{ 
   sys_lock(&ph_mutex); 
  
    // state that thinking 
    state[id] = THINKING; 
    forkState[left(id)]=MAXPHILO;
    forkState[id]=MAXPHILO;
    
    //print_ph_state();
           

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
    print_f("----------------------------\n");   


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
    // int create_process; ver!
    // int delete_process;
    
    for(int i=0;i<MAXPHILO;i++){
        forkState[i]=MAXPHILO;
    }
    sys_clear_console();

    
	/*print_f("Press 'c' to create a new philosopher.\n");
    print_f("Press 'd' to delete one philosopher.\n");
    print_f("Press 'q' to quit dining philosophers\n");*/

    create_philosopher();
    create_philosopher();
    create_philosopher();

    sys_create_process(print_ui,"uicomensales", FOREGROUND);
    while(running){
        c=get_key();
        switch (c){
            case 'c':
                if(ph_count<MAXPHILO){
                    create_philosopher();
                    // sys_print_all_procceses();
                    // print_f("\n");
                }
                break;
            case 'd':
                if(ph_count>0) delete_philosopher();
                break;
            case 'q':
                running=0;
                print_f("QUIT\n");
                while (ph_count>0) delete_philosopher();
                sys_print_all_procceses();
                break;
        }
    }
}

int min(int a, int b){
        if(a < b) return a;
        return b;
}

int max(int a, int b){
        if(a < b) return b;
        return a;
}