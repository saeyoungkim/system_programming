import java.util.concurrent.*;

public class sumWithTenThreads {
    static private class Summation implements Callable<Integer> {

        private int value;
        public Summation(Integer val) {
            this.value = val;
        }
    
        public Integer call() {
            return value;
        }
    
    }
    static public void main(String args[]){
        Integer sum = 0;     

        ExecutorService pool = Executors.newSingleThreadExecutor();

        for(int i = 0; i < 10; ++i){
            Future<Integer> result = pool.submit(new Summation(i));
            
            try {
                int r = result.get();
                System.out.println(r);
                sum += r;
            } catch (InterruptedException | ExecutionException ie) { 
                System.out.println(ie.getMessage());
            }
            
        }

        System.out.println(sum);
    }
}