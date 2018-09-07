package lab2;
/*
* Lab #2
* Variant 7
* Daletski Denis
*/

import java.io.DataInputStream;
import java.io.InputStreamReader;
import java.util.Scanner;

public class Main {

	private static double mcLorainSinOverX(double x, double eps) {
		double mul = 1;
		double prev = 0;
		double sum = mul;

		for(int i = 2; Math.abs(mul - prev) > 0.1 * eps; i+=2) {
		    prev = mul;
			mul *= -1 * x * x / i / (i+1);
			sum += mul;
		}
		return sum;
	}

	public static void main(String[] args) {

	    if(args.length < 2) {
	    	System.out.println("not enough args");
		} else {
			try {
				double x = Double.parseDouble(args[0]);

				int k = Integer.parseInt(args[1]);
				double eps = Math.pow(10, -k);

				String formatString = "MC: %." + k + "f" + " | Lib: %." + k + "f\n";
				System.out.printf(formatString, mcLorainSinOverX(x, 1e-6), Math.sin(x) / x);

			} catch (Exception ex) {
				System.out.println(ex.getMessage());
			}
		}
	}

}
