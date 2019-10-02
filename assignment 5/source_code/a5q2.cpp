#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

//Line or Edge class to create graph with constructor
class Line
{
public:
	char var1,var2;
	int weight;
	Line* xolo;

	//constructor
	Line(char v1, char v2, int weight)
	{
		this->var1 = v1;
		this->var2 = v2;
		this->weight = weight;
	}
};

//mainGraph class with all the methods
class MainGraph
{
private:
    //count vertices function
	int vertices1()
	{
		int count = 0;
		for (int i = 0; i < 26; ++i)
		{
			if (this->vertex[i] > 0)
			{
				count++;
			}
		}
		return count;
	}

	// find function
	int findit(int* parent, int value)
	{
		if (parent[value] == -1)
		{
			return value;
		}
		else
		{
			return findit(parent, parent[value]);
		}
	}

	//unionFind method checker
	void UnionFind(int* parent, int val1, int val2)
	{
		int set1 = findit(parent, val1);
		int set2 = findit(parent, val2);
		if (set1 != set2)
		{
			parent[set1] = set2;
		}
	}

public:
	int vertices, lines;
	Line* head;
	int vertex[26];

	//constructor
	MainGraph()
	{
		this->vertices = 0;
		this->lines = 0;
		head = new Line(0, 0, 0);
		head->xolo = nullptr;
		for (int i = 0; i < 26; ++i)
		{
			vertex[i] = 0;
		}
	}

	Line* addLine(char v1, char v2, int weight)
	{
		Line* edge = new Line(v1, v2, weight);

		Line* it = head->xolo;
		Line* prev = head;
		while(it != nullptr && it->weight <= weight)
		{
			prev = it;
			it = it->xolo;
		}
		edge->xolo = it;
		prev->xolo = edge;

		vertex[v1 % 65]++;
		vertex[v2 % 65]++;
		this->vertices = vertices1();
		this->lines++;
		return prev;
	}

	//get line function
	Line* popLine()
	{
		Line* edge = head->xolo;
		if (edge != nullptr)
		{
			head->xolo = edge->xolo;
			edge->xolo = nullptr;
			vertex[edge->var1 % 65]--;
			vertex[edge->var2 % 65]--;
			this->lines--;
			this->vertices = vertices1();
			return edge;
		}
		else
		{
			return nullptr;
		}
	}

	//remove line function
	void remove(Line* prev)
	{
		Line* temp = prev->xolo;
		prev->xolo = temp->xolo;
		lines--;
		vertex[temp->var1 % 65]--;
		vertex[temp->var2 % 65]--;
		vertices = vertices1();
		delete temp;
	}

	//function to print graph
	void printGraph()
	{
		Line* it = head->xolo;
		while(it != nullptr)
		{
			cout << it->var1 << "," << it->var2 << "," << it->weight << endl;
			it = it->xolo;
		}
	}

//to check if graph is a closed loop
	bool ifClosed()
	{
		int* parent = new int[26];
		for (int i = 0; i < 26; ++i)
		{
			parent[i] = -1;
		}
		Line* it = head->xolo;
		for (int i = 0; i < lines; ++i)
		{
			int set1 = findit(parent, it->var1 % 65);
			int set2 = findit(parent, it->var2 % 65);
			if (set1 == set2)
			{
				return true;
			}
			else
			{
                UnionFind(parent, set1, set2);
			}
			it = it->xolo;
		}
		return false;
	}

	// to get weight of each line
	int getWeight()
	{
		int wt = 0;
		for (Line* it = head->xolo; it != nullptr; it = it->xolo)
		{
			wt += it->weight;
		}
		return wt;
	}

	//for the pictorial representation using DOT
	void dot(string fileName)
	{
		ofstream file;
		file.open(fileName);

		if (file.is_open())
		{
			file << "graph MST {" << endl;
			file << "\tgraph [ dpi = 1200 ];" << endl;

			for (Line* it = head->xolo; it != nullptr; it = it->xolo)
			{
				file << "\t" << it->var1 << " -- " << it->var2 << " [label=" << it->weight << "];" << endl;
			}

			file << "}" << endl;

			file.close();
		}
	}

};

//main method
int main(void)
{
	ifstream inputFile;
	inputFile.open("2019_CSN_261_L5_P2.csv");

	MainGraph graphMST;

	if (inputFile.is_open())
	{
		string temp;
		while(getline(inputFile, temp))
		{
			char v1,v2,comma;
			int weight;
			stringstream s(temp);
			s >> v1;
			s >> comma;
			s >> v2;
			s >> comma;
			s >> weight;
            graphMST.addLine(v1, v2, weight);
		}
		inputFile.close();
	}

	MainGraph mst;
	int V = graphMST.vertices;

	while(mst.lines < V - 1)
	{
		Line* edge = graphMST.popLine();
		Line* temp = mst.addLine(edge->var1, edge->var2, edge->weight);
		if (mst.ifClosed())
		{
			mst.remove(temp);
		}
		delete edge;
	}

	cout << endl;
    mst.printGraph();
	cout << endl;
	cout << "The total edge weight of the MST is : " << mst.getWeight() << endl;

    mst.dot("Krushkal.dot");

	return 0;
}