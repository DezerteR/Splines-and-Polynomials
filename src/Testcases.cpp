#include <fstream>
#include "Spline.hpp"
using namespace std;

void writeSplineToFile(const std::string &filename, Spline<float> &spline, float from=0.f, float to=1000.f, float step=1.f){
	fstream file;
	file.open(filename, fstream::out | fstream::trunc);

	for(float i=from; i<=to; i+=step){
		float t = 0;
			t = spline(i);
		file << i << "," << t << "\n";
	}
	file.close();
}

void tc(){
	HermiteCardinal<float> spline({250,350,390,30}, 0.5);

	writeSplineToFile("HermiteSpline.csv", spline, 0, 1, 0.001);

}


int main(){
	tc();

	return 0;
}
