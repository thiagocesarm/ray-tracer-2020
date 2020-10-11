#ifndef _COLOR_
#define _COLOR_

typedef unsigned char uchar;
enum RGB { R = 0, G, B };

class Color {
    private:
        float values[3] {0}; // default color white
    public:
        Color() {}
        Color(float r, float g, float b) {
            this->values[R] = r;
            this->values[G] = g;
            this->values[B] = b;
        }
        float red() const { return this->values[R]; }
        float green() const { return this->values[G]; }
        float blue() const { return this->values[B]; }
        float r() const { return this->values[R]; }
        float g() const { return this->values[G]; }
        float b() const { return this->values[B]; }
        float* getValues() {
            return values;
        }
        void setValues(uchar r, uchar g, uchar b) {
            this->values[R] = r;
            this->values[G] = g;
            this->values[B] = b;
        }
        bool operator == (const Color& rhs) {
            return this->values[R] == rhs.red() &&
                    this->values[G] == rhs.green() &&
                    this->values[B] == rhs.blue();
        }
        bool operator != (const Color& rhs) {
            return !(*this == rhs);
        }
        void operator = (const Color& rhs) {
            this->values[R] = rhs.red();
            this->values[G] = rhs.green();
            this->values[B] = rhs.blue();
        }
};

#endif
