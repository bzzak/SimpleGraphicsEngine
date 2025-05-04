#ifndef BUFFER_H
#define BUFFER_H



class Buffer {
protected:
    unsigned int* color;
    float* depth;
    float maxDepth;
    int w, h;

public:

    Buffer(int w, int h, float _maxDepth = 100);
    ~Buffer();

    [[nodiscard]] int getWidth() const {
        return w;
    }

    [[nodiscard]] int getHeight() const {
        return h;
    }


    float getMaxDepth() const;
    void setSize(int width, int height);
    void setMaxDepth(float depth);
    void fillColor(unsigned int r,unsigned int g,unsigned int b, unsigned int a = 255) const;
    void fillSingleColor(int index, unsigned int r,unsigned int g,unsigned int b, unsigned int a = 255) const;
    float getDepth(int index) const;
    void setDepth(int index, float d) const;
    void clearColor() const;
    void clearDepth() const;

};



#endif //BUFFER_H
