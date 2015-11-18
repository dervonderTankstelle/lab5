#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

struct colloid{
    double x,y;
};

void init(colloid* const c, const int N);
void conditions(int* const rx, int* const ry, const int N);
void pusher(colloid* const c, const int* const rx, const int* const ry, const double step, const int N);
void print(const colloid* const c, const int N, const string fname);
void statistics(double& mean, double& var, const colloid* const c, const int N);


int main(void){
  
    const int N  = 50;
    int*      rx = new int[N];
    int*      ry = new int[N];
    colloid*  c  = new colloid[N];
    
    const double step = 0.1;
    
    init(c, N);
    
    stringstream s;
    string       fname = "rwalk";
    
    const int Nsteps = 100;
    const int Nfiles = 10;
    int Nsubsteps    = Nsteps / Nfiles;
    
    s.str("");
    s << fname << "_0.dat";
    print(c, N, s.str());
    
    srand(time(NULL));
    
    for(int i = 1; i <= Nfiles; i++){
	for(int j = 0; j < Nsubsteps; j++){
	    conditions(rx, ry, N);
	    pusher(c, rx, ry, step, N);
	}
	s.str("");
	s << fname << "_" << i << ".dat";
	print(c, N, s.str());
    }
    
    
    delete[] rx,ry,c;
    return 0;
}

void init(colloid* const c, const int N){
    for(int i = 0; i < N; i++){
	c[i].x = 0;
	c[i].y = 0;
    }
}

void conditions(int* const rx, int* const ry, const int N){
    for(int i = 0; i < N; i++){
	rx[i] = int(2*double(rand())/RAND_MAX + 0.5) - 1;
	ry[i] = int(2*double(rand())/RAND_MAX + 0.5) - 1;
    }
}

void pusher(colloid* const c, const int* const rx, const int* const ry, const double step, const int N){
    for(int i = 0; i < N; i++){
	c[i].x += rx[i]*step;
	c[i].y += ry[i]*step;
    }    
}

void print(const colloid* const c, const int N, const string fname){
    ofstream out(fname.c_str());
    for(int i = 0; i < N; i++)
	out << c[i].x << "\t" << c[i].y << endl;
    out.close();
}

void statistics(double& mean, double& var, const colloid* const c, const int N){
}