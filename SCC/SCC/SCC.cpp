//============================================================================
// Name        : SCC.cpp
// Author      : Rohit Priyadarshi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <fstream>
#include <random>
#include <bitset>

////////////////////////////////////////////////////////////////////////////////
class Vertex {
public: // typedefs
    typedef std::bitset<1> Flags;

public: // constructors/destructors
    Vertex() : m_data(-1), m_delay(-1), m_group(0) {}
    explicit Vertex(int d) : m_data(d), m_delay(-1), m_group(0) {}
    ~Vertex() {}

public: // Operators
    bool operator==(const Vertex& v) const { return getData() == v.getData(); }
    bool operator<(const Vertex& v) const { return getData() < v.getData(); }
    bool operator>(const Vertex& v) const { return getData() > v.getData(); }

public: // Accessors
    int getData() const { return m_data; }
    int getDelay() const { return m_delay; }
    int getGroup() const { return m_group; }
    Flags& getFlags() const { return m_flags; }
    // Set functions
    void setData(int d) const { m_data = d; }
    void setDelay(int d) const { m_delay = d; }
    void setGroup(int g) const { m_group = g; }

private: // Accessors
    int getData() { return m_data; }
    int getDelay() { return m_delay; }
    int getGroup() { return m_group; }
    Flags& getFlags() { return m_flags; }

public:
    mutable int m_data;
    mutable int m_delay;
    mutable int m_group;
    mutable Flags m_flags;
};

////////////////////////////////////////////////////////////////////////////////
class VertexCmpGroup {
public:
	bool operator() (const Vertex* a, const Vertex* b) {
		return a->getGroup() < b->getGroup();
	}
};

////////////////////////////////////////////////////////////////////////////////
class Graph {
public: // typedefs
    typedef std::list<int> IntList;
    typedef std::list<const Vertex*> VertexList;
    typedef std::vector<VertexList> VertexTable;
    typedef std::vector<const Vertex*> VertexVec;

public: // constructors/destructors
    Graph() : m_delay(0), m_group(0) {}
    ~Graph();

public: // Algorithms
    void scc() const;

public: // Navigation functions
    void fwdDfs() const;
    void revDfs() const;

private: // Navigation functions
    void dfs(const VertexTable& t, const VertexVec& v, int delay) const;
    void dfs(const VertexTable& t, int index) const;

public: // Utility functions
    bool read(const std::string& filename);
    void mapDelays() const;
    void clear() const;

public: // Dump functions
    void fwdDump(std::ostream& o = std::cout) const;
    void revDump(std::ostream& o = std::cout) const;
    void dump(std::ostream& o = std::cout) const;
    void dump(const VertexTable& t, std::ostream& o = std::cout) const;
    void dumpDelay(std::ostream& o = std::cout) const;

private:
    VertexTable m_fwdTable;
    VertexTable m_revTable;
    VertexVec m_vertices;
    mutable VertexVec m_delays;
    mutable int m_delay;
    mutable int m_group;
    mutable VertexList m_scc;
};

