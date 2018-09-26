import java.util.Random;

public class Main {
    public static BoolVector randomVector(int n) throws Exception {
        Random gen = new Random();

        BoolVector vec = new BoolVector(n, false);
        for(int i = 0; i < vec.length(); ++i) {
            vec.setAt(i, gen.nextBoolean());
        }

        return vec;
    }

    public static void main(String[] args) throws Exception {
        BoolVector vec = randomVector(10);
        System.out.println(vec);
        BoolVector vec2 = randomVector(10);
        System.out.println(vec2);

        System.out.println(vec.length());
        System.out.println(vec.countOnes());
        System.out.println(vec.countZeros());
        System.out.println(vec.inversed());

        System.out.println(vec2.conjunction(vec));
        System.out.println(vec2.disjunction(vec));

    }
}
