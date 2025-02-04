/**
* Solution to course project #4
* Introduction to programming course
* Faculty of Matematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Irina Vlaykova
* @idnumber 8MI0600507
* @compiler <VC>
*
* file with all the functions
*
*/


#include <iostream>
#include <vector>
using namespace std;

void displayMenu() {
    cout << "Welcome to Polynomial Calculator, a mini project intended to work with polynomials with rational coefficients" << endl;
    cout << "\nChoose one of the following functionalities:\n";
    cout << "1) Add polynomials\n";
    cout << "2) Subtract polynomials\n";
    cout << "3) Multiply polynomials\n";
    cout << "4) Divide polynomials\n";
    cout << "5) Multiply polynomial by scalar\n";
    cout << "6) Find value of polynomial at a given number\n";
    cout << "7) Find GCD of two polynomials\n";
    cout << "8) Display Vieta's formulas for a given polynomial\n";
    cout << "11) Quit program\n";
}

int myAbs(int num) {
    if (num < 0) {
        return -num;
    }
    return num;
}

int getDegreeManual(const vector<pair<int, int>>& poly) {
    int count = 0;
    for (vector<pair<int, int>>::const_iterator it = poly.begin(); it != poly.end(); ++it) {
        count++;
    }
    return count - 1;
}

int myMax(int a, int b) {
    return (a > b) ? a : b;
}

bool isZeroPolynomial(const vector<pair<int, int>>& poly) {
    for (size_t i = 0; i < poly.size(); ++i) {
        if (poly[i].first != 0) {
            return false;
        }
    }
    return true;
}

