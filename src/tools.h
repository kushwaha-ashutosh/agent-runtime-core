#pragma once
#include <string>


class Tool{
public:
    virtual ~Tool()=default;
    virtual std::string name() const=0;
    virtual void run()=0;
};

// Concrete tools
class SearchTool:public Tool{
public:
    std::string name() const override;
    void run() override;
};

class SummaryTool:public Tool{
public:
    std::string name() const override;
    void run() override;
};
