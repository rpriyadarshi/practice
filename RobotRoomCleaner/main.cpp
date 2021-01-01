#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <cassert>


// This is the robot's control interface.
// You should not implement it, or speculate about its implementation
class Robot {
    const int cDR[4]{-1, 0, 1, 0};
    const int cDC[4]{0, 1, 0, -1};
    enum class Dir {
        eUP = 0,
        eRIGHT = 1,
        eDOWN = 2,
        eLEFT = 3
    };

public: // Alias
    using Loc = std::pair<int, int>;
    using Row = std::vector<int>;
    using Matrix = std::vector<Row>;

private: // Data
    Matrix _world;
    Loc _loc;
    Dir _dir{Dir::eUP};

public: // Helpers
    void loadData(const std::string& filename) {
        std::ifstream ifstr(filename);
        std::string str;
        if (ifstr.good()) {
            ifstr >> str;
            ifstr >> _loc.first;
            ifstr >> _loc.second;
        }

        std::istringstream istrstr(str);
        Row data;
        while (istrstr.good()) {
            std::string line;
            std::getline(istrstr, line, ',');
            if (line[0] == '[') {
                data.clear();
                if (line.size() > 2 && line[1] == '[') { // Table begin
                    data.push_back(std::stoi(line.substr(2)));
                } else { // Row begin
                    data.push_back(std::stoi(line.substr(1)));
                }
            } else if (line[line.size() - 1] == ']') {
                if (line.size() > 2 && line[line.size() - 2] == ']') { // Table end
                    data.push_back(std::stoi(line.substr(0, line.size() - 2)));
                } else { // Row end
                    data.push_back(std::stoi(line.substr(0, line.size() - 1)));
                }
                _world.emplace_back(data);
            } else {
                data.push_back(std::stoi(line));
            }
        }
    }
    void printDir() const {
        switch(_dir) {
            case Dir::eUP:      std::cout << "up   "; break;
            case Dir::eRIGHT:   std::cout << "right"; break;
            case Dir::eDOWN:    std::cout << "down "; break;
            case Dir::eLEFT:    std::cout << "left "; break;
        }
    }
    void printLoc() const {
        std::cout << "loc (" << _loc.first << ", " << _loc.second << ")";
    }
    void printMatrix() const {
        int dirty = 0;
        for (auto& data : _world) {
            for (auto& num : data) {
                std::cout << num << " ";
                dirty += (num == 1);
            }
            std::cout << std::endl;
        }
        std::cout << "dirty [" << dirty << "]";
    }
    void print() const {
        printMatrix();
        std::cout << " ";
        printLoc();
        std::cout << " ";
        printDir();
        std::cout << std::endl;
    }

    bool isValidRow(int r) const {
        return r >= 0 && r < _world.size();
    }
    bool isValidCol(int c) const {
        return c >= 0 && c < _world[0].size();
    }
    bool isValid(int r, int c) const {
        return isValidRow(r) && isValidCol(c);
    }
    bool isValid(const Loc& loc) const {
        return isValid(loc.first, loc.second);
    }
    bool isBlocked(const Loc& loc) const {
        return _world[loc.first][loc.second] == 0;
    }
public:
    // Returns true if the cell in front is open and robot moves into the cell.
    // Returns false if the cell in front is blocked and robot stays in the current cell.
    bool move() {
        int dir = static_cast<int>(_dir);
        Loc loc(_loc.first + cDR[dir], _loc.second + cDC[dir]);

        if (isValid(loc) && !isBlocked(loc)) {
            _loc.first += cDR[dir];
            _loc.second += cDC[dir];
            return true;
        }
        return false;
    }

    // Robot will stay in the same cell after calling turnLeft/turnRight.
    // Each turn will be 90 degrees.
    void turnLeft() {
        switch(_dir) {
            case Dir::eUP: _dir = Dir::eLEFT; break;
            case Dir::eRIGHT: _dir = Dir::eUP; break;
            case Dir::eDOWN: _dir = Dir::eRIGHT; break;
            case Dir::eLEFT: _dir = Dir::eDOWN; break;
        }
    }

    void turnRight() {
        switch(_dir) {
            case Dir::eUP: _dir = Dir::eRIGHT; break;
            case Dir::eRIGHT: _dir = Dir::eDOWN; break;
            case Dir::eDOWN: _dir = Dir::eLEFT; break;
            case Dir::eLEFT: _dir = Dir::eUP; break;
        }
    }

