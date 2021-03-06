#include <vector>
#include <iostream>
#include <set>
#include <list>
#include <climits>
#include <stack>
#include <queue>
#include <iomanip>

using namespace std;

//Defining class of edges contains dest (end of edge) and weight of edges
class Edge
{
    public:
    int dest, weight;
    Edge(int x,int y)//edge constructor
    {
        dest=x;
        weight=y;
    }
};

int main()
{
    int num_of_v, num_of_e;
    cin >> num_of_v >> num_of_e;;
    vector<list<Edge> > adj_list(num_of_v); // using adjacency list representation (taking vector containing list of edges)
    vector<double> Betweenness_Centrality(num_of_v,0.0);//Betweenness_Centrality of each vertex initialized by '0'
    int count=0;
    //taking no_of_edges and insert into adj_list
    for (int i = 0; i < num_of_e; ++i)
    {
        int x,y,w;
        cin >> x >> y >> w;
        adj_list[x].push_back(Edge{y, w});
        adj_list[y].push_back(Edge{x, w});
    }
    //do this for all vertex
    for (int source=0; source < num_of_v;source++)
    {
    	//1. we implement dijkstra's algorithm to count path and all the predecessor of each vertex
    	vector<list<int> > parent(num_of_v);//list of parents of each node initially empty
    	vector<int> distance(num_of_v,INT_MAX);// distance will infinite initially for each node
    	vector<int> path(num_of_v,0);
    	vector<double> dependency(num_of_v,0.0);
    	set<pair<int, int> > T;
    	set<int> A;
    	stack<int> accumulation;//for back propagation we use stack
    	distance[source] = 0;
    	path[source]=1;
    	T.insert(make_pair(0,source));
    	while (!T.empty())
    	{
    		int temp = T.begin()->second;
    		A.insert(temp);
    		accumulation.push(temp);
    		T.erase(T.begin());
    		list<Edge> li=adj_list[temp];
    		for (list<Edge>::iterator i=li.begin();i!=li.end();i++)
    		{
    			if (A.count(i->dest) == 1)
    				continue;
    			int v=i->dest;
    			int weight = i->weight;
    			if (distance[v] > distance[temp]+weight)
    			{
    				if(distance[v]!=INT_MAX)
    					T.erase(T.find(make_pair(distance[v], v)));
    				distance[v] = distance[temp]+weight;
    				T.insert(make_pair(distance[v], v));
    				parent[v].push_back(temp);
    				path[v]=path[temp];
    			}
    			else if (distance[v] == distance[temp]+weight)
    			{
    				path[v]=path[v]+path[temp];
    				parent[v].push_back(temp);
    			}
    		}
    		/*for (int i=0;i<num_of_v;i++)
    		{
				if(parent[i].empty() && i!=source)
     				path[i]=0;
    		   	cout<<path[i]<<" ";
    		}*/

    	}
    	//back-propagation of dependencies
    	while ( !accumulation.empty() )
    	{
    		int acc_top=accumulation.top();
    		accumulation.pop();
    		list<int> li=parent[acc_top];
    		for (list<int> :: iterator i=li.begin(); i!=li.end(); i++ )
    		{
    			int t=*i;
    			dependency[t]=dependency[t] + ( (double)path[t]/(double)path[acc_top])*(double)(1+dependency[acc_top]) ;
    		}
    		if(acc_top!=source)
    		{
    			Betweenness_Centrality[acc_top]=Betweenness_Centrality[acc_top]+dependency[acc_top];
    		}
    	}
        if(count==0 || count==(num_of_v/2))
        {
            for(int i=0;i<num_of_v;i++)
            {
                double t=(double)Betweenness_Centrality[i]/(double)2;
                cout<<setprecision(201);
                cout<<t<<"\n";
            }
            cout<<"\n";
        }
        count++;
    }
    for(int i=0;i<num_of_v;i++)
    {
        double t=(double)Betweenness_Centrality[i]/(double)2;
        cout<<setprecision(201);
        cout<<t<<"\n";
    }
    return 0;
}

