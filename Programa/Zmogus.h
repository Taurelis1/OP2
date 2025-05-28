#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string var_;
    std::string pav_;
public:
    Zmogus() : var_(""), pav_("") {}
    Zmogus(const std::string& var, const std::string& pav) : var_(var), pav_(pav) {}
    virtual ~Zmogus() = default;

    virtual std::string vardas() const { return var_; }
    virtual std::string pavarde() const { return pav_; }

    // Grynai virtuali funkcija (abstrakti)
    virtual void info() const = 0;
};

#endif // ZMOGUS_H