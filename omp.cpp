#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <set>
#include <omp.h>

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
    int numb_of_threads = 4;
    omp_set_num_threads(numb_of_threads);
    int num_points = points.size()/numb_of_threads;
    set<set<point>> result;
    #pragma omp paralell
    {
        int last_points = 0;
        int rank = omp_get_thread_num();
        if(rank + 1 == numb_of_threads){
            last_points = points.size()%numb_of_threads;
        }
        double temp_tg1, temp_tg2;
        point a;
        for (int p = rank*num_points; p < rank*num_points + num_points + last_points; p++) {
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
                        #pragma omp critical
                        {
                        result.insert(half_result);
                        }
                    }
                } else {
                    half_result.clear();
                }
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


//        for (const set<point> &iii : result) {
//            cout << endl << endl;
//            for (const point &p : iii) {
//                cout << "(";
//                cout.width(4);
//                cout << p.x << ";";
//                cout.width(4);
//                cout << p.y << ")" << endl;
//            }
//        }
    cout << "Time(s): " << (double )(end - start)/CLOCKS_PER_SEC << endl;
    return 0;
}

