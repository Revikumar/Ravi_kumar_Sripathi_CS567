#include "currencyconverter.h"

// Currency class methods
Currency::~Currency() {}

double Currency::getExchangeRate() const 
{
    return exchangeRate;
}

double Currency::getCommissionRate() const 
{
    return commissionRate;
}

// US Dollar methods
US_Dollar::US_Dollar() 
{
    exchangeRate = 1.0;
    commissionRate = 0.02;
}

double US_Dollar::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 0, toCurrency);
}

// Euro methods
Euro::Euro() 
{
    exchangeRate = 0.84;
    commissionRate = 0.03;
}

double Euro::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 1, toCurrency);
}

// British Pound methods
British_Pound::British_Pound() 
{
    exchangeRate = 0.72;
    commissionRate = 0.035;
}

double British_Pound::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 2, toCurrency);
}

// Japanese Yen methods
Japanese_Yen::Japanese_Yen() 
{
    exchangeRate = 109.11;
    commissionRate = 0.025;
}

double Japanese_Yen::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 3, toCurrency);
}

// Chinese Yuan methods
Chinese_Yuan::Chinese_Yuan() 
{
    exchangeRate = 6.47;
    commissionRate = 0.03;
}

double Chinese_Yuan::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 4, toCurrency);
}

// Australian Dollar methods
Australian_Dollar::Australian_Dollar() 
{
    exchangeRate = 0.90;
    commissionRate = 0.025;
}

double Australian_Dollar::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 5, toCurrency);
}

// Canadian Dollar methods
Canadian_Dollar::Canadian_Dollar() 
{
    exchangeRate = 0.65;
    commissionRate = 0.02;
}

double Canadian_Dollar::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 6, toCurrency);
}

// Swiss Franc methods
Swiss_Franc::Swiss_Franc() 
{
    exchangeRate = 0.81;
    commissionRate = 0.035;
}

double Swiss_Franc::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 7, toCurrency);
}

// Indian Rupee methods
Indian_Rupee::Indian_Rupee() 
{
    exchangeRate = 20.17;
    commissionRate = 0.03;
}

double Indian_Rupee::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 8, toCurrency);
}

// Russian Ruble methods
Russian_Ruble::Russian_Ruble() 
{
    exchangeRate = 74.23;
    commissionRate = 0.04;
}

double Russian_Ruble::convertTo(double amount, Mediator& mediator, int toCurrency) 
{
    return mediator.convert(amount, 9, toCurrency);
}

// Mediator methods
Mediator::Mediator() 
{
    currencies.push_back(new US_Dollar());
    currencies.push_back(new Euro());
    currencies.push_back(new British_Pound());
    currencies.push_back(new Japanese_Yen());
    currencies.push_back(new Chinese_Yuan());
    currencies.push_back(new Australian_Dollar());
    currencies.push_back(new Canadian_Dollar());
    currencies.push_back(new Swiss_Franc());
    currencies.push_back(new Indian_Rupee());
    currencies.push_back(new Russian_Ruble());
}

Mediator::~Mediator() 
{
    for (auto& currency : currencies) 
    {
        delete currency;
    }
}

int Mediator::getNumCurrencies() const 
{
    return currencies.size();
}

std::string Mediator::getCurrencyName(int index) const 
{
    if (index >= 0 && index < currencies.size()) 
    {
        std::string names[] = {"US Dollar (USD)", "Euro (EUR)", "British Pound (GBP)", "Japanese Yen (JPY)", "Chinese Yuan (CNY)",
                               "Australian Dollar (AUD)", "Canadian Dollar (CAD)", "Swiss Franc (CHF)", "Indian Rupee (INR)", "Russian Ruble (RUB)"};
        return names[index];
    }
    return "Unknown Currency";
}

double Mediator::getExchangeRate(int fromCurrency, int toCurrency) const 
{
    double fromRate = currencies[fromCurrency]->getExchangeRate();
    double toRate = currencies[toCurrency]->getExchangeRate();
    return toRate / fromRate;
}

double Mediator::calculateCommission(double amount, int fromCurrency) const 
{
    double commissionRate = currencies[fromCurrency]->getCommissionRate();
    return amount * commissionRate;
}

double Mediator::convert(double amount, int fromCurrency, int toCurrency) 
{
    double exchangeRate = getExchangeRate(fromCurrency, toCurrency);
    double convertedAmount = amount * exchangeRate;
    double commission = calculateCommission(convertedAmount, fromCurrency);
    double finalAmount = convertedAmount - commission;

    std::cout << "\nConverting..." << std::endl;
    std::cout << "Actual Converted Amount: " << convertedAmount << std::endl;
    std::cout << "Commission Rate: " << (currencies[fromCurrency]->getCommissionRate() * 100) << "%" << std::endl;
    std::cout << "Commission Deducted: " << commission << std::endl;
    std::cout << "Processing..." << std::endl;
    return finalAmount;
}

// Function to initiate currency conversion
void convertCurrency(Mediator& mediator) 
{
    double amount;
    int fromCurrency, toCurrency;

    std::cout << "==============================" << std::endl;
    std::cout << "       Currency Converter     " << std::endl;
    std::cout << "==============================" << std::endl;

    do {
        std::cout << "\nEnter the amount: ";
        std::cin >> amount;

        std::cout << "\nSelect the currency to convert from:" << std::endl;
        for (int i = 0; i < mediator.getNumCurrencies(); ++i) 
        {
            std::cout << i+1 << ". " << mediator.getCurrencyName(i) << std::endl;
        }
        std::cout << "Enter your choice: ";
        std::cin >> fromCurrency;

        std::cout << "\nSelect the currency to convert to:" << std::endl;
        for (int i = 0; i < mediator.getNumCurrencies(); ++i) 
        {
            std::cout << i+1 << ". " << mediator.getCurrencyName(i) << std::endl;
        }
        std::cout << "Enter your choice: ";
        std::cin >> toCurrency;

        double convertedAmount = mediator.convert(amount, fromCurrency-1, toCurrency-1);

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\n" << amount << " " << mediator.getCurrencyName(fromCurrency-1) << " is equivalent to "
                  << convertedAmount << " " << mediator.getCurrencyName(toCurrency-1) << std::endl;
        std::cout << "==============================" << std::endl;

        char another;
        std::cout << "Do you want to perform another conversion? (y/n): ";
        std::cin >> another;

        if (tolower(another) != 'y')
            break;

    } while (true);

    std::cout << "\nThank you for using the Currency Converter!" << std::endl;
}
