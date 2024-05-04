
#include<iomanip>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include<stdlib.h>
#include <bits/stdc++.h>
using namespace std;

const int N = 1e9;
void gotoXY(int X, int Y)
{
    COORD coordinates;
    coordinates.X = X;
    coordinates.Y = Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void border(int xLenS = 2, int yLenS = 2,int xLenE = 76, int yLenE = 22 )
{   char c1=201;
    char c2=200;
    char c3= 205;
    char c4= 187;
    char c5= 188;
	system("cls");
	gotoXY(xLenS,yLenS);
	cout<<c1;

	gotoXY(xLenS,yLenE);
	cout<<c2;

    for(int i=xLenS+1;i<=xLenE-1;i++) //Top and Bottom Border line
    {
        gotoXY(i,yLenS);
        cout<<c3;
		//puts(style);
        gotoXY(i,yLenE);
        //puts(style);
        cout<<c3;

    }
    gotoXY(xLenE,yLenS);cout<<c4;
    gotoXY(xLenE,yLenE);cout<<c5;
    for(int i=yLenS+1;i<=yLenE-1;i++)         //Left and Right Border Line
    {
        gotoXY(xLenS, i);
        cout<<c4;
		//puts(style);
        gotoXY(xLenE, i);
        cout<<c5;
		//puts(style);
    }
    cout<<endl;
}
void loginFrame(int xLenS = 18, int yLenS = 8, int xLenE = 70, int yLenE = 25)
{
    border(xLenS,yLenS,xLenE,yLenE);
}
void intro()
{
	gotoXY(22,4);
	cout<<("WELCOME TO INVENTORY MANAGEMENT AND SUPPLY CHAIN OPTIMISATION");
	gotoXY(24,6);
	cout<<"BUILT BY:";
	gotoXY(24,8);
	cout<<"SAUMYA SHARMA\t9922103195";
	gotoXY(24,10);
	cout<<"AMAN TYAGI\t 9922103176";
	gotoXY(24,12);
	gotoXY(24,14);
    gotoXY(24,16);
    cout<<("Press Any key to continue...");
    getch();
}


    bool userExists(const string& username, const string& password) {
    ifstream file("Profile.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            string storedUsername = line.substr(0, pos);
            string storedPassword = line.substr(pos + 1);
            if (storedUsername == username && storedPassword == password) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}
class customer  // customer class
{
	public:
	    int id;
	    int age;
	    int contact;
    string gen;
    string pas;
    string uppas;
	string customername=" ";
  //  char data;
    int login();
    // variables defined in this class in public mode.
};
class profile: public customer{
public:
  //  int op;
   // void write_user();
   // void update_user();
   // void displayprof();
    //void showdata();
    void registerr(){

    cout<<endl;
    gotoXY(0,3);
    cout<<"____________________________________________________________________________"<<endl;
    gotoXY(29,5);
    cout<<"REGISTRATION PAGE"<<endl;
    gotoXY(0,7);
    cout<<"____________________________________________________________________________"<<endl;
    gotoXY(20,10);
    ofstream file1("Profile.txt", ios::app);
    cout << "Please Enter your ID: ";
    cin>>id;
    // file1<<id<<" ";
    fflush(stdin);
    gotoXY(20,12);
    cout << "Please Enter your Name: "; //taking data from the user
    cin >> customername;
    cout<<endl;
    gotoXY(20,13);
    fflush(stdin);
    cout<<"Please enter your age: ";
    cin>>age;
    // file1<<age<<" ";
    gotoXY(20,14);
    cout << "Please Enter your gender (M/F/O): "; //taking data from the user
    cin >> gen;
    // file1<<gen<<" ";
    gotoXY(20,15);
    cout << "Please enter your password: ";
    cin >> contact;
    //file1<<contact<<" ";
    file1<<customername<<","<<contact<<endl;
    file1.close();
    gotoXY(20,22);
    cout<<"\t\t REGISTERED SUCCESSFULLY!"<<endl;
    gotoXY(20,23);
    cout<<"\t\t  LOGIN TO YOUR ACCOUNT"<<endl;
    system("PAUSE");
    system("CLS");
    }
    void login(){
   char ch;
   gotoXY(20,10);
   cout<<"INVENTORY MANAGEMENT AND SUPPLY CHAIN OPTIMISATION \n\n";
   gotoXY(20,12);
   cout<<"------------------------------";
   gotoXY(20,14);
   cout<<"LOGIN \n";
   gotoXY(20,15);
   cout<<"-----------------------------\n\n";
   gotoXY(20,17);
   string username="";
   string pass="";
   cout << "Enter Username: ";
   gotoXY(20,19);
   cin>>username;
   fflush(stdin);
   gotoXY(20,21);
   cout<<"Enter password";
   
   cin>>pass;
   fflush(stdin);
   if(userExists(username,pass)){
    gotoXY(20,23);
      cout << "Access Granted! \n";
      system("PAUSE");
      system ("CLS");
   }
   else{
    cout << "\n\n\t\t\t\t\t\t\tAccess Aborted...\n\t\t\t\t\t\t\tPlease Try Again\n\n";
      system("PAUSE");
      system("CLS");
     login();
   }
   
   }
 
};

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
            cout << "Name: " << suppliers[i].name << " | Direct Connection List: ";
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

    vector<int> dijkstras(int src){
    vector<int> dist(40,N);
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    q.push({0,src});
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
        vector<int> cost = dijkstras(0);
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

    void dfs_rate(vector<int> &path_visited, vector<int> &visited, int i, int dest, int n, float &rating, int &length)
    {
        visited[i] = 1;
        path_visited[i] = 1;
        if (i != dest)
        {
            for (auto j : adjacency[i])
            {
                if (!visited[j.first])
                    dfs_rate(path_visited, visited, j.first, dest, n, rating, length);
            }
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                if (path_visited[j] == 1)
                {
                    rating += suppliers[j].ratings;
                    length++;
                }
            }
        }
        path_visited[i] = 0;
    }

    // For finding the path from source location to destination -->
    void path_rate(int src, int dest, float &rating, int &length)
    {
        int n = suppliers.size();
        vector<int> visited(n, 0);
        vector<int> path_visited(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && i == src)
            {
                dfs_rate(path_visited, visited, i, dest, n, rating, length);
            }
        }
    }

    // To find the highest rated location of a given category from the source location -->
    pair<SupplyLocation,pair<int,float> > findBestSupplier(){
        int max_rating = 0;
        int dist;
        float rate;
        SupplyLocation ans;
        vector<int> cost = dijkstras(0);
        float rate1 = 0; int length1 = 0;
        float rate2 = 0; int length2 = 0;
        float rate3 = 0; int length3 = 0;
        float rate4 = 0; int length4 = 0;
        float rate5 = 0; int length5 = 0;
        float rate6 = 0; int length6 = 0;
        path_rate(0,18,rate1,length1);
        path_rate(0,21,rate2,length2);
        path_rate(0,27,rate3,length3);
        path_rate(0,29,rate4,length4);
        path_rate(0,35,rate5,length5);
        path_rate(0,39,rate6,length6);

        float path1 = rate1/length1;
        float path2 = rate2/length2;
        float path3 = rate3/length3;
        float path4 = rate4/length4;
        float path5 = rate5/length5;
        float path6 = rate6/length6;
        
        if(path1>=path2 && path1>=path3 && path1>=path4 && path1>=path5 && path1>=path6){
            ans = suppliers[18];
            dist = cost[18];
            rate = path1;
        }
        
        if(path2>=path1 && path2>=path3 && path2>=path4 && path2>=path5 && path2>=path6){
            ans = suppliers[21];
            dist = cost[21];
            rate = path2;
        }
       
        if(path3>=path1 && path3>=path2 && path3>=path4 && path3>=path5 && path3>=path6){
            ans = suppliers[27];
            dist = cost[27];
            rate = path3;
        }

        if(path4>=path1 && path4>=path2 && path4>=path3 && path4>=path5 && path4>=path6){
            ans = suppliers[29];
            dist = cost[29];
            rate = path4;
        }

        if(path5>=path1 && path5>=path2 && path5>=path3 && path5>=path4 && path5>=path6){
            ans = suppliers[35];
            dist = cost[35];
            rate = path5;
        }

        if(path6>=path1 && path6>=path2 && path6>=path3 && path6>=path4 && path6>=path5){
            ans = suppliers[39];
            dist = cost[39];
            rate = path6;
        }
        
        return {ans,{dist,rate}};
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
            for (int j = n-1; j >= 0; j--)
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

    // The results are being loaded based on the keyword you typed -->
 
    void KMPSearch(string pat, string txt, bool &flag){
        int m = pat.length();
        int n = txt.length();
        int lps[m];
        computeLPSArray(pat, m, lps);
        
        int i = 0; // index for the string
        int j = 0; // index for the pattern
        while ((n - i) >= (m - j)) {
            if(pat[j]==txt[i] || pat[j]==txt[i]-32 || pat[j]==txt[i]+32) {
                j++;
                i++;
            }
            if(j==m){
                flag = 1;
                return ;
            }
            else if(i<n && pat[j]!=txt[i]) {
                if(j!=0)
                    j = lps[j-1];
                else
                    i = i + 1;
            }
        }
    }

    void computeLPSArray(string pat, int m, int* lps)
    {
        int len = 0;
        lps[0] = 0;

        int i = 1;
        while (i < m) {
            if (pat[i]==pat[len] || pat[i]==pat[len]-32 || pat[i]==pat[len]+32) {
                len++;
                lps[i] = len;
                i++;
            }
            else{
                if (len!=0){
                    len = lps[len - 1];
                }
                else{
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    vector<SupplyLocation> search_supplier(string search){
        int cnt = 1;
        vector<SupplyLocation> results;
        for(int i=0;i<40;i++){
            bool flag = 0;
            KMPSearch(search,suppliers[i].name,flag);
            if(flag){  
                cout << cnt << ".) Name: " << suppliers[i].name<<endl;
                results.push_back(suppliers[i]);
                cnt++;
            }
        }
        return results;
    }
};

class item
{
public:
    int id;
    string name;
    int deadline;
    int profit;
    int weight;

    item(int i, string n, int d, int p, int w)
    {
        id = i;
        name = n;
        deadline = d;
        profit = p;
        weight = w;
    }
    void calculateProductionInventoryDeadline(const vector<item> &items, ofstream &outputFile);
    void calculateProductionInventoryCapacity(const vector<item> &items, int capacity, ofstream &outputFile);
    void calculateProductionInventoryDeadlineandCapacity(vector<item> &items, ofstream &outputFile);
    
    
};

struct MinHeapNode
{
    char data;
    int freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparator function for the priority queue
struct compare
{
    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return (l->freq > r->freq);
    }
};
void encode(MinHeapNode *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
    {
        huffmanCode[root->data] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void buildHuffmanTree(const string &text, ofstream &outputFile)
{
    unordered_map<char, unsigned> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }
    int flag=0;
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;
    for (auto &pair : freq)
    {

        //outputFile << "Huffman Codes:\n";
        //cout<<pair.first<<" "<<pair.second<<endl;
        minHeap.push(new MinHeapNode(pair.first, pair.second));
    }
    unordered_map<char, string> huffmanCode;
    if(minHeap.size()==1){
        huffmanCode[text[0]]="0"; 
        flag=1;              
    }
    while (minHeap.size() != 1)
    {
        MinHeapNode *left = minHeap.top();
        minHeap.pop();
        MinHeapNode *right = minHeap.top();
        minHeap.pop();
        //unsigned to make sure freq is positive
        unsigned sumFreq = left->freq + right->freq;
        MinHeapNode *newNode = new MinHeapNode('\0', sumFreq);
        newNode->left = left;
        newNode->right = right;
        //pushing sumfreq as new node
        minHeap.push(newNode);
    }

    MinHeapNode *root = minHeap.top();
    // cout<<*(minHeap.top());
    if(!flag)

    //encode with huffman logic: left=0 right=1
    encode(root, "", huffmanCode);
    // if(!flag){
    
    outputFile << "Huffman Codes:\n";
    for (auto &pair : huffmanCode)
    {
        if (pair.first == ' ')
        {
            outputFile << "S"
                       << " : " << pair.second << '\n';
        }
        else if (pair.first == '\n')
        {
            outputFile << "N"
                       << " : " << pair.second << '\n';
        }
        else
        {
            outputFile << pair.first << " : " << pair.second << '\n';
            //cout << pair.first << " : " << pair.second << '\n';
        }
    }
    
    outputFile << '\n';
    string encodedText;
    for (char ch : text)
    {
        if (ch == ' ')
        {
            encodedText += huffmanCode['S'];
        }
        else if (ch == '\n')
        {
            encodedText += huffmanCode['N'];
        }
        else
        {
            encodedText += huffmanCode[ch];
        }
    }

    outputFile << "Encoded Text:\n"
               << encodedText << '\n';
    cout<< "Encoded Text:\n"
               << encodedText << '\n';
    // }
}
void compressTextFile(const vector<item> &inputVector, ofstream &outputFile, string FileName)
{
    string inputText;
    for (auto num : inputVector)
    {
        inputText += to_string(num.id);
    }
    buildHuffmanTree(inputText, outputFile);
    cout << "Text has been compressed and saved to " << FileName << ".txt" << endl;
    outputFile.close();
}
void item:: calculateProductionInventoryCapacity(const vector<item> &items, int capacity, ofstream &outputFile)
    {
        int n = items.size();
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

        for (int i = 1; i <= n; ++i)
        {
            for (int w = 1; w <= capacity; ++w)
            {
                if (items[i - 1].weight > w)
                {
                    dp[i][w] = dp[i - 1][w];
                }
                else
                {
                    dp[i][w] = max(dp[i - 1][w], items[i - 1].profit + dp[i - 1][w - items[i - 1].weight]);
                }
            }
        }

        vector<item> selectedItems;
        int remainingCapacity = capacity;

        for (int i = n; i > 0 && remainingCapacity > 0; --i)
        {
            if (dp[i][remainingCapacity] != dp[i - 1][remainingCapacity])
            {
                selectedItems.push_back(items[i - 1]);
                remainingCapacity -= items[i - 1].weight;
            }
        }

        cout << "\nItems selected for production scheduling based on capacity:\n";
        for (const auto &idx : selectedItems)
        {
            cout << "Item " << idx.id << " (Weight: " << idx.weight << ", Profit: " << idx.profit << ", Deadline: " << idx.deadline << ")\n";
        }
        cout << "Save data to log?(y/n)" << endl;
        char x;
        cin >> x;
        if (x == 'y')
        {
            vector<int> data;
            for (const auto &idx : selectedItems)
            {
                data.push_back(idx.id);
            }
            compressTextFile(selectedItems, outputFile, "output");
        }
        else
        {
            cout << "Data not saved!" << endl;
        }
    }
    
void item:: calculateProductionInventoryDeadlineandCapacity(vector<item> &items, ofstream &outputFile)
    {
        int n = items.size();
        vector<pair<int, pair<int, int>>> sortedItems;

        for (int i = 0; i < n; ++i)
        {
            sortedItems.push_back({items[i].deadline, {items[i].weight, items[i].profit}});
        }

        sort(sortedItems.begin(), sortedItems.end());

        vector<bool> filled(n, false);
        vector<item> filledItems;
        int totalProfit = 0;

        cout << "\nItems selected for production scheduling based on deadlines:\n";
        for (int i = 0; i < n; ++i)
        {
            int deadline = sortedItems[i].first;
            int weight = sortedItems[i].second.first;
            int profit = sortedItems[i].second.second;

            for (int j = min(n, deadline) - 1; j >= 0; --j)
            {
                if (!filled[j])
                {
                    filled[j] = true;
                    totalProfit += profit;
                    filledItems.push_back(items[i]);
                    cout << "Item " << items[i].id << " (Weight: " << weight << ", Profit: " << profit << ", Deadline: " << deadline << ")\n";
                    break;
                }
            }
        }
        cout << "Now calculating the items that can be transported today based on capacity" << endl;
        int capacity;
        cout << "Enter capacity: ";
        cin >> capacity;

        calculateProductionInventoryCapacity(filledItems, capacity, outputFile);
    }
void item:: calculateProductionInventoryDeadline(const vector<item> &items, ofstream &outputFile)
    {
        int n = items.size();
        vector<pair<int, pair<int, int>>> sortedItems;

        for (int i = 0; i < n; ++i)
        {
            sortedItems.push_back({items[i].deadline, {items[i].weight, items[i].profit}});
        }

        sort(sortedItems.begin(), sortedItems.end());

        vector<bool> filled(n, false);
        vector<item> filledItems;
        int totalProfit = 0;

        cout << "\nItems selected for production scheduling based on deadlines:\n";
        for (int i = 0; i < n; ++i)
        {
            int deadline = sortedItems[i].first;
            int weight = sortedItems[i].second.first;
            int profit = sortedItems[i].second.second;

            for (int j = min(n, deadline) - 1; j >= 0; --j)
            {
                if (!filled[j])
                {
                    filled[j] = true;
                    totalProfit += profit;
                    filledItems.push_back(items[i]);
                    cout << "Item " << items[i].id << " (Weight: " << weight << ", Profit: " << profit << ", Deadline: " << deadline << ")\n";
                    break;
                }
            }
        }
        cout << "Total Profit: " << totalProfit << "\n\n";
        cout << "Save data to log?(y/n)" << endl;
        char x;
        cin >> x;
        if (x == 'y')
        {
            vector<int> data;
            for (auto i : filledItems)
            {
                int id = i.id;
                data.push_back(id);
            }
            compressTextFile(filledItems, outputFile, "output");
        }
        else
        {
            cout << "Data not saved!" << endl;
        }
    }
string readEncodedTextFromFile(const string &fileName)
{
    ifstream inputFile(fileName);
    string line;
    bool foundEncodedText = false;
    string encodedText;

    if (!inputFile)
    {
        cerr << "Error: Could not open the input file.\n";
        return encodedText;
    }
    while (getline(inputFile, line))
    {
        if (line.find("Encoded Text:") != string::npos)
        {
            foundEncodedText = true;
            break;
        }
    }

    if (foundEncodedText)
    {
        getline(inputFile, encodedText);
    }
    else
    {
        cerr << "Error: Encoded text not found in the input file.\n";
    }

    inputFile.close();
    return encodedText;
}
string decodeHuffmanText(const string &encodedText, const unordered_map<string, char> &huffmanMap)
{
    string decodedText;
    string currentCode;
    for (char bit : encodedText)
    {
        currentCode += bit;
        if (huffmanMap.find(currentCode) != huffmanMap.end())
        {
            decodedText += huffmanMap.at(currentCode);
            currentCode = "";
        }
    }
    return decodedText;
}
unordered_map<string, char> readHuffmanCodesFromFile(const string &fileName)
{
    ifstream huffmanFile(fileName);
    unordered_map<string, char> huffmanCodeMap;

    if (!huffmanFile)
    {
        cerr << "Error: Could not open the Huffman code file.\n";
        return huffmanCodeMap;
    }

    string line;
    bool readCodes = false;
    while (getline(huffmanFile, line))
    {
        if (line.empty())
            break;
        if (line == "Huffman Codes:")
        {
            readCodes = true;
            continue;
        }
        if (readCodes)
        {
            string character, code;
            size_t pos = line.find(":");
            if (pos != string::npos)
            {
                character = line.substr(0, pos - 1);
                code = line.substr(pos + 2);
                huffmanCodeMap[code] = character[0];
                cout << character << " " << code << endl;
            }
        }
    }

    huffmanFile.close();
    return huffmanCodeMap;
}

int main()
{
    border();
    intro();
    profile p;
    loginFrame();
    p.registerr();
    loginFrame();
    p.login();
    system("CLS");
    Graph locationGraph; // Graph to store locations and edges

    // Add locations to the graph

    // First Supplier Chain -->
    locationGraph.addSupplier("The Underdogs", 4.1); // --> This is our manufacturer and all the rest are acting as suppliers for him/her.
    locationGraph.addSupplier("Star Enterprises", 4.3);
    locationGraph.addSupplier("Royal Imports", 4.7);
    locationGraph.addSupplier("Bright Future Industries", 4.0);
    locationGraph.addSupplier("Evergreen Suppliers", 4.5);
    locationGraph.addSupplier("Radiant Exports", 4.6);
    locationGraph.addSupplier("Unity Merchants", 4.0);
    locationGraph.addSupplier("Crystal Clear Trading", 4.1);
    locationGraph.addSupplier("Victory Ventures", 4.7);
    locationGraph.addSupplier("Sapphire Enterprises", 4.2);   
    locationGraph.addSupplier("Oceanic Imports", 4.2);
    locationGraph.addSupplier("Elite Suppliers Pvt. Ltd.", 3.9);
    locationGraph.addSupplier("Sunrise Trading Co.", 4.1);
    locationGraph.addSupplier("Silverline Merchants", 4.5);
    locationGraph.addSupplier("Perfect Partnerships", 4.9);
    locationGraph.addSupplier("Divine Exports", 3.9);
    locationGraph.addSupplier("Zenith Enterprises", 5.0);
    locationGraph.addSupplier("Global Traders Co.", 3.5);
    locationGraph.addSupplier("Sunshine Suppliers", 4.6);

    // Second Supplier Chain -->
    locationGraph.addSupplier("Harmony Distributors", 4.2);
    locationGraph.addSupplier("Aneja and Sons", 4.8);
    locationGraph.addSupplier("SilverPeak Suppliers", 2.3);

    // Third Supplier Chain -->
    locationGraph.addSupplier("BrightStar Suppliers", 4.4);
    locationGraph.addSupplier("NexusSupply Co.", 4.5);
    locationGraph.addSupplier("InfiniteGoods", 4.4);
    locationGraph.addSupplier("SwiftSource Suppliers", 3.7);
    locationGraph.addSupplier("Stellar Supply Solutions", 4.6);
    locationGraph.addSupplier("Horizon Traders", 4.6);

    // Fourth Supplier Chain -->
    locationGraph.addSupplier("Nova Merchandise", 3.6);
    locationGraph.addSupplier("Prime Partners Supply", 4.9);

    // Fifth Supplier Chain -->
    locationGraph.addSupplier("Zenith Suppliers", 4.6);
    locationGraph.addSupplier("Aurora Importers", 4.6);
    locationGraph.addSupplier("Crestline Distributors", 4.2);
    locationGraph.addSupplier("Fusion Trade Co.", 4.0);
    locationGraph.addSupplier("Summit Suppliers", 5.0);
    locationGraph.addSupplier("Harmony Goods Inc.", 4.8);

    // Sixth Supplier Chain -->
    locationGraph.addSupplier("Oasis Imports", 3.8);
    locationGraph.addSupplier("ZenTrade Suppliers", 4.1);
    locationGraph.addSupplier("Apex Merchants", 3.5);
    locationGraph.addSupplier("Phoenix Procurement Group", 3.4);

    // Connecting edges in the graph
    locationGraph.addEdge(0, 1, 543);   // The Underdogs to Star Enterprises
    locationGraph.addEdge(1, 2, 728);   // Star Enterprises to Royal Imports
    locationGraph.addEdge(2, 3, 225);   // Royal Imports to Bright Future Industries
    locationGraph.addEdge(3, 4, 642);   // Bright Future Industries to Evergreen Suppliers
    locationGraph.addEdge(4, 5, 189);   // Evergreen Suppliers to Radiant Exports
    locationGraph.addEdge(5, 6, 547);   // Radiant Exports to Unity Merchants
    locationGraph.addEdge(6, 7, 427);   // Unity Merchants to Crystal Clear Trading
    locationGraph.addEdge(7, 8, 301);   // Crystal Clear Trading to Victory Ventures
    locationGraph.addEdge(8, 9, 883);   // Victory Ventures to Sapphire Enterprises
    locationGraph.addEdge(9, 10, 946);  // Sapphire Enterprises to Oceanic Imports
    locationGraph.addEdge(10, 11, 549); // Oceanic Imports to Elite Suppliers Pvt. Ltd.
    locationGraph.addEdge(11, 12, 854); // Elite Suppliers Pvt. Ltd. to Sunrise Trading Co.
    locationGraph.addEdge(12, 13, 108); // Sunrise Trading Co. to Silverline Merchants
    locationGraph.addEdge(13, 14, 388); // Silverline Merchants to Perfect Partnerships
    locationGraph.addEdge(14, 15, 825); // Perfect Partnerships to Divine Exports
    locationGraph.addEdge(15, 16, 732); // Divine Exports to Zenith Enterprises
    locationGraph.addEdge(16, 17, 430); // Zenith Enterprises to Global Traders Co.
    locationGraph.addEdge(17, 18, 901); // Global Traders Co. to Sunshine Suppliers

    locationGraph.addEdge(5, 19, 621);  // Radiant Exports to Harmony Distributors
    locationGraph.addEdge(19, 20, 264); // Harmony Distributors to Aneja and Sons
    locationGraph.addEdge(20, 21, 929); // Aneja and Sons to SilverPeak Suppliers

    locationGraph.addEdge(12, 22, 438);  // Sunrise Trading Co. to BrightStar Suppliers
    locationGraph.addEdge(22, 23, 172);  // BrightStar Suppliers to NexusSupply Co.
    locationGraph.addEdge(23, 24, 275);  // NexusSupply Co. to The InfiniteGoods
    locationGraph.addEdge(24, 25, 800);  // The InfiniteGoods to SwiftSource Suppliers
    locationGraph.addEdge(25, 26, 629);  // SwiftSource Suppliers to Stellar Supply Solutions
    locationGraph.addEdge(26, 27, 142);  // Stellar Supply Solutions to Horizon Traders

    locationGraph.addEdge(17, 28, 463); // Global Traders Co. to Nova Merchandise
    locationGraph.addEdge(28, 29, 540); // Nova Merchandise to Prime Partners Supply

    locationGraph.addEdge(18, 30, 705); // Cannaught Palace to Zenith Suppliers
    locationGraph.addEdge(30, 31, 663); // Zenith Suppliers to Aurora Importers
    locationGraph.addEdge(31, 32, 796); // Aurora Importers to Crestline Distributors
    locationGraph.addEdge(32, 33, 654); // Crestline Distributors to Fusion Trade Co.
    locationGraph.addEdge(33, 34, 611); // Fusion Trade Co. to Summit Suppliers
    locationGraph.addEdge(34, 35, 724); // Summit Suppliers to Harmony Goods Inc.

    locationGraph.addEdge(0, 36, 1000);  // Sunshine Suppliers to Oasis Imports
    locationGraph.addEdge(36, 37, 2345); // Oasis Imports to ZenTrade Suppliers
    locationGraph.addEdge(37, 38, 3456); // ZenTrade Suppliers to Apex Merchants
    locationGraph.addEdge(38, 39, 100); // Apex Merchants to Phoenix Procurement Group

    int option;
    cout << "Choose an option:" << endl;
    cout << "1. Supply chain operations" << endl;
    cout << "2. Calculate Production Inventory" << endl;
    cout << "3. Display previous logs (using Huffman Decoding)" << endl;
    cout << "4. Exit" << endl;
    cin >> option;
    while (option != 4)
    {
        switch (option)
        {
        case 1:
        {
            // Display all locations and edges in the graph
    cout << endl
         << endl;
    cout << " *********************" << endl;
    cout << "| Available Suppliers |" << endl;
    cout << " *********************" << endl
         << endl;

    locationGraph.displayGraph();

    char a;
    cout << endl
         << endl
         << "Do you want to search your supplier or want to get our assistance on cracking your supplier chain(s/a):";
    cin >> a;
    system("CLS");
    switch (a)
    {
    case 'a':
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
        case 2:{
            // Here, place is suggested according to rating -->
            pair<SupplyLocation,pair<int,float> > Best = locationGraph.findBestSupplier();
            SupplyLocation best = Best.first;

            // Event e(day, name, h, best.name, best.category);
            // addEventtofile(e);
            cout<<endl<<endl<<"Best supplier chain --> "<<"Name: "<<best.name<<endl;
                    cout<<"*******************"<<endl<<endl;
                    cout<<"Cost = Rs. "<<Best.second.first<<endl<<endl;
                    cout<<"Average Rating = "<<Best.second.second<<endl<<endl;
                    cout<<"Your supplier chain :- "<<endl;  
                    int src = 0; 
                    int best_dest = locationGraph.search_in_graph(best);
                    locationGraph.path(src,best_dest);
                    cout<<endl<<endl;
                    break;
                }
        }
        break;
    }
    case 's':
    {
        cout << endl
             << "Search your trusted supplier and get to know everything about him!!!" << endl;

        cout << endl
             << endl
             << "DO YOU HAVE ALL THE RAW MATERIALS REQUIRED BY YOUR SUPPLIER" << endl;
        cout << "***********************************************************" << endl;
        cout << "1.) OF COURSE, I DO HAVE ALL OF THEM"<<endl;
        cout << endl
             << "2.) I'M AFRAID BUT I DON'T HAVE ANYTHING IN PRIOR"<< endl;
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
            int choose;
            string search;
            cout<<"Enter the search string:";
            cin>>search;
            vector<SupplyLocation> results = locationGraph.search_supplier(search);
            cout<<"Choose One --> ";
            cin>>choose;
            system("CLS");
            vector<int> ans = locationGraph.dijkstras(0);
            int search_result = locationGraph.search_in_graph(results[choose-1]);
            cout<<"For the given Supplier -->"<<endl;
            cout<<"**************************"<<endl<<endl; 
            cout<<"Name = "<<results[choose-1].name<<endl;
            cout<<"Rating = "<<results[choose-1].ratings<<endl;
            cout<<"Cost = "<<ans[search_result]<<endl;
            cout<<"Your supplier chain :- "<<endl;  
                    int src = 0; 
                    locationGraph.path(src,search_result);
                    cout<<endl<<endl;
                    break;
        }
        case 2:{
            int choose;
            string search;
            cout<<"Enter the search string:";
            cin>>search;
            vector<SupplyLocation> results = locationGraph.search_supplier(search);
            cout<<"Choose One --> ";
            cin>>choose;
            system("CLS");
            vector<int> ans = locationGraph.dijkstras(0);
            int search_result = locationGraph.search_in_graph(results[choose-1]);
            cout<<"For the given Supplier -->"<<endl;
            cout<<"**************************"<<endl<<endl; 
            cout<<"Name = "<<results[choose-1].name<<endl;
            cout<<"Rating = "<<results[choose-1].ratings<<endl;
            vector<int> cost = locationGraph.dijkstras(search_result);
            int minCost, minCostIdx;
            if(cost[18]<=cost[21] && cost[18]<=cost[27] && cost[18]<=cost[29] && cost[18]<=cost[35] && cost[18]<=cost[39]){
                minCost = cost[18];
                minCostIdx = 18;
            }
            if(cost[21]<=cost[18] && cost[21]<=cost[27] && cost[21]<=cost[29] && cost[21]<=cost[35] && cost[21]<=cost[39]){
                minCost = cost[21];
                minCostIdx = 21;
            }
            if(cost[27]<=cost[18] && cost[27]<=cost[21] && cost[27]<=cost[29] && cost[27]<=cost[35] && cost[27]<=cost[39]){
                minCost = cost[27];
                minCostIdx = 27;
            }
            if(cost[29]<=cost[18] && cost[29]<=cost[21] && cost[29]<=cost[27] && cost[29]<=cost[35] && cost[29]<=cost[39]){
                minCost = cost[29];
                minCostIdx = 29;
            }
            if(cost[35]<=cost[18] && cost[35]<=cost[21] && cost[35]<=cost[27] && cost[35]<=cost[29] && cost[35]<=cost[39]){
                minCost = cost[35];
                minCostIdx = 35;
            }
            if(cost[39]<=cost[18] && cost[39]<=cost[21] && cost[39]<=cost[27] && cost[39]<=cost[29] && cost[39]<=cost[35]){
                minCost = cost[39];
                minCostIdx = 39;
            }
            cout<<"Total Cost = "<<minCost + ans[search_result]<<endl<<endl;
            cout<<"Recommended supplier chain :- "<<endl;
            cout<<"*****************************"<<endl<<endl;
                    int src = 0; 
                    locationGraph.path(src,minCostIdx);
                    cout<<endl<<endl;
                    break;
        }
    }
    break;
}
} 
        }
        break;

        case 2:

        {
            vector<item> items;
            vector<int> weights = {2, 3, 1, 4, 8, 3, 5, 1, 2, };
            vector<int> profits = {10, 20, 15, 30, 12, 15, 17, 18, 20};
            vector<int> deadlines = {3, 1, 2, 4, 5, 1, 2, 6, 2};

            // Create items vector
            for (int i = 0; i < weights.size(); ++i)
            {
                items.push_back(item(i + 1, "Item " + to_string(i + 1), deadlines[i], profits[i], weights[i]));
            }

            cout << "Choose an option for production inventory:" << endl;
            cout << "1. Maximise production profit based on unlimited production capacity but strict deadline" << endl;
            cout << "2. Maximise production profit based on unlimited deadline but strict production capacity" << endl;
            cout << "3. Maximise production profit based on strict deadline and strict production capacity" << endl;

            int prodOption;
            cin >> prodOption;
            ofstream outputFile("output.txt");
            if (!outputFile)
            {
                cerr << "Error: Could not open the file for writing.\n";
                return 1;
            }

            switch (prodOption)
            {
            case 1:
                items[0].calculateProductionInventoryDeadline(items, outputFile);
                break;
            case 2:
            {
                int capacity;
                cout << "Enter the capacity: ";
                cin >> capacity;
                items[0].calculateProductionInventoryCapacity(items, capacity, outputFile);
            }
            break;
            case 3:
            {
                items[0].calculateProductionInventoryDeadlineandCapacity(items, outputFile);
            }
            break;
            default:
                cout << "Invalid production inventory option." << endl;
                break;
            }
            cout << "Production inventory information has been saved to 'output.txt'.\n";
            outputFile.close();
        }
        break;

        case 3:
        {
            ifstream huffmanFile("output.txt");
            if (!huffmanFile)
            {
                cerr << "Error: Could not open the output file.\n";
                return 1;
            }
            unordered_map<string, char> huffmanMap = readHuffmanCodesFromFile("output.txt");

            cout << "Huffman Codes:\n";
            for (const auto &pair : huffmanMap)
            {
                cout << "Character: " << pair.second << ", Code: " << pair.first << endl;
            }
            string encodedText = readEncodedTextFromFile("output.txt");
            cout << encodedText << endl;
            string decodedText = decodeHuffmanText(encodedText, huffmanMap);
            for (int i = 0; i < decodedText.length(); i++)
            {
                cout << "Item id: " << decodedText[i] << endl;
            }
            // cout << "Decoded Text:\n"
            //      << decodedText << endl;
        }
        break;
        default:
            cout << "Invalid production inventory option." << endl;
            break;
        }
        cout << "Choose an option:" << endl;
        cout << "1. Supply chain operations" << endl;
        cout << "2. Calculate Production Inventory" << endl;
        cout << "3. Display previous logs (using Huffman Decoding)" << endl;
        cout << "4. Exit" << endl;
        cin >> option;
    }
    return 0;
}