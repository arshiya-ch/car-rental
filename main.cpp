#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <thread>
#include <bits/stdc++.h>
using namespace std;

int isContractDaysExceeded(int, int, int);

//Just read welcome.txt and print on console
class Welcome
{
public:
  void welcome()
  {
    ifstream in("welcome.txt");
    try //handled IOexception
    {
      if (!in)
      {
        throw 3;
      }
      char str[1000000];
      while (in)
      {
        in.getline(str, 1000000);
        if (in)
          cout << str << endl;
      }
      in.close();
    }
    catch (...)
    {
      cout << "Cannot open input file.\n";
    }
    sleep(1);
    cout << "\nStarting the program please wait....." << endl;
    sleep(1);
    cout << "\nloading up files....." << endl;
    sleep(1);
    system("CLS");
  }
};

// int welcome()
// {
//   ifstream in("welcome.txt");
//   try //handled IOexception
//   {
//     if (!in)
//     {
//       throw 3;
//     }
//     char str[1000];
//     while (in)
//     {
//       in.getline(str, 1000);
//       if (in)
//         cout << str << endl;
//     }
//     in.close();
//   }
//   catch (...)
//   {
//     cout << "Cannot open input file.\n";
//   }
//   sleep(1);
//   cout << "\nStarting the program please wait....." << endl;
//   sleep(1);
//   cout << "\nloading up files....." << endl;
//   sleep(1);
//   system("CLS");
// }

class login
{
public:
  login()
  {
    fflush(stdin);
    string password = "";
    char c;
    system("Color B5");
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t       CAR RENTAL SYSTEM \n\n";
    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t     LOGIN \n";
    cout << "\t\t\t\t\t------------------------------\n\n";
    cout << "\t\t\t\t\tEnter Password: ";
    c = _getch();

    while (c != '\r') //Loop until 'Enter' is pressed
    {
      c = getch();
      if (c == '\b') //If the 'Backspace' key is pressed
      {
        if (password.size() != 0) //If the password string contains data, erase last character
        {
          cout << "\b \b";
          password.erase(password.size() - 1, 1);
        }
        continue;
      }
      else if (c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') //If user enters 1-9, a-z, or A-Z, add it to the password and display an asterisk
      {
        password += c;
        cout << "*";
      }
      else
        continue;
    }
    try
    {
      if (password == "aryan")
      {
        cout << "\n\n\n\t\t\t\t\t\tAccess Granted! \n";
        system("PAUSE");
        system("CLS");
      }
      else
      {
        throw 10;
      }
    }
    catch (...)
    {
      cout << "\n\n\t\t\t\t\t\t\tAccess Aborted...\n\t\t\t\t\t\t\tPlease Try Again\n\n";
      system("PAUSE");
      system("CLS");
      login();
    }
  }
};

//
class CarData
{
public:
  string carName;
  int seatingCapacity, chargingTime, range;
  float power, batteryCapacity;
  int ratePerKm, stocks;

  void showAllCars()
  {
    ifstream fin;
    fin.open("allCar.txt");
    string line;
    char carSrNo = 'A';
    while (!fin.eof())
    {
      getline(fin, line, ',');
      if (line.size() != 0)
      {
        cout << carSrNo << ") ------->" << line << "\n";
        getline(fin, line);
        carSrNo++;
      }
    }
    fin.close();
  }

