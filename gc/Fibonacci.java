import java.util.ArrayList;
import java.util.List;

public class Fibonacci {
    public static void main(String[] args) {
        //int n = 10; // Number of Fibonacci numbers to generate

        long start = System.nanoTime();
        List<Integer> fibSequence = fibonacci(100000);
        long elapsed = System.nanoTime() - start;

        System.out.println(fibSequence);
        System.out.println("Execution time: " + elapsed + " nanoseconds");
    }

    public static List<Integer> fibonacci(int n) {
        List<Integer> sequence = new ArrayList<>();
        int a = 0, b = 1;
        for (int i = 0; i < n; i++) {
            sequence.add(a);
            int temp = a;
            a = b;
            b = temp + b;
        }
        return sequence;
    }
}
//29959141
// javac Fibonacci.java 
// java Fibonacci 