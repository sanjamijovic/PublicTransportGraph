#ifndef POOP_P1_PTRCOMPARATOR_H
#define POOP_P1_PTRCOMPARATOR_H


class PtrComparator {
public:
    template <typename T>
    bool operator()(const T *ptr1, const T *ptr2) const {
        return *ptr1 < *ptr2;
    }
};


#endif //POOP_P1_PTRCOMPARATOR_H
