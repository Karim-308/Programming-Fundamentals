#include <iostream>
#include <limits>
#include "Complex.h"

using namespace std;

int main() {

    Complex defaultComplex;
    Complex parametrizedComplex(3.5f, -2.25f);
    Complex copyComplex(parametrizedComplex);


    cout << defaultComplex << endl;
    cout << parametrizedComplex << endl;
    cout << copyComplex << endl;
    cout << copyComplex[0] << "  " <<copyComplex[0]<<endl;
    cout << copyComplex.getReal()<< copyComplex.getImg() << endl;

    defaultComplex.setImg(50);
    defaultComplex.setReal(70);
    cout<<defaultComplex<<endl;

    copyComplex = defaultComplex;
    cout<< copyComplex<<endl;

    cout << "complex1 + complex2  : " << defaultComplex + copyComplex << endl;
    cout << "complex1 - complex2  : " << defaultComplex - copyComplex << endl;
    cout << "complex1 * complex2  : " << defaultComplex * copyComplex << endl;
    cout << "complex1 / complex2  : " << defaultComplex / copyComplex << endl;
    Complex zeroCom(0,0);
    try {
        cout << "A / B  : " << defaultComplex / copyComplex << endl;
    }
    catch (const std::runtime_error& e) {
       cout <<e.what() << endl;
   }



    Complex powerComplex(2, 2);
    cout << powerComplex<<endl;
    cout << (powerComplex ^ 3)<<endl;

    ++powerComplex;
    cout << powerComplex<<endl;

    
    cout << powerComplex--<<endl;

    cout<< -powerComplex<<endl;
    cout<< +powerComplex<<endl;


    Complex left(3, -2);
    Complex right(-1, 4);
    cout << "AA : " << left << " BB : " << right << endl;
    Complex temp = left;
    cout << "AA += BB : " << (temp += right) << endl;
    temp = left;
    cout << "AA -= BB : " <<  (temp -= right) << endl;
    temp = left;
    cout << "AA *= BB : " <<  (temp *= right) << endl;
    temp = left;
    cout << "AA /= BB : " <<  (temp /= right) << endl;
    temp = left;
    cout << "AA += BB : " <<  (temp ^= 3) << endl;

    try
    {
        cout << "AA /= BB : " <<  (temp /= zeroCom) << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    Complex cmp1L(1, 2);
    Complex cmp1R(1, 0);

    if (cmp1L>cmp1R){
        cout<<cmp1L << " is bigger than " << cmp1R<< endl;
    }
    else if (cmp1L<cmp1R){
        cout<<cmp1R << " is bigger than " << cmp1L <<endl;
    }
    else
     cout<<cmp1L << " is equal to " << cmp1R<<endl;


    Complex complexWithParantethis;
    complexWithParantethis(80, 70);
    cout << complexWithParantethis<<endl;

    return 0;
}
