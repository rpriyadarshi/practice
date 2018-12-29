//============================================================================
// Name        : Karastuba.cpp
// Author      : Rohit Priyadarshi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include "Karastuba.h"
using namespace std;

int main(int argc, const char** argv) {
	pra::Karastuba ka;
	const pra::Karastuba& cka = ka;

	int rc = ka.process(argc, argv);
    if (rc) {
        return rc;
    }
    // 9234 9893
	std::cout << ka.pad(cka.getX(), 5) << std::endl;
	std::cout << ka.pad(cka.getY(), 10) << std::endl;

	std::cout << ka.compare(cka.getY(), cka.getY()) << std::endl;
	std::cout << ka.compare(cka.getX(), cka.getY()) << std::endl;
	std::cout << ka.compare(cka.getY(), cka.getX()) << std::endl;
	std::cout << ka.compare(cka.getX(), cka.getX()) << std::endl;

	std::cout << ka.add(cka.getX(), cka.getY()) << std::endl;

	std::cout << ka.subs(cka.getX(), cka.getY()) << std::endl;
	std::cout << ka.subs(cka.getY(), cka.getX()) << std::endl;

	std::cout << ka.mult(cka.getX(), cka.getY()) << std::endl;

	return rc;
}

namespace pra {

Karastuba::Karastuba() {
}

Karastuba::~Karastuba() {
}

int Karastuba::process(int argc, const char** argv) {
	if (argc == 3) {
		getX() = argv[1];
		getY() = argv[2];
		return 0;
    } else {
        help();
        return 1;
    }
}

const std::string Karastuba::mult(const std::string& xstr,
		const std::string& ystr) const {
    std::string x(xstr);
    std::string y(ystr);
    pad(x, y);
    std::string res;
	size_t len = x.size();
	if (len == 1) {
		int nx = std::stoi(x);
		int ny = std::stoi(y);
        res = std::to_string(nx * ny);
	} else {
		size_t posl = 0;
        size_t posm = len/2;
		size_t posr = len;

		std::string a = x.substr(posl, posm);
		std::string b = x.substr(posm, posr);
		std::string c = y.substr(posl, posm);
		std::string d = y.substr(posm, posr);

        std::string p = add(a, b);
        std::string q = add(c, d);
        
		std::string ac = mult(a, c);
		std::string bd = mult(b, d);
		std::string pq = mult(p, q);

        std::string pqac = subs(pq, ac);
        std::string adbc = subs(pqac, bd);

		std::string padac = pad(ac, posr);
		std::string padadbc = pad(adbc, (posr - posm));
        
        std::string res1 = add(padac, padadbc);
        res = add(res1, bd);
	}
    ltrim(res);
    return res;
}

const std::string Karastuba::add(const std::string& xstr,
		const std::string& ystr) const {
    std::string x(xstr);
    std::string y(ystr);
    pad(x, y);
	std::string sum;
	int len = static_cast<int>(x.size());
	int c = 0;
	for (int i = len - 1; i >= 0; i--) {
		int p = x[i] - '0';
		int q = y[i] - '0';
		int r = p + q + c;
		char s = 0;
		std::string rstr = std::to_string(r);
		size_t slen = rstr.size();
		if (slen == 1) {
			c = 0;
			s = rstr[0];
		} else {
			c = rstr[0] - '0';
			s = rstr[1];
		}
		sum += s;
	}
	if (c > 0) {
		sum += c + '0';
	}
	std::reverse(sum.begin(), sum.end());
	return sum;
}

const std::string Karastuba::subs(const std::string& xstr,
		const std::string& ystr) const {
	std::string x(xstr);
	std::string y(ystr);
    pad(x, y);
	int sgn = compare(x, y);
	if (sgn < 0) {
        std::string t(x);
		x = y;
		y = t;
	}
	std::string sum;
	int len = static_cast<int>(x.size());
	int b = 0;
	for (int i = len - 1; i >= 0; i--) {
		int p = x[i] - '0';
		int q = y[i] - '0';
		if (b > 0) {
			p = p - b;
			b = 0;
		}
		if (p < q) {
			b = 1;
		}
		int r = b ? (10 + p - q) : (p - q);
		char s = r + '0';
		sum += s;
	}
	if (sgn < 0) {
		sum += '-';
	}
	std::reverse(sum.begin(), sum.end());
	return sum;
}

const std::string Karastuba::pad(const std::string& str, size_t n) const {
	std::string res(n, '0');
	return str + res;
}

const std::string Karastuba::pad(size_t n, const std::string& str) const {
    std::string res(n, '0');
    return res + str;
}

void Karastuba::pad(std::string& x, std::string& y) const {
    size_t lx = x.size();
    size_t ly = y.size();
    size_t l = std::max(lx, ly);
    int n = std::rint(std::exp2(std::ceil(std::log2(l))));
    x = pad(n - lx, x);
    y = pad(n - ly, y);
}

int Karastuba::compare(const std::string& x, const std::string& y) const {
	int len = static_cast<int>(x.size());
	for (int i = 0; i < len; i++) {
		int p = x[i] - '0';
		int q = y[i] - '0';
		if (p > q) {
			return 1;
		} else if (p < q) {
			return -1;
		}
	}
	return 0;
}

void Karastuba::ltrim(std::string& s) const {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return ch != '0'; }));
}

void Karastuba::help() {
	std::cout << "Usage: karastuba <x string> <y string>" << std::endl;
}
    
} /* namespace pra */
