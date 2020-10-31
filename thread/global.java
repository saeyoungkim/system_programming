import java.util.concurrent.ForkJoinTask;

public class global extends ForkJoinTask<Integer> {
    int value = 0;

    @Override
    public Integer compute() {
        ++value;
        return value;
    }

    public static void main(String args[]) {
        global g1 = new global();
        // Common ForkJoinPool
        g1.fork();
        g1.join();
    }
}
