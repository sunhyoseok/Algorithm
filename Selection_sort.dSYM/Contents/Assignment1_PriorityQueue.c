#include<stdio.h>
#include<stdlib.h>
#include <stdint.h>
#define HEAP_MAX 500000



//  Heap implementation

typedef struct _heap{
    int data[HEAP_MAX];
    int size;
} heap;

void initHeap(heap* h){
    h->size = 0;
}

int isEmpty(heap* h){
    if(h->size == 0){
        return 1;
    }
    return 0;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Parent(int i){
    return i/2;
}
int Left(int i){
    return 2*i;
}
int Right(int i){
    return 2*i + 1;
}

void MaxHeapify(heap* h, int i){
    int l, r, largest;
    l = Left(i);
    r = Right(i);
    if((l <= h->size) && (h->data[l] > h->data[i])){
        largest = l;
    }
    else{
        largest = i;
    }

    if((r <= h->size) && h->data[r] > h->data[largest]){
        largest = r;
    }
    if(largest != i){
        swap(h->data+i, h->data+largest);
        MaxHeapify(h, largest);
    }
    //  O(lg(n))
}

void MinHeapify(heap* h, int i){
    int l, r, smallest;
    l = Left(i);
    r = Right(i);
    if((l <= h->size) && (h->data[l] < h->data[i])){
        smallest = l;
    }
    else{
        smallest = i;
    }

    if((r <= h->size) && (h->data[r] < h->data[smallest])){
        smallest = r;
    }
    if(smallest != i){
        swap(h->data+i, h->data+smallest);
        MinHeapify(h, smallest);
    }
    //  O(lg(n))
}

void BuildMaxHeap(heap* h){
    for(int i = h->size/2; i > 0; i--){
        MaxHeapify(h, i);
    }
    //  O(n)
}

void BuildMinHeap(heap* h){
    for(int i = h->size/2; i > 0; i--){
        MinHeapify(h, i);
    }
    //  O(n)
}

void HeapIncreaseKey(heap* maxHeap, int i, int key){
    if(key < maxHeap->data[i]){
        printf("error: new key is smaller than current key \n");
        exit(1);
    }
    maxHeap->data[i] = key;
    while((i > 1) && maxHeap->data[Parent(i)] < maxHeap->data[i]){
        swap(maxHeap->data+i, maxHeap->data+Parent(i));
        i = Parent(i);
    }
}

void HeapDecreaseKey(heap* minHeap, int i, int key){
    if(key > minHeap->data[i]){
        printf("error: new key is bigger than current key \n");
        exit(1);
    }
    minHeap->data[i] = key;
    while((i > 1) && minHeap->data[Parent(i)] > minHeap->data[i]){
        swap(minHeap->data+i, minHeap->data+Parent(i));
        i = Parent(i);
    }
    //  O(lg(n))
}    

void insert(heap* maxHeap, heap* minHeap, int element){
    if(element < maxHeap->data[0]){
        /*
            maxHeap->data[0]: 기준값
            element가 기준값보다 작으므로 maxHeap에 insert
        */  
        maxHeap->data[maxHeap->size] = INT32_MIN;   //  max heap의 성질을 깨지 않기 위함
        HeapIncreaseKey(maxHeap, maxHeap->size, element);
        maxHeap->size += 1;
    }
    else{
        //  element가 기준값보다 크므로 minHeap에 insert(element가 unique하다는 전제)
        minHeap->data[minHeap->size] = INT32_MAX;
        HeapDecreaseKey(minHeap, minHeap->size, element);
        minHeap->size += 1;
    }

    //  O(lg(n))
}

int find_median(heap* maxHeap){
    //  max heap의 root node 리턴
    return maxHeap->data[0];
}

int find_max(heap* minHeap){
    int max;
    BuildMaxHeap(minHeap);
    max = minHeap->data[0];  //  max heap의 rootnode이므로 최댓값
    BuildMinHeap(minHeap);
    return max;
}

int find_min(heap* maxHeap){
    int min;
    BuildMinHeap(maxHeap);
    min = maxHeap->data[0];
    BuildMaxHeap(maxHeap);
    return min;
}

int delete_median(heap* maxHeap){
    //  max heap의 root node 삭제
    int median = maxHeap->data[0];
    swap(&maxHeap->data[maxHeap->size-1], &maxHeap->data[0]);
    maxHeap->size -= 1;
    MaxHeapify(maxHeap, 0);
}

int delete_max(heap* minHeap){
    int max;
    BuildMaxHeap(minHeap);  //  minHeap -> maxHeap
    max = minHeap->data[0];
    //  delete max
    swap(&minHeap->data[minHeap->size-1], &minHeap->data[0]);
    minHeap->size -= 1;
    BuildMinHeap(minHeap);
    //  최댓값을 삭제한 후 다시 min heap으로 만들기
    //  어차피 BuildMinHeap을 실행시킬 것이기 때문에 swap이후에 maxheapify를 안해도 됨
    return max;
}

int delete_min(heap* maxHeap){
    int min;
    BuildMinHeap(maxHeap);
    min = maxHeap->data[0];
    // delete min
    swap(&maxHeap->data[maxHeap->size-1], &maxHeap->data[0]);
    maxHeap->size -= 1;
    BuildMaxHeap(maxHeap);
    return min;
}

int main(void){
    heap maxHeap, minHeap;
    int iteration, operationType, input;
    initHeap(&maxHeap);
    initHeap(&minHeap);
    maxHeap.data[0] = INT32_MAX;    
    //  첫번째 input이 들어오기전에 기준값 최대로 설정. 첫번째 input이 max heap의 root node가 되도록하기 위함.
    
    scanf("%d", &iteration);

    for(int i=0; i<iteration; i++){
        scanf("%d", &operationType);
        switch (operationType) {
            case 'I':
                scanf("%d", &input);
                insert(&maxHeap, &minHeap, input);
                break;
            case 'D':
                scanf("%d", &input);
                if(input == 'M'){
                    delete_min(&maxHeap);
                }
                else if(input == 'X'){
                    delete_max(&minHeap);
                }
                else if(input == 'E'){
                    delete_median(&maxHeap);
                }
                break;
            case 'F':
                scanf("%d", &input);
                if(input == 'M'){
                    find_min(&maxHeap);
                }
                else if(input == 'X'){
                    find_max(&minHeap);
                }
                else if(input == 'E'){
                    find_median(&maxHeap);
                }
                break;
            default:
                printf("error: Invalid operation type\n");
                exit(-1);
                break;
        }
    }

    return 0;
}

