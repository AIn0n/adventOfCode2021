package day7;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class day7_task2 {
    static ArrayList<Integer> readFileIntoArray(Scanner scanner) {
        ArrayList<Integer> arrayList = new ArrayList<>();
        while (scanner.hasNext())
            arrayList.add(scanner.useDelimiter(",").nextInt());
        return arrayList;
    }

    static int countFuel(int x, int y) {
        int sum = 0, incr = 1;
        x = Math.abs(x);
        y = Math.abs(y);
        if (x > y) {
            int tmp = y;
            y = x;
            x = tmp;
        }
        for (int i = x; i < y; ++i)
            sum += incr++;
        return sum;
    }

    static int countForEntry(ArrayList<Integer> array, int val) {
        return array.stream().map(x -> countFuel(x, val)).reduce(0, (x, y) -> x = x + y);
    }
    
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(new File("input.txt"))) {
            ArrayList<Integer> crabs = readFileIntoArray(scanner);
            ArrayList<Integer> sums = new ArrayList<>();
            for (int i = 0; i < Collections.max(crabs); ++i)
                sums.add(countForEntry(crabs, i));
            
            System.out.println(Collections.min(sums));
        } catch (FileNotFoundException e) { e.printStackTrace(); }
    }
}