  static int totalCars()
  {
    ifstream fin;
    int noOfCars = 0;
    fin.open("allCar.txt");
    string line;
    while (!fin.eof())
    {
      getline(fin, line);
      noOfCars++;
    }
    fin.close();
    return noOfCars;
  }
};

void changeCarStock(string carName, int changeStock)
{
  int carStock;
  ifstream fin;
  ofstream fout;
  fout.open("temp.txt", ios::app);
  fin.open("allCar.txt");
  string line;

  while (!fin.eof())
  {
    getline(fin, line, ',');
    if (line.size() != 0)
    {
      fout << line<<" , ";
      if (line.compare(carName))
      {
        for (int i = 4; i >= 0; i--)
        {
          getline(fin, line, ',');
          fout << line<<" , ";
        }
        carStock = stoi(line);
        carStock += changeStock;
        fout << to_string(carStock) << endl;
      }
      else
      {
        getline(fin, line);
        fout << line << endl;
      }
      getline(fin, line);
    }
  }
  fout.close();
  fin.close();

  remove("allCar.txt");
  rename("temp.txt", "allCar.txt");
}

int readCarRate(string carName)
{
  int carRate;

  ifstream fin;
  fin.open("allCar.txt");
  string line;
  char carSrNo = 'A';
  while (!fin.eof())
  {
    getline(fin, line, ',');
    if (line.size() != 0)
    {
      if (line.compare(carName))
      {
        for (int i = 4; i >= 0; i--)
        {
          getline(fin, line, ',');
        }
        carRate = stoi(line);
        break;
      }
      getline(fin, line);
      carSrNo++;
    }
  }
  fin.close();
  return carRate;
}

class Customer
{
public:
  string customerName;
  string carModel;
  string carNumber;
  string phone_no;
  string adhaar_no;
  int rentDate = 0;
  int rentDays = 0;

private:
  int isValidNumber = 0; //for Phone Number Validation
  int isValidAdhaar = 0; //for adhaar validation

public:
  void takeCustomerData() // to take all data of customer
  {
    fflush(stdin);
    system("PAUSE");
    system("CLS");

    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t     CUSTOMER DATA \n";
    cout << "\t\t\t\t\t------------------------------\n\n";

    cout << "\t\t\t\tPlease Enter your Name: ";
    getline(cin, customerName);
    cout << endl;

    cout << "\t\t\t\tPlease Enter your Phone Number: ";
    cin >> phone_no;
    cout << endl;

    cout << "\t\t\t\tPlease Enter your Adhaar Number: ";
    cin >> adhaar_no;
    cout << endl;

    //Validation of Phone Number
    if (phone_no.length() == 10)
    {
      for (int i = 0; i < 10; i++)
      {
        if (!isdigit(phone_no[i]))
        {
          isValidNumber = 1;
          break;
        }
      }
    }
    else
    {
      isValidNumber = 1;
    }
    isValidNumber = 0;
    isValidAdhaar = 0;

    //Validation of Adhaar Number
    if (adhaar_no.length() == 12)
    {
      if (adhaar_no[0] == 1 || adhaar_no[0] == 0)
      {
        isValidAdhaar = 1;
      }
      for (int i = 0; i < 12; i++)
      {
        if (!isdigit(adhaar_no[i]))
        {
          isValidAdhaar = 1;
          break;
        }
      }
    }
    else
    {
      isValidAdhaar = 1;
    }
    if (isValidNumber == 1 && isValidAdhaar == 1)
    {
      cout << "\n\n\t\t\tYou have Entered Invalid Phone Number And Adhaar Number." << endl;
      cout << "\t\t\tPlease ! Insert Valid Information!!" << endl;

      system("PAUSE");
      system("CLS");

      takeCustomerData();
    }
    else if (isValidNumber == 1)
    {
      cout << "\n\n\t\t\tYou have Entered Invalid Phone Number." << endl;
      cout << "\t\t\tPlease ! Insert Valid Information!!" << endl;

      system("PAUSE");
      system("CLS");

      takeCustomerData();
    }
    else if (isValidAdhaar == 1)
    {
      cout << "\t\t\tYou have Entered Invalid Adhaar Number" << endl;
      cout << "\t\t\tPlease ! Insert Valid Information!!" << endl;

      system("PAUSE");
      system("CLS");

      takeCustomerData();
    }
  }

  void showAllCustomers()
  {
    system("PAUSE");
    system("CLS");
    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t     ALL CUSTOMERS\n";
    cout << "\t\t\t\t\t------------------------------\n\n";

    ifstream fin;
    fin.open("allCustomerHistory.txt");

    string line;

    while (!fin.eof())
    {

      getline(fin, line, ',');
      //cout<<"line size  "<<line.size()<<"\n";
      if (line.size() != 0)
      {
        cout << "\n\t\t\t-----------------------";
        cout << "\n\t\t\t\t  " << line << "\n";
        cout << "\t\t\t-----------------------\n\n";

        getline(fin, line, ',');
        cout << "Car Model                "
             << "\t\t\t\t" << line << "\n";

        getline(fin, line, ',');
        cout << "Car Number               "
             << "\t\t\t\t" << line << "\n";

        getline(fin, line, ',');
        cout << "Phone Number             "
             << "\t\t\t\t" << line << "\n";

        getline(fin, line, ',');
        cout << "Adhaar Number            "
             << "\t\t\t\t" << line << "\n";

        getline(fin, line, ',');
        cout << "Date of Rent             "
             << "\t\t\t\t" << line << "\n";

        getline(fin, line);
        cout << "Contract Days            "
             << "\t\t\t\t" << line << "\n";
      }
    }

    fin.close();
  }

