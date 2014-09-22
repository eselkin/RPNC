#include <iostream>
#include "fraction.h"
#include "mixednum.h"
using namespace std;

int main()
{
    // Fraction tests
    fraction eli, eli5;
    //    fraction eli2;
    //    fraction eli3;
    //    cout << "eli" << eli << endl;
    try {
        cout << "Enter a fraction:";
        cin >> eli;
        cout << "Fraction eli: " << eli << endl;
        cout << "Enter another fraction:";
        cin >> eli5;
        cout << "Fraction eli5: " << eli5 << endl;
        // eli = eli^5 // this is interpreted as eli^(new fraction(5,1);
        cout << "Eli to the eli5th power=" << (eli ^ eli5) << endl;  // got inline ^ to work, but needs parenthesis, I guess because of odd ^ precedence
    }
    catch (FRAC_ERROR f)
    {
        if (f == DIV_BY_ZERO)
            cout << "DIVIDE BY ZERO";
        else if (f == NOT_A_FRAC)
            cout << "NOT A FRAC";
        cout << endl;
    }

    //    cin >> eli2;
    //    cout << eli << endl;
    //    cout << eli << "/" << eli2 << "=";
    //    eli3 = eli / eli2;
    //    cout << eli3 << endl;
    //    fraction eli4(eli3 * eli2);
    //    cout << "ELI4: " << eli4 << endl;
    //    cout << eli << "-" << eli2 << "=";
    //    eli = eli - eli2;
    //    cout << eli << endl;
    //    cout << eli << "+" << eli2 << "=" << eli + eli2 << endl;
    MixedNum eli2, eli3;
    try {
        cout << "Enter a mixed number: ";
        cin >> eli2;
        cout << "Mixed number eli2: " << eli2 << endl;
        cout << "Enter another mixed number: ";
        cin >> eli3;
        cout << "Mixed number eli3: " << eli3 << endl;
        cout << "eli2-eli3 =" << eli2 - eli3 << endl;
        cout << "eli2+eli3 =" << eli2 + eli3 << endl;
        cout << "eli2/eli3 =" << eli2 / eli3 << endl;
        cout << "eli2*eli3 =" << eli2 * eli3 << endl;

        cout << "Enter mixed number as a power: ";
        cin >> eli3;
        cout << eli2 << " to the power of " << eli3 << "=" <<  (eli2 ^ eli3) << endl; // got inlining to work, but needs ()
    }
    catch (FRAC_ERROR f)
    {
        if (f == DIV_BY_ZERO)
            cout << "DIVIDE BY ZERO";
        else if (f == NOT_A_FRAC)
            cout << "NOT A FRAC";
        cout << endl;
    }
    catch (MIXED_NUM_ERROR m)
    {
        if (m == BAD_MIXED_NUM)
            cout << "BAD MIXED NUM" <<endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}

