#include <iostream>
#include <limits>
#include "Complex.h"

using namespace std;

int main() {
    cout << "Simple Complex test\n";

    Complex def;
    Complex param(3.5f, -2.25f);
    Complex copy(param);
    cout << "Default    : " << def << '\n';
    cout << "Param      : " << param << '\n';
    cout << "Copy       : " << copy << '\n';
    cout << "copy real=" << copy.getReal() << " img=" << copy.getImg() << '\n';

    cout << " using setters:\n";
    Complex setter;
    setter.setReal(5.5f);
    setter.setImg(-4.25f);
    cout << "After setters : " << setter << '\n';
    setter(7.75, 9.5);
    cout << "After operator(): " << setter << '\n';

    cout << "using assigment operators\n";
    Complex assignSrc(1, 1);
    Complex assignB, assignC;
    assignC = assignB = assignSrc;
    cout << "Source : " << assignSrc << '\n';
    cout << "B      : " << assignB << '\n';
    cout << "C      : " << assignC << '\n';

    cout << "overloading arthismatic operatior\n";
    Complex arithA(2, 3);
    Complex arithB(-4, 1);
    cout << "A      : " << arithA << '\n';
    cout << "B      : " << arithB << '\n';
    cout << "A + B  : " << arithA + arithB << '\n';
    cout << "A - B  : " << arithA - arithB << '\n';
    cout << "A * B  : " << arithA * arithB << '\n';
    cout << "A / B  : " << arithA / arithB << '\n';

    cout << "power operator\n";
    Complex powerBase(1, 1);
    for (int p = 0; p <= 4; ++p) {
        cout << "base ^ " << p << " : " << (powerBase ^ p) << '\n';
    }

    cout << "prefic and postfix\n";
    Complex inc(0, 0);
    cout << "start   : " << inc << '\n';
    cout << "++inc   : " << ++inc << '\n';
    cout << "--inc   : " << --inc << '\n';
    Complex post = inc++;
    cout << "inc++ return : " << post << '\n';
    cout << "after ++     : " << inc << '\n';
    post = inc--;
    cout << "inc-- return : " << post << '\n';
    cout << "after --     : " << inc << '\n';

    cout << "compound operators\n";
    Complex left(3, -2);
    Complex right(-1, 4);
    cout << "left : " << left << " right : " << right << '\n';
    Complex temp = left;
    cout << "left += right : " << (temp += right) << '\n';
    temp = left;
    cout << "left -= right : " << (temp -= right) << '\n';
    temp = left;
    cout << "left *= right : " << (temp *= right) << '\n';
    temp = left;
    cout << "left /= right : " << (temp /= right) << '\n';
    temp = left;
    cout << "left ^= 3     : " << (temp ^= 3) << '\n';

    cout << "unary operators\n";
    Complex unary(5, -7);
    cout << "+unary : " << +unary << '\n';
    cout << "-unary : " << -unary << '\n';

    cout << "using Comparisons \n";
    Complex cmp1L(1, 2);
    Complex cmp1R(1, 2);
    cout << "Case 1 -> " << cmp1L << " vs " << cmp1R << '\n';
    cout << " == " << (cmp1L == cmp1R ? "true" : "false")
         << " != " << (cmp1L != cmp1R ? "true" : "false")
         << " < "  << (cmp1L < cmp1R ? "true" : "false")
         << " <= " << (cmp1L <= cmp1R ? "true" : "false")
         << " > "  << (cmp1L > cmp1R ? "true" : "false")
         << " >= " << (cmp1L >= cmp1R ? "true" : "false") << '\n';

    Complex cmp2L(1, 2);
    Complex cmp2R(2, 1);
    cout << "Case 2 -> " << cmp2L << " vs " << cmp2R << '\n';
    cout << " == " << (cmp2L == cmp2R ? "true" : "false")
         << " != " << (cmp2L != cmp2R ? "true" : "false")
         << " < "  << (cmp2L < cmp2R ? "true" : "false")
         << " <= " << (cmp2L <= cmp2R ? "true" : "false")
         << " > "  << (cmp2L > cmp2R ? "true" : "false")
         << " >= " << (cmp2L >= cmp2R ? "true" : "false") << '\n';

    Complex cmp3L(3, 0);
    Complex cmp3R(2, 5);
    cout << "Case 3 -> " << cmp3L << " vs " << cmp3R << '\n';
    cout << " == " << (cmp3L == cmp3R ? "true" : "false")
         << " != " << (cmp3L != cmp3R ? "true" : "false")
         << " < "  << (cmp3L < cmp3R ? "true" : "false")
         << " <= " << (cmp3L <= cmp3R ? "true" : "false")
         << " > "  << (cmp3L > cmp3R ? "true" : "false")
         << " >= " << (cmp3L >= cmp3R ? "true" : "false") << '\n';

    Complex cmp4L(-1, -1);
    Complex cmp4R(-1, 5);
    cout << "Case 4 -> " << cmp4L << " vs " << cmp4R << '\n';
    cout << " == " << (cmp4L == cmp4R ? "true" : "false")
         << " != " << (cmp4L != cmp4R ? "true" : "false")
         << " < "  << (cmp4L < cmp4R ? "true" : "false")
         << " <= " << (cmp4L <= cmp4R ? "true" : "false")
         << " > "  << (cmp4L > cmp4R ? "true" : "false")
         << " >= " << (cmp4L >= cmp4R ? "true" : "false") << '\n';

    cout << "\n== Index [] ==\n";
    Complex indexC(8.5f, -3.25f);
    cout << "indexC[0] : " << indexC[0] << '\n';
    cout << "indexC[1] : " << indexC[1] << '\n';
    try {
        cout << indexC[2] << '\n';
    } catch (const out_of_range& ex) {
        cout << "indexC[2] threw -> " << ex.what() << '\n';
    }

    cout << "input and output streams\n";
    Complex streamValue;
    cout << "Enter a complex number (real imag): ";
    if (cin >> streamValue) {
        cout << "istream >> : " << streamValue << '\n';
        cout << "ostream << : " << streamValue << '\n';
    } else {
        cout << "istream >> failed, clearing input buffer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "operator() loop\n";
    Complex call;
    for (int i = 0; i < 3; ++i) {
        double r = i * 1.25;
        double im = -i * 0.5;
        call(r, im);
        cout << "call #" << i << " -> " << call << '\n';
    }

    return 0;
}
