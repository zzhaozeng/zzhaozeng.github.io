#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>


void swap(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void insertsort(int *arr, int l, int h)
{
    if (arr == NULL || h - l <= 0) return;

    if (h - l == 1) return;

    int i, j;
    for (i = l; i < h; i++) {
        for (j = i+1; j > 0 && arr[j-1] > arr[j]; j--) {
            swap(arr, j-1, j);
        }
    }
}

int issorted(int *arr, int n)
{
    if (arr == NULL || n <= 0) return -1;
    if (n == 1) return 0;

    int i;
    for (i = 1; i < n; i++)
        if (arr[i] > arr[i-1])
            return -1;
    return 0;
}

int randint(int l, int h)
{
    assert(l>=0 && h>=l);

    srand(time(NULL));
    int r = rand() % (h-l);

    return (l + r);
}

int partition(int *arr, int l, int h)
{
    int i = l, j = h+1;
    swap(arr, l, randint(l, h));
    int t = arr[l];

    while (1) {
        while (arr[++i] < t && i < h);
        while (arr[--j] > t && j > l);
        if (i > j) break;
        swap(arr, i, j);
    }
    swap(arr, l, j);

    return j;
}

void _qsort(int *arr, int l, int h)
{
    if (arr == NULL) return;
    if (l >= h) return;

    // partition之后，l~h这部分数组已排好序，返回值为划分元素的下标
    int m = partition(arr, l, h);

    _qsort(arr, l, m-1);
    _qsort(arr, m+1, h);
}

void merge(int *a, int l, int m, int h)
{

    int *aux = (int *) malloc(sizeof(int) * (h-l+1));

    int k;
    for (k = 0; k <= h-l; k++) //将a[l...h]复制到aux[l...h]
        aux[k] = a[l+k];
    
    // 归并到a[l...h]
    int i = 0, j = m-l+1;
    for (k = l; k <= h; k++) {
        if (i > m-l) a[k] = aux[j++];
        else if (j > h-l) a[k] = aux[i++];
        else if (aux[i] > aux[j]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }

    free (aux);
}

void mergesort(int *a, int l, int h)
{
    if (h <= l) return;
    int m = l + ((h-l) >> 1);

    mergesort(a, l, m);
    mergesort(a, m+1, h);
    merge(a, l, m, h);
}

int main()
{
    int v[] = {1, 3, 3, 10, 4, 2, 6, 5, 7, 8, 9};
    int n = sizeof(v) / sizeof(int);
    mergesort(v, 0, n);
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);

    assert(issorted(v, n));
    return 0;
}
