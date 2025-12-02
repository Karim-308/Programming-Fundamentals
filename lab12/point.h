#ifndef POINT_H
#define POINT_H

class Point {
    int x;
    int y;

public:
    Point();
    Point(int xCoord, int yCoord);

    int getX() const;
    int getY() const;

    void setX(int xCoord);
    void setY(int yCoord);
};

#endif  // POINT_H
