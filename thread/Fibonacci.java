import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.lang.InterruptedException;

public class Fibonacci {
    
    public static void main(String[] args) {
        ExecutorService service = Executors.newSingleThreadExecutor();

        Future<List<Integer>> future = service.submit(
            (Callable<List<Integer>>)(() -> {
                Integer numbers = Integer.parseInt(args[0]);
                List<Integer> list = new ArrayList<Integer>();
                
                for(int i = 0; i < numbers; ++i){
                    if(i == 0) list.add(0);
                    else if(i == 1) list.add(1);
                    else list.add(
                        list.get(list.size()-1) + list.get(list.size()-2)
                    );
                }

                return list;
            })
        );

        try {
            System.out.println(future.get());
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
        finally {
            service.shutdown();
        }
    }
    
}
