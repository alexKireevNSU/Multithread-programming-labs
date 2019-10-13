#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void* print_strings(void* args){
        int i;
        for(i = 0; i < 4; i++){
                printf("%s\n", ((char**)args)[i]);
        }
        pthread_exit(NULL);
}

int main(){
        const int num_of_threads = 16;
        pthread_t threads[num_of_threads];
        char* string[num_of_threads*4];
        int i;
        for(i = 0; i < num_of_threads*4; i++){
                char* tmp = (char*)malloc(sizeof(char)*128);
                if(tmp == NULL){
                        perror("Failed to allocate memory");
                        pthread_exit(NULL);
                }
                string[i] = tmp;
                sprintf(string[i], "t%d: abcd%d", i/4, i);
        }
        for(i = 0; i < num_of_threads; i++){
                int stat;
                stat = pthread_create(&(threads[i]), NULL, print_strings, (void*)(string + i*4));
                if(stat != 0){
                        perror(NULL);
                        return -1;
                }
        }
        for(i = 0; i < num_of_threads; i++){
                int err = pthread_join(threads[i], NULL);
                if(err != 0){
                        perror(NULL);
                }
        }
        for(i = 0; i < num_of_threads*4; i++)
                free(string[i]);
        pthread_exit(NULL);
}
