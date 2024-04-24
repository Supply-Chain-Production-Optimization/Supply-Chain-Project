#include<bits/stdc++.h>
using namespace std;

const int N = 1e9;

// Node class representing a supplier location
class SupplyLocation
{
public:
    string name;
    float ratings; // Ratings of each place

    // Constructor to initialize the location
    SupplyLocation(const string &n, float rate)
    {
        name = n;
        ratings = rate;
    }
    SupplyLocation() {}
};

class Graph
{
public:
    vector<SupplyLocation> suppliers;    // Vector to store supplier locations
    vector<vector<pair<int,int> > > adjacency; // Adjacency list to store edges

    // Function to add a supplier to the graph
    void addSupplier(const string &name, float rate)
    {
        SupplyLocation supplier(name, rate);
        suppliers.push_back(supplier);
        // Add an empty vector for the new supplier in the adjacency list
        adjacency.emplace_back();
    }

    // Function to add an edge between two suppliers in the graph
    void addEdge(int from, int to, int cost)
    {
        adjacency[from].push_back({to,cost});
        adjacency[to].push_back({from,cost});
    }

    // Function to display all suppliers and edges in the graph
    void displayGraph()
    {
        for (int i = 0; i < suppliers.size(); ++i)
        {
            cout << "Name: " << suppliers[i].name << " | Connected Places: ";
            for (int j = 0; j < adjacency[i].size(); ++j)
            {
                int connectedIndex = adjacency[i][j].first;
                cout << suppliers[connectedIndex].name;
                if (j < adjacency[i].size() - 1)
                    cout << ", ";
            }
            cout << "|";
            cout << endl;
        }
    }

    vector<int> dijkstras(){
    vector<int> dist(40,N);
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    q.push({0,0});
    dist[0] = 0;
    while(!q.empty()){
        int d = q.top().first;
        int node = q.top().second;
        q.pop();
        for(auto it: adjacency[node]){
            if(dist[it.first]>d+it.second){      
                dist[it.first] = d + it.second;
                q.push({dist[it.first],it.first});
            }
        }
    }
    return dist;
    }

    // To find the cheapest supplier from the source location -->
    pair<SupplyLocation,int> findCheapestSupplier(){
        int minCost = N;
        int minCostIndex = -1;
        vector<int> cost = dijkstras();
        // Finding the cost from the starting supplier -->
        minCost = min(cost[18],min(cost[21],min(cost[27],min(cost[29],min(cost[35],cost[39]) ) ) ) );
        if(minCost==cost[18])    minCostIndex = 18;
        else if(minCost==cost[21])  minCostIndex = 21;
        else if(minCost==cost[27])  minCostIndex = 27;    
        else if(minCost==cost[29])  minCostIndex = 29;
        else if(minCost==cost[35])  minCostIndex = 35;
        else    minCostIndex = 39;
        if(minCostIndex!=-1)
            return {suppliers[minCostIndex],minCost};
        else{
            cout<<"No supplier found.\n";
            return {SupplyLocation("", 0.0),0};
        }
    }

    // For traversing the paths to finally reach the destination starting from source -->
    void dfs(vector<int> &path_visited, vector<int> &visited, int i, int dest, int n)
    {
        visited[i] = 1;
        path_visited[i] = 1;
        if (i != dest)
        {
            for (auto j : adjacency[i])
            {
                if (!visited[j.first])
                    dfs(path_visited, visited, j.first, dest, n);
            }
        }
        else
        {
            int cnt = 1;
            for (int j = 0; j < n; j++)
            {
                if (path_visited[j] == 1 && cnt != 1)
                {
                    cout << " -> " << suppliers[j].name;
                }
                else if (path_visited[j] == 1 && cnt == 1)
                {
                    cout << suppliers[j].name;
                }
                cnt++;
            }
        }
        path_visited[i] = 0;
    }

    // For finding the path from source location to destination -->
    void path(int src, int dest)
    {
        int n = suppliers.size();
        vector<int> visited(n, 0);
        vector<int> path_visited(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && i == src)
            {
                dfs(path_visited, visited, i, dest, n);
            }
        }
    }

    int search_in_graph(SupplyLocation nearest)
    {
        for (int i = 0; i < suppliers.size(); i++)
        {
            if (nearest.name == suppliers[i].name)
                return i;
        }
        return -1;
    }
};

