#include <iostream> 
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <ctime>


using namespace std;

int finalA, finalB;
double minDist;



struct point {
	int x, y, id;
};



int vvod(ifstream& file, point* a) {
	int i = 0;
	while (!file.eof()) {

		file >> a[i].x;
		file >> a[i].y;
		a[i].id = i + 1;
		i++;
	}
	return i;
}

bool sortX(const point& a, const point& b) { //операторы для сортировки
	return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool SortY(const point& a, const point& b) {
	return a.y < b.y;
}




void pointDist(const point& a, const point& b) { //сравнение точек
	double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + .0);
	if (dist < minDist)
		minDist = dist; finalA = a.id; finalB=b.id;
}


void Dist(const point& a, const point& b) { //сравнение точек
	double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + .0);
	cout<<"minimal distance between of two point: "<< dist<<endl;
}

void func(int first, int last, point* a) {

	if (last - first <= 3) {
		for (int i = first; i <= last; ++i)
			for (int j = i + 1; j <= last; ++j)
				pointDist(a[i], a[j]);
		sort(a + first, a + last + 1, &SortY);
		return;
	}

	int mid = (first + last) >> 1;
	int midx = a[mid].x;
	func(first, mid, a), func(mid + 1, last, a);
	static point b[20000];
	merge(a + first, a + mid + 1, a + mid + 1, a + last + 1, b, &SortY);
	copy(b, b + last - first + 1, a + first);

	int tsz = 0;
	for (int i = first; i <= last; ++i)
		if (abs(a[i].x - midx) < minDist) {
			for (int j = tsz - 1; j >= 0 && a[i].y - b[j].y < minDist; --j)
				pointDist(a[i], b[j]);
			b[tsz++] = a[i];
		}

}





int main() {

	int startTime = clock();
	point a[20000];
	point cop[20000];
	int n;
	int mem;

	ifstream file ("text.txt");

	n=vvod(file, a);
	memcpy(cop, a,sizeof(a));

	

	sort(a, a + n, &sortX);
	minDist = 1E20;
	func(0, n - 1,a);

	cout << finalA << " " << finalB << endl;

	Dist(cop[finalA-1], cop[finalB-1]);
	int endTime = clock();

	cout << "work time: " << endTime - startTime << endl;

	return 0;
}