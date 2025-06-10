#include "cheat/Cheat.h"
#include <iostream>

int main()
{
    Framework::Cheat cheat;

    if (!cheat.Initialize()) {
        std::cerr << "Failed to initialize cheat" << std::endl;
        return 1;
    }

    cheat.Run();
    return 0;
}