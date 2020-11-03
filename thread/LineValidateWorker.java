import java.util.*;
import java.util.concurrent.Callable;

public class LineValidateWorker implements Callable<Boolean> {
    private final List<Integer> col;
    private final int N;

    public LineValidateWorker(List<Integer> col, int N) {
        this.col = col;
        this.N = N;
    }
    
    @Override
    public Boolean call() {
        boolean[] isExisted = new boolean[N];
        Arrays.fill(isExisted, false);

        for(int i = 0; i < N; ++i) {
            if(isExisted[col.get(i)-1]) return false;
            isExisted[col.get(i)-1] = true;
        }

        return true;
    }
}
