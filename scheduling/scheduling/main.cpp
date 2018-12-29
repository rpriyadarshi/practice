//
//  main.cpp
//  scheduling
//
//  Created by Rohit Priyadarshi on 10/26/18.
//  Copyright © 2018 Rohit Priyadarshi. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>

class Job {
public:
    Job(long wt, long len) : m_weight(wt), m_length(len) {}
    ~Job() {}
    
public:
    constexpr bool operator()(const Job &lhs, const Job &rhs) const {
        return lhs.cmpDiff(rhs);
    }
    
public:
    bool cmpWeight(const Job& job) const {
        return (getWeight() > job.getWeight());
    }
    bool cmpLength(const Job& job) const {
        return (getLength() > job.getLength());
    }
    bool cmpDiff(const Job& job) const {
        if (diff() == job.diff()) {
            return cmpWeight(job);
        } else {
            return (diff() > job.diff());
        }
    }
    bool cmpRatio(const Job& job) const {
        return (ratio() > job.ratio());
    }

    long diff() const { return getWeight() - getLength(); }
    double ratio() const { return getWeight() / (getLength() * 1.0); }
    
public:
    long getWeight() const { return m_weight; }
    long getLength() const { return m_length; }
    
private:
    void setWeight(long wt) { m_weight = wt; }
    void setLength(long len) { m_length = len; }
    
private:
    long m_weight;
    long m_length;
};

struct {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.cmpWeight(rhs);
    }
} JobCmpWeight;

struct {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.cmpLength(rhs);
    }
} JobCmpLength;

struct {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.cmpDiff(rhs);
    }
} JobCmpDiff;

struct {
    bool operator()(const Job& lhs, const Job& rhs) const {
        return lhs.cmpRatio(rhs);
    }
} JobCmpRatio;

class Scheduler {
public:
    Scheduler() {}
    ~Scheduler() {}
    
public:
    bool read(const std::string& file) {
        std::ifstream ifstr(file);
        if (! ifstr.is_open()) {
            return false;
        }
        std::string line;
        
        if (std::getline(ifstr, line)) {
            long tok;
            std::stringstream sstr(line);
            sstr >> tok;
        }
        
        while (std::getline(ifstr, line)) {
            long tok1, tok2;
            std::stringstream sstr(line);
            sstr >> tok1;
            sstr >> tok2;
            m_jobs.push_back(Job(tok1, tok2));
        }
        std::cout << m_jobs.size() << std::endl;
        return true;
    }
    
    void dump() {
        for (auto& j : m_jobs) {
            std::cout << j.getWeight() << " " << j.getLength() << std::endl;
        }
    }
    
    void dumpDiff() {
        for (auto& j : m_jobs) {
            std::cout << j.getWeight() << " - " << j.getLength() << " = " << j.diff() << std::endl;
        }
    }

    void dumpRatio() {
        for (auto& j : m_jobs) {
            std::cout << j.getWeight() << " / " << j.getLength() << " = " << j.ratio() << std::endl;
        }
    }

    
    void sortWeight() {
        std::sort(m_jobs.begin(), m_jobs.end(), JobCmpWeight);
    }
    void sortLength() {
        std::sort(m_jobs.begin(), m_jobs.end(), JobCmpLength);
    }
    void sortDiff() {
        std::sort(m_jobs.begin(), m_jobs.end(), JobCmpDiff);
    }
    void sortRatio() {
        std::sort(m_jobs.begin(), m_jobs.end(), JobCmpRatio);
    }

    long completion() {
        long ct = 0;
        long tl = 0;
        for(auto& j : m_jobs) {
            tl += j.getLength();
            ct += tl * j.getWeight();
        }
        return ct;
    }
    
public:
    std::vector<Job> m_jobs;
};

int main(int argc, const char * argv[]) {
    // 16
//    std::string filename("/Users/rohit/Documents/Development/practice/scheduling/small_jobs1.txt");
    // (weight - length) = 68615, (weight/length) = 67247
//    std::string filename("/Users/rohit/Documents/Development/practice/scheduling/small_jobs2.txt");
    // (weight - length) = 69119377652, (weight/length) = 67311454237
    std::string filename("/Users/rohit/Documents/Development/practice/scheduling/jobs.txt");

    Scheduler schd;
    schd.read(filename);
    
//    schd.sortWeight();
//    schd.dump();
    
//    schd.sortLength();
//    schd.dump();
    
    schd.sortDiff();
//    schd.dumpDiff();
    std::cout << schd.completion() << std::endl;
    
    schd.sortRatio();
//    schd.dumpRatio();
    std::cout << schd.completion() << std::endl;

    return 0;
}
