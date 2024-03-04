#include <iostream>
#include <string>
using namespace std;

void ashbabe(string num, int divisor)
{
    string result;
    int index = 0;
    int temp = num[index] - '0';

    if (divisor == 0)
    {
        cout << "Undefined" << endl;
        return;
    }

    while (temp < divisor && index < num.size() - 1)
    {
        temp = temp * 10 + (num[++index] - '0');
    }

    while (index < num.size())
    {
        result += (temp / divisor) + '0';
        temp = (temp % divisor) * 10 + num[++index] - '0';
    }

    if (result.empty())
    {
        cout << "Quotient: 0" << endl;
    }
    else
    {
        cout << "Quotient: " << result << endl;
    }
}

int main()
{
    string dividend;
    int divisor;

    cout << "Enter the dividend: ";
    cin >> dividend;
    cout << "Enter the divisor: ";
    cin >> divisor;

    ashbabe(dividend, divisor);

    return 0;
}
