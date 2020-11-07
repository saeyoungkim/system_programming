import java.util.concurrent.*;

import java.util.concurrent.*;

public class ForkJoinMergeHelper implements Runnable {
    int[] arr;
    int start;
    int end;

    public ForkJoinMergeHelper(int[] _arr, int _start, int _end){
        this.arr = _arr;
        this.start = _start;
        this.end = _end;
    }

    private void merge() {
        int[] temp = new int[end-start+1];

        int mid = start + ((end - start) >> 1);

        int left_start = start;
        int right_start = mid+1;

        int idx = 0;
        int size = end - start + 1;

        while(left_start <= mid && right_start <= end) {
            if(arr[left_start] < arr[right_start]) temp[idx++] = arr[left_start++];
            else temp[idx++] = arr[right_start++];
        }

        while(left_start <= mid) {
            temp[idx++] = arr[left_start++];
        }

        while(right_start <= end) {
            temp[idx++] = arr[right_start++];
        }

        for(idx = 0; idx < size; ++idx){
            arr[start+idx] = temp[idx];
        }
    }

    @Override
    public void run() {
        merge();
        return ;
        
    }
}
