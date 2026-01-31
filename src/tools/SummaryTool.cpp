#include "SummaryTool.h"
#include <iostream>
#include <stdexcept>

std::string SummaryTool::name() const {
    return "summarize";
}

void SummaryTool::run() {
    throw std::runtime_error("Summary model failed to load");
}
