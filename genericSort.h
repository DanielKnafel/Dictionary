#ifndef __GEN_SORT_H
#define __GEN_SORT_H

void sort(void* arr, int size, int(*compare)(void*,int,int), void(*swap)(void*,int,int));

#endif
