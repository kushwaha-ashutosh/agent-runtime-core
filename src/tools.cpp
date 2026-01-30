#include <iostream>
#include "tools.h"

void SearchTool::run(){
    std::cout << "Tool: found files -> a.pdf, b.pdf" << std::endl;
}

void SummaryTool::run(){
    std::cout << "Tool: summary created" << std::endl;
}
