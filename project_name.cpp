#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

\\ evalution 2 

int main()
{
    ifstream file("food_data.csv");

    if (!file.is_open())
    {
        cout << "Error: CSV file not found!" << endl;
        return 1;
    }

    string line;
    string day, preparedText, usedText, wasteText;

    int prepared, used, actualWaste;
    int totalPrepared = 0;
    int totalUsed = 0;
    int totalWaste = 0;
    int days = 0;

    cout << "====================================" << endl;
    cout << "   SMART FOOD WASTE PREDICTION SYSTEM" << endl;
    cout << "====================================" << endl;

    // Skip CSV header
    getline(file, line);

    cout << "\nDAILY FOOD WASTE ANALYSIS\n";
    cout << "Day\tPrepared\tUsed\tWaste\n";

    while (getline(file, line))
    {
        stringstream ss(line);

        getline(ss, day, ',');
        getline(ss, preparedText, ',');
        getline(ss, usedText, ',');
        getline(ss, wasteText, ',');

        if (day.empty() || preparedText.empty() ||
            usedText.empty() || wasteText.empty())
        {
            continue;
        }

        prepared = stoi(preparedText);
        used = stoi(usedText);
        actualWaste = stoi(wasteText);


        if (prepared < 0 || used < 0 || actualWaste < 0 ||
            used > prepared)
        {
            cout << "Invalid data found!" << endl;
            file.close();
            return 1;
        }

        totalPrepared += prepared;
        totalUsed += used;
        totalWaste += actualWaste;
        days++;

        cout << day << "\t"
             << prepared << "\t\t"
             << used << "\t"
             << actualWaste << endl;
    }

    file.close();

    if (days == 0)
    {
        cout << "\nNo valid food records found." << endl;
        return 1;
    }

    double averageWaste = (double)totalWaste / days;

    double wastePercentage =
        (double)totalWaste / totalPrepared * 100;

    double predictedWaste = averageWaste;

    cout << "\n====================================" << endl;
    cout << "          FINAL ANALYSIS" << endl;
    cout << "====================================" << endl;

    cout << "Total Days: " << days << endl;
    cout << "Total Food Prepared: " << totalPrepared << endl;
    cout << "Total Food Used: " << totalUsed << endl;
    cout << "Total Food Waste: " << totalWaste << endl;

    cout << fixed << setprecision(2);

    cout << "Average Daily Waste: "
         << averageWaste << endl;

    cout << "Food Waste Percentage: "
         << wastePercentage << "%" << endl;

    cout << "\nPREDICTION\n";
    cout << "Predicted Waste for Next Day: "
         << predictedWaste << endl;

    cout << "\nDONATION SUGGESTION\n";

    if (totalPrepared > totalUsed)
    {
        cout << "Potential surplus food identified." << endl;
        cout << "Check safe and untouched surplus for donation." << endl;
    }
    else
    {
        cout << "No surplus food identified." << endl;
    }

    cout << "\nAnalysis Completed Successfully!" << endl;

    return 0;
}