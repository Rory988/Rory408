## 2）交换类（Bubble / Quick）

### 2.1 冒泡排序（会写：一趟 + 提前结束 flag）

> “一趟冒泡”=相邻比较逆序就交换；若某一趟没有交换说明整体有序 

```C
void BubbleSort(int A[], int n){
    for(int i=0;i<n-1;i++){
        int swapped=0;
        for(int j=0;j<n-1-i;j++){
            if(A[j]>A[j+1]){
                swap(&A[j],&A[j+1]);
                swapped=1;
            }
        }C
        if(!swapped) break;
    }
}
```

### 2.2 快速排序（必会：Partition + 递归）

> 要点：以枢轴 pivot（常取 A[0]）为基准，**先从右往左找小于 pivot 的**，再从左往右找大于 pivot 的，循环直到 low==high 

```C
int Partition(int A[], int low, int high){
    int pivot = A[low];
    while(low < high){
        while(low<high && A[high] >= pivot) high--;
        A[low] = A[high];
        while(low<high && A[low] <= pivot) low++;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}
void QuickSort(int A[], int low, int high){
    if(low < high){
        int p = Partition(A, low, high);
        QuickSort(A, low, p-1);
        QuickSort(A, p+1, high);
    }
}
```

------

## 3）选择类（Simple Select / Heap）

### 3.1 简单选择排序（会写：每趟选最小）

> “每一趟在待排序元素中选取关键字最小的元素加入有序子序列” 

```C
void SelectSort(int A[], int n){
    for(int i=0;i<n-1;i++){
        int minp=i;
        for(int j=i+1;j<n;j++){
            if(A[j]<A[minp]) minp=j;
        }
        if(minp!=i) swap(&A[i],&A[minp]);
    }
}
```

------

## 4）堆（Heap）：408 常考“堆排序 + 堆插入/删除”

> 堆的定义（大根堆/小根堆）及父子下标关系 
>  堆排序：每趟把堆顶与末尾交换，再把剩余部分调整为堆（小元素“下坠”）

### 4.1（推荐背）

### 1 下标：AdjustDown / BuildHeap / HeapSort（大根堆排升序）

```C
void AdjustDown(int A[], int k, int len){ // 1..len
    A[0]=A[k];                 // 暂存
    for(int i=2*k; i<=len; i*=2){
        if(i<len && A[i]<A[i+1]) i++;     // 找更大的孩子
        if(A[0]>=A[i]) break;
        A[k]=A[i];
        k=i;
    }
    A[k]=A[0];
}
void BuildMaxHeap(int A[], int len){
    for(int i=len/2;i>=1;i--) AdjustDown(A,i,len);
}
void HeapSort(int A[], int len){
    BuildMaxHeap(A,len);
    for(int i=len;i>1;i--){
        swap(&A[1],&A[i]);
        AdjustDown(A,1,i-1);
    }
}
```

### 4.2 堆插入（上浮）与删除堆顶（下沉）

> 插入：新元素放表尾，与父结点比较，若更“小/大”则交换，一路“上升”
>  删除：用堆底元素替代被删元素，然后不断“下坠”直到不能下坠

```c
// 小根堆示例（1下标），插入：上浮
void HeapPush_Min(int H[], int *len, int x){
    int i=++(*len);
    while(i>1 && H[i/2] > x){
        H[i]=H[i/2];
        i/=2;
    }
    H[i]=x;
}
// 删除堆顶：下沉
int HeapPop_Min(int H[], int *len){
    int ret=H[1];
    int x=H[(*len)--];
    int i=1, child=2;
    while(child<=*len){
        if(child<*len && H[child+1]<H[child]) child++;
        if(x<=H[child]) break;
        H[i]=H[child];
        i=child; child*=2;
    }
    H[i]=x;
    return ret;
}
```