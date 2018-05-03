#ifndef PUBLICTRANSPORTGRAPH_PTRCOMPARATOR_H
#define PUBLICTRANSPORTGRAPH_PTRCOMPARATOR_H


class PtrComparator {
public:
    template <typename T>
    bool operator()(const T *ptr1, const T *ptr2) const {
        return *ptr1 < *ptr2;
    }
};
#endif //PUBLICTRANSPORTGRAPH_PTRCOMPARATOR_H
