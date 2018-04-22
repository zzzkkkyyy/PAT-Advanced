#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <map>
#include <cstdlib>

using namespace std;
map<char, int> str_to_int;

int find(long long ref_value, string str, long long down_threshold, long long up_threshold)
{
    while (down_threshold <= up_threshold)
    {
        long long radix = (up_threshold + down_threshold) / 2;
        long long sum = 0;
        for (string::iterator it = str.begin(); it != str.end(); it++)
        {
            sum = sum * radix + str_to_int[*it];
            if (sum > ref_value)
            {
                break;
            }
        }
        if (sum < ref_value)
        {
            down_threshold = radix + 1;
        }
        else if (sum > ref_value)
        {
            up_threshold = radix - 1;
        }
        else
        {
            cout << radix << endl;
            return 0;
        }
    }
    cout << "Impossible" << endl;
    return 0;
}
int main(void)
{
    string num1, num2;
    long long radix_1, radix_2, radix;
    cin >> num1 >> num2 >> radix_1 >> radix_2;
    while ((!num1.empty()) && num1[0] == '0')
    {
        num1.erase(num1.begin());
    }
    if (num1.empty()) num1 = '0';
    while ((!num2.empty()) && num2[0] == '0')
    {
        num2.erase(num2.begin());
    }
    if (num2.empty()) num2 = '0';
    if (radix_1 == 2)
    {
        swap(num1, num2);
    }
    radix = radix_2;

    if (num1 == num2 && num2 == "1")
    {
        cout << 2 << endl;
        return 0;
    }
    else if (num1 == num2 && num2 != "1")
    {
        cout << radix << endl;
        return 0;
    }

    for (char i = '0'; i <= '9'; i++)
    {
        str_to_int[i] = i - '0';
    }
    for (char i = 'a'; i <= 'z'; i++)
    {
        str_to_int[i] = i - 'a' + 10;
    }

    long long ref = 0;
    for (string::iterator it = num1.begin(); it != num1.end(); it++)
    {
        ref = ref * radix + str_to_int[*it];
    }
    long long down_threshold, up_threshold;
    if (num1 != num2)
    {
        char max_ch = '0';
        for (string::iterator it = num2.begin(); it != num2.end(); it++)
        {
            if (str_to_int[*it] > str_to_int[max_ch])
                max_ch = *it;
        }
        down_threshold = str_to_int[max_ch] + 1;
        up_threshold = max(ref, down_threshold);
        find(ref, num2, down_threshold, up_threshold);
    }
}