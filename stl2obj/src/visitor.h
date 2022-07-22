#ifndef TYPE_VISITOR_H_
#define TYPE_VISITOR_H_
#pragma once

#include "geombase.h"

template<typename T>
class Visitor {
public:
    virtual void dispatch(T& model) = 0;
};

#endif // TYPE_VISITOR_H_
