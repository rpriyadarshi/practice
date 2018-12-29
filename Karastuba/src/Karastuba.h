/*
 * Karastuba.h
 *
 *  Created on: May 6, 2018
 *      Author: rohit
 */

#ifndef KARASTUBA_H_
#define KARASTUBA_H_

namespace pra {

class Karastuba {
public:
	Karastuba();
	virtual ~Karastuba();

public: // Main Course Helper
	const std::string mult(const std::string& x, const std::string& y) const;
	const std::string add(const std::string& x, const std::string& y) const;
	const std::string subs(const std::string& x, const std::string& y) const;
	const std::string pad(const std::string& str, size_t n) const;
    const std::string pad(size_t n, const std::string& str) const;
    void pad(std::string& x, std::string& y) const;
	int compare(const std::string& x, const std::string& y) const;
    void ltrim(std::string &s) const;

public: // Utilities
	int process(int argc, const char** argv);
	void help();

public: // Accessors
	const std::string& getX() const { return m_x; }
	const std::string& getY() const { return m_y; }

private: // Accessors
	std::string& getX() { return m_x; }
	std::string& getY() { return m_y; }

private:
	std::string m_x;
	std::string m_y;
};

} /* namespace pra */
#endif /* KARASTUBA_H_ */

