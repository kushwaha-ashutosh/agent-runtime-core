#include <iostream>
#include "tools.h"

// SearchTool
std::string SearchTool::name() const{
    return "search";
}

void SearchTool::run(){
    std::cout << "Tool: found files -> a.pdf, b.pdf" << std::endl;
}

// SummaryTool
std::string SummaryTool::name() const{
    return "summarize";
}

void SummaryTool::run(){
    std::cout << "Tool: summary created" << std::endl;
}
