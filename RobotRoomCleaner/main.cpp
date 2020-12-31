#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <cassert>

const int cDR[]{-1, 0, 1, 0};
const int cDC[]{0, 1, 0, -1};
enum class Dir {
    eUP = 0,
    eRIGHT = 1,
    eDOWN = 2,
    eLEFT = 3
};

// This is the robot's control interface.
// You should not implement it, or speculate about its implementation
class Robot {
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
    void print () {
        int dirty = 0;
        for (auto& data : _world) {
            for (auto& num : data) {
                std::cout << num << " ";
                dirty += (num == 1);
            }
            std::cout << std::endl;
        }
        std::cout << "(" << _loc.first << ", " << _loc.second << ") dirty = " << dirty;
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

const int cUP{0x1};
const int cDOWN{0x2};
const int cLEFT{0x4};
const int cRIGHT{0x8};

struct Cell {
public: // Alias
    using IntPair = std::pair<int, int>;

public: // Constructors/destructors
    Cell() : _tried(cUP) {}

public: // Data
    IntPair _loc;
    int _tried:4;

public: // Helpers

    int next90Dir(Robot& robot, int dir) const { // clockwise
        robot.turnRight(); // 90
        switch(dir) {
            case cUP: return cRIGHT;
            case cRIGHT: return cDOWN;
            case cDOWN: return cLEFT;
            case cLEFT: return cUP;
            default: return dir;
        }
    }
    int next180Dir(Robot& robot, int dir) const { // clockwise
        robot.turnRight(); // 90
        robot.turnRight(); // 90
        switch(dir) {
            case cUP: return cDOWN;
            case cRIGHT: return cLEFT;
            case cDOWN: return cUP;
            case cLEFT: return cRIGHT;
            default: return dir;
        }
    }
    int next270Dir(Robot& robot, int dir) const { // clockwise
        robot.turnLeft(); // -90
        switch(dir) {
            case cUP: return cLEFT;
            case cRIGHT: return cUP;
            case cDOWN: return cRIGHT;
            case cLEFT: return cDOWN;
            default: return dir;
        }
    }
    int nextValidDir(Robot& robot, int dir) const {
        int d = dir;
        for (int i = 0; i < 4; i++) {
            if (!(_tried & d)) {
                return d;
            }
            d = next90Dir(robot, dir);
        }
        assert(d == dir);
        return next180Dir(robot, dir);
    }
    void tried(int dir) {
        _tried &= dir;
    }
};

struct cmp {
    constexpr bool operator()(const Cell &lhs, const Cell &rhs) const {
        return lhs._loc < rhs._loc;
    }
};

class Solution {
public: // Aliases
    using Cells = std::set<Cell, cmp>;

public: // Data
    Cells _cells;

public: // Helpers
    void dfs(Robot& robot, Cell& cell, int dir) {
        robot.clean();
        bool moved = false;
        while (!moved) {
            moved = robot.move();
            if (moved) {
            } else {
                int d = cell.nextValidDir(robot, dir);
            }
        }
    }
public:
    void cleanRoom(Robot& robot) {
        _cells.emplace(Cell());
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
