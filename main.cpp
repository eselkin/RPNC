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
        cin >> eli;
        cout << "Fraction eli: " << eli << endl;
        cin >> eli5;
        cout << "Fraction eli5: " << eli5 << endl;
        eli = eli ^ eli5;
        // eli = eli^5 // this is interpreted as eli^(new fraction(5,1);
        cout << "Eli to the eli5th power=" << eli;
        cout << endl;
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
        cin >> eli2;
        cout << "Mixed number eli2: " << eli2 << endl;
        cin >> eli3;
        cout << "Mixed number eli3: " << eli3 << endl;
        cout << "eli2-eli3 =" << eli2 - eli3 << endl;
        cout << "eli2+eli3 =" << eli2 + eli3 << endl;
        cout << "eli2/eli3 =" << eli2 / eli3 << endl;
        cout << "eli2*eli3 =" << eli2 * eli3 << endl;
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

