#ifndef CURRENCY_CONVERTER_H
#define CURRENCY_CONVERTER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class Mediator;

class Currency 
{
protected:
    double exchangeRate;
    double commissionRate;
public:
    virtual double convertTo(double amount, Mediator& mediator, int toCurrency) = 0;
    double getExchangeRate() const;
    double getCommissionRate() const;
    virtual ~Currency();
};

class US_Dollar : public Currency 
{
public:
    US_Dollar();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Euro : public Currency 
{
public:
    Euro();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class British_Pound : public Currency 
{
public:
    British_Pound();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Japanese_Yen : public Currency 
{
public:
    Japanese_Yen();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Chinese_Yuan : public Currency 
{
public:
    Chinese_Yuan();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Australian_Dollar : public Currency 
{
public:
    Australian_Dollar();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Canadian_Dollar : public Currency 
{
public:
    Canadian_Dollar();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Swiss_Franc : public Currency 
{
public:
    Swiss_Franc();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Indian_Rupee : public Currency 
{
public:
    Indian_Rupee();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Russian_Ruble : public Currency 
{
public:
    Russian_Ruble();
    double convertTo(double amount, Mediator& mediator, int toCurrency) override;
};

class Mediator 
{
private:
    std::vector<Currency*> currencies;
public:
    Mediator();
    ~Mediator();
    int getNumCurrencies() const;
    std::string getCurrencyName(int index) const;
    double getExchangeRate(int fromCurrency, int toCurrency) const;
    double calculateCommission(double amount, int fromCurrency) const;
    double convert(double amount, int fromCurrency, int toCurrency);
};

void convertCurrency(Mediator& mediator);

#endif // CURRENCY_CONVERTER_H
