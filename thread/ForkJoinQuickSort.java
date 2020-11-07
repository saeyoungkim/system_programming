import java.util.concurrent.*;

public class ForkJoinQuickSort {
    
    static int[] arr;

    private static void initialize(String[] args){
        arr = new int[args.length];
        for(int i = 0; i < args.length; ++i){
            arr[i] = Integer.parseInt(args[i]);
        }
    }

    private static void print() {
        for(int i = 0; i < arr.length; ++i){
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args){
        initialize(args);
        
        ForkJoinQuickSortHelper helper = new ForkJoinQuickSortHelper(arr, 0, args.length-1);

        print();

        helper.fork().join();

        print();
    }
}