int main(){
    Graph locationGraph; // Graph to store locations and edges

    // Add locations to the graph

    // Noida to Delhi Lane(Blue Line) -->
    locationGraph.addSupplier("JIIT 62", 4.1);
    locationGraph.addSupplier("Ithum", 4.3);
    locationGraph.addSupplier("3rd Wave Coffee", 4.7);
    locationGraph.addSupplier("Haldirams", 4.0);
    locationGraph.addSupplier("Fortis Hospital", 4.5);
    locationGraph.addSupplier("Mithaas", 4.6);
    locationGraph.addSupplier("Kailash Hospital", 4.0);
    locationGraph.addSupplier("Iskcon", 4.1);
    locationGraph.addSupplier("Logix", 4.7);
    locationGraph.addSupplier("Metro Multi Speciality hospital", 4.2);   
    locationGraph.addSupplier("The Great Kebab Factory", 4.2);
    locationGraph.addSupplier("Golf Course", 3.9);
    locationGraph.addSupplier("Botanical Garden", 4.1);
    locationGraph.addSupplier("Wave Mall", 4.5);
    locationGraph.addSupplier("DLF Mall", 4.9);
    locationGraph.addSupplier("Felix hospital", 3.9);
    locationGraph.addSupplier("Akshardham", 5.0);
    locationGraph.addSupplier("Pragati Maidan", 3.5);
    locationGraph.addSupplier("Cannaught Palace", 4.6);

    // 128 lane -->
    locationGraph.addSupplier("Karigari Restaurent(By : Harpal Singh)", 4.2);
    locationGraph.addSupplier("Shopprix Mall", 4.8);
    locationGraph.addSupplier("JIIT 128", 4.2);

    // Botanical Lane -->
    locationGraph.addSupplier("Thios", 4.4);
    locationGraph.addSupplier("Okhla Bird Sanctuary", 4.5);
    locationGraph.addSupplier("The Saffron Boutique", 4.4);
    locationGraph.addSupplier("Jamia Milia Islamia", 3.7);
    locationGraph.addSupplier("Kalkaji Mandir", 4.6);
    locationGraph.addSupplier("Hauz Khaas", 4.6);

    // Pragati Maidan -->
    locationGraph.addSupplier("Mandi House", 3.6);
    locationGraph.addSupplier("Khan Market", 4.9);

    // Cannaught Palace -->
    locationGraph.addSupplier("New Delhi", 4.6);
    locationGraph.addSupplier("A.I.I.M.S. hospital", 4.6);
    locationGraph.addSupplier("Chawri Bazaar", 4.2);
    locationGraph.addSupplier("Chandni Chowk", 4.0);
    locationGraph.addSupplier("Red Fort", 5.0);
    locationGraph.addSupplier("Majnu ka tila", 4.8);

    // Noida to Ghaziabad -->
    locationGraph.addSupplier("Shipra Mall", 3.8);
    locationGraph.addSupplier("Shipra Market", 4.5);
    locationGraph.addSupplier("Habitat", 4.6);
    locationGraph.addSupplier("Windsor Street", 5.0);

    // Connecting edges in the graph
    locationGraph.addEdge(0, 1, 543);   // JIIT 62 to Ithum
    locationGraph.addEdge(1, 2, 728);   // Ithum to 3rd Wave Coffee
    locationGraph.addEdge(2, 3, 225);   // 3rd Wave Coffee to Haldirams
    locationGraph.addEdge(3, 4, 642);   // Haldirams to Fortis Hospital
    locationGraph.addEdge(4, 5, 189);   // Fortis to Mithaas
    locationGraph.addEdge(5, 6, 547);   // Mithaas to Kailash
    locationGraph.addEdge(6, 7, 427);   // Kailash to Iskcon
    locationGraph.addEdge(7, 8, 301);   // Isckon to Logix
    locationGraph.addEdge(8, 9, 883);   // Logix to Metro Multi Speciallity hospital
    locationGraph.addEdge(9, 10, 946);  // Metro Multi Speciallity hospital to The Great Kebab factory
    locationGraph.addEdge(10, 11, 549); // The Great Kebab Factory to Golfcourse
    locationGraph.addEdge(11, 12, 854); // Golf Course to Botanical
    locationGraph.addEdge(12, 13, 108); // Botanical to Wave
    locationGraph.addEdge(13, 14, 388); // Wave to DLF
    locationGraph.addEdge(14, 15, 825); // DLF to Felix
    locationGraph.addEdge(15, 16, 732); // Felix to Akshardham
    locationGraph.addEdge(16, 17, 430); // Akshardham to Pragati Maidan
    locationGraph.addEdge(17, 18, 901); // Pragati to Cannaught

    locationGraph.addEdge(5, 19, 621);  // Mithaas to Karigari
    locationGraph.addEdge(19, 20, 264); // Karigari to Shopprix
    locationGraph.addEdge(20, 21, 929); // Shopprix to JIIT 128

    locationGraph.addEdge(12, 22, 438);  // Botanical to Thios
    locationGraph.addEdge(22, 23, 172);  // Thios to Okhla
    locationGraph.addEdge(23, 24, 275);  // Okhla to The Saffron Boutique
    locationGraph.addEdge(24, 25, 800);  // The Saffron Boutique to Jamia
    locationGraph.addEdge(25, 26, 629);  // Jamia to Kalkaji
    locationGraph.addEdge(26, 27, 142);  // Kalkaji to Hauz Khaas

    locationGraph.addEdge(17, 28, 463); // Pragati to Mandi House
    locationGraph.addEdge(28, 29, 540); // Mandi House to Khan Market

    locationGraph.addEdge(18, 30, 705); // Cannaught Palace to New Delhi
    locationGraph.addEdge(30, 31, 663); // New Delhi to AIIMS
    locationGraph.addEdge(31, 32, 796); // AIIMS to Chawri Bazar
    locationGraph.addEdge(32, 33, 654); // Chawri Bazar to Chandni Chowk
    locationGraph.addEdge(33, 34, 611); // Chandni Chowk to Red Fort
    locationGraph.addEdge(34, 35, 724); // Red Fort to Majnu ka tila

    locationGraph.addEdge(0, 36, 857);  // JIIT 62 to Shipra Mall
    locationGraph.addEdge(36, 37, 764); // Shipra Mall to Shipra Market
    locationGraph.addEdge(37, 38, 585); // Shipra Market to Habitat
    locationGraph.addEdge(38, 39, 981); // Habitat to Windsor Street

    // Display all locations and edges in the graph
    cout << endl
         << endl;
    cout << " *********************" << endl;
    cout << "| Available locations |" << endl;
    cout << " *********************" << endl
         << endl;

    locationGraph.displayGraph();

    char a;
    cout << endl
         << endl
         << "Do you want to visit any of the above given locations(y/n):";
    cin >> a;
    system("CLS");
    switch (a)
    {
    case 'y':
    {
        cout << endl
             << "Ahhhh shit, Here you are again!!!" << endl;

        cout << endl
             << endl
             << "Choose wisely as your \'SAFAR\' should not become a \'SUFFER\' for you" << endl;
        cout << "**********************************************************************" << endl;
        cout << "1.) SEARCH BY MINIMUM COST"<<endl;
        cout << endl
             << "2.) SEARCH BY MAXIMUM AVERAGE RATING" << endl;
        cout << endl;
        fflush(stdin);
        int b;
        cout << endl
             << endl
             << "Enter your prefered option : ";
        fflush(stdin);
        cin >> b;
        switch (b)
        {
        case 1:
        {
            // Here, place is suggested according to minimum cost -->
            SupplyLocation cheapest = locationGraph.findCheapestSupplier().first;
            
            // Event e(day, name, h, nearest.name, nearest.category);
            // addEventtofile(e);
            cout<<endl<<endl<<"Min. cost supply chain --> "<<"Name: "<<cheapest.name<<endl;
                    cout<<"**********************"<<endl<<endl;
                    cout<<"Min. cost required =  Rs. "<<locationGraph.findCheapestSupplier().second<<endl<<endl;
                    cout<<"Your supply chain looks like this :- "<<endl;   
                    int src = 0;
                    int cheapest_dest = locationGraph.search_in_graph(cheapest);
                    locationGraph.path(src,cheapest_dest);
                    cout<<endl<<endl;
                    break;
        }
        }
        break;
    }
    }   
}