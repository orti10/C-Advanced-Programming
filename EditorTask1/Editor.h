#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Document.h"


using namespace std;

class Editor{

    public:
    Document d;
    
    Editor();
    void loop();
};

