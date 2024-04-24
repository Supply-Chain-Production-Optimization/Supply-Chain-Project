#include <bits/stdc++.h>
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
    vector<SupplyLocation> suppliers;         // Vector to store supplier locations
    vector<vector<pair<int, int>>> adjacency; // Adjacency list to store edges

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
        adjacency[from].push_back({to, cost});
        adjacency[to].push_back({from, cost});
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

    vector<int> dijkstras()
    {
        vector<int> dist(40, N);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({0, 0});
        dist[0] = 0;
        while (!q.empty())
        {
            int d = q.top().first;
            int node = q.top().second;
            q.pop();
            for (auto it : adjacency[node])
            {
                if (dist[it.first] > d + it.second)
                {
                    dist[it.first] = d + it.second;
                    q.push({dist[it.first], it.first});
                }
            }
        }
        return dist;
    }

    // To find the cheapest supplier from the source location -->
    pair<SupplyLocation, int> findCheapestSupplier()
    {
        int minCost = N;
        int minCostIndex = -1;
        vector<int> cost = dijkstras();
        // Finding the cost from the starting supplier -->
        minCost = min(cost[18], min(cost[21], min(cost[27], min(cost[29], min(cost[35], cost[39])))));
        if (minCost == cost[18])
            minCostIndex = 18;
        else if (minCost == cost[21])
            minCostIndex = 21;
        else if (minCost == cost[27])
            minCostIndex = 27;
        else if (minCost == cost[29])
            minCostIndex = 29;
        else if (minCost == cost[35])
            minCostIndex = 35;
        else
            minCostIndex = 39;
        if (minCostIndex != -1)
            return {suppliers[minCostIndex], minCost};
        else
        {
            cout << "No supplier found.\n";
            return {SupplyLocation("", 0.0), 0};
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

    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;
    for (auto &pair : freq)
    {
        minHeap.push(new MinHeapNode(pair.first, pair.second));
    }

    while (minHeap.size() != 1)
    {
        MinHeapNode *left = minHeap.top();
        minHeap.pop();
        MinHeapNode *right = minHeap.top();
        minHeap.pop();

        unsigned sumFreq = left->freq + right->freq;
        MinHeapNode *newNode = new MinHeapNode('\0', sumFreq);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    MinHeapNode *root = minHeap.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);
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

    void calculateProductionInventoryDeadline(const vector<item> &items, ofstream &outputFile)
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
    void calculateProductionInventoryCapacity(const vector<item> &items, int capacity, ofstream &outputFile)
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
                selectedItems.push_back(items[i-1]);
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
    void calculateProductionInventoryDeadlineandCapacity(vector<item> &items, ofstream &outputFile)
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

    
};

int main()
{
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

    locationGraph.addEdge(12, 22, 438); // Botanical to Thios
    locationGraph.addEdge(22, 23, 172); // Thios to Okhla
    locationGraph.addEdge(23, 24, 275); // Okhla to The Saffron Boutique
    locationGraph.addEdge(24, 25, 800); // The Saffron Boutique to Jamia
    locationGraph.addEdge(25, 26, 629); // Jamia to Kalkaji
    locationGraph.addEdge(26, 27, 142); // Kalkaji to Hauz Khaas

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
                cout << "1.) SEARCH BY MINIMUM COST" << endl;
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
                    cout << endl
                         << endl
                         << "Min. cost supply chain --> "
                         << "Name: " << cheapest.name << endl;
                    cout << "**********************" << endl
                         << endl;
                    cout << "Min. cost required =  Rs. " << locationGraph.findCheapestSupplier().second << endl
                         << endl;
                    cout << "Your supply chain looks like this :- " << endl;
                    int src = 0;
                    int cheapest_dest = locationGraph.search_in_graph(cheapest);
                    locationGraph.path(src, cheapest_dest);
                    cout << endl
                         << endl;
                    break;
                }
                case 2:
                {
                    //average rate path here
                }
                break;
                }
                break;
            }
            break;
            case 'n':
            {
                cout << "You chose n" << endl;
                // continue;
            }
            break;
            }
            break;
        }
        break;

        case 2:

        {
            vector<item> items;
            vector<int> weights = {2, 3, 1, 4, 8, 3, 5, 1, 2, 4, 6};
            vector<int> profits = {10, 20, 15, 30, 12, 15, 17, 18, 20, 11, 14};
            vector<int> deadlines = {3, 1, 2, 4, 5, 1, 2, 6, 2, 1, 8};

            // Create items vector
            for (int i = 0; i < weights.size(); ++i)
            {
                items.push_back(item(i + 1, "Item " + to_string(i + 1), deadlines[i], profits[i], weights[i]));
            }

            cout << "Choose an option for production inventory:" << endl;
            cout << "1. Based on Deadline (Greedy Algorithm)" << endl;
            cout << "2. Based on Capacity (0/1 Knapsack Algorithm)" << endl;
            cout << "3. Based on both" << endl;

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
            for(int i=0; i<decodedText.length(); i++){
                cout<<"Item id: "<<decodedText[i]<<endl;
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