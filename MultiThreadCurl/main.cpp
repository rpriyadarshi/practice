#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <cpr/cpr.h>
#include "queries.h"

std::mutex UrlQueryLckMt::_mutex;

/* Problem statement:
 * Given: Sample code for URL access is shown below
 *      https://github.com/whoshuu/cpr
 *      You can skip the authentication and paramaters arguments as shown below:
 *      cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"});
 *      You would need only need to use the r.status_code for the first part.
 *
 * You can use the URLs obtained from the following link:
 *      https://gist.githubusercontent.com/demersdesigns/4442cd84c1cc6c5ccda9b19eac1ba52b/raw/cf06109a805b661dd12133f9aa4473435e478569/craft-popular-urls
 *
 * 1.   Given a list of URLs, run a query on each URL using the code shown above. The query returns a status code.
 *      When done with the queries, print the status code along with how many times that code was returned by those URLs.
 *      Be mindful od the design as it would be needed for part II. Compile and test your code.
 *
 * 2.   Now that you have build the code, can you throw some some insights on the performance bottlenecks?
 *      What these are?
 *      How would you resolve these?
 *
 */

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
    UrlQueryManager uql(100, 100);
    uql.run(argv[1]);
}
