//
// Created by rohit on 1/30/21.
//

#pragma once

// URL file loader. The file contains a list of urls
class UrlLoader{
public: // Aliases
    using StrVec = std::vector<std::string>;

private: // Data
    StrVec _urls;

public: // Constructors/Destructors
    UrlLoader() {}
    ~UrlLoader() {}

public: // Accessors
    const StrVec& urls() const { return _urls; }

public: // Utility
    bool load(const std::string& filename) {
        std::ifstream ifstr(filename);
        if (!ifstr.good()) {
            std::cout << "ERROR: Cannot find file \"" << filename << "\"" << std::endl;
            return false;
        }
        std::string url;
        while (ifstr >> url) {
            _urls.emplace_back(url);
        }
        return true;
    }

    void print(int count) const {
        for (int i = 0; i < _urls.size() && i < count; i++) {
            std::cout << _urls[i] << std::endl;
        }
    }
};

// URL query status finder base class. Contains overall infrastructure
class UrlQueryBase {
public: // Alias
    using IntMap = std::map<int, int>;

protected: // Data
    const UrlLoader& _ul;
    size_t _count;
    int _maxthreads;
    IntMap _map;

public: // Constructors/Destructors
    UrlQueryBase(const UrlLoader& ul, int count, int maxthreads) : _ul(ul), _count(count), _maxthreads(maxthreads) {}
    ~UrlQueryBase() {}

public: // Accessors
    const IntMap& map() const { return _map; }

public: // Helpers
    void run() {
        auto t1 = std::chrono::high_resolution_clock::now();
        queries();
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << "INFO: Time taken to run the queries is " << duration << " ms" << std::endl;
    }

public: // Utility
    virtual void queries()  = 0;
    void print() const {
//        _ul.print(_count);
        for (auto& m : _map) {
            std::cout << m.first << ": " << m.second << std::endl;
        }
    }
};

// Single-threaded URL query status finder
class UrlQuerySt : public UrlQueryBase {
public: // Alias
    using StrVec = std::vector<std::string>;

private: // Data

public: // Constructors/Destructors
    UrlQuerySt(const UrlLoader& ul, int count, int maxthreads) : UrlQueryBase(ul, count, maxthreads) {}
    ~UrlQuerySt() {}

public: // Helpers
    void query(const std::string& url) {
        cpr::Response r = cpr::Get(cpr::Url{url.c_str()});
        _map[r.status_code]++;
    }
    void querygroup(const StrVec& urls) {
        for (int i = 0; i < urls.size() && i < _count; i++) {
            query(urls[i]);
        }
    }

public: // Core
    void queries() {
        querygroup(_ul.urls());
    }

public: // Utility
};

// Multi-threaded URL query status finder
class UrlQueryMt : public UrlQueryBase {
public: // Alias
    using StrVec = std::vector<std::string>;
    using IntMap = std::map<int, int>;
    using ThreadIdIntMap = std::map<std::thread::id, IntMap>;
    using Threads = std::vector<std::thread>;

private: // Data
    ThreadIdIntMap _tmap;

public: // Constructors/Destructors
    UrlQueryMt(const UrlLoader& ul, int count, int maxthreads) : UrlQueryBase(ul, count, maxthreads) {}
    ~UrlQueryMt() {}

public: // Helpers
    void query(const std::string& url, std::thread::id tid) {
        cpr::Response r = cpr::Get(cpr::Url{url.c_str()});
        _tmap[tid][r.status_code]++;
    }
    void querygroup(const StrVec& urls) {
        std::thread::id tid = std::this_thread::get_id();
        for (int i = 0; i < urls.size() && i < _count; i++) {
            query(urls[i], tid);
        }
    }

public: // Core
    void queries() {
        StrVec urlgrp;
        int cluster = std::min(_ul.urls().size(), _count) / _maxthreads;
        Threads threads;
        for (int i = 0; i < _ul.urls().size() && i <= _count; i++) {
            if (i % cluster == 0) {
                threads.emplace_back(std::thread(&UrlQueryMt::querygroup, this, urlgrp));
                urlgrp.clear();
            }
            urlgrp.emplace_back(std::move(_ul.urls()[i]));
        }
        for (auto& th : threads) {
            if (th.joinable()) {
                th.join();
            }
        }
        for (auto& tm : _tmap) {
            for (auto& m : tm.second) {
                _map[m.first] += m.second;
            }
        }
    }

public: // Utility
};

// Multi-threaded with locking URL query status finder
class UrlQueryLckMt : public UrlQueryBase {
public: // Alias
    using StrVec = std::vector<std::string>;
    using IntMap = std::map<int, int>;
    using Threads = std::vector<std::thread>;

private: // Data
    static std::mutex _mutex;

public: // Constructors/Destructors
    UrlQueryLckMt(const UrlLoader& ul, int count, int maxthreads) : UrlQueryBase(ul, count, maxthreads) {}
    ~UrlQueryLckMt() {}

public: // Helpers
    void query(const std::string& url) {
        cpr::Response r = cpr::Get(cpr::Url{url.c_str()});
        std::lock_guard<std::mutex> guard(_mutex);
        _map[r.status_code]++;
    }
    void querygroup(const StrVec& urls) {
        for (int i = 0; i < urls.size() && i < _count; i++) {
            query(urls[i]);
        }
    }

public: // Core
    void queries() {
        StrVec urlgrp;
        int cluster = std::min(_ul.urls().size(), _count) / _maxthreads;
        Threads threads;
        for (int i = 0; i < _ul.urls().size() && i <= _count; i++) {
            if (i % cluster == 0) {
                threads.emplace_back(std::thread(&UrlQueryLckMt::querygroup, this, urlgrp));
                urlgrp.clear();
            }
            urlgrp.emplace_back(std::move(_ul.urls()[i]));
        }
        for (auto& th : threads) {
            if (th.joinable()) {
                th.join();
            }
        }
    }

public: // Utility
};

// URL query Manager
class UrlQueryManager {
public: // Alias
private: // Data
    size_t _count;
    int _maxthreads;
    UrlLoader _ul;

public: // Constructors/Destructors
    UrlQueryManager(int count, int maxthreads) : _count(count), _maxthreads(maxthreads) {}
    ~UrlQueryManager() {}

public: // Utility
    void run(const std::string& filename) {
        _ul.load(filename);

        UrlQueryMt uqmt(_ul, _count, _maxthreads);
        uqmt.run();
        uqmt.print();

        UrlQueryLckMt uqlmt(_ul, _count, _maxthreads);
        uqlmt.run();
        uqlmt.print();

        UrlQuerySt uqst(_ul, _count, _maxthreads);
        uqst.run();
        uqst.print();
    }
};