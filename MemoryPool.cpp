#include <iostream>
#define POOL_SIZE 1024
#define CHUNK_SIZE 128
#define NUM_CHUNKS (POOL_SIZE / CHUNK_SIZE)
using namespace std;

struct Block{
    Block *next;
};
Block *head = NULL;
Block memory_pool[POOL_SIZE];
void init_pool(){
    for(int i=0;i<NUM_CHUNKS;i++){
        Block *block = (Block*)(memory_pool + i*CHUNK_SIZE);
        block->next = head;
        head = block;
    }   
}
void* allocate_block(){
    if(head == NULL){printf("Memory pool exhausted");return NULL;}
    Block *allocated_block = head;
    head = head->next;
    return (void*)allocated_block;
}
void deallocate_block(void *block){
    if(block == NULL){cout<<"Can't free NULL block";return ;}
    Block *reallocated_block = (Block *)block;
    reallocated_block->next = head;
    head = reallocated_block;
}
void display_list(){
    int ct = 0;
    Block *temp = head;
    while(temp!=NULL){
        cout<<"Block at adress: "<<temp<<"\n";
        temp = temp->next;
        ct++;
    }
    cout<<"Total free blocks: "<<ct<<endl;
}
int main(){

    init_pool();
    void *one = allocate_block();
    void *two = allocate_block();
    void *three = allocate_block();
    deallocate_block(two);
    deallocate_block(three);
    display_list();
    return 0;
}