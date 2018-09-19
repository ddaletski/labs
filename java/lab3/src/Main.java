import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.function.BiConsumer;
import java.util.function.Function;

public class Main {

    public static TreeMap<Character, Integer> freqTable(String str) {
        TreeMap<Character, Integer> freqs = new TreeMap<>();

        for (int i = 0; i < str.length(); ++i) {
            char ch = str.charAt(i);
            freqs.putIfAbsent(ch, 0);
            int currFreq = freqs.get(ch);
            freqs.replace(ch, currFreq + 1);
        }

        return freqs;
    }

    public static void printPair(Character c, Integer i) {

    }

    public static void printFreqTable(TreeMap<Character, Integer> freqs) {
        freqs.forEach((ch, i) -> System.out.printf("%c : %d\n", ch, i));
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNext()) {
            String s = scanner.nextLine();
            System.out.printf("\"%s\"\n", s);
            printFreqTable(freqTable(s));
            System.out.println();
        }

	scanner.close();
    }

}
