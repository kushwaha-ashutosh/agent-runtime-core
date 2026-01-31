#include "SearchTool.h"
#include <iostream>

std::string SearchTool::name() const {
    return "search";
}

void SearchTool::run() {
    std::cout << "Tool: found files -> a.pdf, b.pdf" << std::endl;
}