  //public:
  static int totalCustomers()
  {
    ifstream fin;
    int noOfCustomers = 0;
    fin.open("customers.txt");
    string line;
    while (!fin.eof())
    {
      getline(fin, line);
      if (line.size() > 0)
        noOfCustomers++;
    }
    fin.close();
    return noOfCustomers;
  }
};

class HandleCars : public CarData
{
public:
  //CarData car;
private:
  char carChoice;

public:
  void addNewCar()
  {
    system("PAUSE");
    system("CLS");
    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t    ADD NEW CAR\n";
    cout << "\t\t\t\t\t------------------------------\n\n";

    cout << "Enter following specifications of car\n";
    cout << "Car Name             : ";
    getline(cin, carName);
    cout << "Power                : ";
    cin >> power;
    cout << "Battery Capacity     : ";
    cin >> batteryCapacity;
    cout << "Range                : ";
    cin >> range;
    cout << "Charging Time        : ";
    cin >> chargingTime;
    cout << "Seating Capacity     : ";
    cin >> seatingCapacity;
    cout << "Car rate per KM      : ";
    cin >> ratePerKm;
    cout << "Car stock            : ";
    cin >> stocks;

    //adding this new car information in file
    ofstream fout;
    fout.open("allCar.txt", ios::app);

    string line;
    line = carName + ", " + to_string(power) + "bhp, " + to_string(batteryCapacity) + "kWh, " + to_string(range) + "km, " + to_string(chargingTime) + "Min(0-80%), " + to_string(seatingCapacity) + ", " + "$" + to_string(ratePerKm) + "/KM, " + to_string(stocks);
    fout << endl
         << line;

    fout.close();
  }

  void deleteCar()
  {
    do
    {
      system("PAUSE");
      system("CLS");
      cout << "\t\t\t\t\t------------------------------";
      cout << "\n\t\t\t\t\t\t     DELETE CAR\n";
      cout << "\t\t\t\t\t------------------------------\n\n";
      showAllCars();

      cout << endl;
      cout << "\t\t\t\tChoose a Car from the above options: ";
      carChoice = getche();
      cout << endl;

      string line;
      char carSrNo = 'A';

      if (!(carChoice <= 'A' + totalCars() && carChoice >= 'A' || carChoice <= 'a' + totalCars() && carChoice >= 'a'))
        cout << "Invalid Car choice. Please try again!" << endl;
      else
      {
        ifstream fin;
        ofstream fout;

        fin.open("allCar.txt");
        fout.open("temp.txt");

        while (!fin.eof())
        {
          getline(fin, line);
          if (carChoice == carSrNo || carChoice == carSrNo + 32)
          {
            //DELETING choosed car
            cout << "\n\nCar has been deleted";
          }
          else
          {
            if (line.size() != 0)
              fout << line << endl;
          }
          carSrNo++;
        }
        fin.close();
        fout.close();

        remove("allCar.txt");
        rename("temp.txt", "allCar.txt");
      }
    } while (!(carChoice <= 'A' + totalCars() && carChoice >= 'A' || carChoice <= 'a' + totalCars() && carChoice >= 'a'));
  }

