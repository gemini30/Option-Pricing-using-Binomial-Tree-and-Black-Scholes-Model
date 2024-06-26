#include "option.h"
#include <math.h>
#include <cmath>
#include <iostream>
#include <vector>

// Constructor for a Option class
Option::Option(double K, double T, double sigma, double r) {
    this->K = K;  // Strike Price 
    this->T = T; // Time to maturity
    this->sigma = sigma; // Volatility of the underlying asset
    this->r = r; // Risk free rate
}

double Option::getBinomialTreeValue(double s, int n, double contDivYield) {
    std::vector<double> treeValues(n + 1); // tree node values
    double deltaT = this->T / n;
    double up = exp(this->sigma * sqrt(deltaT)); // up factor
    double down = 1 / up; // down factor
    double p0; // risk-neutral probability of an up move
    if (contDivYield == -1.0) {
        p0 = (exp(r * deltaT) - down) / (up - down); 
    } else {
        p0 = (exp((r - contDivYield) * deltaT) - down) / (up - down); 
    }
    double p1 = 1 - p0; // risk-neutral probability of an down move

    // get exercice values and store payoff values at each node
    for(int i = 0; i <= n; i++) {
        // calulate asset price 
        double asset_price = s * pow(up, 2.0 * i - n);
        // cal payoff
        treeValues[i] = this->getExerciseValue(asset_price, this->T);
    }
    // move to ealier times
    double t = this->T; // current time
    for(int j = n - 1; j >= 0; j--) {
        t -= deltaT; // current time goes down by one timeStep
        for(int i = 0; i <= j; i++) {
            double currentSpot = s * pow(up, 2 * i - j);
            // exercise value at this time (this current spot, this time)
            double exercise = getExerciseValue(currentSpot, t);
            treeValues[i] = (p0 * treeValues[i + 1] + p1 * treeValues[i]) * exp(-r * deltaT);
            // check for early exercise
            if (treeValues[i] < exercise) {
                treeValues[i] = exercise;
            }
        }
    }
    return treeValues[0];
}

double Option::getd1(double s) {
    double d1 = (1 / (this->sigma * sqrt(this->T))) * (log(s / this->K) + (this->r + this->sigma * this->sigma / 2) * this->T);
    return d1;
}

double Option::getd2(double s) {
    double d2 = this->getd1(s) - this->sigma * sqrt(this->T);
    return d2;
}

double Option::N(double x) {
    return std::erfc(-x/std::sqrt(2))/2;
}

EuropeanOption::EuropeanOption(double K, double T, double sigma, double r): Option(K, T, sigma, r) {
}

double EuropeanOption::getValue(double s) {
    return getBinomialTreeValue(s, 250);
}

AmericanOption::AmericanOption(double K, double T, double sigma, double r): Option(K, T, sigma, r) {
}

double AmericanOption::getValue(double s) {
    return getBinomialTreeValue(s, 250);
}

KnockOutOption::KnockOutOption(double K, double T, double sigma, double r, double B): Option(K, T, sigma, r) {
    this->B = B;
}

double KnockOutOption::getValue(double s) {
    return getBinomialTreeValue(s, 250);
}

bool KnockOutOption::isAcrossBarrier(double s) {
    // If we have a down-and-out option...
    if (this->K > this->B) {
        // then isAcrossBarrier returns true if s < B.
        return (s < this->B);
    }
    // If we have an up-and-out option, isAcrossBarrier returns true if s > B
    return (s > this->B);
}


EuropeanCall::EuropeanCall(double K, double T, double sigma, double r): EuropeanOption(K, T, sigma, r) {
}

EuropeanPut::EuropeanPut(double K, double T, double sigma, double r): EuropeanOption(K, T, sigma, r) {
}

AmericanCall::AmericanCall(double K, double T, double sigma, double r): AmericanOption(K, T, sigma, r) {
}

AmericanPut::AmericanPut(double K, double T, double sigma, double r): AmericanOption(K, T, sigma, r) {
}

KnockOutCall::KnockOutCall(double K, double T, double sigma, double r, double B): KnockOutOption(K, T, sigma, r, B) {
}


KnockOutPut::KnockOutPut(double K, double T, double sigma, double r, double B): KnockOutOption(K, T, sigma, r, B) {
}




double AmericanCall::getExerciseValue(double s, double t) {
    return std::max(0.0, s - this->K);
}

double AmericanPut::getExerciseValue(double s, double t) {
    return std::max(0.0, this->K - s);
}



double EuropeanCall::getExerciseValue(double s, double t) {
    if (this->T != t) {
        return 0;
    }
    return std::max(0.0, s - this->K);
}

double EuropeanPut::getExerciseValue(double s, double t) {
    if (this->T != t) {
        return 0;
    }
    return std::max(0.0, this->K - s);
}



double EuropeanCall::getBlackScholesValue(double s) {
    return N(getd1(s)) * s - N(getd2(s)) * this->K * exp(- r * this->T);
}



double EuropeanPut::getBlackScholesValue(double s) {
    return N(- getd2(s)) * this->K * exp(-r * this->T) - N(- getd1(s)) * s;
}

double AmericanCall::getBlackScholesValue(double s) {
    return N(getd1(s)) * s - N(getd2(s)) * this->K * exp(- r * this->T);
}

double AmericanPut::getBlackScholesValue(double s) {
    return N(- getd2(s)) * this->K * exp(-r * this->T) - N(- getd1(s)) * s;
}

double KnockOutCall::getExerciseValue(double s, double t) {
    if (this->T != t) {
        return 0;
    }
    if (isAcrossBarrier(s)) {
        return 0;
    }
    return std::max(0.0, s - this->K);
}

double KnockOutCall::getBlackScholesValue(double s) {
    return N(getd1(s)) * s - N(getd2(s)) * this->K * exp(- r * this->T);
}

double KnockOutPut::getExerciseValue(double s, double t) {
    if (this->T != t) {
        return 0;
    }
    if (isAcrossBarrier(s)) {
        return 0;
    }
    return std::max(0.0, this->K - s);
}

double KnockOutPut::getBlackScholesValue(double s) {
    return N(- getd2(s)) * this->K * exp(-r * this->T) - N(- getd1(s)) * s;
}
