//
// Created by rohit on 1/30/21.
//

#pragma once

// URL file loader
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

// URL query status finder
class UrlQuery {
public: // Alias
    using StrVec = std::vector<std::string>;
    using IntMap = std::map<int, int>;
    using ThreadIdIntMap = std::map<std::thread::id, IntMap>;
    using Threads = std::vector<std::thread>;

private: // Data
    const UrlLoader& _ul;
    size_t _count;
    int _maxthreads{4};
    IntMap _map;
    ThreadIdIntMap _tmap;

public: // Constructors/Destructors
    UrlQuery(const UrlLoader& ul) : _ul(ul), _count(_ul.urls().size()) {}
    UrlQuery(const UrlLoader& ul, int count) : _ul(ul), _count(count) {}
    ~UrlQuery() {}

public: // Helpers
    void stquery(const std::string& url) {
        cpr::Response r = cpr::Get(cpr::Url{url.c_str()});
        _map[r.status_code]++;
    }
    void mtquery(const std::string& url, std::thread::id tid) {
        cpr::Response r = cpr::Get(cpr::Url{url.c_str()});
        _tmap[tid][r.status_code]++;
    }
    void stqueries(const StrVec& urls) {
        for (int i = 0; i < urls.size() && i < _count; i++) {
            stquery(urls[i]);
        }
    }
    void mtqueries(const StrVec& urls) {
        std::thread::id tid = std::this_thread::get_id();
        for (int i = 0; i < urls.size() && i < _count; i++) {
            mtquery(urls[i], tid);
        }
    }

public: // Utility
    void runst() {
        auto t1 = std::chrono::high_resolution_clock::now();

        stqueries(_ul.urls());

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << "INFO: Time taken to run the queries is " << duration << " ms" << std::endl;
    }
    void runmtmutex() {
    }
    void runmtnomutex() {
        auto t1 = std::chrono::high_resolution_clock::now();

        StrVec urls;
        int cluster = std::min(_ul.urls().size(), _count) / _maxthreads;
        Threads threads;
        for (int i = 0; i < _ul.urls().size() && i <= _count; i++) {
            if (i % cluster == 0) {
                threads.emplace_back(std::thread(&UrlQuery::mtqueries, this, urls));
                urls.clear();
            }
            urls.emplace_back(std::move(_ul.urls()[i]));
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

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << "INFO: Time taken to run the queries is " << duration << " ms" << std::endl;
    }
    void print() const {
//        _ul.print(_count);
        for (auto& m : _map) {
            std::cout << m.first << ": " << m.second << std::endl;
        }
    }
};
