import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinTask;
import java.util.Random;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.Future;

public class MonteCarlo extends ForkJoinTask<Integer> {
    private final int LENGTH = 1;
    private int count_in;

    static Random random = new Random(System.currentTimeMillis());

    @Override
    public boolean exec() {
        double x = random.nextDouble();
        double y = random.nextDouble();

        count_in = (x*x + y*y <= LENGTH) ? 1 : 0;
        return true;
    }

    @Override
	public Integer getRawResult() {
		return count_in;
	}

	@Override
	protected void setRawResult(Integer arg) {
		this.count_in = arg;
	}
    
    public static void main(String args[]) {
        ForkJoinPool pool = new ForkJoinPool();
        List<ForkJoinTask<Integer>> tasks = new ArrayList<ForkJoinTask<Integer>>();

        for(int i = 0; i < 1000000; ++i){
            tasks.add(new MonteCarlo());
        }

        int entire_count_in = 0, entire_count_all = 0;

        for(ForkJoinTask<Integer> task: tasks) {
            entire_count_in += task.invoke();
            entire_count_all += 1;
        }

        pool.shutdown();

        System.out.println("entire count-in : " + entire_count_in + ", entire count-all : " + entire_count_all);
        System.out.println("pi = " + ((double)(entire_count_in << 2) / (double)entire_count_all));

        
        return ;
    }
}