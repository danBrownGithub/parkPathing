#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;

//a ride struct to make returning wait and visit order easier
struct Ride {
    Ride()
        : name(""),
          waitTime(0),
          rideDuration(0){
          };
    
    Ride(string _rideName, int _waitTime, int _rideDuration)
        : name(_rideName),
          waitTime(_waitTime),
          rideDuration(_rideDuration){
          };

    Ride& operator=(Ride old)
    {
        this->name = old.name;
        this->rideDuration = old.rideDuration;
        this->waitTime = old.waitTime;
    };

    string name;
    int waitTime;
    int rideDuration;
};

//prints ride list in user friendly format
void printRidesList()
{
    cout << "1. Astro Orbiter" << endl;
    cout << "2. Barn Stormer" << endl;
    cout << "3. Big Thunder Mountain Railroad" << endl;
    cout << "4. Buzz Lightyear's Space Ranger Spin" << endl;
    cout << "5. Carousel of Progress" << endl; 
    cout << "6. Country Bear Jamboree" << endl;
    cout << "7. Dumbo the Flying Elephant" << endl;
    cout << "8. Haunted Mansion" << endl;
    cout << "9. It's a Small World" << endl;
    cout << "10. Jungle Cruise" << endl;
    cout << "11. Mad Tea Party" << endl;
    cout << "12. The Magic Carpets of Aladdin" << endl;
    cout << "13. Mickey's Philhar Magic" << endl;
    cout << "14. Monsters, Inc. Laugh Floor" << endl;
    cout << "15. Peter Pan's Flight" << endl;
    cout << "16. Pirates of the Caribbean" << endl;
    cout << "17. Prince Charming Regal Carrousel" << endl;
    cout << "18. Seven Dwarfs Mine Train" << endl;
    cout << "19. Space Mountain" << endl;
    cout << "20. Splash Mountain" << endl;
    cout << "21. The Many Adventures of Winnie the Pooh" << endl;
    cout << "22. Tomorrowland Speedway" << endl;
    cout << "23. Tomorrowland Transit Authority PeopleMover" << endl;
    cout << "24. Under the Sea - Journey of The Little Mermaid" << endl << endl; 
}

// adds ride to ride list based on user input
void AddRideToList(int _rideIndex, vector<Ride>& toVisit)
{
    
    string rideName;
    Ride temp;
    switch(_rideIndex)
    {
        case 1: 
        {
            rideName = "Astro Orbiter";
            temp = Ride(rideName, 0, 2);
            break;
        }
        case 2: 
        {
            rideName = "Barnstormer";
            temp = Ride(rideName, 0, 1);
            break;
        }
        case 3: 
        {
            rideName = "Thunder Mountain";
            temp = Ride(rideName, 0, 4);
            break;
        }
        case 4: 
        {
            rideName = "Buzz Lightyear";
            temp = Ride(rideName, 0, 4);
            break;
        }
        case 5: 
        {
            rideName = "Carousel of Progress";
            temp = Ride(rideName, 0, 21);
            break;
        }
        case 6: 
        {
            rideName = "Country Bear Jamboree";
            temp = Ride(rideName, 0, 12);
            break;
        }
        case 7: 
        {
            rideName = "Dumbo";
            temp = Ride(rideName, 0, 2);
            break;
        }
        case 8: 
        {
            rideName = "Haunted Mansion";
            temp = Ride(rideName, 0, 8);
            break;
        }
        case 9: 
        {
            rideName = "Its a Small World";
            temp = Ride(rideName, 0, 11);
            break;
        }
        case 10: 
        {
            rideName = "Jungle Cruise";
            temp = Ride(rideName, 0, 9);
            break;
        }
        case 11: 
        {
            rideName = "Mad Tea Party";
            temp = Ride(rideName, 0, 2);
            break;
        }
        case 12: 
        {
            rideName = "Magic Carpets of Aladdin";
            temp = Ride(rideName, 0, 2);
            break;
        }
        case 13: 
        {
            rideName = "Mickeys PhilharMagic";
            temp = Ride(rideName, 0, 12);
            break;
        }
        case 14: 
        {
            rideName = "Monsters Inc Laugh Floor";
            temp = Ride(rideName, 0, 11);
            break;
        }
        case 15: 
        {
            rideName = "Peter Pan";
            temp = Ride(rideName, 0, 3);
            break;
        }
        case 16: 
        {
            rideName = "Pirates of the Caribbean";
            temp = Ride(rideName, 0, 9);
            break;
        }
        case 17: 
        {
            rideName = "Prince Charming Carousel";
            temp = Ride(rideName, 0, 2);
            break;
        }
        case 18: 
        {
            rideName = "Seven Dwarfs Mine Train";
            temp = Ride(rideName, 0, 3);
            break;
        }
        case 19: 
        {
            rideName = "Space Mountain";
            temp = Ride(rideName, 0, 3);
            break;
        }
        case 20: 
        {
            rideName = "Splash Mountain";
            temp = Ride(rideName, 0, 11);
            break;
        }
        case 21: 
        {
            rideName = "Winnie the Pooh";
            temp = Ride(rideName, 0, 4);
            break;
        }
        case 22: 
        {
            rideName = "Tomorrowland Speedway";
            temp = Ride(rideName, 0, 5);
            break;
        }
        case 23: 
        {
            rideName = "PeopleMover";
            temp = Ride(rideName, 0, 10);
            break;
        }
        case 24: 
        {
            rideName = "Little Mermaid";
            temp = Ride(rideName, 0, 7);
            break;
        }
        default: {
            break;
        }
        
    }
    toVisit.push_back(temp);
}

