#include <bits/stdc++.h>
using namespace std;

// Equal Width Binning
void equiwidth(const vector<double> &data, int numberOfBins)
{
    int dataSize = data.size();
    double maxi = *max_element(data.begin(), data.end());
    double mini = *min_element(data.begin(), data.end());

    int w = (maxi - mini + numberOfBins) / numberOfBins;

    vector<int> arr;

    for (int i = 0; i <= numberOfBins; i++)
    {
        arr.push_back(mini + w * i);
    }

    vector<vector<int>> bins(numberOfBins, vector<int>());

    for (double j : data)
    {
        for (int i = 0; i < numberOfBins; i++)
        {
            if (j >= arr[i] && j <= arr[i + 1])
            {
                bins[i].push_back(j);
                break; // No need to check in other bins
            }
        }
    }
    ofstream outputFile("equiwidth_output.txt");

    if (!outputFile.is_open())
    {
        cout << "Couldn't create/open the output file.";
        return;
    }

    for (int i = 0; i < numberOfBins; i++)
    {
        outputFile << "Bin " << i + 1 << ": ";
        for (int num : bins[i])
        {
            outputFile << num << " ";
        }
        outputFile << endl;
    }
    outputFile.close();
}

double getMean(const vector<double> &data)
{
    double sum = accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size();
    return mean;
}

void binningByMean(const vector<double> &data, int numberOfBins)
{
    double mean = getMean(data);
    double minValue = *min_element(data.begin(), data.end());

    double binWidth = 2 * (mean - minValue) / numberOfBins;

    pair<double, double> belowMeanWidth = {minValue, minValue + binWidth};
    pair<double, double> aroundMeanWidth = {minValue + binWidth, minValue + 2 * binWidth};
    pair<double, double> aboveMeanWidth = {minValue + 2 * binWidth, minValue + 3 * binWidth};

    ofstream outputFile("bin_by_mean_output.txt");

    if (!outputFile.is_open())
    {
        cout << "Couldn't create/open the output file.";
        return;
    }

    outputFile << "3 Bins are:-\n";

    // Bin 1 (Below mean)
    outputFile << "Bin 1 (Below mean)\n";
    outputFile << "Range:- (" << belowMeanWidth.first << "-" << belowMeanWidth.second << "):- ";
    for (double element : data)
    {
        if (element < belowMeanWidth.second)
        {
            outputFile << element << " ";
        }
    }
    outputFile << "\n\n";

    // Bin 2 (Around mean)
    outputFile << "Bin 2 (Around mean)\n";
    outputFile << "Range:- (" << aroundMeanWidth.first << "-" << aroundMeanWidth.second << "):- ";
    for (double element : data)
    {
        if (element < aroundMeanWidth.second and element >= aroundMeanWidth.first)
        {
            outputFile << element << " ";
        }
    }
    outputFile << "\n\n";

    // Bin 3 (Above mean)
    outputFile << "Bin 3 (Above mean)\n";
    outputFile << "Range:- (" << aboveMeanWidth.first << "-" << aboveMeanWidth.second << "):- ";
    for (double element : data)
    {
        if (element >= aboveMeanWidth.first)
        {
            outputFile << element << " ";
        }
    }
    outputFile << "\n\n";
}

int main()
{
    ifstream inputFile("binning.csv");

    if (!inputFile.is_open())
    {
        cout << "Couldn't open the input file.";
        return 1;
    }

    string header;
    getline(inputFile, header);

    vector<double> data;
    double value;

    while (inputFile >> value)
    {
        data.push_back(value);
    }

    inputFile.close();

    int numberOfBins = 3;

    // cout << "\nBinning by Mean" << endl;
    binningByMean(data, numberOfBins);

    // cout << "\nEqual Width Binning" << endl;
    equiwidth(data, numberOfBins);

    return 0;
}