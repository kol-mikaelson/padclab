#include <bits/stdc++.h>
using namespace std;
vector<int> algo(int mat[6][6], vector<int>& vis, int v) {
    vis[0] = 0;
    vector<int> new_vis = vis;
    for (int k = 0; k < v; ++k) {
        for (int i = 0; i < v; i++) {
            if (new_vis[i] < INT_MAX) {
                for (int j = 0; j < v; j++) {
                    if (mat[i][j] < INT_MAX) {
                        new_vis[j] = min(new_vis[j], new_vis[i] + mat[i][j]);
                    }
                }
            }
        }
        vis = new_vis;
    }
    return vis;
}
int main() {
    int v = 6;
    int mat[6][6] = {
            {100, 7, 12, 100, 100, 100},
            {100, 100, 2, 9, 100, 100},
            {100, 100, 100, 100, 10, 100},
            {100, 100, 100, 100, 100, 1},
            {100, 100, 100, 4, 100, 5},
            {100, 100, 100, 100, 100, 100}
    };
    vector<int> vis(v, INT_MAX);
    auto start = chrono::high_resolution_clock::now();
    vis=algo(mat, vis, v);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " milliseconds" << endl;
    for (int i = 0; i < v; i++) {
        cout << vis[i] << endl;
    }
    return 0;
}//
// Created by aero7 on 09-11-2024.
//
