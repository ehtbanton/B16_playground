#ifndef B6_EXAMPLE_HPP
#define B6_EXAMPLE_HPP

#include <iostream>
#include <cmath>

// Base class for functions.
class Func {
public:
    virtual double operator()(double x) const = 0;  // Compute f(x)
    virtual double Derivative(double x) const = 0;  // Compute f'(x)
    virtual bool HasDerivative() const = 0;         // Check if derivative is available
    virtual ~Func() {}                              // Virtual destructor
};

// Class for the specific function e^x/x^2
class ExpOverXSquared : public Func {
public:
    virtual double operator()(double x) const override {
        return exp(x) / (x * x);
    }

    virtual double Derivative(double x) const override {
        // f'(x) = (e^x * x^2 - 2x * e^x) / x^4
        return (exp(x) * x * x - 2 * x * exp(x)) / (x * x * x * x);
    }

    virtual bool HasDerivative() const override {
        return true;
    }
};

// Minimiser class as given in the problem
class Minimiser {
public:
    Minimiser(const Func& f, const double startX)
        : _f(f), _startX(startX) {
        // Constructor implementation
        if (!_f.HasDerivative()) {
            throw std::runtime_error("Function must provide derivatives");
        }

        // Find minimum using Newton-Raphson method
        FindMinimum();
    }

    double Minimum() const {
        return _minimum;
    }

    double MinimumLocation() const {
        return _minimumX;
    }

private:
    const Func& _f;
    double _startX;
    double _minimum;
    double _minimumX;

    void FindMinimum() {
        const double tolerance = 1e-10;  // Convergence tolerance
        const int maxIterations = 100;   // Maximum iterations to prevent infinite loops

        double x = _startX;
        double prevX;
        int iterations = 0;

        do {
            prevX = x;

            // Newton-Raphson step: x = x - f'(x)/f''(x)
            // For finding minimum, we use derivative as function
            // and second derivative as derivative
            double derivative = _f.Derivative(x);

            // Approximate second derivative using finite difference
            const double h = 1e-7;  // Small step for numerical differentiation
            double secondDerivative = (_f.Derivative(x + h) - _f.Derivative(x)) / h;

            // Prevent division by zero
            if (std::abs(secondDerivative) < 1e-10) {
                throw std::runtime_error("Second derivative too close to zero");
            }

            x = x - derivative / secondDerivative;

            iterations++;
            if (iterations > maxIterations) {
                throw std::runtime_error("Failed to converge");
            }

        } while (std::abs(x - prevX) > tolerance);

        _minimumX = x;
        _minimum = _f(x);
    }
};

void b6_example_main() {
    try {
        ExpOverXSquared f;
        double startX = 2.0;  // Starting point

        Minimiser minimiser(f, startX);

        std::cout << "Minimum value: " << minimiser.Minimum() << std::endl;
        std::cout << "Location of minimum: " << minimiser.MinimumLocation() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

#endif