//Function that makes time work good.
//really it just runs around the clock with a mod
//we left room in for bathroom breaks!
void addTime(int& currentTime, Ride& ride)
{
    int currentHour;
    int currentMin;
    if (ride.waitTime + ride.rideDuration + (currentTime % 100) >= 60) // ex. if currTime = 840, waitLength = 30, total time would be 870. currHour = 8, currMin = 40, currTime = 10 + 900 == 910
    {
        currentHour = currentTime / 100;
        currentMin = (currentTime % 100);
        currentTime = (ride.waitTime + ride.rideDuration + currentMin) % 60;
        currentTime += (currentHour + 1) * 100;
    }
    else
    {
        currentTime+=ride.waitTime + ride.rideDuration;
    }

    // round current time up to nearest 5th minute
    currentTime = currentTime + (5 / 2);
    currentTime -= currentTime % 5;
    currentTime += 5;

    if (currentTime % 100 >= 60)
        currentTime += 40;
}

// Averages a month and day from multiple years into one day | ex. 1/1/19, 1/1/20, 1/1/21 into just 1/1
void CalculateAverageWaitTimeUnordered(unordered_map<string, unordered_map<string, unordered_map<int, int>>>& _rides, 
               unordered_map<string,unordered_map<string, unordered_map<int,int>>>& _disneyUnordered)
{
    
    for (int i = 1; i <= 12; i++) // for each month of ride
    {
        string month = "";
        if (i < 10)
            month += "0";
            
        month += to_string(i);

        for (int j = 1; j <= 31; j++)
        {
            string day = "";
            if (j < 10)
                day += "0";
            day += to_string(j);


            int k = 700;
            while (k <= 2400)   // k == time of day 700 (am) to 2400 (midnight)
            {
                int numYears = 0;
                int timeWaitSum = 0;
                int timeWaitAverage = 0;

                string date2019 = "2019-" + month + "-" + day;
                string date2020 = "2020-" + month + "-" + day;
                string date2021 = "2021-" + month + "-" + day;

                unordered_map<string, unordered_map<string, unordered_map<int, int>>>::iterator h = _rides.begin();
                unordered_map<int, int>::iterator iter2019 = h->second[date2019].find(k);
                unordered_map<int, int>::iterator iter2020 = h->second[date2020].find(k);
                unordered_map<int, int>::iterator iter2021 = h->second[date2021].find(k);

                if (iter2019 != h->second[date2019].end())
                {
                    timeWaitSum += iter2019->second;
                    numYears++;
                }
                if (iter2020 != h->second[date2020].end())
                {
                    timeWaitSum += iter2020->second;
                    numYears++;
                }
                if (iter2021 != h->second[date2021].end())
                {
                    timeWaitSum += iter2021->second;
                    numYears++;
                }

                if (numYears != 0)
                    timeWaitAverage = timeWaitSum / numYears;

                string finalMonth = to_string(i);
                string finalDay = to_string(j);
                string finalDate = finalMonth + "/" + finalDay;

                if (timeWaitSum != 0)
                    _disneyUnordered[h->first][finalDate][k] = timeWaitAverage;
                
                if ((k % 100 + 5) < 60) // k not rolling over to new hour ie. less than 55 minutes out of the hour
                    k += 5;
                else // k is rolling over to new hour because it is at 55 minutes, so just add 45 and it'll be a new hour
                    k += 45;
            }
        }
    }
}

