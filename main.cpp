// The main.cpp you can use for testing will replace this file soon.

#include "provided.h"

#include "MyMap.h"
#include <cassert>

int main()
{
    MyMap<int, std::string> m;
    assert(m.size() == 0);
    m.associate(10, "d");
    m.associate(9, "c");
    m.associate(11, "e");
    m.associate(11, "f");
    
    const std::string s = *m.find(10);
    assert(s == "d");
    
    const std::string s2 = *m.find(11);
    assert(s2 == "f");
    
    assert(m.size() == 3);
}
