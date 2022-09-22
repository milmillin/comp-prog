
import java.util.*;
import java.math.*;

public class Cryptopangrams {

	public static void f(Scanner sc) {
		int n = sc.nextInt();
		int l = sc.nextInt();
		BigInteger[] tbl = new BigInteger[l];
		BigInteger[] ans = new BigInteger[l + 1];
		for (int i = 0; i < l; i++) {
			tbl[i] = new BigInteger(sc.next());
		}
		int index = -1;
		for (int i = 0; i < l - 1; i++) {
			if (!tbl[i].equals(tbl[i + 1])) {
				ans[i + 1] = tbl[i].gcd(tbl[i + 1]);				
				index = i + 1;
				break;
			}
		}
		for (int i = index + 1; i <= l; i++) {
			ans[i] = tbl[i - 1].divide(ans[i - 1]);
		}
		for (int i = index - 1; i >= 0; i--) {
			ans[i] = tbl[i].divide(ans[i + 1]);
		}
		TreeMap<BigInteger, Character> map = new TreeMap<BigInteger, Character>();
		for (BigInteger i : ans) {
			map.put(i, ' ');
		}

		char x = 'A';
		Set<BigInteger> keySet = new TreeSet<BigInteger>(map.keySet());
		for (BigInteger i : keySet) {
			map.put(i, x++);
		}

		for (int i = 0; i <= l; i++) {
			System.out.print(map.get(ans[i]));
		}
		System.out.println();
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int q = sc.nextInt();
		for (int i = 1; i <= q; i++) {
			System.out.printf("Case #%d ", i);
			f(sc);
		}
	}

}
