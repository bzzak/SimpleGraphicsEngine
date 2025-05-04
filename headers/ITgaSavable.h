#ifndef ITGASAVABLE_H
#define ITGASAVABLE_H

class ITgaSavable {
    public:
    virtual ~ITgaSavable()= default;
    virtual int save() = 0;
};

#endif //ITGASAVABLE_H
