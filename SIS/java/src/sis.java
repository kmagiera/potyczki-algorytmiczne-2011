import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class sis {

	static final BigInteger int5 = new BigInteger("5"), int1 = new BigInteger(
			"1"), int2 = new BigInteger("2"), int0 = new BigInteger("0");

	public static void main(String[] args) throws IOException {
		BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
		BigInteger n = new BigInteger(is.readLine());
		BigInteger five = int5;
		BigInteger res = int0;
		while (n.compareTo(five) >= 0) {
			BigInteger first = n.mod(five).add(int1);
			BigInteger last = n.subtract(five).add(int1);
			res = res.add(first.add(last).multiply(last.subtract(first).add(five).divide(five)).divide(int2));
			five = five.multiply(int5);
			//System.out.println("Od " + first + " do " + last + " => res " + res + " f" + five);
		}
		System.out.println(res);
		System.exit(0);
	}
}
