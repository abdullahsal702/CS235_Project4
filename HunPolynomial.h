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
    void RemoveLeadingZeros(std::vector<int> &coefficients);
    std::string CreatePolynomial();
    HunPolynomial operator+(HunPolynomial other);
    HunPolynomial operator-(HunPolynomial other);
    HunPolynomial operator*(HunPolynomial other);
    float operator()(float x);

private:
    std::vector<int> coefficients;
};

std::ostream &operator<<(std::ostream &stream, HunPolynomial &poly);

#endif