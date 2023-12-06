#include <stdio.h>
#include <stdlib.h>
void allocArray(int ***p, int m, int n)
{
  int **arr = (int **)malloc(sizeof(int*) * m);
  int *data = (int *)malloc(sizeof(int) * m * n);
  if(arr == NULL)return;
  for(int i = 0 ; i < m ; i ++)
    arr[i] = &data[i*n];
  *p = arr;
}

int main()
{
  int **array, *a;
  int j, k;
  allocArray(&array, 5, 10);
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      scanf("%p ", &(array[j][k]));

  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      printf("%p ", &(array[j][k]));
}
