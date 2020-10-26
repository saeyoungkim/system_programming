import java.util.concurrent.*;

public class MergeSortHelper extends RecursiveTask<Boolean> {
    static final long serialVersionUID = 11251236123123L;
    
    private int[] arr;
    private int left, right;

    public static Boolean StartMerge(int _left, int _right, int[] _arr) {
        return new ForkJoinPool(8).invoke(new MergeSortHelper(_left, _right, _arr));
    }
    
    public MergeSortHelper(int _left, int _right, int[] _arr) {
        this.left = _left;
        this.right = _right;
        this.arr = _arr;
    }

    private void Merge(int left, int mid, int right, int[] arr){
        int size = right-left+1;
        int[] temp = new int[size];
        int l = left, r = mid+1;
        int i = 0;

        while(l <= mid && r <= right) {
            if(arr[l] <= arr[r]){
                temp[i++] = arr[l++];
            }
            else {
                temp[i++] = arr[r++];
            }
        }

        while(l <= mid) {
            temp[i++] = arr[l++];
        }

        while(r <= right){
            temp[i++] = arr[r++];
        }

        for(int j = 0; j < size; ++j){
            arr[j + left] = temp[j];
        }

        return ;
    }

    public Boolean compute() {
        System.out.println(Thread.currentThread().getName() + " " + Thread.currentThread().getId());

        if(left > right) return false;
        if(left == right) return true;

        int mid = left + ((right - left) >> 1);
        MergeSortHelper leftSort = new MergeSortHelper(left, mid, arr);
        MergeSortHelper rightSort = new MergeSortHelper(mid+1, right, arr);

        leftSort.fork();
        rightSort.fork();

        leftSort.join();
        rightSort.join();

        Merge(left, mid, right, arr);

        return true;
    }
}