#include <iostream>

int main()
{
    double original_price, first_discount_price, second_discount_price, first_discount_percent, second_discount_percent;
    double discount_percent = 0;
    
    std::cin >> original_price >> first_discount_price >> second_discount_price >> first_discount_percent >> second_discount_percent;

    if(original_price > first_discount_price && original_price <= second_discount_price)
    {
        discount_percent = first_discount_percent;
    }
    else if (original_price > second_discount_price)
    {
        discount_percent = second_discount_percent;
    }
    
    std::cout << original_price * (1 - discount_percent / 100);
}