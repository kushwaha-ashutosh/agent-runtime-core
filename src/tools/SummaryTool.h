#pragma once
#include "Tool.h"

class SummaryTool : public Tool {
public:
    std::string name() const override;
    void run() override;
};
