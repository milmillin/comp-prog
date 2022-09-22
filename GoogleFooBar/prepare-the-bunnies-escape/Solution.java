import java.util.Queue;
import java.util.LinkedList;

class State {
    public int R;
    public int C;
    public int Doomed;

    public State(int r, int c, int d) {
        R = r;
        C = c;
        Doomed = d;
    }
}

public class Solution {

    public static int solution(int[][] map) {
        int[] dr = new int[] {-1, 0, 0, 1};
        int[] dc = new int[] {0, -1, 1, 0};

        int r = map.length;
        int c = map[0].length;
        int[][][] dist = new int[r][c][2];

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                dist[i][j][0] = 1000000000;
                dist[i][j][1] = 1000000000;
            }
        }

        dist[0][0][0] = 1;
        Queue<State> q = new LinkedList<State>();
        q.add(new State(0, 0, 0));
        while (!q.isEmpty()) {
            State now = q.remove();
            for (int i = 0; i < 4; i++) {
                int nextr = now.R + dr[i];
                int nextc = now.C + dc[i];
                int willDoom = now.Doomed;

                if (nextr < 0 || nextc < 0 || nextr >= r || nextc >= c) continue;
                if (map[nextr][nextc] != 0 && now.Doomed != 0) continue;
                if (map[nextr][nextc] != 0) willDoom = 1;
                if (dist[nextr][nextc][willDoom] <= dist[now.R][now.C][now.Doomed] + 1) continue;
                dist[nextr][nextc][willDoom] = dist[now.R][now.C][now.Doomed] + 1;
                q.add(new State(nextr, nextc, willDoom));
            }
        }

        return Math.min(dist[r - 1][c - 1][0], dist[r - 1][c - 1][1]);
    }
}