// Same as above function, but for ordered maps instead of unordered
void CalculateAverageWaitTimeOrdered(map<string, map<string, map<int, int>>>& _rides, 
               map<string,map<string,map<int,int>>>& _disneyOrdered)
{
    for (int i = 1; i <= 12; i++) // for each month of ride
    {
        string month = "";

        if (i < 10)
            month += "0";
            
        
        month += to_string(i);

        for (int j = 1; j <= 31; j++)
        {
            string day = "";
            if (j < 10)
                day += "0";
            day += to_string(j);

            int k = 700;
            while (k <= 2400)   // k == time of day 700 (am) to 2400 (midnight)
            {
                int numYears = 0;
                int timeWaitSum = 0;
                int timeWaitAverage = 0;

                string date2019 = "2019-" + month + "-" + day;
                string date2020 = "2020-" + month + "-" + day;
                string date2021 = "2021-" + month + "-" + day;

                map<string, map<string, map<int, int>>>::iterator h = _rides.begin();
                map<int, int>::iterator iter2019 = h->second[date2019].find(k);
                map<int, int>::iterator iter2020 = h->second[date2020].find(k);
                map<int, int>::iterator iter2021 = h->second[date2021].find(k);

                if (iter2019 != h->second[date2019].end())
                {
                    timeWaitSum += iter2019->second;
                    numYears++;
                }
                if (iter2020 != h->second[date2020].end())
                {
                    timeWaitSum += iter2020->second;
                    numYears++;
                }
                if (iter2021 != h->second[date2021].end())
                {
                    timeWaitSum += iter2021->second;
                    numYears++;
                }

                if (numYears != 0)
                    timeWaitAverage = timeWaitSum / numYears;

                string finalMonth = to_string(i);
                string finalDay = to_string(j);
                string finalDate = finalMonth + "/" + finalDay;

                if (timeWaitSum != 0)
                    _disneyOrdered[h->first][finalDate][k] = timeWaitAverage;
                
                if ((k % 100 + 5) < 60) // k not rolling over to new hour ie. less than 55 minutes out of the hour
                    k += 5;
                else // k is rolling over to new hour because it is at 55 minutes, so just add 45 and it'll be a new hour
                    k += 45;
            }
        }
    }
}

//Reads in the files into an ordered map and keeps track of time elapsed
void orderedMapReadFile(string _fileName,string _month, map<string,map<string,map<int,int>>>& disneyOrdered)
{
    fstream fin;
    string file("./data_sets/" + _fileName + "/" + _month + ".csv");

    fin.open(file, ios::in);

    vector<string> row;
    queue<string> inputQueue;
    map<string, map<string, map<int, int>>> rides;

    string line;
    string temp;
    string rideName;
    string targetDate;
    string targetTime;
    string tempDateTime;
    string tempWaitTime;

    int waitTime;

    while(getline(fin, temp))
    {
        while (getline(fin, line, ','))
        {
            inputQueue.push(line);               // line contains ride name

            getline(fin, tempDateTime, ',');
            inputQueue.push(tempDateTime);

            getline(fin, tempWaitTime);
            inputQueue.push(tempWaitTime);
        }
    }
    fin.close();

    while(!inputQueue.empty())
    {
        rideName = inputQueue.front();
        inputQueue.pop();

        targetDate = inputQueue.front().substr(0, inputQueue.front().find_last_of(' '));
        targetTime = inputQueue.front().substr(inputQueue.front().find_last_of(' ') + 1, inputQueue.front().size() - 1);

        targetTime.erase(remove(targetTime.begin(), targetTime.end(), ':'), targetTime.end());  // removes : from string ex: 9:00:00 -> 90000
        
        int convertedTargetTime = stoi(targetTime.substr(0, targetTime.size() - 2)); // converts from ex. 90000 to 900 for time
        
        convertedTargetTime = convertedTargetTime + (5 / 2);
        convertedTargetTime -= convertedTargetTime % 5;

        inputQueue.pop();

        waitTime = stoi(inputQueue.front());
        inputQueue.pop();

        rides[rideName][targetDate][convertedTargetTime] = waitTime;
    }
    CalculateAverageWaitTimeOrdered(rides, disneyOrdered);
}

