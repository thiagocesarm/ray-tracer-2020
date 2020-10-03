#ifndef _COLOR_
#define _COLOR_

typedef unsigned char uchar;
enum RGB { R = 0, G, B };

class Color {
    private:
        uchar values[3] {0}; // default color white
    public:
        Color() {}
        Color(uchar r, uchar g, uchar b) {
            this->values[R] = r;
            this->values[G] = g;
            this->values[B] = b;
        }
        uchar red() const { return this->values[R]; }
        uchar green() const { return this->values[G]; }
        uchar blue() const { return this->values[B]; }
        uchar r() const { return this->values[R]; }
        uchar g() const { return this->values[G]; }
        uchar b() const { return this->values[B]; }
        uchar* getValues() {
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
