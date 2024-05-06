// testcase.cpp

#include <deepstate/DeepState.hpp>
#include "currencyconverter.cpp" // Include your actual header file
#include <limits> // Include for std::numeric_limits

using namespace deepstate;

TEST(CurrencyConverter, TestConversion) 
{
    Mediator mediator;

    float amount = 100;
    int fromCurrency = 1; // USD
    int toCurrency = 2;   // Euro
    float expectedConvertedAmount = amount * 0.84;
    float actualConvertedAmount = mediator.convert(amount, fromCurrency - 1, toCurrency - 1);
    
    printf("TestConversion: actual=%f, expected=%f\n", actualConvertedAmount, expectedConvertedAmount);


    ASSERT_NE(actualConvertedAmount, amount); // Assert not equal to original amount
    ASSERT_LT(actualConvertedAmount, amount * 2); // Assert less than double the original amount
    ASSERT_LE(actualConvertedAmount, amount * 1.5); // Assert less than or equal to 1.5 times the original amount
    ASSERT_GT(expectedConvertedAmount, 0); // Assert greater than 0
    ASSERT_GE(actualConvertedAmount, 0); // Assert greater than or equal to 0
}

TEST(CurrencyConverter, TestCommission) 
{
    Mediator mediator;

    float amount = 100;
    int fromCurrency = 1; // USD
    float expectedCommission = amount * 0.02;
    float actualCommission = mediator.calculateCommission(amount, fromCurrency - 1);
    
    printf("TestCommission: actual=%f, expected=%f\n", actualCommission, expectedCommission);

    ASSERT_EQ(actualCommission, expectedCommission);
    ASSERT_FALSE(actualCommission > amount); // Assert commission is not greater than original amount
    ASSERT_TRUE(actualCommission >= 0); // Assert commission is greater than or equal to 0
}

TEST(CurrencyConverter, TestExchangeRate) 
{
    Mediator mediator;

    int fromCurrency = 1; // USD
    int toCurrency = 2;   // Euro
    float expectedExchangeRate = 0.84;
    float actualExchangeRate = mediator.getExchangeRate(fromCurrency - 1, toCurrency - 1);
    
    printf("TestExchangeRate: actual=%f, expected=%f\n", actualExchangeRate, expectedExchangeRate);

    ASSERT_EQ(actualExchangeRate, expectedExchangeRate);
    ASSERT_GT(actualExchangeRate, 0); // Assert exchange rate is greater than 0
}

TEST(CurrencyConverter, TestInvalidConversion) 
{
    Mediator mediator;

    float amount = 100;
    int fromCurrency = -1; // Invalid index
    int toCurrency = 1000; // Invalid index
    float convertedAmount = mediator.convert(amount, fromCurrency, toCurrency);
    
    printf("TestInvalidConversion: convertedAmount=%f\n", convertedAmount);

    ASSERT_EQ(convertedAmount, 0); // Assert converted amount is 0 for invalid indices
}

TEST(CurrencyConverter, TestZeroAmountConversion) 
{
    Mediator mediator;

    float amount = 0;
    int fromCurrency = 1; // USD
    int toCurrency = 2;   // Euro
    float expectedConvertedAmount = 0;
    float actualConvertedAmount = mediator.convert(amount, fromCurrency - 1, toCurrency - 1);
    
    printf("TestZeroAmountConversion: actual=%f, expected=%f\n", actualConvertedAmount, expectedConvertedAmount);

    ASSERT_EQ(actualConvertedAmount, expectedConvertedAmount);
    ASSERT_TRUE(actualConvertedAmount == 0); // Assert converted amount is 0
}

TEST(CurrencyConverter, TestSameCurrencyConversion) 
{
    Mediator mediator;

    float amount = 100;
    int fromCurrency = 1; // USD
    int toCurrency = 1;   // USD
    float expectedConvertedAmount = amount;
    float actualConvertedAmount = mediator.convert(amount, fromCurrency - 1, toCurrency - 1);
    
    printf("TestSameCurrencyConversion: actual=%f, expected=%f\n", actualConvertedAmount, expectedConvertedAmount);

    ASSERT_EQ(actualConvertedAmount, expectedConvertedAmount);
    ASSERT_TRUE(actualConvertedAmount == amount); // Assert converted amount is equal to original amount
}

TEST(CurrencyConverter, TestNegativeAmountConversion) 
{
    Mediator mediator;

    float amount = -100;
    int fromCurrency = 1; // USD
    int toCurrency = 2;   // Euro
    float expectedConvertedAmount = amount * 0.84;
    float actualConvertedAmount = mediator.convert(amount, fromCurrency - 1, toCurrency - 1);
    
    printf("TestNegativeAmountConversion: actual=%f, expected=%f\n", actualConvertedAmount, expectedConvertedAmount);

    ASSERT_EQ(actualConvertedAmount, expectedConvertedAmount);
    ASSERT_LE(actualConvertedAmount, 0); // Assert converted amount is less than or equal to 0
}

TEST(CurrencyConverter, TestBoundaryConversion) 
{
    Mediator mediator;

    float minAmount = std::numeric_limits<float>::min();
    float maxAmount = std::numeric_limits<float>::max();
    int fromCurrency = 1; // USD
    int toCurrency = 2;   // Euro
    float expectedMinConvertedAmount = minAmount * 0.84;
    float expectedMaxConvertedAmount = maxAmount * 0.84;
    float actualMinConvertedAmount = mediator.convert(minAmount, fromCurrency - 1, toCurrency - 1);
    float actualMaxConvertedAmount = mediator.convert(maxAmount, fromCurrency - 1, toCurrency - 1);
    
    printf("TestBoundaryConversion: min=%f, max=%f\n", actualMinConvertedAmount, actualMaxConvertedAmount);

    ASSERT_EQ(actualMinConvertedAmount, expectedMinConvertedAmount);
    ASSERT_EQ(actualMaxConvertedAmount, expectedMaxConvertedAmount);
    ASSERT_GE(actualMaxConvertedAmount, actualMinConvertedAmount); // Assert max amount is greater than or equal to min amount
}