void stringToFraction(const char* str, int& numerator, int& denominator) {
    numerator = 0;
    denominator = 1;
    bool isNegative = false;

    if (*str == '-') {
        isNegative = true;
        ++str;
    }

    const char* slashPosition = nullptr;
    for (const char* ptr = str; *ptr != '\0'; ++ptr) {
        if (*ptr == '/') {
            slashPosition = ptr;
            break;
        }
    }

    if (slashPosition) {
        for (const char* ptr = str; ptr < slashPosition; ++ptr) {
            if (*ptr >= '0' && *ptr <= '9') {
                numerator = numerator * 10 + (*ptr - '0');
            }
        }

        denominator = 0;
        for (const char* ptr = slashPosition + 1; *ptr != '\0'; ++ptr) {
            if (*ptr >= '0' && *ptr <= '9') {
                denominator = denominator * 10 + (*ptr - '0');
            }
        }
    }
    else {
        for (const char* ptr = str; *ptr != '\0'; ++ptr) {
            if (*ptr >= '0' && *ptr <= '9') {
                numerator = numerator * 10 + (*ptr - '0');
            }
        }
    }

    if (isNegative) numerator = -numerator;

    if (denominator == 0) denominator = 1;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void printPolynomial(const vector<pair<int, int>>& poly, const char* name) {
    int degree = poly.end() - poly.begin() - 1;

    cout << name << " = ";
    bool isFirst = true;

    for (int i = 0; i <= degree; ++i) {
        int numerator = poly[i].first;
        int denominator = poly[i].second;

        if (numerator == 0) continue;

        int divisor = gcd(myAbs(numerator), denominator);
        numerator /= divisor;
        denominator /= divisor;

        if (!isFirst && numerator > 0) cout << " + ";
        if (numerator < 0 && !isFirst) cout << " - ";
        if (numerator < 0 && isFirst) cout << "-";

        numerator = myAbs(numerator);

        if (numerator != 1 || denominator != 1 || i == degree) {
            if (denominator == 1) {
                cout << numerator;
            }
            else {
                cout << numerator << "/" << denominator;
            }
        }

        if (i < degree) {
            cout << "x";
            if ((degree - i) > 1) cout << "^" << (degree - i);
        }

        isFirst = false;
    }

    cout << endl;
}

vector<pair<int, int>> inputPolynomial(const char* name) {
    cout << "\nEnter Polynomial " << name << "(x):";

    int degree;
    cout << "\nEnter degree of your polynomial>> ";
    cin >> degree;

    vector<pair<int, int>> polynomial(degree + 1);

    cin.ignore();

    for (int i = degree; i >= 0; --i) {
        cout << "Enter coefficient before x^" << i << ">> ";
        char input[100];
        cin.getline(input, 100);

        int numerator = 0, denominator = 1;
        stringToFraction(input, numerator, denominator);

        polynomial[degree - i] = { numerator, denominator };
    }

    printPolynomial(polynomial, name);

    return polynomial;
}

vector<pair<int, int>> addPolynomials(const vector<pair<int, int>>& poly1, const vector<pair<int, int>>& poly2) {
    int degree1 = getDegreeManual(poly1);
    int degree2 = getDegreeManual(poly2);
    int resultDegree = myMax(degree1, degree2);

    vector<pair<int, int>> result(resultDegree + 1, { 0, 1 });

    for (int i = 0; i <= resultDegree; ++i) {
        int idex1 = degree1 - (resultDegree - i);
        int idex2 = degree2 - (resultDegree - i);

        int numerator1 = (idex1 >= 0) ? poly1[idex1].first : 0;
        int denominator1 = (idex1 >= 0) ? poly1[idex1].second : 1;

        int numerator2 = (idex2 >= 0) ? poly2[idex2].first : 0;
        int denominator2 = (idex2 >= 0) ? poly2[idex2].second : 1;

        int commonDenominator = denominator1 * denominator2;
        int newNumerator = numerator1 * denominator2 + numerator2 * denominator1;

        result[i].first = newNumerator;
        result[i].second = commonDenominator;
    }

    return result;
}

vector<pair<int, int>> subtractPolynomials(const vector<pair<int, int>>& poly1, const vector<pair<int, int>>& poly2) {
    int degree1 = getDegreeManual(poly1);
    int degree2 = getDegreeManual(poly2);

    int resultDegree = (degree1 > degree2) ? degree1 : degree2;

    vector<pair<int, int>> result(resultDegree + 1, { 0, 1 });

    for (int i = 0; i <= resultDegree; ++i) {
        int idex1 = degree1 - (resultDegree - i);
        int idex2 = degree2 - (resultDegree - i);

        int numerator1 = (idex1 >= 0) ? poly1[idex1].first : 0;
        int denominator1 = (idex1 >= 0) ? poly1[idex1].second : 1;

        int numerator2 = (idex2 >= 0) ? poly2[idex2].first : 0;
        int denominator2 = (idex2 >= 0) ? poly2[idex2].second : 1;

        int commonDenominator = denominator1 * denominator2;
        int newNum = numerator1 * denominator2 - numerator2 * denominator1;

        result[i] = { newNum, commonDenominator };
    }

    return result;
}

vector<pair<int, int>> multiplyPolynomials(const vector<pair<int, int>>& poly1, const vector<pair<int, int>>& poly2) {
    int degree1 = getDegreeManual(poly1);
    int degree2 = getDegreeManual(poly2);

    int resultDegree = degree1 + degree2;

    vector<pair<int, int>> result(resultDegree + 1, { 0, 1 });

    for (int i = 0; i <= degree1; ++i) {
        for (int j = 0; j <= degree2; ++j) {
            int numerator1 = poly1[i].first;
            int denominator1 = poly1[i].second;
            int numerator2 = poly2[j].first;
            int denominator2 = poly2[j].second;

            int newNumerator = numerator1 * numerator2;
            int newDenominator = denominator1 * denominator2;

            int targetIndex = i + j;
            result[targetIndex].first = result[targetIndex].first * newDenominator + newNumerator * result[targetIndex].second;
            result[targetIndex].second *= newDenominator;

            int divisor = gcd(myAbs(result[targetIndex].first), result[targetIndex].second);
            result[targetIndex].first /= divisor;
            result[targetIndex].second /= divisor;
        }
    }

    return result;
}

pair<vector<pair<int, int>>, vector<pair<int, int>>> dividePolynomials(const vector<pair<int, int>>& dividend,
    const vector<pair<int, int>>& divisor) {

    if (isZeroPolynomial(divisor)) {
        cout << "Error: Attempt to divide by a zero polynomial!" << endl;
        return { {}, dividend };  
    }

    int degreeDividend = getDegreeManual(dividend);
    int degreeDivisor = getDegreeManual(divisor);

    if (degreeDividend < degreeDivisor) {
        return { {}, dividend };
    }

    vector<pair<int, int>> quotient(degreeDividend - degreeDivisor + 1, { 0, 1 });
    vector<pair<int, int>> remainder = dividend;

    while (degreeDividend >= degreeDivisor) {
        int leadNumDividend = remainder[0].first;
        int leadDenomDividend = remainder[0].second;
        int leadNumDivisor = divisor[0].first;
        int leadDenomDivisor = divisor[0].second;

        int resultNum = leadNumDividend * leadDenomDivisor;
        int resultDenom = leadDenomDividend * leadNumDivisor;

        quotient[degreeDividend - degreeDivisor] = { resultNum, resultDenom };

        for (int i = 0; i <= degreeDivisor; ++i) {
            int numDivisor = divisor[i].first;
            int denomDivisor = divisor[i].second;

            int currentNum = resultNum * numDivisor;
            int currentDenom = resultDenom * denomDivisor;

            remainder[i].first = remainder[i].first * currentDenom - currentNum * remainder[i].second;
            remainder[i].second *= currentDenom;

            int divisorGCD = gcd(myAbs(remainder[i].first), remainder[i].second);
            remainder[i].first /= divisorGCD;
            remainder[i].second /= divisorGCD;
        }

        remainder.erase(remainder.begin());
        --degreeDividend;
    }

    return { quotient, remainder };
}

vector<pair<int, int>> multiplyPolynomialByScalar(const vector<pair<int, int>>& poly, int scalarNumerator, int scalarDenominator) {
    int degree = getDegreeManual(poly);

    vector<pair<int, int>> result(degree + 1); 

    for (int i = 0; i <= degree; ++i) {  
        int newNumerator = poly[i].first * scalarNumerator;
        int newDenominator = poly[i].second * scalarDenominator;

        if (newDenominator == 0) {
            cout << "Error: Denominator cannot be zero!" << endl;
            newDenominator = 1;
        }

        int divisor = gcd(myAbs(newNumerator), myAbs(newDenominator));
        newNumerator /= divisor;
        newDenominator /= divisor;

        if (newDenominator < 0) {
            newNumerator = -newNumerator;
            newDenominator = -newDenominator;
        }

        result[i] = { newNumerator, newDenominator };
    }

    return result;
}


pair<int, int> evaluatePolynomialAsFraction(const vector<pair<int, int>>& poly, int numerator, int denominator) {
    int degree = getDegreeManual(poly);

    int resultNumerator = 0;
    int resultDenominator = 1;

    for (int i = 0; i <= degree; ++i) {
        int coeffNumerator = poly[i].first;
        int coeffDenominator = poly[i].second;

        int powerNumerator = 1, powerDenominator = 1;
        for (int j = 0; j < degree - i; ++j) {
            powerNumerator *= numerator;
            powerDenominator *= denominator;
        }

        int termNumerator = coeffNumerator * powerNumerator;
        int termDenominator = coeffDenominator * powerDenominator;

        int commonDenominator = resultDenominator * termDenominator;
        resultNumerator = resultNumerator * termDenominator + termNumerator * resultDenominator;
        resultDenominator = commonDenominator;

        int divisor = gcd(myAbs(resultNumerator), resultDenominator);
        resultNumerator /= divisor;
        resultDenominator /= divisor;
    }

    return { resultNumerator, resultDenominator };
}

vector<pair<int, int>> gcdPolynomials(const vector<pair<int, int>>& p1, const vector<pair<int, int>>& p2) {
    vector<pair<int, int>> a = p1;
    vector<pair<int, int>> b = p2;

    while (!isZeroPolynomial(b)) {
        pair<vector<pair<int, int>>, vector<pair<int, int>>> divisionResult = dividePolynomials(a, b);
        vector<pair<int, int>>& quotient = divisionResult.first;
        vector<pair<int, int>>& remainder = divisionResult.second;

        a = b;
        b = remainder;
    }

    for (pair<int, int>& coeff : a) {
        int divisor = gcd(myAbs(coeff.first), coeff.second);
        coeff.first /= divisor;
        coeff.second /= divisor;
    }

    return a;
}

void displayVietasFormulas(const vector<pair<int, int>>& poly) {
    int degree = getDegreeManual(poly);

    if (degree < 1) {
        cout << "Vieta's formulas are not applicable for this polynomial.\n";
        return;
    }

    cout << "\nVieta's Formulas for polynomial: ";
    printPolynomial(poly, "P(x)");

    int leadingCoeffNum = poly[0].first;
    int leadingCoeffDenom = poly[0].second;

    for (int k = 1; k <= degree; ++k) {
        int numerator = (k % 2 == 1 ? -1 : 1) * poly[k].first * leadingCoeffDenom;
        int denominator = poly[k].second * leadingCoeffNum;
        int gcdVal = gcd(myAbs(numerator), myAbs(denominator));

        numerator /= gcdVal;
        denominator /= gcdVal;

        cout << "y" << k << " = " << numerator;
        if (denominator != 1) {
            cout << "/" << denominator;
        }
        cout << endl;
    }
}


int main() {
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<pair<int, int>> poly1 = inputPolynomial("P");
            vector<pair<int, int>> poly2 = inputPolynomial("Q");

            vector<pair<int, int>> result = addPolynomials(poly1, poly2);
            printPolynomial(result, "P(x) + Q(x)");
            break;
        }
        case 2: {
            vector<pair<int, int>> poly1 = inputPolynomial("P");
            vector<pair<int, int>> poly2 = inputPolynomial("Q");

            vector<pair<int, int>> result = subtractPolynomials(poly1, poly2);
            printPolynomial(result, "P(x) - Q(x)");
            break;
        }
        case 3: {
            vector<pair<int, int>> poly1 = inputPolynomial("P");
            vector<pair<int, int>> poly2 = inputPolynomial("Q");

            vector<pair<int, int>> result = multiplyPolynomials(poly1, poly2);
            printPolynomial(result, "P(x) * Q(x)");
            break;
        }

        case 4: {
            vector<pair<int, int>> poly1 = inputPolynomial("Dividend");
            vector<pair<int, int>> poly2 = inputPolynomial("Divisor");

            pair<vector<pair<int, int>>, vector<pair<int, int>>> result = dividePolynomials(poly1, poly2);

            vector<pair<int, int>> quotient = result.first;
            vector<pair<int, int>> remainder = result.second;

            cout << "Quotient: ";
            printPolynomial(quotient, "Q(x)");

            cout << "Remainder: ";
            printPolynomial(remainder, "R(x)");
            break;
        }
        
        case 5: {
            vector<pair<int, int>> poly = inputPolynomial("P");

            cout << "Enter rational number: ";

            int scalarNumerator = 0, scalarDenominator = 1;
            char separator;

            cin >> scalarNumerator;

            if (cin.peek() == '/') {
                cin >> separator >> scalarDenominator; 
            }
            else {
                scalarDenominator = 1; 
            }

            if (scalarDenominator == 0) {
                cout << "Error: Denominator cannot be zero! Defaulting to 1." << endl;
                scalarDenominator = 1;
            }

            vector<pair<int, int>> result = multiplyPolynomialByScalar(poly, scalarNumerator, scalarDenominator);

            printPolynomial(result, "Scalar * P(x)");
            break;
        }

        case 6: {
            vector<pair<int, int>> poly = inputPolynomial("P");

            cout << "Enter rational number: ";

            int numerator = 0, denominator = 1;
            char separator;

            cin >> numerator;

            if (cin.peek() == '/') {
                cin >> separator >> denominator; 
            }
            else {
                denominator = 1; 
            }

            if (denominator == 0) {
                cout << "Error: Denominator cannot be zero! Defaulting to 1." << endl;
                denominator = 1;
            }

            auto result = evaluatePolynomialAsFraction(poly, numerator, denominator);

            cout << "P(" << numerator;
            if (denominator != 1) {
                cout << "/" << denominator;
            }
            cout << ") = " << result.first;
            if (result.second != 1) {
                cout << "/" << result.second;
            }
            cout << endl;

            break;
        }

        case 7: {
            vector<pair<int, int>> poly1 = inputPolynomial("P");
            vector<pair<int, int>> poly2 = inputPolynomial("Q");

            vector<pair<int, int>> result = gcdPolynomials(poly1, poly2);

            printPolynomial(result, "GCD(P(x), Q(x))");
            break;
        }

        case 8: {
            vector<pair<int, int>> poly = inputPolynomial("P");

            displayVietasFormulas(poly);
            break;
        }

        case 11:
            running = false;
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
