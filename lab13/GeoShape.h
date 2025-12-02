#ifndef GEOSHAPE_H
#define GEOSHAPE_H

class GeoShape {
    protected:
        double dim1, dim2;
    public:
        GeoShape(double d1 = 0, double d2 = 0) : dim1(d1), dim2(d2) {}
        void setDimension1(double d1);
        void setDimension2(double d2);
        double getDimension1() const;
        double getDimension2() const;
        virtual double area() const = 0;
        virtual ~GeoShape() {}
};

#endif
