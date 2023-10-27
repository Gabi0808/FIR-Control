#include <iostream>
#include "interfaces.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    int loginResult = login();
    if (loginResult == 0)
    {
        return 0;
    }
    selectAction(loginResult);
    return 0;
}
