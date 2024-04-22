#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Vertex{
public:
Vertex();
Vertex(int);

bool const isVisited();
void setVisited();

void setVertex(int);
int const getVertex();

void setNeighbor(vector<Vertex>& n, int index);

int const getNeighborSize();
int getAdj(int i);

private:
int vertex;  //vertex ID/ Value stored within
bool visited = false;
vector<Vertex> adj;

};

int const MAX_SIZE=6;
//_________Main Functions__________

void makeVertex(vector<Vertex>& v, int vertexID);

void edgeFromFile(ifstream& input, vector<Vertex>& v);

void printAdjacency(vector<Vertex> v);

void DfsAt(vector<Vertex>& v, int vertexID);

int main() {
  vector<Vertex> v;
  ifstream file("input.txt");
  int userIn= 0;

  for(int i = 0; i < MAX_SIZE; i++)
    {
  makeVertex(v, i);
    }
  edgeFromFile(file, v);
  printAdjacency(v);
  cout << "Enter a vertex to start at: ";
  cin>> userIn;

  cout<<"Starting DFS at vertex: "<<userIn<<endl;
  DfsAt(v, userIn);
  
}


//_________Vertex Functions__________
Vertex::Vertex(){
  vertex = 0;
}

Vertex::Vertex(int v)
{
  vertex = v;
}

bool const Vertex::isVisited()
{
  return visited;
}

void Vertex::setVisited()
{
  visited = true;
}

void Vertex::setVertex(int n)
{
 vertex = n;
}

const int Vertex::getVertex()
{
  return vertex;
}

void Vertex::setNeighbor(vector<Vertex> &v, int n)
{
  adj.push_back(v[n]);
}

int const Vertex::getNeighborSize()
{
  return adj.size();
}

int Vertex::getAdj(int i)
{
  return adj[i].getVertex();
}
//_________Main Functions__________

void makeVertex(vector<Vertex>& v, int vertexID)
{
  Vertex newVertex(vertexID);
  v.push_back(newVertex);
}

void edgeFromFile(ifstream& input, vector<Vertex>& v)
{
  cout<<"Opening file..."<<endl;
  if (!input.is_open()) {
  cout << "Failed to open the file." << endl;
  }
  else{
    string line ;
    int vertexID = 0;
    cout<<"Building adjacency for each vertex..."<<endl;
    while(!input.eof() && input.is_open())
      {
        while (getline(input, line) && vertexID < v.size()) {
            istringstream iss(line);
            int neighborID;
            while (iss >> neighborID) {
                v[vertexID].setNeighbor(v, neighborID);
            }
            vertexID++;
        }
        input.close();
      }
  }
}

void printAdjacency(vector<Vertex> v)
{
  for(int i = 0; i < v.size(); i++)
    {
    cout<<"Adjacency list of vertex "<<v[i].getVertex()<< " : ";
      for(int j = 0; j < v[i].getNeighborSize(); j++)
        {
          cout<<v[i].getAdj(j)<<" ";
          
        }
      cout<< endl;
        }
}

void DfsAt(vector<Vertex>& v, int vertexID)
{
  
  //v[vertexID].setVisited();
  for(int i = 0; i < v[vertexID].getNeighborSize(); i++)
    {
      //cout<<v[vertexID].getVertex() <<" ";
      if(!v[v[vertexID].getAdj(i)].isVisited())
      {
        cout<< v[vertexID].getAdj(i)<<" ";
        DfsAt(v, v[vertexID].getAdj(i));
      }
     // cout<< " / ";
    }
  
}