#include <iostream>
#include <cstdlib>
using namespace std;

class Mem_Pool{

    public:
        struct Block{
            Block *next;
        };
        int num_chunks = 8,chunk_size = 128;
        Block *head = NULL;
        Block *memory_pool = (Block*)malloc(num_chunks*chunk_size);
        Mem_Pool(){
            for(int i=0;i<num_chunks;i++){
                Block *block = (Block*)(memory_pool + i*chunk_size);
                block->next = head;
                head = block;
            }
        }
        void* allocate_block(){
            if(head == NULL){cout<<"Memory pool exhuasted!\n";return nullptr;}
            Block *allocated_block = head;
            head = head->next;
            return (void*)allocated_block;
        }
        void free_block(void* block){
            if(block == NULL){cout<<"Can't free a NULL block";return ;}
            Block *reallocated_block = (Block*) block;
            reallocated_block->next = head;
            head = reallocated_block;
        }
        void display_list(){
            int ct=0;
            Block *temp = head;
            while(temp != NULL){
                cout<<"Block free at address"<<temp<<"\n";
                temp = temp->next;
                ct++;
            }
            cout<<"Number of empty blocks: "<<ct<<"\n";
        }
        void terminate_pool() {
            free(memory_pool);
            memory_pool = NULL;
            head = NULL;
        }
};

int main(){
    Mem_Pool pool;
    void *last_allocated;
    while(1){
        int option;
        cout<<"Choose option:\n1.Allocate Block\n2.Free Block.\n3.Display List\n0.Exit\n->";
        cin>>option;
        if(option == 0){pool.terminate_pool();break;}
        if(option == 1){
            int type;
            cout<<"Enter variable type:\n1.Int\n2.Fhloat\n->";cin>>type;cout<<"\n";
            if(type == 1){
                int *one = (int*)pool.allocate_block();
                last_allocated = one;
                cout<<one;
                if(one == nullptr){int ct;cout<<"Continue?1/0:";cin>>ct;if(ct==0){break;}}
            }
            if(type == 2){
                float *one = (float*)pool.allocate_block();
                last_allocated = one;
                cout<<one;
                if(one == nullptr){int ct;cout<<"Continue?1/0:";cin>>ct;if(ct==0){break;}}
            }
        }
        if(option == 2){
            pool.free_block(last_allocated);
            cout<<"Block freed.\n";
            int ct;
            cout<<"Continue?1/0:";cin>>ct;if(ct==0){break;}

        }
        if(option == 3){
            int ct;
            pool.display_list();
            cout<<"Continue?1/0:";cin>>ct;if(ct==0){break;}
        }
        
    }
    return 0;

}
