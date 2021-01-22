#include <iostream>
#include <vector>
#include <set>
#include <map>

/*
[[1,1],[2,2],[3,3]]

[[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]

[[1,1],[3,2],[5,3],[4,1],[2,3],[1,4],[2,0],[6,2]]

[]

[[4,0],[4,-1],[4,5]]

[[1,1],[1,1],[1,1]]

[[1,1],[1,1],[1,1],[1,1],[1,1],[1,1]]

[[1,1],[3,2],[3,2],[5,3],[4,1],[4,1],[2,3],[1,4],[2,0],[6,2],[3,2],[4,1]]

[[0,0]]

[[0,0],[0,0]]

[[1,1],[1,1],[0,0],[3,4],[4,5],[5,6],[7,8],[8,9]]

*/

class Solution {
public: // Alias
    using Point = std::tuple<int, int>;
    using Usage = std::map<Point, int>;
    using Points = std::set<Point>;
    using Segments = std::map<Point, Points>;
    using Slopes = std::map<double, Segments>;

public: // Data
    Usage _usage;
    Slopes _slopes;

public: // Helpers
    void print() const {
        for (auto& s : _slopes) {
            std::cout << s.first << std::endl;
            for (auto& segs : s.second) {
                std::cout << "    {" << std::get<0>(segs.first) << ", " << std::get<1>(segs.first) << "} -> ";
                for (auto& pt : segs.second) {
                    std::cout << "(" << std::get<0>(pt) << ", " << std::get<1>(pt) << ") ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

public:
    int maxPoints(std::vector<std::vector<int>>& points) {
        if (points.empty()) {
            return 0;
        } else if (points.size() == 1) {
            return 1;
        }

        for (int i = 0; i < points.size(); i++) {
            auto& p = points[i];
            _usage[Point(p[0], p[1])]++;
        }

        // Build slope groups
        for (int i = 0; i < points.size(); i++) {
            auto& p1 = points[i];
            int x1 = p1[0];
            int y1 = p1[1];
            Point pt1(x1, y1);

            for (int j = i + 1; j < points.size(); j++) {
                auto& p2 = points[j];
                int x2 = p2[0];
                int y2 = p2[1];
                double p = y2 - y1;
                double q = x2 - x1;
                double s = p / q;
                Point pt2(x2, y2);

                auto& segs = _slopes[s];
                segs[pt1].emplace(pt1);
                segs[pt1].emplace(pt2);
                segs[pt2].emplace(pt1);
                segs[pt2].emplace(pt2);
            }
        }

//        print();

        // find the largest group
        size_t maxsize = std::numeric_limits<size_t>::min();
        for (auto& s : _slopes) {
            for (auto& segs : s.second) {
                // size_t segsize = segs.second.size();
                size_t segsize = 0;
                for (auto& pt : segs.second) {
                    segsize += _usage[pt];
                }
                maxsize = std::max(maxsize, segsize);
            }
        }
        return maxsize;
    }
};

void runtest(std::vector<std::vector<int>> points, int res) {
    Solution sol;
    int cnt = sol.maxPoints(points);
    if (cnt == res) {
        std::cout << "PASS [" << cnt << "==" << res << "]";
    } else {
        std::cout << "FAIL [" << cnt << "!=" << res << "]";
    }
    std::cout << std::endl;
}

int main() {
    runtest({{1,1},{2,2},{3,3}}, 3);
    runtest({{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}}, 4);
    runtest({{1,1},{3,2},{5,3},{4,1},{2,3},{1,4},{2,0},{6,2}}, 4);
    runtest({}, 0);
    runtest({{4,0},{4,-1},{4,5}}, 3);
    runtest({{1,1},{1,1},{1,1}}, 3);
    runtest({{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}}, 6);
    runtest({{1,1},{3,2},{3,2},{5,3},{4,1},{4,1},{2,3},{1,4},{2,0},{6,2},{3,2},{4,1}}, 8);
    runtest({{0,0}}, 1);
    runtest({{0,0},{0,0}}, 2);
    runtest({{1,1},{1,1},{0,0},{3,4},{4,5},{5,6},{7,8},{8,9}}, 5);
    return 0;
}
