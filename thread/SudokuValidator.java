import java.io.IOException;
import java.util.*;
import java.util.concurrent.*;

public class SudokuValidator {
    final static int N = 9;
    static int[][] sudoku = {
        {6,2,4,5,3,9,1,8,7},
        {5,1,9,7,2,8,6,3,4},
        {8,3,7,6,1,4,2,9,5},
        {1,4,3,8,6,5,7,2,9},
        {9,5,8,2,4,7,3,6,1},
        {7,6,2,3,9,1,4,5,8},
        {3,7,1,9,5,6,8,4,2},
        {4,9,6,1,8,2,5,7,3},
        {2,8,5,4,7,3,9,1,6}
    };

    public static void main(String[] args){
        System.out.println("=================================");
        System.out.println("Start validate sudoku solution...");
        System.out.println("=================================");

        ExecutorService service = Executors.newFixedThreadPool(9);
    
        List<LineValidateWorker> lineValWorkers1 = new ArrayList<LineValidateWorker>();
        List<LineValidateWorker> lineValWorkers2 = new ArrayList<LineValidateWorker>();
        List<LineValidateWorker> subGridValWorkers = new ArrayList<LineValidateWorker>();

        for(int i = 0; i < N; ++i){
            List<Integer> line1 = Arrays.asList(
                sudoku[0][i], sudoku[1][i], sudoku[2][i], sudoku[3][i], sudoku[4][i], sudoku[5][i], sudoku[6][i], sudoku[7][i], sudoku[8][i]
            );
            List<Integer> line2 = Arrays.asList(
                sudoku[i][0], sudoku[i][1], sudoku[i][2], sudoku[i][3], sudoku[i][4], sudoku[i][5], sudoku[i][6], sudoku[i][7], sudoku[i][8]
            );
            int startRow = (i / 3) * 3;
            int startCol = (i % 3) * 3;
            List<Integer> subGrid = Arrays.asList(
                sudoku[startRow][startCol], sudoku[startRow][startCol+1], sudoku[startRow][startCol+2],
                sudoku[startRow+1][startCol], sudoku[startRow+1][startCol+1], sudoku[startRow+1][startCol+2],
                sudoku[startRow+2][startCol], sudoku[startRow+2][startCol+1], sudoku[startRow+2][startCol+2]
            );

            lineValWorkers1.add(new LineValidateWorker(line1, N));
            lineValWorkers2.add(new LineValidateWorker(line2, N));
            subGridValWorkers.add(new LineValidateWorker(subGrid, N));
        }

        try {
            System.out.println("Start column validation...");
            List<Future<Boolean>> isValidColumns = 
                service.invokeAll(lineValWorkers1);
                    
            for(Future<Boolean> isValidColumn : isValidColumns){
                if(isValidColumn.get() == false) {
                    System.out.println("column is not valid...");
                    return ;
                }
            }

            System.out.println("Start row validation...");
            List<Future<Boolean>> isValidRows = 
            service.invokeAll(lineValWorkers2);
                
            for(Future<Boolean> isValidRow : isValidRows){
                if(isValidRow.get() == false) {
                    System.out.println("row is not valid...");
                    return ;
                }
            }

            System.out.println("Start sub grid validation...");
            List<Future<Boolean>> isValidSubGrids = 
            service.invokeAll(subGridValWorkers);
                
            for(Future<Boolean> isValidSubGrid : isValidSubGrids){
                if(isValidSubGrid.get() == false) {
                    System.out.println("sub greed is not valid...");
                    return ;
                }
            }
        } catch (InterruptedException e){
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }

        System.out.println("Valid sudoku solution!");
        service.shutdown();
        return ;
    }
}
