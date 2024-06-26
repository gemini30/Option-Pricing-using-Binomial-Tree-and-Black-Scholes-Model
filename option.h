#ifndef option_hpp
#define option_hpp


class Option {
public:

    Option(double K, double T, double sigma, double r);
    // returns the exercise value of the option for spot price s at time t
    virtual double getExerciseValue(double s, double t) = 0;
    // returns the Black Scholes value of the option
    virtual double getBlackScholesValue(double s) = 0;
    // returns the value of the option using a binomial tree of depth N
    double getBinomialTreeValue(double s, int N, double contDivYield=-1);
    // returns the option value for spot value s
    virtual double getValue(double s) = 0;
    
protected:
    double K; // strike
    double T; // time-to-maturity
    double sigma; // underlying volatility
    double r; // risk-free rate
    double getd1(double s);
    double getd2(double s);
    double N(double x);
};


class EuropeanOption: public Option {
public:
    EuropeanOption(double K, double T, double sigma, double r);
    virtual double getValue(double s);
};

class AmericanOption: public Option {
public:
    AmericanOption(double K, double T, double sigma, double r);
    virtual double getValue(double s);
};

class KnockOutOption: public Option {
public:
    KnockOutOption(double K, double T, double sigma, double r, double B);
    virtual double getValue(double s);
protected:
    double B;
    bool isAcrossBarrier(double s); 
};

// Specifying whether can buy or sell underlying
class EuropeanCall: public EuropeanOption {
public:
    EuropeanCall(double K, double T, double sigma, double r);
    virtual double getExerciseValue(double s, double t);
    virtual double getBlackScholesValue(double s);

};

class EuropeanPut: public EuropeanOption {
public:
    EuropeanPut(double K, double T, double sigma, double r);
    virtual double getExerciseValue(double s, double t);
    virtual double getBlackScholesValue(double s);
};



class AmericanCall: public AmericanOption {
public:
    AmericanCall(double K, double T, double sigma, double r);
    virtual double getExerciseValue(double s, double t);
    virtual double getBlackScholesValue(double s);
};

class AmericanPut: public AmericanOption {
public:
    AmericanPut(double K, double T, double sigma, double r);
    virtual double getExerciseValue(double s, double t);
    virtual double getBlackScholesValue(double s);
};

class KnockOutCall: public KnockOutOption {
public:
    KnockOutCall(double K, double T, double sigma, double r, double B);
    virtual double getExerciseValue(double s, double t);
    virtual double getBlackScholesValue(double s);
};

class KnockOutPut: public KnockOutOption {
public:
    KnockOutPut(double K, double T, double sigma, double r, double B);
    virtual double getExerciseValue(double s, double t);
    virtual double getBlackScholesValue(double s);
};
#endif 
