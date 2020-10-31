import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class PrimaryNumberHelper implements Runnable {

    Integer n;

    public PrimaryNumberHelper(Integer v){
        n = v;
    }

    static void print(Integer v) {
        PrimaryNumberHelper helper = new PrimaryNumberHelper(v);
        ExecutorService executor = Executors.newSingleThreadExecutor();
        executor.submit((Runnable)helper);
        executor.shutdown();
    }

    public void run() {
        Integer root = (int)Math.sqrt((double)n);

        Boolean isPrimaryNumber[] = new Boolean[n+1];

        for(int i = 0; i <= n; ++i) isPrimaryNumber[i] = true;

        for(int i = 2; i <= root; ++i){
            if(isPrimaryNumber[i]){
                for(int j = i << 1; j <= n; j += i){
                    isPrimaryNumber[j] = false;
                }
            }
        }

        System.out.print("Primary Number : [");
        for(int i = 2; i <= n; ++i){
            if(isPrimaryNumber[i]){
                System.out.print(" " + i);
            }
        }
        System.out.println(" ]");

        return ;
    }
}