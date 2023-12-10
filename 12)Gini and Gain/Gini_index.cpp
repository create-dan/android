#include <bits/stdc++.h>
using namespace std;
double gini_of_class(double p1, double p2)
{
    int tot = p1 + p2;
    double tmp1 = (double)pow((p1 / tot), 2.0);
    double tmp2 = (double)pow((p2 / tot), 2.0);
    double ans = 1 - tmp1 - tmp2;
    return ans;
}
double gini_attribute(map<string, map<string, int>> attribute, double count)
{

    double gini = 0.0;
    for (auto i : attribute)
    {
        string val = i.first;
        double play_cnt = attribute[val]["Play"];
        double NoPlay_cnt = attribute[val]["NoPlay"];
        double tot = play_cnt + NoPlay_cnt;
        gini += (double)(tot / (double)count) * (1 - (play_cnt / tot) * (play_cnt / tot) - (NoPlay_cnt / tot) * (NoPlay_cnt / tot));
    }
    return gini;
}

int main()
{
    ifstream file("12gini.csv");
    string line, word;
    string outlook, temp, humidity, windy, mainclass;
    map<string, int> parent;
    map<string, map<string, int>> attribute;
    int count = 0;
    if (!file.is_open())
    {
        perror("Error in opening input file : ");
        return -1;
    }
    int i = 0;
    string attributeName, name;
    while (getline(file, line))
    {
        stringstream str(line);
        getline(str, outlook, ',');
        getline(str, temp, ',');
        getline(str, humidity, ',');
        getline(str, windy, ',');
        getline(str, mainclass, ',');

        int choice;
        if (i == 0)
        {
            i++;
            cout << "Enter Attribute Column Number : ";
            cin >> choice;
            cout << endl;
            continue;
        }
        switch (choice)
        {
        case 1:
            attributeName = outlook;
            break;
        case 2:
            attributeName = temp;
            break;
        case 3:
            attributeName = humidity;
            break;
        case 4:
            attributeName = windy;
            break;
        // case 5:
        // attributeName = mainclass;
        // break;
        default:
            attributeName = outlook;
            break;
        }
        parent[mainclass]++;
        attribute[attributeName][mainclass]++;
        count++;
    }
    int p1 = parent["Play"];

    int p2 = parent["NoPlay"];
    // cout << p1 << " " << p2 << endl;
    double gini_parent = gini_of_class(p1, p2);
    cout << "Gini Index "
         << "(column class): " << gini_parent << endl;
    double gini = gini_attribute(attribute, count);
    cout << "Gini Index "
         << "(column " << i << ") : " << gini << endl;
}