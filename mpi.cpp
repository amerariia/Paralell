#include <mpi/mpi.h>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <set>
using namespace std;
int ProcNum;  // Число доступних процесів
int ProcRank; // Ранг поточного процесу


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

void find_points(const vector<point> &points) {
    int num_points = points.size() / ProcNum;
    set<set<point>> result;
    int last_points = 0;
    if (ProcRank + 1 == ProcNum) {
        last_points = points.size() % ProcNum;
    }
    double temp_tg1, temp_tg2;
    point a;
    for (int p = ProcRank * num_points; p < ProcRank * num_points + num_points + last_points; p++) {
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
//    int rank = 0;
//    while (rank < ProcNum) {
//        if (rank++ == ProcRank) {
//            cout << endl << " Rank      " << ProcRank << endl;
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
//        }
//        MPI_Barrier(MPI_COMM_WORLD);
//    }
    MPI_Barrier(MPI_COMM_WORLD);
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


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    clock_t start = clock();
   find_points(pointss);
    clock_t end = clock();

    
    if(ProcRank == 0){
        cout << "Time(s): " << (double )(end - start)/CLOCKS_PER_SEC << endl;
    }
    MPI_Finalize();
    return 0;
}

