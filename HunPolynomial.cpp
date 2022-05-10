#include "HunPolynomial.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

HunPolynomial::HunPolynomial(){};

HunPolynomial::HunPolynomial(std::vector<int> new_coefficients)
{
    coefficients = new_coefficients;
}

void HunPolynomial::Set(std::vector<int> new_coefficients)
{
    coefficients = new_coefficients;
}

// 5*x^3 – 12*x – 1  => std::vector<int>{5, 0, -12, -1}
void HunPolynomial::RemoveLeadingZeros(std::vector<int> &coefficients)
{
    if (coefficients.size() <= 1)
        return;
    while (coefficients[0] == 0)
    {
        coefficients.erase(coefficients.begin());
        if (coefficients.size() == 1)
            return;
    }
}

std::string HunPolynomial::CreatePolynomial()
{
    RemoveLeadingZeros(coefficients);
    std::string polynomial = "";
    if (coefficients.size() < 1)
        return polynomial;
    else if (coefficients.size() == 1)
    {
        polynomial += std::to_string(coefficients[0]);
        return polynomial;
    }

    // gets the value of the first term
    int power = coefficients.size() - 1;
    if (coefficients[0] != 0)
    {
        if (coefficients[0] < -1)
            polynomial += "- " + std::to_string(coefficients[0]).erase(0, 1);
        else if (coefficients[0] == -1)
            polynomial = "- ";

        // else if (coefficients[0] == 1) do nothing
        else if (coefficients[0] > 1)
            polynomial += std::to_string(coefficients[0]);

        if (coefficients[0] != -1 && coefficients[0] != 0 && coefficients[0] != 1)
            polynomial += "*";

        if (power > 1)
            polynomial += "x^" + std::to_string(power);
        else if (power == 1)
            polynomial += "x";
    }
    power--;

    // iterates from second term and on
    for (int i = 1; i < coefficients.size(); i++)
    {
        // gets the correct coefficient
        std::string coefficient = "";
        if (coefficients[i] < -1)
            coefficient = " - " + std::to_string(coefficients[i]).erase(0, 1);
        else if (coefficients[i] == -1)
            coefficient = " - ";
        else if (coefficients[i] == 0)
        {
            power--;
            continue;
        }
        else if (coefficients[i] == 1)
            coefficient = " + ";
        else if (coefficients[i] > 1)
            coefficient = " + " + std::to_string(coefficients[i]);

        // places * when needed
        if (i != coefficients.size() - 1 && coefficients[i] != -1 && coefficients[i] != 0 && coefficients[i] != 1)
            coefficient += "*";

        // gets the correct power
        if (power > 1)
            polynomial += coefficient + "x^" + std::to_string(power);
        else if (power == 1)
            polynomial += coefficient + "x";
        else if (power == 0)
        {
            if (coefficients[i] == -1 || coefficients[i] == 1)
                coefficient += "1";
            polynomial += coefficient;
        }
        power--;
    }
    // for debugging
    //  for (int i = 0; i < coefficients.size(); i++)
    //      std::cout << coefficients[i] << ' ';
    //  std::cout << '\n';
    return polynomial;
}

//<< override
std::ostream &operator<<(std::ostream &stream, HunPolynomial &poly)
{
    stream << poly.CreatePolynomial();
    return stream;
}

HunPolynomial HunPolynomial::operator+(HunPolynomial other)
{
    // find smaller vector, add zeroes to the start of that vector until it matches the size of the larger vector
    // add each element of the vectors one by one
    std::vector<int> result_coefficients;

    while (coefficients.size() < other.coefficients.size())
        coefficients.insert(coefficients.begin(), 0);
    while (coefficients.size() > other.coefficients.size())
        other.coefficients.insert(other.coefficients.begin(), 0);

    for (int i = 0; i < coefficients.size(); i++)
        result_coefficients.push_back(coefficients[i] + other.coefficients[i]);

    HunPolynomial result{result_coefficients};

    return result;
}

HunPolynomial HunPolynomial::operator-(HunPolynomial other)
{
    // the order of subtraction matters
    std::vector<int> result_coefficients;

    while (coefficients.size() < other.coefficients.size())
        coefficients.insert(coefficients.begin(), 0);
    while (coefficients.size() > other.coefficients.size())
        other.coefficients.insert(other.coefficients.begin(), 0);

    for (int i = 0; i < coefficients.size(); i++)
        result_coefficients.push_back(coefficients[i] - other.coefficients[i]);

    HunPolynomial result{result_coefficients};

    return result;
}

HunPolynomial HunPolynomial::operator*(HunPolynomial other)
{
    // create a result vector with size = size of both vectors added together - 1
    // fill the result vector with zeroes
    // loop through both vectors, result[i + j] += coefficients[i] * other.coefficients[j]
    // this will add like terms and assign the product of terms their proper power
    int size = coefficients.size() + other.coefficients.size() - 1;
    std::vector<int> result_coefficients;
    for (int i = 0; i < size; i++)
        result_coefficients.push_back(0);

    for (int i = 0; i < coefficients.size(); i++)
    {
        for (int j = 0; j < other.coefficients.size(); j++)
        {
            result_coefficients[i + j] += coefficients[i] * other.coefficients[j];
        }
    }

    HunPolynomial result{result_coefficients};
    return result;
}

float HunPolynomial::operator()(float x)
{
    int power = coefficients.size() - 1;
    float result = 0;
    for (int i = 0; i < coefficients.size(); i++)
    {
        result += coefficients[i] * (pow(x, power));
        power--;
    }
    return result;
}
