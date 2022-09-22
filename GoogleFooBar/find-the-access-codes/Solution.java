
import java.lang.Math;

public class Solution {
    public static int solution(int[] l) {
        int n = l.length;
        int[] mul = new int[1000000];
        int ans = 0;

        for (int i = n - 1; i >= 0; i--) {
            int right = mul[l[i]];
            int left = 0;
            for (int j = 0; j < i; j++) {
                if (l[i] % l[j] == 0) left++;
            }
            ans += left * right;

            int sq = (int)Math.floor(Math.sqrt(l[i]));
            for (int k = 1; k <= sq; k++) {
                if (l[i] % k == 0) {
                    int kk = l[i] / k;
                    mul[k]++;
                    if (k != kk) mul[kk]++;
                }
            }
        }
        return ans;
    }
}
