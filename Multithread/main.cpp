#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

using namespace std;

void foo(int num) {
	cout << "thread " << num << endl;
}

int main() {
    const int threadCount = 20;
	for(int i = 0; i < 5; ++i){
	    boost::thread_group tg;
	    
		cout << "beginning of loop " << i << ":" << endl;
		for(int j = 1; j < threadCount; ++j) {
			tg.create_thread(boost::bind(foo, j));
		}
		
		foo(0);
		cout << "after foo" << endl;
		
		cout << "waiting for join.all" << endl;
		tg.join_all();
		cout << "after join.all" << endl << endl;
	}
	return 0;
}

