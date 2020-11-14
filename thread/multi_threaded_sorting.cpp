#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

#define INVALID_ARGUMENTS 1
#define CANNOT_CREATE_THREAD 2

struct Parameter {
    int* arr;
    int size;

    Parameter(int _size, char** _arr) {
        size = _size;
        arr = new int[size];

        for(size_t idx = 0; idx < size; ++idx){
            arr[idx] = atoi(_arr[idx+1]);
        }
    }

    Parameter(int _size, int* _arr) {
        size = _size;
        arr = _arr;
    }
};

void quick_sort(int left, int right, int* arr) {
    if(left >= right) return ;

    int pivot = arr[left];

    int l = left+1;
    int r = right;
    
    while(l <= r){
        if(arr[l] > pivot){
            std::swap(arr[l], arr[r--]);
        }
        else ++l;
    }

    std::swap(arr[r], arr[left]);

    quick_sort(left, r-1, arr);
    quick_sort(r+1, right, arr);
}

void* sort_worker(void* param) {
    struct Parameter* param_pt = (Parameter*)param;

    quick_sort(0, param_pt->size-1, param_pt->arr);
    return NULL;
}

void merge(int left, int mid, int right, int* arr) {
    int* tmp = new int[right - left + 1];

    int left_start = left, left_end = mid-1, right_start = mid, right_end = right;

    int idx = 0;
    while(left_start <= left_end && right_start <= right_end) {
        if(arr[left_start] < arr[right_start]) tmp[idx++] = arr[left_start++];
        else tmp[idx++] = arr[right_start++];
    }

    while(left_start <= left_end){
        tmp[idx++] = arr[left_start++];
    }

    while(right_start <= right_end){
        tmp[idx++] = arr[right_start++];
    }

    idx = 0;
    while(left <= right){
        arr[left++] = tmp[idx++];
    }

    delete[] tmp;
}

void* merge_worker(void* params) {
    struct Parameter* param_pt = (Parameter*)params;
    
    merge(0, param_pt->size >> 1, param_pt->size - 1, param_pt->arr);
    return NULL;
}

void print(Parameter* param){
    for(int i = 0; i < param->size; ++i){
        std::cout << param->arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    if(argc == 1){
        fprintf(stderr, "arguments must be existed more than 1\n");
        std::exit(INVALID_ARGUMENTS);
    }

    Parameter param(argc-1, argv);

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_t sort_thread[2];

    int mid = (argc-1) >> 1;

    Parameter sub_params_1(mid, (param.arr));
    Parameter sub_params_2(param.size-mid, (int*)(param.arr+mid));

    if(pthread_create(&sort_thread[0], &attr, sort_worker, &sub_params_1) != 0){
        fprintf(stderr, "threads does not be created\n");
        std::exit(CANNOT_CREATE_THREAD);        
    }
    

    if(pthread_create(&sort_thread[1], &attr, sort_worker, &sub_params_2) != 0){
        fprintf(stderr, "threads does not be created\n");
        std::exit(CANNOT_CREATE_THREAD);        
    }

    pthread_join(sort_thread[0], NULL);
    pthread_join(sort_thread[1], NULL);

    pthread_t merge_thread;

    if(pthread_create(&merge_thread, &attr, &sort_worker, &param) != 0){
        fprintf(stderr, "threads does not be created\n");
        std::exit(CANNOT_CREATE_THREAD);        
    }

    pthread_join(merge_thread, NULL);

    fprintf(stdout, "merge sort finished\n");

    print(&param);

    return 0;
} 