    // Clean the current cell.
    void clean() {
        if (_world[_loc.first][_loc.second]) { // Open
            _world[_loc.first][_loc.second] = 2;
        }
    }
};

class Solution {
public: // Aliases
    using Loc = std::pair<int, int>;
    using Locs = std::set<Loc>;

public: // Constants, enums
    const int cDR[4]{-1, 0, 1, 0};
    const int cDC[4]{0, 1, 0, -1};
    enum class Dir {
        eUP = 0,
        eRIGHT = 1,
        eDOWN = 2,
        eLEFT = 3
    };

public: // Data
    Locs _locs;

public: // Helpers
    constexpr Dir nextDir(Dir dir) const {
        switch(dir) {
            case Dir::eUP:      return Dir::eRIGHT;
            case Dir::eRIGHT:   return Dir::eDOWN;
            case Dir::eDOWN:    return Dir::eLEFT;
            case Dir::eLEFT:    return Dir::eUP;
        }
        return dir;
    }
    constexpr Dir prevDir(Dir dir) const {
        switch(dir) {
            case Dir::eUP:      return Dir::eLEFT;
            case Dir::eRIGHT:   return Dir::eUP;
            case Dir::eDOWN:    return Dir::eRIGHT;
            case Dir::eLEFT:    return Dir::eDOWN;
        }
        return dir;
    }
    void print(Dir dir) const {
        switch(dir) {
            case Dir::eUP:      std::cout << "up   "; break;
            case Dir::eRIGHT:   std::cout << "right"; break;
            case Dir::eDOWN:    std::cout << "down "; break;
            case Dir::eLEFT:    std::cout << "left "; break;
        }
    }
    void print(const Loc& loc) const {
        std::cout << "loc (" << loc.first << ", " << loc.second << ")";
    }
    void print(Robot& robot, Loc loc, Dir dir) const {
        robot.printLoc();
        std::cout << " @";
        robot.printDir();
        std::cout << " -> ";
        print(loc);
        std::cout << " @";
        print(dir);
    }

public: // Helpers
    void dfs(Robot& robot, Loc loc, Dir dir) {
        robot.clean();

        Dir newdir = prevDir(dir);
        robot.turnLeft();
        for (int i = 0; i < 3; i++) {
            Loc newloc(loc.first + cDR[int(newdir)], loc.second + cDC[int(newdir)]);
            auto iter = _locs.find(newloc);
            if (iter == _locs.end()) {
                bool moved = robot.move();
                if (moved) {
                    print(robot, newloc, newdir);
                    std::cout << " [moved  ]" << std::endl;
                    _locs.insert(newloc);
                    dfs(robot, newloc, newdir);
                    std::cout << " -- backtrack(a)" << std::endl;
                } else {
                    print(robot, newloc, newdir);
                    std::cout << " [blocked]" << std::endl;
                }
            } else {
                print(robot, newloc, newdir);
                std::cout << " [visited]" << std::endl;
            }
            robot.turnRight();
            newdir = nextDir(newdir);
        }

//        robot.turnLeft();
//        robot.turnLeft();
        bool moved = robot.move();
        assert(moved);
        robot.turnLeft();
        robot.turnLeft();
        std::cout << " -- backtrack(b) ";
        print(robot, loc, newdir);
        std::cout << std::endl;
    }

public:
    void cleanRoom(Robot& robot) {
        Loc loc(1, 3);

        print(robot, loc, Dir::eUP);
        std::cout << std::endl;

        _locs.insert(loc);
        dfs(robot, loc, Dir::eUP);
    }
};

void runtest(Robot& robot) {
    robot.move();
    robot.clean();

    robot.move();
    robot.clean();

    robot.turnRight();
    robot.move();
    robot.clean();

    robot.turnRight();
    robot.move();
    robot.clean();

    robot.turnRight();
    robot.move();
    robot.clean();
    robot.move();
    robot.clean();
    robot.move();
    robot.clean();
    robot.move();
    robot.clean();

    robot.print();
}

int main(int argc, const char** argv) {
    if (argv[1] == nullptr) {
        std::cout << "Missing filename" << std::endl;
        return 1;
    }

    const std::string filename(argv[1]);

    Robot robot;
    robot.loadData(filename);
//    runtest(robot);
    Solution sol;
    sol.cleanRoom(robot);
    robot.print();
    return 0;
}