  void modifyCarData()
  {
    do
    {
      system("PAUSE");
      system("CLS");
      cout << "\t\t\t\t\t------------------------------";
      cout << "\n\t\t\t\t\t\t     MODIFY CAR\n";
      cout << "\t\t\t\t\t------------------------------\n\n";
      showAllCars();

      cout << endl;
      cout << "\t\t\t\tChoose a Car from the above options: ";
      carChoice = getche();
      cout << endl;

      ifstream fin;
      ofstream fout;

      fin.open("allCar.txt");
      fout.open("temp.txt");
      string line;
      char carSrNo = 'A';

      if (!(carChoice <= 'A' + totalCars() && carChoice >= 'A' || carChoice <= 'a' + totalCars() && carChoice >= 'a'))
        cout << "Invaild Car Model. Please try again!" << endl;
      else
      {
        while (!fin.eof())
        {
          getline(fin, line);
          if (carChoice == carSrNo || carChoice == carSrNo + 32)
          {
            //modifying choosed car

            cout << "Enter following specifications of car\n";
            cout << "Car Name             : ";
            getline(cin, carName);
            cout << "Power                : ";
            cin >> power;
            cout << "Battery Capacity     : ";
            cin >> batteryCapacity;
            cout << "Range                : ";
            cin >> range;
            cout << "Charging Time        : ";
            cin >> chargingTime;
            cout << "Seating Capacity     : ";
            cin >> seatingCapacity;
            cout << "Car rate per KM      : ";
            cin >> ratePerKm;
            cout << "Car stock            : ";
            cin >> stocks;

            line = carName + ", " + to_string(power) + "bhp, " + to_string(batteryCapacity) + "kWh, " + to_string(range) + "km, " + to_string(chargingTime) + "Min(0-80%), " + to_string(seatingCapacity) + ", " + "$" + to_string(ratePerKm) + "/KM, " + to_string(stocks);
            fout << line << endl;

            cout << "\nCar has been modified";
          }
          else
          {
            if (line.size() != 0)
              fout << line << endl;
          }
          carSrNo++;
        }
        fin.close();
        fout.close();

        remove("allCar.txt");
        rename("temp.txt", "allCar.txt");
      }

    } while (!(carChoice <= 'A' + totalCars() && carChoice >= 'A' || carChoice <= 'a' + totalCars() && carChoice >= 'a'));
  }
};

class Rent : public Customer, public CarData
{

private:
  int rentalfee = 0;
  char carChoice;

public:
  void customersCarInfo()
  {
    do
    {
      system("PAUSE");
      system("CLS");
      cout << "\t\t\t\t\t------------------------------";
      cout << "\n\t\t\t\t\t\t     CAR OPTIONS\n";
      cout << "\t\t\t\t\t------------------------------\n\n";
      showAllCars();

      cout << endl;
      cout << "\t\t\t\tChoose a Car from the above options: ";
      carChoice = getche();
      cout << endl;

      system("PAUSE");
      system("CLS");

      ifstream fin;
      fin.open("allCar.txt");
      string line;
      stringstream templine;
      char carSrNo = 'A';
      while (!fin.eof())
      {
        getline(fin, line, ',');
        carModel = line;
        if (carChoice == carSrNo || carChoice == carSrNo + 32)
        {
          carModel = line;

          cout << "\t\t\t\t\t------------------------------";
          cout << "\n\t\t\t\t\t\t  " << line << "\n";
          cout << "\t\t\t\t\t------------------------------\n\n";
          cout << "Specification\n\n";

          //reading power
          getline(fin, line, ',');
          cout << "Power           "
               << "\t\t\t\t" << line << "\n";

          //reading battery capacity
          getline(fin, line, ',');
          cout << "Battery Capacity"
               << "\t\t\t\t" << line << "\n";

          //reading Range
          getline(fin, line, ',');
          cout << "Range           "
               << "\t\t\t\t" << line << "\n";

          //reading Charging Time
          getline(fin, line, ',');
          cout << "Charging Time   "
               << "\t\t\t\t" << line << "\n";

          //reading Seating Capacity
          getline(fin, line, ',');
          cout << "Seating Capacity"
               << "\t\t\t\t" << line << "\n";

          //reading Seating Capacity
          getline(fin, line, ',');
          cout << "rate per KM     "
               << "\t\t\t\t" << line << "\n";
          templine << line;
          templine >> ratePerKm;

          //reading Seating Capacity
          getline(fin, line, ',');
          cout << "Available Stock "
               << "\t\t\t\t" << line << "\n";
          templine << line;
          templine >> stocks;

          carChoice = carSrNo;
          break;
        }
        getline(fin, line);
        carSrNo++;
      }
      fin.close();

      if (carChoice >= 'A' + totalCars())
        cout << "Invaild Car Model. Please try again!\n";

      if (stocks == 0)
        cout << "Sorry! this car is out of stocks choose any other car\n";

    } while (carChoice >= 'A' + totalCars() && stocks == 0);

    cout << "\n\nPlease provide following information: " << endl;

    cout << "Please select a Car No. : ";
    cin >> carNumber;
    cout << "Number of days you wish to rent the car : ";
    cin >> rentDays;
    cout << "Enter rent date (informat ddmmyyyy): ";
    cin >> rentDate;
    cout << endl;

    calculateRent();
  }

  void calculateRent()
  {
    sleep(1);
    system("CLS");
    cout << "Calculating rent. Please wait......" << endl;
    sleep(2);
    rentalfee = rentDays * 149;

    rentInvoice();
  }

