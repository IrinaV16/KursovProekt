# Polynomial Calculator

## Introduction

This project is a Polynomial Calculator that allows users to perform various operations on polynomials with rational coefficients. It is developed as a mini-project for the Introduction to Programming course at the Faculty of Mathematics and Informatics, Sofia University during the Winter semester 2024/2025.

## Features

The Polynomial Calculator provides the following functionalities:

1.**Addition of polynomials**
2.**Subtraction of polynomials**
3.**Multiplication of polynomials**
4.**Division of polynomials (returns quotient and remainder)**
5.**Multiplication of a polynomial by a scalar**
6.**Evaluation of a polynomial at a given number**
7.**Finding the Greatest Common Divisor (GCD) of two polynomials**
8.**Displaying Vieta's formulas for a given polynomial**
11.**Exit the program**

## Menu and Input

Once executed, the program displays a menu with all available operations. The user can select an option by entering the corresponding number. For operations requiring input (such as polynomial coefficients), the user must follow the program's instructions carefully.

### Input Format

* **Polynomials are entered as coefficients of terms with decreasing powers.**

* **Coefficients can be entered as fractions (e.g., 3/4 for three-fourths) or integers (e.g., 2 for two).**

* **For scalar multiplication and polynomial evaluation, rational numbers should be input as either whole numbers (e.g., 5) or fractions (e.g., 7/2).**

### Example Usage

**Adding Two Polynomials:**
```
Enter Polynomial P(x):
Enter degree of your polynomial>> 2
Enter coefficient before x^2>> 3
Enter coefficient before x^1>> 2
Enter coefficient before x^0>> 1

Enter Polynomial Q(x):
Enter degree of your polynomial>> 1
Enter coefficient before x^1>> -1
Enter coefficient before x^0>> 4

Result: P(x) + Q(x) = 3x^2 + x + 5
```
## Implementation Details

* **Data Representation: Polynomials are represented as ```vector<pair<int, int>>```, where each pair stores the numerator and denominator of a coefficient.**

* **Mathematical Operations:**

  * Arithmetic operations are performed using **fraction arithmetic**.

  * The **GCD function** is used to simplify fractions when necessary.

* **Error Handling: The program ensures that denominators are never zero and validates user inputs.**

## Dependencies

* **Standard C++ Library (iostream, vector)**

* **Compatible with most C++ compilers**
