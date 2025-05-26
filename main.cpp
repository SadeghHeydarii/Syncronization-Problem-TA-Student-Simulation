#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_CHAIRS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_ta_sleep = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_students = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_done_help = PTHREAD_COND_INITIALIZER;

sem_t chairs_sem;

int chairs[MAX_CHAIRS];
int front = 0, rear = 0;

int current_student = -1;
int ta_sleeping = 1;
int num_students = 0;
int students_helped = 0;

void enqueue(int id) {
    chairs[rear] = id;
    rear = (rear + 1) % MAX_CHAIRS;
}

int dequeue() {
    int id = chairs[front];
    front = (front + 1) % MAX_CHAIRS;
    return id;
}

int is_queue_empty() {
    return front == rear;
}

void* student_thread(void* arg) {
    int id = *(int*)arg;

    while (1) {
        if (sem_trywait(&chairs_sem) == 0) {
            pthread_mutex_lock(&mutex);

            enqueue(id);

            if (ta_sleeping) {
                ta_sleeping = 0;
                pthread_cond_signal(&cond_ta_sleep);
            }

            while (current_student != id)
                pthread_cond_wait(&cond_students, &mutex);

            pthread_mutex_unlock(&mutex);

            printf("Student %d is getting help from TA\n", id);
            sleep(2);

            pthread_mutex_lock(&mutex);
            current_student = -1;
            pthread_cond_signal(&cond_done_help);
            pthread_mutex_unlock(&mutex);

            sem_post(&chairs_sem);

            break;
        } else {
            printf("Student %d found no chair and will come back later\n", id);
            sleep(rand() % 3);
        }
    }

    return NULL;
}

void* ta_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (is_queue_empty()) {
            printf("TA is sleeping\n");
            ta_sleeping = 1;
            pthread_cond_wait(&cond_ta_sleep, &mutex);
        }

        int id = dequeue();
        current_student = id;
        pthread_cond_broadcast(&cond_students);

        pthread_cond_wait(&cond_done_help, &mutex);
        students_helped++;
        if (students_helped == num_students) {
            pthread_mutex_unlock(&mutex);
            printf("TA has helped all students. Exiting...\n");
            pthread_exit(NULL);
        }


        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char* argv[]) {

    num_students = atoi(argv[1]);
    pthread_t ta;
    pthread_t students[num_students];
    int ids[num_students];

    sem_init(&chairs_sem, 0, MAX_CHAIRS);

    pthread_create(&ta, NULL, ta_thread, NULL);

    for (int i = 0; i < num_students; i++) {
        ids[i] = i + 1;
        pthread_create(&students[i], NULL, student_thread, &ids[i]);
        sleep(rand() % 2);
    }

    for (int i = 0; i < num_students; i++) {
        pthread_join(students[i], NULL);
    }
    pthread_join(ta, NULL);
    sem_destroy(&chairs_sem);
    return 0;
}
