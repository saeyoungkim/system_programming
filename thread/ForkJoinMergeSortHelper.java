import java.util.concurrent.*;
import java.util.ArrayList;
import java.util.List;

public class ForkJoinMergeSortHelper implements Runnable {
    
    final static int THRESH_HOLD = 4;
    static ExecutorService pool = Executors.newFixedThreadPool(8);

    int[] arr;
    int start;
    int end;

    public ForkJoinMergeSortHelper(int[] _arr, int _start, int _end){
        this.arr = _arr;
        this.start = _start;
        this.end = _end;
    }

    private void insertionSort() {
        for(int j = start+1; j <= end; ++j){
            int pivot = arr[j];
            int i = j-1;
            for(; i >= start; --i){
                if(arr[i] > pivot) arr[i+1] = arr[i];
                else break;
            }
            arr[i+1] = pivot;
        }
        return ;
    }

    private void mergeSort() {
        int mid = (end - start) >> 1;

        try {
            pool.submit(new ForkJoinMergeSortHelper(arr, start, start+mid)).get();
            pool.submit(new ForkJoinMergeSortHelper(arr, start+mid+1, end)).get();
            pool.submit(new ForkJoinMergeHelper(arr, start, end)).get();
        } catch (InterruptedException e){
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }

        return ;
    }

    @Override
    public void run() {
        if(start >= end) return ;
        
        if(end - start <= THRESH_HOLD) insertionSort();
        else mergeSort();

        return ;
        
    }
}
