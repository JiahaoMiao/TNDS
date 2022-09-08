#include "vectorOperations.h"
#include "fmtlib.h"


int main(){
    std::vector<double> v1{2,3,4};
    std::vector<double> v2{22,33,44};

    fmt::print("This is v1\n");
    Print(v1);
    fmt::print("This is v2\n");
    Print(v2);

    double k{4};
    std::vector<double> v3 =k*v1;
    fmt::print("====>> Multiply v1 by k = {}\n",k);
    fmt::print("This is v3 =k*v1\n");
    Print(v3);
    std::vector<double> v4 =v1+v2;
    fmt::print("====>> Summing v1 and v2\n");
    fmt::print("This is v4=v1+v2\n");
    Print(v4);

    fmt::print("====>> Summing v1 and v2(operator+=)\n");
    std::vector<double> v5 = v1+=v2;
    fmt::print("This is v1 modified\n");
    Print(v1);
    fmt::print("This is v2\n");
    Print(v2);
    fmt::print("This is v5=v1+=v2\n");
    Print(v5);
   

    return 0;
}