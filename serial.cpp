#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <set>
using namespace std;

struct point{
    int x;
    int y;
    bool operator<(point p) const{
        return x < p.x;
    }
};

double tg_of_points(point b, point a){
    return (double)(b.y- a.y)/(b.x - a.x);
}

set<set<point>> find_points(const vector<point> &points){
    double temp_tg1, temp_tg2;
    point a;
    set<set<point>> result;
    for(int p = 0; p < points.size(); p++) {
        a = points[p];
        for (int i = 0; i < points.size(); i++) {
            set<point> half_result;
            half_result.clear();
            temp_tg1 = tg_of_points(points[i], a);
            {
                half_result.insert(a);
                half_result.insert(points[i]);
            }
            for (int j = 0; j < points.size(); j++) {
                temp_tg2 = tg_of_points(points[j], a);
                if (temp_tg2 == temp_tg1) {
                    {
                        half_result.insert(points[j]);
                    }
                }
            }
            if (half_result.size() > 2) {
                {
                    result.insert(half_result);
                }
            } else {
                half_result.clear();
            }
        }
    }
    return result;
}

int main(int argc, char ** argv) {
    int N = 1000;
    vector<point> pointss;

    srand(time(NULL));
    point temp_point;
    for(int i = 0; i < N; i++) {
        temp_point.x = 1000 - (rand() % 2000);
        temp_point.y = 1000 - (rand() % 2000);
        pointss.push_back(temp_point);
    }

    clock_t start = clock();
    set<set<point>> result = find_points(pointss);
    clock_t end = clock();

//            for (const set<point> &iii : result) {
//                cout << endl << endl;
//                for (const point &p : iii) {
//                    cout << "(";
//                    cout.width(4);
//                    cout << p.x << ";";
//                    cout.width(4);
//                    cout << p.y << ")" << endl;
//                }
//            }
    cout << "Time(s): " << (double )(end - start)/CLOCKS_PER_SEC << endl;
    return 0;
}

