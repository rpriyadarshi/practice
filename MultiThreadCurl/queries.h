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

private: // Data
    int _count;
    IntMap _map;
    const UrlLoader& _ul;

public: // Constructors/Destructors
    UrlQuery(const UrlLoader& ul) : _ul(ul), _count(_ul.urls().size()) {}
    UrlQuery(const UrlLoader& ul, int count) : _ul(ul), _count(count) {}
    ~UrlQuery() {}

public: // Helpers
    void query(const std::string& url) {
        cpr::Response r = cpr::Get(cpr::Url{url.c_str()});
        _map[r.status_code]++;
    }
    void queries(const StrVec& urls) {
        for (int i = 0; i < urls.size() && i < _count; i++) {
            query(urls[i]);
        }
    }

public: // Utility
    void runst() {
        auto t1 = std::chrono::high_resolution_clock::now();
        queries(_ul.urls());
        auto t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

        std::cout << "INFO: Time taken to run the queries is \"" << duration << "\" ms" << std::endl;
    }
    void runmt() {
    }
    void print() const {
        _ul.print(_count);
        for (auto& m : _map) {
            std::cout << m.first << ": " << m.second << std::endl;
        }
    }
};
