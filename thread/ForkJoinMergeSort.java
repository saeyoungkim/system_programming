import java.util.concurrent.ExecutionException;

public class ForkJoinMergeSort {
    private static void print(int[] arr, int length) {
        for(int i = 0; i < length; ++i){
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }
    public static void main(String[] args) {
        int length = args.length;
        int[] arr = new int[length];
        for(int i = 0; i < length; ++i){
            arr[i] = Integer.parseInt(args[i]);
        }

        print(arr, length);

        try {
            ForkJoinMergeSortHelper.pool.submit(new ForkJoinMergeSortHelper(arr, 0, length-1)).get();
        } catch (InterruptedException e){
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }

        print(arr, length);

        ForkJoinMergeSortHelper.pool.shutdown();
    }
}
