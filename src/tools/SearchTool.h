#pragma once
#include "Tool.h"

class SearchTool : public Tool {
public:
    std::string name() const override;
    void run() override;
};
