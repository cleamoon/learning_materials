#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

class NQueen {
private:
    int board_size;

    vector<vector<int>> res; 

    vector<int> pos; 

    bool isSafe(int p) {
        int s = pos.size();
        for (int i = 0; i < s; i++) {
            if (pos[i] == p) return false;
            if (abs(s-i) == abs(p-pos[i])) return false;
        }
        return true;
    }

    void solve(int nQueens) {
        if (nQueens == 0) {
            res.push_back(pos);
            return;
        } else {
            for (int i = 0; i < board_size; i++) {
                if (isSafe(i)) {
                    pos.push_back(i);
                    solve(nQueens - 1);
                    pos.pop_back();
                }
            }
        }
    }

public: 
    NQueen(int _board_size) : board_size(_board_size) {
        solve(board_size);
    }

    void print_res() {
        for(auto i = 0; i < res.size(); i++) {
            for (auto j = 0; j < board_size; j++) {
                for (auto k = 0; k < board_size; k++) {
                    if (k == res[i][j]) printf("[o]");
                    else printf("[ ]");
                }
                printf("\n");
            }
            printf("\n");
        }
    }
};

int main(int argc, char* argv[]) {
		if (argc != 2) cout << "Usage: \n\t nqueue N\n";
		else {
    		NQueen q(atoi(argv[1]));
    		q.print_res();
    }
    return 0;
}
