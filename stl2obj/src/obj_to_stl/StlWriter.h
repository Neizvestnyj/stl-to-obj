#pragma once

#include "StlModel.h"

#include <ostream>

using namespace std;

class StlWriter
{
public:
    StlWriter(const StlModel& model) : model_(model) {}

    void WriteToFile(const string& fname) const;
    void WriteToStream(ostream& os) const;

private:
    const StlModel& model_;

    void WriteHeader(ostream& os) const;
    void WriteBody(ostream& os) const;
};
