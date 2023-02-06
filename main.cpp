#include <iostream>
#include <vector>

using namespace std;

class Dot {
public:
    Dot() {
        x = 0;
        y = 0;
    }

    Dot(const int& new_x, const int& new_y) {
        x = new_x;
        y = new_y;
    }

    int x;
    int y;
};

class Rectangle {
public:
    Rectangle() {
        L = Dot();
        R = Dot();
    }

    Rectangle(const int& xL, const int& yL, const int& xR, const int& yR) {
        L = Dot(xL, yL);
        R = Dot(xR, yR);
    }

    Dot LU() const {
        return Dot(L.x, R.y);
    }

    Dot RD() const {
        return Dot(R.x, L.y);
    }

    Dot L, R;

    int intesections = 0;
};

ostream& operator<<(ostream& os, const Rectangle& r) {
    os << "Rectangle: (" << r.L.x << "; " << r.L.y << "), (" << r.R.x << "; " << r.R.y << ")";
    return os;
}

bool is_dot_in_rectangle(const Dot& d, const Rectangle& r) {
    if (r.L.y < d.y && r.R.y > d.y && r.L.x < d.x && r.R.x > d.x) return true;
    return false;
}

bool on_border(const Rectangle& r1, const Rectangle& r2) {
    bool left = false;
    if ((r1.L.x == r2.L.x && r1.L.y != r2.R.y) || (r1.L.y == r2.L.y && r1.L.x != r2.R.x)) left = true;
    if ((r1.R.x == r2.R.x && r1.R.y != r2.L.y) || (r1.R.y == r2.R.y && r1.R.x != r2.L.x)) return (left ? true : false);
    return false;
}

bool are_intersecting(const Rectangle& r1, const Rectangle& r2) {
    if (on_border(r1, r2)) return true;
    if (is_dot_in_rectangle(r1.L, r2) || is_dot_in_rectangle(r1.LU(), r2) || is_dot_in_rectangle(r1.RD(), r2) || is_dot_in_rectangle(r1.R, r2) ||
        is_dot_in_rectangle(r2.L, r1) || is_dot_in_rectangle(r2.LU(), r1) || is_dot_in_rectangle(r2.RD(), r1) || is_dot_in_rectangle(r2.R, r1)) return true;
    return false;
}

int main() {
    int n;
    cin >> n;
    vector<Rectangle> rectangles(n);
    for (int i = 0; i < n; i++) {
        int xL, yL, xR, yR;
        cin >> xL >> yL >> xR >> yR;
        rectangles[i] = Rectangle(xL, yL, xR, yR);
        for (int j = 0; j < i; j++) {
            if (are_intersecting(rectangles[i], rectangles[j])) {
                //cout << rectangles[i] << " cross " << rectangles[j] << "!!\n";
                rectangles[i].intesections++;
                rectangles[j].intesections++;
            }
        }
    }
    for (Rectangle& r : rectangles) {
        cout << r.intesections << " ";
    }

    return 0;
}
