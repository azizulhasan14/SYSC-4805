void quickSort(volatile uint32_t * arr, int len) {
  _quickSort(arr, 0, len - 1);
}

// function to calculate the median of the array
uint32_t getMedian(volatile uint32_t * arr, int n)
{
  uint32_t median = 0;

  // if number of elements are even
  if (n % 2 == 0)
    median = (arr[(n - 1) / 2] + arr[n / 2]) / 2.0;
  // if number of elements are odd
  else
    median = arr[n / 2];

  return median;
}

void _quickSort(volatile uint32_t arr[], int a, int b) {
  if (a >= b)
    return;

  uint32_t key = arr[a];
  int i = a + 1, j = b;
  while (i < j) {
    while (i < j && arr[j] >= key)
      --j;
    while (i < j && arr[i] <= key)
      ++i;
    if (i < j)
      _swap(arr, i, j);
  }
  if (arr[a] > arr[i]) {
    _swap(arr, a, i);
    _quickSort(arr, a, i - 1);
    _quickSort(arr, i + 1, b);
  } else { // there is no left-hand-side
    _quickSort(arr, a + 1, b);
  }
}

void _swap(volatile uint32_t arr[], int i, int j) {
  uint32_t temp = arr[j];
  arr[j] = arr[i];
  arr[i] = temp;
}
