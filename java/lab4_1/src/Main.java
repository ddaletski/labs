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
        System.out.println("vector1:");
        System.out.println(vec);
        BoolVector vec2 = randomVector(10);
        System.out.println("vector2:");
        System.out.println(vec2);

        System.out.printf("vector1:: length: %d, zeros: %d, ones: %d\n", vec.length(), vec.countZeros(), vec.countOnes());
        System.out.println("vector1 inversed:");
        System.out.println(vec.inversed());

        System.out.println("vector1 & vector2:");
        System.out.println(vec2.conjunction(vec));
        System.out.println("vector1 | vector2:");
        System.out.println(vec2.disjunction(vec));


        try {
            randomVector(6).conjunction(randomVector(8));
        } catch (Exception ex) {
            System.out.printf("exception caught as expected: %s\n", ex.getMessage());
        }

        try {
            randomVector(6).disjunction(randomVector(8));
        } catch (Exception ex) {
            System.out.printf("exception caught as expected: %s\n", ex.getMessage());
        }
    }
}
