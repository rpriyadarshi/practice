#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <cpr/cpr.h>
#include "queries.h"

//https://gist.githubusercontent.com/demersdesigns/4442cd84c1cc6c5ccda9b19eac1ba52b/raw/cf06109a805b661dd12133f9aa4473435e478569/craft-popular-urls
// https://github.com/whoshuu/cpr
void sampleCode() {
    cpr::Response r = cpr::Get(cpr::Url{"http://www.yahoo.com"});
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;                         // JSON text string
    std::cout << r.status_code << std::endl;
    std::cout << r.header["content-type"] << std::endl;
    std::cout << r.text << std::endl;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        return -1;
    }
    UrlLoader ul;
    ul.load(argv[1]);

    UrlQuery uq1(ul, 40);
    uq1.runmtnomutex();
    uq1.print();

    UrlQuery uq(ul, 40);
    uq.runst();
    uq1.print();
}
