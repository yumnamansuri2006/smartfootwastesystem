#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

struct FoodData
{
    int day;
    double prepared;
    double used;
    double waste;
};

int main()
{
    vector<FoodData> data;

    ifstream file("food_data.csv");

    if (!file.is_open())
    {
        cout << "CSV file not found!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip header

    double totalPrepared = 0;
    double totalUsed = 0;
    double totalWaste = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string day, prepared, used, waste;

        getline(ss, day, ',');
        getline(ss, prepared, ',');
        getline(ss, used, ',');
        getline(ss, waste, ',');

        if (day.empty() || prepared.empty() ||
            used.empty() || waste.empty())
        {
            continue;
        }

        FoodData record;

        try
        {
            record.day = stoi(day);
            record.prepared = stod(prepared);
            record.used = stod(used);
            record.waste = stod(waste);
        }
        catch (...)
        {
            continue;
        }

        if (record.prepared < 0 ||
            record.used < 0 ||
            record.waste < 0 ||
            record.used > record.prepared)
        {
            cout << "Invalid record skipped." << endl;
            continue;
        }

        data.push_back(record);

        totalPrepared += record.prepared;
        totalUsed += record.used;
        totalWaste += record.waste;
    }

    file.close();

    int days = data.size();

    if (days < 3)
    {
        cout << "At least 3 valid records required." << endl;
        return 1;
    }

    double averageWaste = totalWaste / days;

    double wastePercentage =
        (totalWaste / totalPrepared) * 100;

    cout << fixed << setprecision(2);

    cout << "\n================================\n";
    cout << " SMART FOOD WASTE SYSTEM\n";
    cout << "================================\n";

    cout << "\nDATA ANALYSIS\n";

    cout << "Total Days: " << days << endl;
    cout << "Total Prepared: "
         << totalPrepared << " kg" << endl;

    cout << "Total Used: "
         << totalUsed << " kg" << endl;

    cout << "Total Waste: "
         << totalWaste << " kg" << endl;

    cout << "Average Waste: "
         << averageWaste << " kg" << endl;

    cout << "Waste Percentage: "
         << wastePercentage << "%" << endl;

    // New user input

    double newPrepared, newUsed;

    cout << "\nNEXT DAY PREDICTION\n";

    cout << "Enter planned food: ";
    cin >> newPrepared;

    cout << "Enter expected used food: ";
    cin >> newUsed;

    if (!cin || newPrepared <= 0 ||
        newUsed < 0 || newUsed > newPrepared)
    {
        cout << "Invalid input!" << endl;
        return 1;
    }

    // KNN REGRESSION

    vector<pair<double, double>> neighbors;

    for (int i = 0; i < days; i++)
    {
        double d1 =
            (newPrepared - data[i].prepared) / 200.0;

        double d2 =
            (newUsed - data[i].used) / 200.0;

        double distance =
            sqrt(d1 * d1 + d2 * d2);

        neighbors.push_back(
            {distance, data[i].waste}
        );
    }

    sort(neighbors.begin(), neighbors.end());

    int K = 3;

    double predictedWaste = 0;

    cout << "\nNearest 3 records:\n";

    for (int i = 0; i < K; i++)
    {
        predictedWaste += neighbors[i].second;

        cout << "Record " << i + 1
             << " Waste: "
             << neighbors[i].second
             << " kg" << endl;
    }

    predictedWaste = predictedWaste / K;

    cout << "\nPREDICTION RESULT\n";

    cout << "Predicted Food Waste: "
         << predictedWaste << " kg" << endl;

    // Waste classification

    cout << "\nWASTE CATEGORY\n";

    if (predictedWaste < 25)
    {
        cout << "Low Waste" << endl;
    }
    else if (predictedWaste <= 40)
    {
        cout << "Medium Waste" << endl;
    }
    else
    {
        cout << "High Waste" << endl;
    }

    // Donation suggestion

    cout << "\nDONATION SUGGESTION\n";

    if (predictedWaste >= 25)
    {
        cout << "Potential food surplus identified."
             << endl;

        cout << "Check food safety and donate "
             << "suitable surplus food." << endl;
    }
    else
    {
        cout << "Food waste is relatively low."
             << endl;
    }

    cout << "\n================================\n";
    cout << "ANALYSIS COMPLETED SUCCESSFULLY\n";
    cout << "================================\n";

    return 0;
}