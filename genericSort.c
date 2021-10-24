void sort(void* arr, int size, int(*compare)(void*,int,int), void(*swap)(void*,int,int)) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-1-i; j++) {
            if (compare(arr, j, j+1) > 0) {
                swap(arr, j, j+1);
            }
        }
    }
}
