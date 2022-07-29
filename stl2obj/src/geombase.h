#ifndef TYPE_GEOMBASE_H_
#define TYPE_GEOMBASE_H_
#pragma once

using namespace std;

// forward declaration
template<typename T> class Visitor;

template<typename T>
class GeomBase {
public:
    virtual void visit(Visitor<T>&& v) {
        static_cast<T*>(this)->visit(move(v));
    }
};

#endif // TYPE_GEOMBASE_H_
