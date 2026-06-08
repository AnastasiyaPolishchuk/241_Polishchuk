#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int *array;
int N;
long long global_sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start;
    int end;
} ThreadData;

void* compute_sum(void* arg) {
    ThreadData *data = (ThreadData*) arg;
    long long local_sum = 0;
    
    for (int i = data->start; i < data->end; i++) {
        local_sum += array[i];
    }
    
    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    scanf("%d", &N);
    
    array = (int*) malloc(N * sizeof(int));
    
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 100;
    }
    
    printf("\nArray contents:\n");
    for (int i = 0; i < N; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
    
    int part_size = (N + 3) / 4;
    pthread_t threads[4];
    ThreadData thread_data[4];
    
    for (int t = 0; t < 4; t++) {
        int start = t * part_size;
        int end = (t == 3) ? N : (t + 1) * part_size;
        if (end > N) end = N;
        
        thread_data[t].start = start;
        thread_data[t].end = end;
    }
    
    for (int t = 0; t < 4; t++) {
        pthread_create(&threads[t], NULL, compute_sum, &thread_data[t]);
    }
    
    for (int t = 0; t < 4; t++) {
        pthread_join(threads[t], NULL);
    }
    
    printf("Total sum of all elements: %lld\n", global_sum);
    
    free(array);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}