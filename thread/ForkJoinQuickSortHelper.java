import java.util.concurrent.RecursiveTask;

public class ForkJoinQuickSortHelper extends RecursiveTask<Boolean> {
    
    final static int THRESH_HOLD = 10;
    int[] arr;
    int start;
    int end;

    public ForkJoinQuickSortHelper(int[] _arr, int _start, int _end) {
        this.arr = _arr;
        this.start = _start;
        this.end = _end;
    }

    private Boolean insertionSort() {
        for(int j = start+1; j <= end; ++j){
            int pivot = arr[j];
            int i = j-1;
            for(; i >= start; --i){
                if(arr[i] > pivot) arr[i+1] = arr[i];
                else break;
            }
            arr[i+1] = pivot;
        }
        return true;
    }

    private void swap(int[] a, int t1, int t2){
        int temp = a[t2];
        a[t2] = a[t1];
        a[t1] = temp;
    }

    private Boolean quickSort() {
        int pivot = arr[start];

        int l = start+1, r = end;

        while(l <= r) {
            if(arr[l] <= pivot) ++l;
            else {
                swap(arr, l, r);
                --r;
            }
        }

        swap(arr, start, r);

        System.out.println("changed position : " + r);

        ForkJoinQuickSortHelper leftPart = new ForkJoinQuickSortHelper(arr, start, r-1);
        ForkJoinQuickSortHelper rightPart = new ForkJoinQuickSortHelper(arr, r+1, end);

        return leftPart.fork().join() && rightPart.fork().join();
    }

    @Override
    public Boolean compute() {
        if(start >= end) return false;
        else if(end - start <= THRESH_HOLD) return insertionSort();
        
        return quickSort();
    }
}
