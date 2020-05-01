#include <iostream>
#include <fstream>
using namespace std;

struct Node {
	int id;
	int g;
	int f;
	int h;
	int color;
	int parent;
};

int a[100][100];
Node p[100];
Node Open[100];
Node Close[100];

void ReadInputFile1(int * b, int & n) {
	fstream file("Input1.txt");

	if (!file.is_open()) {
		cout << "Failed to read file!" << endl;
	}
	else {
		file >> n;

		for (int i = 0; i < n; i++) {
			file >> b[i];
		}
	}
}

void ReadInputFile2(int a[100][100], int & n, int & start, int & finish) {
	fstream file("Input2.txt");

	if (!file.is_open()) {
		cout << "Failed to read file!";
	}
	else {
		file >> n >> start >> finish;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				file >> a[i][j];
		}
	}

	file.close();

}

int Count(int n, Node * Open) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (Open[i].color == 1)
			count++;
	}
	return count;
}

int Find(int n, Node * Open) {
	for (int i = 0; i < n; i++)
		if (Open[i].color == 1)
			return i;
}

int FindMin(int n, Node * Open) {
	int min1 = Find(n, Open);
	int min = Open[min1].f;
	for (int i = 0; i < n; i++) {
		if (Open[i].f < min && Open[i].color == 1) {
			min1 = i;
			min = Open[i].f;
		}
	}

	return min1;
}

void Init(int n, int * b) {
	for (int i = 0; i < n; i++) {
		p[i].id = i;
		p[i].color = 0;
		p[i].g = b[i];
		p[i].parent = 0;
		p[i].f = p[i].g;
		p[i].h = 0;
	}
}

int Findpoint(int n, Node * q, int o) {
	for (int i = 0; i < n; i++)
		if (q[i].id == o)
			return i;
}

void AStar(int a[100][100], int n, int start, int finish, int b[]) {
	int l = 0;
	Open[l] = p[start];
	Open[l].color = 1;
	Open[l].f = Open[l].h + Open[l].g;
	l++;
	int w = 0;

	while (Count(l, Open) != 0)
	{
		int k = FindMin(n, Open);
		Open[k].color = 2;
		Close[w] = Open[k];
		Close[w].color = 2;
		w++;
		p[Findpoint(n, p, Open[k].id)].color = 2;

		if (Findpoint(n, p, Open[k].id) == finish) {
			cout << "Path" << endl;
			cout << finish << "\t";

			int y = Findpoint(w, Close, finish);
			int u = Close[y].parent;

			while (u != start) {
				y = Findpoint(w, Close, u);
				u = Close[y].parent;
				cout << u << "\t";
			}

			break;
		}
		else {
			for (int i = 0; i < n; i++) {
				if (a[Findpoint(n, p, Open[k].id)][i] != 0 && p[i].color == 0)
				{
					Open[l] = p[i];
					Open[l].color = 1;
					Open[l].h = a[Findpoint(n, p, Open[k].id)][i] + Open[k].h;
					Open[l].f = Open[l].g + Open[l].h;
					Open[l].parent = Findpoint(n, p, Open[k].id);
					p[i].color = 1;
					l++;
				}

				if (a[Findpoint(n, p, Open[k].id)][i] != 0 && p[i].color == 1)
				{
					int h = Findpoint(l, Open, p[i].id);
					Node temp = p[i];

					temp.color = 1;
					temp.h = a[Findpoint(n, p, Open[k].id)][i] + Open[k].h;
					temp.parent = k;
					temp.f = temp.h + temp.g;

					if (temp.f < Open[h].f)		
						Open[h] = temp;
				}

				if (a[Findpoint(n, p, Open[k].id)][i] != 0 && p[i].color == 2)
				{
					int h = Findpoint(l, Close, p[i].id);
					Node temp = p[i];

					temp.color = 1;
					temp.h = a[Findpoint(n, p, Open[k].id)][i] + Open[k].h;
					temp.parent = k;
					temp.f = temp.h + temp.g;

					if (temp.f < Close[h].f)	
					{
						Open[l] = temp;
						Close[h].color = 1;				
						l++;
					}
				}
			}
		}
	}
}

int main() {
	int n;
	int start;
	int finish;
	int b[100];

	ReadInputFile2(a, n, start, finish);
	ReadInputFile1(b, n);

	Init(n, b);
	cout << "Beginning peak" << endl;
	cout << start << endl;
	cout << "Ending peak" << endl;
	cout << finish << endl;

	AStar(a, n, start, finish, b);
	return 0;
}