////////////////////////////////////////////////////////////////////////////////
inline Graph::~Graph() {
    for (const Vertex* v : m_vertices) {
        delete v;
    }
    m_fwdTable.clear();
    m_vertices.clear();
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::fwdDfs() const {
    dfs(m_fwdTable, m_delays, 0);
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::revDfs() const {
    dfs(m_revTable, m_vertices, 1);
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::dfs(const VertexTable& t, const VertexVec& v, int delay) const {
    m_delay = delay;
    m_scc.clear();
    for (int i = static_cast<int>(v.size()) - 1; i >= 0; i--) {
        auto data = v.at(i);
        if (!data || data->getFlags().test(0)) {
            continue;
        }
        m_group = 0;
        dfs(t, data->getData());
        data->setGroup(m_group);
        m_scc.push_back(data);
    }
    m_scc.sort(VertexCmpGroup());
    clear();
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::dfs(const VertexTable& t, int index) const {
    if (index < 0) {
        return;
    }
    auto v = m_vertices.at(index);
    v->getFlags().set(0);
    auto& rows = t.at(index);
    if (rows.empty()) {
        return;
    }
    for (auto data : rows) {
        if (!data || data->getFlags().test(0)) {
            continue;
        }
        dfs(t, data->getData());
    }
    if (m_delay) {
        v->setDelay(m_delay++);
    }
    m_group++;
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::mapDelays() const {
    m_delays.assign(m_vertices.size(), 0);
    for (auto data : m_vertices) {
    	int index = data->getDelay();
    	if (index < 0) {
    		continue;
    	}
        m_delays.at(index) = data;
    }
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::scc() const {
    revDfs();
    mapDelays();
    fwdDfs();
}

////////////////////////////////////////////////////////////////////////////////
inline bool Graph::read(const std::string& filename) {
    std::ifstream ifstr(filename);
    if (! ifstr.good()) {
        return false;
    }
    std::string line;

    int maxKey = 0;
    int maxVal = 0;
    while(std::getline(ifstr, line).good()) {
        std::stringstream strstr(line);
        std::string keyTok, valTok;

        strstr >> keyTok;
        strstr >> valTok;

        int key = std::stoi(keyTok);
        int val = std::stoi(valTok);
        maxKey = std::max(maxKey, key);
        maxVal = std::max(maxVal, val);

        // Initialize
        while (static_cast<int>(m_vertices.size()) <= key) {
            m_vertices.push_back(new Vertex());
        }
        while (static_cast<int>(m_vertices.size()) <= val) {
            m_vertices.push_back(new Vertex());
        }
        while (static_cast<int>(m_fwdTable.size()) <= key) {
            m_fwdTable.push_back(VertexList());
        }
        while (static_cast<int>(m_revTable.size()) <= val) {
            m_revTable.push_back(VertexList());
        }

        // Set values
        m_vertices.at(key)->setData(key);
        m_vertices.at(val)->setData(val);

        // Build graphs
        m_fwdTable.at(key).push_back(m_vertices.at(val));
        m_revTable.at(val).push_back(m_vertices.at(key));
    }

    // Missing data
    while (m_fwdTable.size() <= m_vertices.size()) {
        m_fwdTable.push_back(VertexList());
    }
    while (m_revTable.size() <= m_vertices.size()) {
        m_revTable.push_back(VertexList());
    }

    std::cout << "Max key = " << maxKey << ", maxVal = " << maxVal << std::endl;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::fwdDump(std::ostream& o) const {
    dump(m_fwdTable, o);
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::revDump(std::ostream& o) const {
    dump(m_revTable, o);
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::dump(const VertexTable& t, std::ostream& o) const {
    for (int i = 0; i < static_cast<int>(t.size()); i++) {
        const VertexList& rows = t.at(i);
        if (rows.empty()) continue;
        o << m_vertices.at(i)->getData() << " : ";
        for(auto data : rows) {
            o << data->getData() << " ";
        }
        o << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::dump(std::ostream& o) const {
    for (auto data : m_scc) {
        std::cout << data->getGroup() << ": f(" << data->getData() << ") = " << data->getDelay() << std::endl;
    }
    std::cout << "SCC = " << m_scc.size() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::dumpDelay(std::ostream& o) const {
    for (auto data : m_vertices) {
        if (data->getData() < 0) {
            continue;
        }
        std::cout << data->getData() << " : " << data->getDelay() << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////
inline void Graph::clear() const {
    for (auto data : m_vertices) {
        data->getFlags().reset(0);
    }
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    Graph g;
//    const std::string filename("/home/rohit/Projects/C++/SCC-1f.txt");
//    const std::string filename("/home/rohit/Projects/C++/SCC-2.txt");
    const std::string filename("/home/rohit/Projects/C++/SCC.txt");
    g.read(filename);
    g.scc();
    g.dump();

    return 0;
}
