#include <vector>
#include <string>
#include <iostream>
#ifndef HunPolynomial_h
#define HunPolynomial_h

class HunPolynomial
{
public:
    HunPolynomial();
    HunPolynomial(std::vector<int> new_coefficients);
    void Set(std::vector<int> new_coefficients);
    std::string CreatePolynomial();
    HunPolynomial operator+(HunPolynomial other);
    HunPolynomial operator-(HunPolynomial other);

private:
    std::vector<int> coefficients;
    // std::string polynomial;
};

std::ostream &operator<<(std::ostream &stream, const HunPolynomial &poly);

#endif