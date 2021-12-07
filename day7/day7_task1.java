package day7;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class day7_task1 {

    static ArrayList<Integer> readFileIntoArray(Scanner scanner) {
        ArrayList<Integer> arrayList = new ArrayList<>();
        while (scanner.hasNext())
            arrayList.add(scanner.useDelimiter(",").nextInt());
        return arrayList;
    }

    static int countForEntry(ArrayList<Integer> array, int idx) {
        var val = array.get(idx);
        return array.stream().map(x -> Math.abs(x - val)).reduce(0, (x, y) -> x = x + y);
    }
    
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(new File("input.txt"))) {
            ArrayList<Integer> crabs = readFileIntoArray(scanner);
            ArrayList<Integer> sums = new ArrayList<>();
            for (int i = 0; i < crabs.size(); ++i)
                sums.add(countForEntry(crabs, i));
            
            System.out.println(sums.stream().min(Integer::compareTo));
        } catch (FileNotFoundException e) { e.printStackTrace(); }
    }
}