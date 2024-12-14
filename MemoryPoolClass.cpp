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