  void rentInvoice()
  {
    cout << "\n\t\t                       Car Rental - Customer Invoice                  " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	| Invoice No. :"
         << "----------------------|" << setw(25) << "#Cnb81353"
         << " |" << endl;
    cout << "\t\t	| Customer Name:"
         << "---------------------|" << setw(25) << customerName << " |" << endl;
    cout << "\t\t	| Car Model :"
         << "------------------------|" << setw(25) << carModel << " |" << endl;
    cout << "\t\t	| Car No. :"
         << "--------------------------|" << setw(25) << carNumber << " |" << endl;
    cout << "\t\t	| Number of rentDays :"
         << "---------------|" << setw(25) << rentDays << " |" << endl;
    cout << "\t\t	| Your Rental Amount is :"
         << "------------|" << setw(23) << "Rs." << rentalfee << " |" << endl;
    cout << "\t\t	| Caution Money :"
         << "--------------------|" << setw(25) << "Rs.50"
         << " |" << endl;
    cout << "\t\t	| Advanced :"
         << "-------------------------|" << setw(25) << "Rs.40"
         << " |" << endl;
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\n";
    cout << "\t\t	| Total Rental Amount is :"
         << "-----------|" << setw(25) << "Rs." << rentalfee + 50 + 40 << " |" << endl;
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\t\t	 # This is a computer generated invoce and it does not" << endl;
    cout << "\t\t	 require an authorised signture #" << endl;
    cout << " " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	You are advised to pay up the amount before due date." << endl;
    cout << "\t\t	Otherwise penelty fee will be applied" << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;

    system("PAUSE");
    system("CLS");

    changeCarStock(carModel, -1);

    //adding this customer information in file
    ofstream fout, foutAllCustomerHistory;
    fout.open("customers.txt", ios::app);
    foutAllCustomerHistory.open("allCustomerHistory.txt", ios::app);

    string line;
    line = customerName + ", " + carModel + ", " + carNumber + ", " + phone_no + ", " + adhaar_no + ", " + to_string(rentDate) + ", " + to_string(rentDays);
    fout << endl
         << line;
    foutAllCustomerHistory << endl
                           << line;
    foutAllCustomerHistory.close();
    fout.close();
  }
};

//calculating difference between dates
struct Date
{
  int d, m, y;
};
const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int countLeapYears(Date d)
{
  int years = d.y;
  if (d.m <= 2)
    years--;
  return years / 4 - years / 100 + years / 400;
}
int getDifference(Date dt1, Date dt2)
{
  long int n1 = dt1.y * 365 + dt1.d;
  for (int i = 0; i < dt1.m - 1; i++)
    n1 += monthDays[i];
  n1 += countLeapYears(dt1);
  long int n2 = dt2.y * 365 + dt2.d;
  for (int i = 0; i < dt2.m - 1; i++)
    n2 += monthDays[i];
  n2 += countLeapYears(dt2);
  return (n2 - n1);
}

//returns difference between dates
int isContractDaysExceeded(int customerRentDate, int todaysDate, int customerRentDays)
{

  int d1, m1, y1, d2, m2, y2, temp3;
  d1 = customerRentDate / 1000000;
  temp3 = customerRentDate % 1000000;
  m1 = temp3 / 10000;
  y1 = temp3 % 10000;

  d2 = todaysDate / 1000000;
  temp3 = todaysDate % 1000000;
  m2 = temp3 / 10000;
  y2 = temp3 % 10000;

  Date dt1 = {d1, m1, y1};
  Date dt2 = {d2, m2, y2};

  temp3 = getDifference(dt1, dt2);
  if (temp3 > customerRentDays)
  {
    return temp3;
  }
  else
  {
    return 0;
  }
}

class CarReturn
{
public:
  void takeBackCar()
  {
    Customer customer[Customer::totalCustomers()];

    ifstream fin;
    ofstream fout;

    fin.open("customers.txt");
    string line;
    //stringstream templine;
    int customerSrNo = 0;

    while (!fin.eof())
    {
      getline(fin, line, ',');
      customer[customerSrNo].customerName = line;

      getline(fin, line, ',');
      customer[customerSrNo].carModel = line;

      getline(fin, line, ',');
      customer[customerSrNo].carNumber = line;

      getline(fin, line, ',');
      customer[customerSrNo].phone_no = line;

      getline(fin, line, ',');
      customer[customerSrNo].adhaar_no = line;

      getline(fin, line, ',');
      customer[customerSrNo].rentDate = stoi(line);

      getline(fin, line);
      customer[customerSrNo].rentDays = stoi(line);

      customerSrNo++;
    }
    fin.close();

    int isCustomer = 0;
    string name;

    do
    {
      system("PAUSE");
      system("CLS");
      cout << "\t\t\t\t\t------------------------------";
      cout << "\n\t\t\t\t\t\t    TAKE BACK CAR\n";
      cout << "\t\t\t\t\t------------------------------\n\n";

      cout << "Enter customer's name : ";
      getline(cin, name);

      for (customerSrNo = 0; customerSrNo < Customer::totalCustomers(); customerSrNo++)
      {
        if (!name.compare(customer[customerSrNo].customerName))
        {
          isCustomer = customerSrNo + 1;
          break;
        }
      }

      if (!isCustomer)
        cout << "there is no customer with name : " << name << " Please try again!" << endl;
    } while (!isCustomer);

    //taking some data before taking car like km used, todays date

    int KM, todaysDate, penaltyAmount = 0, penaltyDays = 0, totalAmountDue = 0;
    int prePaidAmount = 90;
    cout << "Enter KM used       : ";
    cin >> KM;
    cout << "enter todays date   : ";
    cin >> todaysDate;
    penaltyDays = isContractDaysExceeded(customer[isCustomer - 1].rentDate, todaysDate, customer[isCustomer - 1].rentDays);

    if (penaltyDays > 0)
    {
      penaltyAmount = penaltyDays * (49 + 149);
    }

    totalAmountDue = (readCarRate(customer[isCustomer - 1].carModel)) * KM;
    totalAmountDue += penaltyAmount;
    totalAmountDue -= prePaidAmount;

    fout.open("temp.txt");

    for (customerSrNo = 0; customerSrNo < Customer::totalCustomers(); customerSrNo++)
    {
      if ((name.compare(customer[customerSrNo].customerName)))
      {
        line = customer[customerSrNo].customerName + ", " + customer[customerSrNo].carModel + ", " + customer[customerSrNo].carNumber + ", " + customer[customerSrNo].phone_no + ", " + customer[customerSrNo].adhaar_no + ", " + to_string(customer[customerSrNo].rentDate) + ", " + to_string(customer[customerSrNo].rentDays);
        if (customerSrNo == 0)
        {
          fout << line;
        }
        else
        {
          fout << endl
               << line;
        }
      }
    }

    fout.close();
    remove("customers.txt");
    rename("temp.txt", "customers.txt");

    ////////// HERE INVOICE///////////////
    cout << "\n\t\t                       Car Rental - Customer Invoice                  " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	| Invoice No. :"
         << "----------------------------------|" << setw(25) << "#CxRb8353"
         << " |" << endl;
    cout << "\t\t	| Customer Name:"
         << "---------------------------------|" << setw(25) << customer[isCustomer - 1].customerName << " |" << endl;
    cout << "\t\t	| Car Model :"
         << "------------------------------------|" << setw(25) << customer[isCustomer - 1].carModel << " |" << endl;
    cout << "\t\t	| Car No. :"
         << "--------------------------------------|" << setw(25) << customer[isCustomer - 1].carNumber << " |" << endl;
    cout << "\t\t	| Rent Date. :"
         << "-----------------------------------|" << setw(25) << customer[isCustomer - 1].rentDate << " |" << endl;
    cout << "\t\t	| Todays Date. :"
         << "---------------------------------|" << setw(25) << todaysDate << " |" << endl;
    cout << "\t\t	| Amount of " << KM << "KM used Car :"
         << "----------------------|" << setw(23) << "Rs." << (readCarRate(customer[isCustomer - 1].carModel)) * KM << " |" << endl;
    cout << "\t\t	| Penalty Amount :"
         << "-------------------------------|" << setw(25) << penaltyAmount
         << " |" << endl;
    cout << "\t\t	| Caution Money paid on rent date:"
         << "---------------|" << setw(25) << "Rs.50"
         << " |" << endl;
    cout << "\t\t	| Advanced paid on rent date:"
         << "--------------------|" << setw(25) << "Rs.40"
         << " |" << endl;
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\n";
    if (totalAmountDue > 0)
    {
      cout << "\t\t	| Total Amount to pay :"
           << "-------|" << setw(10) << "Rs." << totalAmountDue << " |" << endl;
    }
    else
    {
      cout << "\t\t	| Total Amount refunded :"
           << "-------|" << setw(10) << "Rs." << -1 * (totalAmountDue) << " |" << endl;
    }
    cout << "\t\t	 ________________________________________________________" << endl;
    cout << "\t\t	 # This is a computer generated invoce and it does not" << endl;
    cout << "\t\t	 require an authorised signture #" << endl;
    cout << " " << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;
    cout << "\t\t	 THANKYOU FOR USING OUR CAR RENTAL SERVICE " << endl;
    cout << "\t\t	Otherwise penelty fee will be applied" << endl;
    cout << "\t\t	///////////////////////////////////////////////////////////" << endl;

    system("PAUSE");
    system("CLS");

    cout << "customer[" << customerSrNo << "].carModel" << customer[customerSrNo].carModel;

    changeCarStock(customer[customerSrNo].carModel, 1);

    cout << "\n Car taken back succesfully ";
  }

