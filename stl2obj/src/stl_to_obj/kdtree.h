#ifndef TYPE_KDTREE_H_
#define TYPE_KDTREE_H_

#include <memory>
#include <limits>
#include <vector>
#include "vectornd.h"

using namespace std;

template <int DIM, typename Real = double>
class KDTree {
    //  define Point type for convenience
    using Point = VectorND<DIM, Real>;

    //  define Node type for private operations on the tree. No one should use
    //  this outside KDTree
    class Node {
        Node(int id, int8_t axis = 0) : id_(id), axis_(axis) {}
        ~Node() { delete left_; delete right_; }
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        uint32_t id_;
        int8_t axis_;
        friend class KDTree<DIM, Real>;
    };

    using NodePtr = Node*;

    //  pointer to the root node
    Node* root_ = nullptr;

    //  vector of all points; this can dynamically grow or shrink
    //  Note that this is the sinle data structure for storing points data. The
    //  tree has access only to elements of this vector, but there is no point
    //  data in the tree. This simplifies the algorithms and makes the API
    //  easier to use.
    vector<Point> data_;

public: // methos
    //  default constructor
    KDTree() = default;

    //  default destructor
    ~KDTree() { delete root_; }

    //  delete copy constructor, assignment operator, move constructor, and
    //  move assignment operator. we don't want someone accidentally copies a
    //  search tree
    KDTree(const KDTree&) = delete;
    KDTree(KDTree&&) = delete;
    KDTree& operator=(const KDTree&) = delete;
    KDTree& operator=(KDTree&&) = delete;

    //  insert a new point into the tree
    void insert(const Point& point);
    //  get the current size
    size_t size() { return data_.size(); }

    //  This function is N^2 so it's very inefficient. It's included only for
    //  testing purpose to confirm the correctness of algorithm. Otherwise,
    //  it shouldn't be used in actual code.
    int findNearestBruteForce(const Point& pt);

    //  This function is NlogN, so it should be used in actual code.
    int findNearest(const Point& pt);

    //  return the point from its id
    Point getPoint(int index) {
        return data_[index];
    }

private: // methods
    int findNearest(Node* node, const Point& point, Real& minDist);
    Node* getParentNode(const Point& point) const;
};

template <int DIM, typename Real>
void KDTree<DIM, Real>::insert(const Point& point) {
    uint32_t id = data_.size();
    data_.push_back(point);
    if (!root_) {
        root_ = new Node(0, 0);
    } else {
        Node* parent = getParentNode(point);
        if (data_[id][parent->axis_] <= data_[parent->id_][parent->axis_]) {
            parent->left_ = new Node(id, (parent->axis_ + 1) % DIM);
        } else {
            parent->right_ = new Node(id, (parent->axis_ + 1) % DIM);
        }
    }
}


//  Find the nearest point in the data set to "point".
//  This is the public version of this function. It does two things:
//  1) It finds the potential tree node were "point" to be inserted into tree.
//  2) It traverses the tree once more to find all points that might be closer
//     to point.
//  return value: index of the nearest node
template <int DIM, typename Real>
int KDTree <DIM, Real>::findNearest(const Point& point)
{
    Node* parent = getParentNode(point);
    if (!parent) return -1;
    Real minDist = Point::get_dist_sqr(point, data_[parent->id_]);
    int better = findNearest(root_, point, minDist);
    return (better >= 0) ? better : parent->id_;
}

//  Find the nearest point in the data set to "point"
//  This is the private version of this function. Although it works for
//  arbitrary large values of "minDist", it's only efficient for small values
//  of minDist. For large values of minDist, it behaves like a brute-force
//  search.
template <int DIM, typename Real>
int
KDTree<DIM, Real>::findNearest(Node* node, const Point& point, Real& minDist)
{
    if (!node) return -1;
    Real d = Point::get_dist_sqr(point, data_[node->id_]);

    int result = -1;
    if (d < minDist) {
        result = node->id_;
        minDist = d;
    }

    Real dp = data_[node->id_][node->axis_] - point[node->axis_];
    if (dp * dp < minDist) {
        int pt = findNearest(node->left_, point, minDist);
        if (pt >= 0) result = pt;
        pt = findNearest(node->right_, point, minDist);
        if (pt >= 0) result = pt;
    } else if (point[node->axis_] <= data_[node->id_][node->axis_]) {
        int pt = findNearest(node->left_, point, minDist);
        if (pt >= 0) result = pt;
    } else {
        int pt = findNearest(node->right_, point, minDist);
        if (pt >= 0) result = pt;
    }
    return result;
}

//  Give a point "point" and a node "node", return the parent node if we were to
//  insert the point into the tree. This is useful because it gives us the
//  initial guess about the nearest point in the tree.

template <int DIM, class Real>
typename KDTree<DIM, Real>::Node*
KDTree<DIM, Real>::getParentNode(const Point& point) const
{
    Node* node = root_;
    Node* parent = nullptr;
    while (node) {
        parent = node;
        node = (point[node->axis_] <= data_[node->id_][node->axis_])
            ? node->left_ : node->right_;
    }
    return parent;
}


// This is just a brute force O(n) search. Use only for testing.
template <int DIM, typename Real>
int
KDTree<DIM, Real>::findNearestBruteForce(const Point& pt)
{
    int index = -1;
    Real minD2 = numeric_limits<Real>::max();
    for (int i = 0; i < data_.size(); i++) {
        Real d2 = Point::get_dist_sqr(pt, data_[i]);
        if (d2 < minD2) {
            minD2 = d2;
            index = i;
        }
    }
    return index;
}


#endif // TYPE_KDTREE_H_
