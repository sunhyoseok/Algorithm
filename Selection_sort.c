#include <stdio.h>

/*
    Loop-invariant : 0~i까지의 sub array가 정렬된 상태를 유지한다.
    Time complexity : O(n^2)
*/

int main(void){
    int i, j, temp, index, min;
    int array[10] = {1, 10, 5, 8, 7, 6, 4, 3, 2, 9};

    for(i=0; i<10; i++){
        min = 9999;  //  충분히 큰 값
        for(j=i; j<10; j++){
            if(min > array[j]){
                min = array[j];
                index = j;
            }
        }
        temp = array[index];
        array[index] = array[i];
        array[i] = temp;
    }

    for(i=0; i<10; i++){
        printf("%d \n", array[i]);
    }
    return 0;
}