//Reads in the files into an unordered map and keeps track of time elapsed
void unorderedMapReadFile(string _fileName,string _month, unordered_map<string,unordered_map<string,unordered_map<int,int>>>& disneyUnordered)
{
    
    fstream fin;
    string file("./data_sets/" + _fileName + "/" + _month + ".csv");

    fin.open(file, ios::in);

    vector<string> row;
    queue<string> inputQueue;
    unordered_map<string, unordered_map<string, unordered_map<int, int>>> rides;

    string line;
    string temp;
    string rideName;
    string targetDate;
    string targetTime;
    string tempDateTime;
    string tempWaitTime;

    int waitTime;

    while(getline(fin, temp))
    {
        while (getline(fin, line, ','))
        {
            inputQueue.push(line);               // line contains ride name

            getline(fin, tempDateTime, ',');
            inputQueue.push(tempDateTime);

            getline(fin, tempWaitTime);
            inputQueue.push(tempWaitTime);
        }
    }
    fin.close();

    while(!inputQueue.empty())
    {
        rideName = inputQueue.front();
        inputQueue.pop();

        targetDate = inputQueue.front().substr(0, inputQueue.front().find_last_of(' '));
        targetTime = inputQueue.front().substr(inputQueue.front().find_last_of(' ') + 1, inputQueue.front().size() - 1);

        targetTime.erase(remove(targetTime.begin(), targetTime.end(), ':'), targetTime.end());  // removes : from string ex: 9:00:00 -> 90000
        
        int convertedTargetTime = stoi(targetTime.substr(0, targetTime.size() - 2)); // converts from ex. 90000 to 900 for time
        
        convertedTargetTime = convertedTargetTime + (5 / 2);
        convertedTargetTime -= convertedTargetTime % 5;

        inputQueue.pop();

        waitTime = stoi(inputQueue.front());
        inputQueue.pop();

        rides[rideName][targetDate][convertedTargetTime] = waitTime;
    }
    
    CalculateAverageWaitTimeUnordered(rides, disneyUnordered);
}

void useOrderedMap(map<string,map<string,map<int,int>>> &disneyOrdered, bool &loop)
{
    int rideCount;
    int rideIndex;
    int month;
    int day;
    int time;
    char restart;
    string date;
    vector<Ride> toVisit;
    vector<Ride> visitOrder;

    cout << "Enter todays date (m/dd): ";
    cin >> date;
        
    cout << "Enter the current time (hmm): ";
    cin >> time;

    cout << "Enter the number of attractions you want to visit: ";
    cin >> rideCount;

    printRidesList();

    //grabbing and adding to a vector where user wants to go
    for (int i =0;i<rideCount;i++)
    {
        cout << "Enter the index of the next ride: ";
        cin >> rideIndex;
        AddRideToList(rideIndex, toVisit);
    }

    vector<int> currentTime;
    currentTime.push_back(time);

    auto start = chrono::high_resolution_clock::now();
    while (toVisit.size() != 0)
    {
        for (int i = 0; i < toVisit.size(); i++)
            toVisit[i].waitTime = disneyOrdered[toVisit[i].name][date][time];

        int minIndex = 0;
        Ride minRide;
        minRide = toVisit[0];
        
        for (int i = 0;i<toVisit.size();i++)
        {
            if (minRide.waitTime > toVisit[i].waitTime)
            {
                minRide = toVisit[i];
                minIndex = i;
            }
        }
        visitOrder.push_back(minRide);
        toVisit.erase(toVisit.begin() + minIndex);
        addTime(time, minRide);
        currentTime.push_back(time);
    }

    cout << "Schedule" << endl;
    cout << "----------------------" << endl;

    for (int i = 0; i < visitOrder.size(); i++)
        cout << "Time: " << currentTime[i] << " || " << visitOrder[i].name << ": " << visitOrder[i].waitTime << " minutes" << endl;
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Elapsed time to calculate data using an ordered map is: " << duration.count() << " milliseconds" << endl << endl;

    cout << "Would you like to restart(y/n): ";
    cin >> restart;

    if(restart == 'n')
    {
        loop = true;
        return;
    } 
    else 
    {
        cout<<"Clearing maps..."<<endl;
        disneyOrdered.clear();
        toVisit.clear();
        visitOrder.clear();
        currentTime.clear();
        time = 0;
        date = "";
        rideCount = 0;
    }
}

