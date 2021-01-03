#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
/*
[[0,1,10], [2,0,5]]
[[0,1,10], [1,0,1], [1,2,5], [2,0,5]]
[[0,1,5],[2,3,1],[2,0,1],[4,0,2]]
[[0,1,1],[1,2,1],[2,0,1]]
[[1,5,8],[8,9,8],[2,3,9],[4,3,1]]
[[0,3,2],[1,4,3],[2,3,2],[2,4,2]]
[[0,3,9],[1,4,2],[2,5,5],[3,4,6],[4,5,2]]
[[0,1,2],[1,2,1],[1,3,1]]
[[1,0,18],[2,1,9],[4,3,11],[5,4,10],[5,6,7],[7,6,5],[8,7,3]]

*/
void print(int idx) {
    std::string pad(idx, ' ');
    std::cout << pad << idx << std::endl;
}
void print(int idx1, int idx2, int bal) {
    std::string pad1(idx1, ' ');
    std::string pad2(idx2 - idx1, ' ');
    std::cout << pad1 << idx1 << pad2 << idx2 << " -> " << bal << std::endl;
}

using Row = std::vector<int>;
using Matrix = std::vector<Row>;

void print(const Matrix& matrix) {
    int dirty = 0;
    for (auto& data : matrix) {
        for (auto& num : data) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

class Solution {
private:// Aliases
    using IntMap = std::unordered_map<int, int>;
    using IntVec = std::vector<int>;

public:
    int dfs(IntVec& balance, int idx) {
        // print(idx);
        while (idx < balance.size() && balance[idx] == 0) {
            idx++;
        }

        if (idx == balance.size()) {
            return 0;
        }

        int res = std::numeric_limits<int>::max();
        for ( int i = idx + 1; i < balance.size(); i++) {
            // bool debtloan = balance[idx]*balance[i] < 0;
            bool debtloan = balance[idx] < 0 ^ balance[i] < 0;
            if (debtloan) {
                balance[i] += balance[idx];
                print(idx, i, balance[i]);
                res = std::min(res, dfs(balance, idx + 1) + 1);
                balance[i] -= balance[idx];
            }
        }
        return res;
    }

    int minTransfers(Matrix& transactions) {
        IntMap cache;
        for (int i = 0; i < transactions.size(); i++) {
            cache[transactions[i][0]] -= transactions[i][2];
            cache[transactions[i][1]] += transactions[i][2];
        }

        IntVec balance;
        for (auto iter : cache) {
            if (iter.second != 0) {
                balance.push_back(iter.second);
            }
        }
        for (auto b : balance) {
            std::cout << b << " ";
        }
        std::cout << std::endl;
        return dfs(balance, 0);
    }
};

// [[1,0,18],[2,1,9],[4,3,11],[5,4,10],[5,6,7],[7,6,5],[8,7,3]]
void runtest1() {
    Matrix transactions = {{1,0,18},{2,1,9},{4,3,11},{5,4,10},{5,6,7},{7,6,5},{8,7,3}};
    print(transactions);

    Solution sol;
    int trans = sol.minTransfers(transactions);
    assert(trans == 6);
}

int main() {
    runtest1();
    return 0;
}