  void showDefaulterCustomers()
  {
    Customer customer[Customer::totalCustomers()];

    system("PAUSE");
    system("CLS");
    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t DEFAULTER CUSTOMERS\n";
    cout << "\t\t\t\t\t------------------------------\n\n";

    ifstream fin;

    fin.open("customers.txt");
    string line;
    //stringstream templine;
    int customerSrNo = 0;

    while (!fin.eof())
    {
      getline(fin, line, ',');
      customer[customerSrNo].customerName = line;

      getline(fin, line, ',');
      customer[customerSrNo].carModel = line;

      getline(fin, line, ',');
      customer[customerSrNo].carNumber = line;

      getline(fin, line, ',');
      customer[customerSrNo].phone_no = line;

      getline(fin, line, ',');
      customer[customerSrNo].adhaar_no = line;

      getline(fin, line, ',');
      customer[customerSrNo].rentDate = stoi(line);
      // templine << line;
      // templine >> customer[customerSrNo].rentDate;

      getline(fin, line);
      customer[customerSrNo].rentDays = stoi(line);
      // templine << line;
      // templine >> customer[customerSrNo].rentDays;

      customerSrNo++;
    }

    fin.close();

    int todaysDate;

    cout << "Enter todays date in format ddmmyyyy : ";
    cin >> todaysDate;

    for (customerSrNo = 0; customerSrNo < Customer::totalCustomers(); customerSrNo++)
    {

      if (isContractDaysExceeded(customer[customerSrNo].rentDate, todaysDate, customer[customerSrNo].rentDays))
      {
        cout << "\n\t\t\t-----------------------";
        cout << "\n\t\t\t " << customer[customerSrNo].customerName << "\n";
        cout << "\t\t\t-----------------------\n\n";

        cout << "Car Model                "
             << "\t\t\t\t" << customer[customerSrNo].carModel << "\n";

        cout << "Car Number               "
             << "\t\t\t\t" << customer[customerSrNo].carNumber << "\n";

        cout << "Phone Number             "
             << "\t\t\t\t" << customer[customerSrNo].phone_no << "\n";

        cout << "Adhaar Number            "
             << "\t\t\t\t" << customer[customerSrNo].adhaar_no << "\n";

        cout << "Date of Rent             "
             << "\t\t\t\t" << customer[customerSrNo].rentDate << "\n";

        cout << "Contract Days            "
             << "\t\t\t\t" << customer[customerSrNo].rentDays << "\n";
      }
    }
  }
};

void thanks()
{
  system("CLS");
  ifstream inf("thanks.txt");

  char str[300];

  while (inf)
  {
    inf.getline(str, 300);
    if (inf)
      cout << str << endl;
  }
  inf.close();
  system("PAUSE");
}
class homescreen2
{
  public:
     void h2()
   {
      char handleCarsChoice;

      do
      {
        system("PAUSE");
        system("CLS");
        cout << "\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t\t     ADMIN MENU\n";
        cout << "\t\t\t\t\t------------------------------\n\n";
        cout << "\t\t\t\t\tchoose any one option\n\n";
        cout << "\t\t\t\t\tA) Add New Car\n"
             << "\t\t\t\t\tB) Modify Existing Cars\n"
             << "\t\t\t\t\tC) Delete Existing Cars\n"
             << "\t\t\t\t\tD) View All Cars\n"
             << "\t\t\t\t\tE) Show all Customers\n";

        handleCarsChoice = getch();

        if (!(handleCarsChoice <= 'd' && handleCarsChoice >= 'a' || handleCarsChoice <= 'D' && handleCarsChoice >= 'A'))
          cout << "Invaild CHoice. Please try again!" << endl;

      } while (!(handleCarsChoice <= 'd' && handleCarsChoice >= 'a' || handleCarsChoice <= 'D' && handleCarsChoice >= 'A'));

      HandleCars handlecar;

      if (handleCarsChoice == 'a' || handleCarsChoice == 'A')
      {
        handlecar.addNewCar();
        cout << "\n\nPress any key to go to homescreen \n";
        getch();
        h2();
      }
      else if (handleCarsChoice == 'b' || handleCarsChoice == 'B')
      {
        handlecar.modifyCarData();
        cout << "\n\nPress any key to go to homescreen \n";
        getch();
        h2();
      }
      else if (handleCarsChoice == 'c' || handleCarsChoice == 'C')
      {
        handlecar.deleteCar();
        cout << "\n\nPress any key to go to homescreen \n";
        getch();
        h2();
      }

      else if (handleCarsChoice == 'd' || handleCarsChoice == 'D')
      {
        system("PAUSE");
        system("CLS");
        cout << "\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t\t     ALL CARS\n";
        cout << "\t\t\t\t\t------------------------------\n\n";
        handlecar.showAllCars();
        cout << "\n\nPress any key to go to homescreen \n";
        getch();
        h2();
      }
       else if (handleCarsChoice  == 'e' || handleCarsChoice  == 'E')
    {
      system("CLS");

      cout << "You have choosed\n\n E) Customer details" << endl;
      Customer customer;
      customer.showAllCustomers();

      cout << "\n\nPress any key to go to homescreen \n";
      getch();
      h2();
      sleep(1);
    }
      sleep(1);
       cout << "\n\nPress any key to go to homescreen \n";
      getch();

   }
};

class homescreen3
  {
    public:
   void h3()
  {
    system("CLS");
    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t     CAR OPTIONS\n";
    cout << "\t\t\t\t\t------------------------------\n\n";
    cout << "\t\t\t\t\tchoose any one option\n\n";
    cout << "\t\t\t\t\tA) Rent Car\n"
         << "\t\t\t\t\tB) Return Car \n"
         << "\t\t\t\t\tC) Show All Cars\n"
         << "\t\t\t\t\tX) To exit\n";

    char homeScreenChoice = getch();
     HandleCars handlecar;

    if (homeScreenChoice == 'a' || homeScreenChoice == 'A')
    {
      system("CLS");

      cout << "You have choosed\n\n A) Rent Car" << endl;

      sleep(1);
      Rent rent;
      rent.takeCustomerData();
      rent.customersCarInfo();
      cout << "\n\nPress any key to go to homescreen \n";
      getch();
      h3();
    }





    else if (homeScreenChoice == 'b' || homeScreenChoice == 'B')
    {
      system("CLS");

      cout << "You have choosed\n\n B) Return Car" << endl;
      CarReturn take;
      take.takeBackCar();

      cout << "\n\nPress any key to go to homescreen \n";
      getch();
      h3();

      sleep(1);
    }

   /* else if (homeScreenChoice == 'e' || homeScreenChoice == 'E')
    {
      system("CLS");

      cout << "You have choosed\n\n E) Customers that Haven't given Car Back Yet" << endl;
      CarReturn defaulter;
      defaulter.showDefaulterCustomers();

      cout << "\n\nPress any key to go to homescreen \n";
      getch();
      h3();

      sleep(1);
    }*/
     else if (homeScreenChoice == 'c' || homeScreenChoice == 'C')
      {
        system("PAUSE");
        system("CLS");
        cout << "\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t\t     ALL CARS\n";
        cout << "\t\t\t\t\t------------------------------\n\n";
        handlecar.showAllCars();
        cout << "\n\nPress any key to go to homescreen \n";
        getch();
        h3();
      }
    else if (homeScreenChoice == 'x' || homeScreenChoice == 'X')
    {
      thanks();
      exit(1);
    }

    else
    {
      cout << "Invaild CHoice. Please try again!" << endl;
      h3();
    }
  }

};

class homescreen
{
public:

  void h1()
  {
     system("CLS");
    cout << "\t\t\t\t\t------------------------------";
    cout << "\n\t\t\t\t\t\t     M E N U\n";
    cout << "\t\t\t\t\t------------------------------\n\n";
    cout << "\t\t\t\t\tchoose any one option\n\n";
    cout << "\t\t\t\t\tA) ADMIN\n"
         << "\t\t\t\t\tB) USER\n"
         << "\t\t\t\t\tX) to exit\n";

         char homeScreenChoice = getch();
          if (homeScreenChoice == 'a' || homeScreenChoice == 'A')
    {
      system("CLS");

      cout << "You have choosed\n\n A) ADMIN" << endl;

      sleep(1);
      login log;
      homescreen2 home2;
      home2.h2();
    }
     if (homeScreenChoice == 'B' || homeScreenChoice == 'b')
    {
      system("CLS");

      cout << "You have choosed\n\n B)USER"<< endl;

      sleep(1);
      homescreen3 home3;
      home3.h3();

      cout << "\n\nPress any key to go to homescreen \n";
      getch();
      h1();
    }


   }
};




int main()
{
  Welcome obj;

  obj.welcome();

  //login log;
  homescreen home;
  home.h1();
  return 0;

}
