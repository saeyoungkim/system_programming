import java.util.concurrent.*;
import java.util.Random;

public class MergeSort {
    public static void main(String[] args) {
        int size = Integer.parseInt(args[0].trim());
    
        int[] arr = new int[size];

        Random random = new Random();
        
        for(int i = 0; i < size; ++i){
            arr[i] = random.nextInt(10000);
        }

        for (int i : arr) {
            System.out.print(i + " ");
        }
        System.out.println();

        MergeSortHelper.StartMerge(0, size-1, arr);

        for (int i : arr) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}