void useUnorderedMap(unordered_map<string,unordered_map<string,unordered_map <int,int>>> &disneyUnordered, bool &loop)
{
    int rideCount;
    int rideIndex;
    int month;
    int day;
    int time;
    char restart;
    string date;
    vector<Ride> toVisit;
    vector<Ride> visitOrder;
    
    cout << "Enter todays date (m/dd): ";
    cin >> date;
        
    cout << "Enter the current time (hmm): ";
    cin >> time;

    cout << "Enter the number of attractions you want to visit: ";
    cin >> rideCount;

    printRidesList();

    //grabbing and adding to a vector where user wants to go
    for (int i =0;i<rideCount;i++)
    {
        cout << "Enter the index of the next ride: ";
        cin >> rideIndex;
        AddRideToList(rideIndex, toVisit);
    }

    vector<int> currentTime;
    currentTime.push_back(time);

    auto start = chrono::high_resolution_clock::now();
    while (toVisit.size() != 0)
    {
        for (int i = 0; i < toVisit.size(); i++)

            toVisit[i].waitTime = disneyUnordered[toVisit[i].name][date][time];

        int minIndex = 0;
        Ride minRide;
        minRide = toVisit[0];
        
        for (int i = 0;i<toVisit.size();i++)
        {
            if (minRide.waitTime > toVisit[i].waitTime)
                {
                    minRide = toVisit[i];
                    minIndex = i;
                }
        }
        
        visitOrder.push_back(minRide);
        toVisit.erase(toVisit.begin() + minIndex);
        addTime(time, minRide);
        currentTime.push_back(time);
    }

    cout << "Schedule" << endl;
    cout << "----------------------" << endl;

    for (int i = 0; i < visitOrder.size(); i++)
        cout << "Time: " << currentTime[i] << "||" << visitOrder[i].name << ": " << visitOrder[i].waitTime << " minutes" << endl;
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Elapsed time to calculate data using an unordered map is: " << duration.count() << " milliseconds" << endl << endl;

    cout << "Would you like to restart(y/n): ";
    cin >> restart;

    if(restart == 'n') 
    {
        loop = true;
        return;
    } 
    else 
    {
        cout<<"Clearing maps..."<<endl;
        disneyUnordered.clear();
        toVisit.clear();
        visitOrder.clear();
        currentTime.clear();
        time = 0;
        date = "";
        rideCount = 0;
    }
}

int main()
{
    int dataStructureSelection;
    bool loop = false;
    char restart;
    map<string,map<string,map<int,int>>> disneyOrdered;
    unordered_map<string,unordered_map<string,unordered_map <int,int>>> disneyUnordered;

    //calling read_file for all rides
    string rides[24] = {"Astro Orbiter","Barnstormer","Buzz Lightyear","Carousel of Progress",
    "Country Bear Jamboree","Dumbo","Haunted Mansion","Its a Small World","Jungle Cruise","Little Mermaid",
    "Mad Tea Party","Magic Carpets of Aladdin","Mickeys PhilharMagic","Monsters Inc Laugh Floor",
    "PeopleMover","Peter Pan","Pirates of the Caribbean","Prince Charming Carousel",
    "Seven Dwarfs Mine Train","Space Mountain","Splash Mountain","Thunder Mountain","Tomorrowland Speedway","Winnie the Pooh"};

    string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    while(!loop)
    {
        cout << "1. Ordered map" << endl;
        cout << "2. Unordered map" << endl;
        cout << "Choose the data structure you would like to use: ";

        cin >> dataStructureSelection;
        
        switch(dataStructureSelection)
        {
            case 1:
            {
                auto startOrderedLoad = chrono::high_resolution_clock::now();
                for (int i=0; i < 24; i++)
                {
                    cout << "Loading current ride file using ordered map " << "(" << i  + 1 << "/24): " <<  rides[i] << endl;

                    for (int j = 0; j < 12; j++)
                        orderedMapReadFile(rides[i],months[j], disneyOrdered);
                }

                auto stopOrderedLoad = chrono::high_resolution_clock::now();
                auto orderedDuration = chrono::duration_cast<chrono::seconds>(stopOrderedLoad - startOrderedLoad);
                cout << "Elapsed time to read files using an ordered map is: " << orderedDuration.count() << " seconds" << endl << endl;

                useOrderedMap(disneyOrdered, loop);
                break;
            }
            case 2:
            {
                auto startUnorderedLoad = chrono::high_resolution_clock::now();
                for (int i=0; i < 24; i++)
                {
                    cout << "Loading current ride file using unordered map " << "(" << i  + 1 << "/24): " <<  rides[i] << endl;
                    
                    for (int j = 0; j < 12; j++)
                        unorderedMapReadFile(rides[i],months[j], disneyUnordered);
                }

                auto stopUnorderedLoad = chrono::high_resolution_clock::now();
                auto unorderedDurataion = chrono::duration_cast<chrono::seconds>(stopUnorderedLoad - startUnorderedLoad);
                cout << "Elapsed time to read files using an unordered map is: " << unorderedDurataion.count() << " seconds" << endl << endl;
                
                useUnorderedMap(disneyUnordered, loop);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}