import java.util.concurrent.ForkJoinTask;
import java.util.ArrayList;
import java.util.List;

public class ForkJoinTest extends ForkJoinTask<Integer> {
    private final static long UID = 1;

    private Integer i;

    public ForkJoinTest(Integer v){
        this.i = v;
    }

    @Override
    public boolean exec() {
        for(int j = 0; j < 100; ++j){
            System.out.println(i);
        }

        setRawResult(i+1);

        return true;
    }

    @Override
    public void setRawResult(Integer v) {
        this.i = v;
    }

    @Override
    public Integer getRawResult() {
        return this.i;
    }

    public static void main(String[] args){
        List<Integer> list = new ArrayList<Integer>();

        for(int i = 0; i < 100; ++i) list.add(i);
        
        list.stream()
            .map(i -> new ForkJoinTest(i))
            .peek(task -> task.fork())
            .forEach(task -> task.join());

        return ;
    }

}
