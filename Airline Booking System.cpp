#include <iostream>
#include <string>
#include <fstream>
using namespace std;



struct Trip
{
	string origin;
	string destination;
	string arrivaltime;
	string flighttime;
	string tripId;
	string status;
	int totalPassenger;
	int seatNumber;
	float ticketPrice;
};

struct User
{
	
	string fName;
	string lName;
	string phone;
	string status;
	string tripStatus;
	Trip trip;
	Trip seat;
};

int numberOfLines(string fileName);
bool isexist(string filen);
bool ifUserdown(string user);

void printTrip(string fo);

bool newBooking();

bool isSeatExist(string tripId,int seat);

void searchAllTrips();

bool cancelBooking();

bool addTripDetails();

void searchAvailableTrips();

void getScheduleAndStatus();

void PassingerList();

bool updateUser();

bool deleteUser();

bool updateTrip(); //Scheduled Delayed Arrived Canceled

bool deleteTrip(); 

int validateInt(int toCheck,string toEnter);

bool validatePhone(string phone);

int main()
{	
	int temp;
	
	cout << "\t\t\t\t***** Welcome To AirLine Booking System *****\n\n\n";
	do
	{
		
		cout << "\n\t-- Please, Choose One of the Following Options! --\n\n";
		cout << "[1] Add new booking\n[2] Cancel booking\n[3] Add New Flight Details\n[4] Search for Available Flights\n[5] Request Report\n[6] Delete Customer/Flight Record\n[7] Update Customer/Flight Details\n[8] Exit\n";
		
		cout << "Your Choice: ";
		
		temp = validateInt(temp,"Choice");
		cout << "---------\n";
		switch(temp)
		{
		
				
			case 1:
				newBooking();
				break;
			case 2:
				cancelBooking();
				break;
			case 3:
				addTripDetails();
				break;
			case 4:
				searchAvailableTrips();
				break;
			case 5:
				// switch()
				cout << "[1] Schedule And Status For All Flights\n[2] Passinger List\n";
				cout << "- Your Choice: ";
				temp = validateInt(temp,"Choice");
				switch(temp)
				{
					case 1:
						searchAllTrips();
						break;
					case 2:
						PassingerList();
						break;
					default:
						cout << "- Wrong Input! -";
				}
				break;
			case 6:
				cout << "[1] Delete User Record\n[2] Delete Flight Record\n";
				cout << "- Your Choice: ";
				temp = validateInt(temp,"Choice");
				switch(temp)
				{
					case 1:
						deleteUser();
						break;
					case 2:
						deleteTrip();
						break;
					default:
						cout << "- Wrong Input! -";
				}
				break;
			case 7:
				cout << "[1] Update User Record\n[2] Update Flight Record\n";
				cout << "- Your Choice: ";
				temp = validateInt(temp,"Choice");
				switch(temp)
				{
					case 1:
						updateUser();
						break;
					case 2:
						updateTrip();
						break;
					default:
						cout << "- Wrong Input! -";
				}
				break;
			case 8:
				cout << "Thanks For Using Our System!";
				return 0;
			default:
				cout << "- Wrong Input! -\n\n";
		}	
	
	}while(temp != 8);
	return 0;
}



bool newBooking()
{
	
	User traveler;
	Trip trip;
	
	cout << "You're About To Book A New Flight\n";
	
	cout << "Enter Traveler First Name: ";
	cin >> traveler.fName;
	
	cout << "Enter Traveler Last Name: ";
	cin >> traveler.lName;
	
	cout << "Enter Traveler Phone Number: ";
	cin >> traveler.phone;
	
	/* Todo: change the user identifier to id number and make it unchangeable */
	while(!validatePhone(traveler.phone))
	{
		cout << "Enter a valid phone number: ";
		cin >> traveler.phone;
	}
	
	if(ifUserdown(traveler.phone))
	{
		cout << "Sorry, This User is deleted";
		return false;
	}
	
	cout << "Enter the Flight Serial Number: ";
	cin >> traveler.trip.tripId;
	
	cout << "Enter the Seat Number: ";
	traveler.seat.seatNumber =  validateInt(traveler.seat.seatNumber,"Seat Number");
	
	
	// trip name file 
	string tripFile;
	tripFile = "flights\\"+traveler.trip.tripId + ".dat";
	
	
	// Check if a trip with this name exist
	while(!isexist(tripFile))
	{	
		cout << "Enter a valid Flight Name Or (e) To Exit: \n";
		cin >> traveler.trip.tripId;
		if(traveler.trip.tripId == "e")
		{
			return false;
		}
		tripFile = "flights\\"+traveler.trip.tripId + ".dat";
	}
	
	// Trip list where all traveler for a specifc trip exsist
	string tripListFile;
	ifstream tripList;
	
	tripList.open(tripFile.c_str());
	tripList >> trip.origin >> trip.destination >>  trip.flighttime >> trip.arrivaltime >> trip.totalPassenger >> trip.ticketPrice >> trip.status;
	
	// Check If flight is not available to not book it
	if(trip.status == "Canceled" || trip.status == "Arrived" || trip.status == "In-Air")
	{
		cout << "\nThis Flight Is Not Available\n";
		return false;
	}
	
	while(isSeatExist(traveler.trip.tripId,traveler.seat.seatNumber))
	{
		cout << "Enter New Seat Number: ";
		traveler.seat.seatNumber = validateInt(traveler.seat.seatNumber,"Seat Number");
	}
	
	tripListFile = "flightsLists\\"+traveler.trip.tripId+"List.dat";
	ofstream file;
	file.open(tripListFile.c_str(), ios::out | ios::app);
	
	// check if a there is a empty seat 
	if(traveler.seat.seatNumber > trip.totalPassenger)
	{
		cout << "\nSorry There Is No More Seats In This Trip, or This Seat Is Not Available !\n";
		file.close();
		return false;
	}
	
	string userNameFile;
	userNameFile = "users\\"+traveler.phone + "User.dat";
	ofstream userFile;
	userFile.open(userNameFile.c_str(),ios::out | ios::app);
	
	
	traveler.status = "Active-Account";
	traveler.tripStatus = "Booked";
	
	// another check if a booking procces done or not
	if(file << traveler.trip.tripId << " "<< traveler.fName << " " << traveler.lName << " " << traveler.phone << " " << traveler.seat.seatNumber << " " << traveler.tripStatus << " " << traveler.status <<  "\n")
	{
		if(userFile << traveler.trip.tripId << " " << traveler.fName << " " << traveler.lName << " " << traveler.phone << " " << traveler.seat.seatNumber << " " << traveler.tripStatus << " " << traveler.status << "\n")
		{
			cout << "\n- Your Flight Has Been Booked Successfully\n";
			file.close();
			userFile.close();
			return true;
			
		}
		else
		{
			cout << "\n- Your Flight Has Not Been Booked\n";
			file.close();
			userFile.close();
			return false;
		}
	}
	else
	{
		cout << "\n- Your Flight Has Not Been Book !\n";
		file.close();
		userFile.close();
		return false;
	}
	file.close();
	userFile.close();
}



bool cancelBooking()
{
	string tripId,phone;
	int seat;
	string fileName;
	bool flag = false, flag2 = false;
	
	cout << "- Enter Flight ID: ";
	cin >> tripId;
	
	cout << "- Enter User Phone: ";
	cin >> phone;
	
	
	
	if(ifUserdown(phone))
	{
		cout << "- Sorry, This User is deleted";
		return false;
	}
	
	cout << "- Enter Seat Number: ";
	
	seat = validateInt(seat,"Seat Number");
	
	fileName = "users\\" + phone+"User.dat";
	
	string tripFile = "flightsLists\\" + tripId+"List.dat";
	
	if(!isexist("flights\\" + tripId+".dat"))
	{
		cout << "- Flight Does Not Exist!";
		return false;
	}
	
    ifstream openFile;
	openFile.open(fileName.c_str(),ios::in);
	
	ofstream temp;
	temp.open("users\\temp.dat");
	
	if(!openFile)
	{
		cout << "- Flight Does not exist!\n";
		return false;
	}
	User line[100];
	int ctr = 0;
	
	while(!openFile.eof() && ctr < numberOfLines(fileName))
	{	
		openFile >> line[ctr].trip.tripId >> line[ctr].fName >> line[ctr].lName >> line[ctr].phone >> line[ctr].seat.seatNumber >> line[ctr].tripStatus >> line[ctr].status; 
	
		
		if( (line[ctr].trip.tripId.compare(tripId) == 0) && (line[ctr].seat.seatNumber == seat))
		{
			temp << line[ctr].trip.tripId << " " << line[ctr].fName << " " << line[ctr].lName << " " << line[ctr].phone << " " << line[ctr].seat.seatNumber << " " << "Canceled " << line[ctr].status << "\n";
			ctr++;
			flag = true;
		}
		else
		{
			temp << line[ctr].trip.tripId << " " << line[ctr].fName << " " << line[ctr].lName << " " << line[ctr].phone << " " << line[ctr].seat.seatNumber << " " << line[ctr].tripStatus << " " << line[ctr].status << "\n";	
			ctr++;
		}
	}
	
	temp.close();
	openFile.close();
	
	
	remove(fileName.c_str());
	
	rename("users\\temp.dat",fileName.c_str());
	
		
		
	User userTrip[100];
	
	ifstream file;
	file.open(tripFile.c_str(),ios::in);
	
	ofstream temp2;
	temp2.open("flightsLists\\temp.dat");
	ctr = 0;
	
	while(!file.eof() && ctr < numberOfLines(tripFile))
	{	
		file >> userTrip[ctr].trip.tripId >> userTrip[ctr].fName >> userTrip[ctr].lName >> userTrip[ctr].phone >> userTrip[ctr].seat.seatNumber >> userTrip[ctr].tripStatus >> userTrip[ctr].status; 
	
		
		if (userTrip[ctr].seat.seatNumber == seat)
		{
			temp2 << userTrip[ctr].trip.tripId  << " "<< userTrip[ctr].fName << " " << userTrip[ctr].lName << " " << userTrip[ctr].phone << " " << userTrip[ctr].seat.seatNumber << " " << "Canceled " << userTrip[ctr].status <<  "\n";
			ctr++;
			flag2 = true;
		}
		else
		{
			temp2 << userTrip[ctr].trip.tripId << " "<< userTrip[ctr].fName << " " << userTrip[ctr].lName << " " << userTrip[ctr].phone << " " << userTrip[ctr].seat.seatNumber << " " << userTrip[ctr].tripStatus << " " << userTrip[ctr].status <<  "\n";	
			ctr++;
		}
	}
	
	temp2.close();
	file.close();
	
	
	remove(tripFile.c_str());
	
	rename("flightsLists\\temp.dat",tripFile.c_str());
	
	if(!flag || !flag2)
	{
		cout << "\n- Nothing Has changed";
	}else
	{
		cout << "\n- Flight Has been Canceled\n";	
	}
}



bool addTripDetails()
{
	Trip trip;
	cout << "- You Are About To Add A New Flight !\n";
	
	cout << "Enter the Place of Departure: ";
	cin >> trip.origin;
	
	cout << "Enter Place of Destination: ";
	cin >> trip.destination;
	
	cout << "Enter Flight Time (HH:MM/DD/MM/YYYY): ";
	cin >> trip.flighttime;
	
	cout << "Enter Arrival Time (HH:MM/DD/MM/YYYY): ";
	cin >> trip.arrivaltime;
	
	cout << "Enter Total Passenger Number: ";
	trip.totalPassenger = validateInt(trip.totalPassenger,"Total Passenger");
	
	
	cout << "Enter Ticket Price (SAR): ";	
	trip.ticketPrice = validateInt(trip.ticketPrice,"Tickt Price");
	
	cout << "Enter Flight ID: ";
	cin >> trip.tripId;
	
	trip.status = "Scheduled";
	string fileName;
	fileName = "flights\\" + trip.tripId +".dat";
	
	
	while(isexist(fileName))
	{
		cout << "- This Flight is Already Exsist, Enter Another One: \n";
		cin >> trip.tripId;
		fileName = "flights\\" + trip.tripId +".dat";
	}
	
	ofstream file;	
	file.open (fileName.c_str(), ios::out | ios::app);
	
	
	 // insert now date in seconds to user file
	file << trip.origin << " " << trip.destination << " " << trip.flighttime << " " << trip.arrivaltime << " " << trip.totalPassenger << " " << trip.ticketPrice << " " << trip.status<<"\n";
	
	
	
	if(file) // check if file of a new flight has been created
	{
		cout << "- Your Flight Has Been Created -\n";
		file.close();
		
		// To creat Trip travelers details file
		string tripListFile;
		tripListFile = "flightsLists\\" + trip.tripId +"List.dat";
		ofstream listFile;
		listFile.open(tripListFile.c_str(), ios::out | ios::app);
		
		// To save all flights names in one file
		ofstream allflightsFile;
		allflightsFile.open("flightsLists\\allFlightsFile.dat", ios::out | ios::app);
		allflightsFile << trip.tripId << "\n";
		allflightsFile.close();
		return true;	
	}
	else
	{
		cout << "Error: **Your Flight Has Not Been Created** !\n";
		return false;
	}
	
	file.close();
    return false;
	
}



void searchAvailableTrips()
{
	Trip trip;
	
	ifstream file;
	string fileName;
	fileName = "flightsLists\\allFlightsFile.dat";
	
	file.open(fileName.c_str());
	if(!file)
	{
		cout << "-- Could Not Process! --";
		return;
	}
	
	string line,flightLine;
	string flightFile;
	int flights[100];
	
	// get all flight id from allFlightsFile
	for(int i = 0; i < numberOfLines(fileName); i++)
	{
		getline(file,line);
		
		flightFile = "flights\\"+line+".dat";
		ifstream flightStram;
		
		flightStram.open(flightFile.c_str(),ios::in);
		
		// if file does not exist skip it
		if(!flightStram)
		{
			continue;
		}
		
		getline(flightStram,flightLine);
		
		// check flight status
		if(flightLine.find("Scheduled") != string::npos || flightLine.find("Delayed") != string::npos )
		{
			// call printTrip function 
			printTrip(flightFile);
		}
		
		flightStram.close();
	}
}



void searchAllTrips()
{
	Trip trip;
	
	ifstream file;
	string fileName;
	fileName = "flightsLists\\allFlightsFile.dat";
	
	file.open(fileName.c_str());
	if(!file)
	{
		cout << "** Could Not Process! **\n";
		return;
	}
	
	string line,flightLine;
	string flightFile;
	int flights[100];
	
	for(int i = 0; i < numberOfLines(fileName); i++)
	{
		getline(file,line);
		
		flightFile = "flights\\"+line+".dat";
		ifstream flightStram;
		
		flightStram.open(flightFile.c_str(),ios::in);
		
		if(!flightStram)
		{
			continue;
		}
		
		getline(flightStram,flightLine);
		
		
		
		printTrip(flightFile);
		
		
		flightStram.close();
	}
}




void printTrip(string fo)
{
	Trip list[1];
	ifstream tripStream;

	
	tripStream.open(fo.c_str());
	
	if(!tripStream)
	{
		cout << "Error: ** Something Wrong Happened **\n";
		return ;
	}
	int ctr = 0;
	// to print the flight information
	while (ctr < 1)
	{
		tripStream >> list[ctr].origin >> list[ctr].destination >> list[ctr].flighttime >> list[ctr].arrivaltime >> list[ctr].totalPassenger >> list[ctr].ticketPrice >> list[ctr].status;
		cout << "=============================================================================================================================================================\n";
		cout <<  "Origin: " << list[ctr].origin << " Destination: "  << list[ctr].destination << " Flight Time: " << list[ctr].flighttime << " Arrival Time: " << list[ctr].arrivaltime  << " Total Passenger: " << list[ctr].totalPassenger << " Ticket Price: " << list[ctr].ticketPrice << " Status: " << list[ctr].status << "\n";
		cout << "=============================================================================================================================================================\n";
		++ctr;
	}
	
}


/* this function is not in use*/
void getScheduleAndStatus()
{
	
	Trip trip;
	
	string tripName,flightFile,flightLine;
	
	cout << "- Enter Flight ID: ";
	cin >> tripName;
	

		flightFile = "flights\\"+tripName+".dat";
		ifstream flightStram;
		flightStram.open(flightFile.c_str(),ios::in);
		
		if(!flightStram)
		{
			cout << "Error: ** Wrong Flight Name ** !\n";
			return;
		}	
		// get flight information and print it
	flightStram >> trip.origin >> trip.destination >> trip.flighttime >> trip.arrivaltime >> trip.totalPassenger >> trip.ticketPrice >> trip.status;		
	cout << "---------------------------------------\n";
	cout <<"Flight ID: " << tripName <<"\n";
	cout <<"Flight Schedule: " << trip.flighttime<<"\n";
	cout <<"Flight Status: " << trip.status<<"\n";
	cout << "---------------------------------------\n";
	flightStram.close();
}


// this function is to print passenger list
void PassingerList()
{
	string tripId,tripListFile,line;
	cout << "- Enter Flight ID: ";
	
	cin >> tripId;
	tripListFile = "flightsLists\\"+tripId+"List.dat";
	
	// if number of lines return 1 then it means their is no passengers
	if(numberOfLines(tripListFile) < 1)
	{
		cout << "\n- There is No Passingers in this Flight! - \n";
		return;
	}
	
	ifstream tripList;
	tripList.open(tripListFile.c_str());
	if(!tripList)
	{
		cout << "Error: ** Flight Does Not Exist! **\n";
		return;
	}
	
	User list[100];
	
	
	int ctr = 0;
	
	while (ctr < numberOfLines(tripListFile))
	{
		
		tripList >> list[ctr].trip.tripId >> list[ctr].fName >> list[ctr].lName >> list[ctr].phone >> list[ctr].seat.seatNumber >> list[ctr].tripStatus >> list[ctr].status;
		
		if(list[ctr].trip.tripId.empty())
		{
			break;
		}
		
		if(ifUserdown(list[ctr].phone))
		{
			continue;
		}
		cout << "==========================================================================================================================================\n";
		cout << "First Name: " << list[ctr].fName << " Last Name: "  << list[ctr].lName << " Phone Number: " << list[ctr].phone << " Seat Number: " << list[ctr].seat.seatNumber << " Booking Status: " << list[ctr].tripStatus << " User Status: " << list[ctr].status <<"\n";
		cout << "==========================================================================================================================================\n";
		++ctr;
	}
	
}


// check if file exist
bool isexist(string filen)
{
	ifstream file;
	
	file.open(filen.c_str());
	
	if(file)
	{
		return true;
	}
	return false;
	file.close();
}


// return a number of lines in a file
int numberOfLines(string fileName)
{
	int numberOfLines = 0;
    string line;
    ifstream myfile;
    myfile.open(fileName.c_str());

    while (getline(myfile, line))       
	{
		++numberOfLines;
	}
	return numberOfLines;
}


// to delete a flight
bool deleteTrip()
{	
	string tripId;
	cout << "- Enter Flight ID: ";
	cin >> tripId;
	string tripFile;
	tripFile = "flights\\" + tripId + ".dat";
	
	ifstream file;
	file.open(tripFile.c_str());
	
	if(!file)
	{
		cout << "\nError: ** Flight Does Not Exist! **\n";
		return false;
	}
	
	int temp;
	Trip trip;
	
	file >> trip.origin >> trip.destination >> trip.flighttime >> trip.arrivaltime >> trip.totalPassenger >> trip.ticketPrice >> trip.status;
	file.close();
	
	ofstream updateFile;
	updateFile.open(tripFile.c_str());
		
		trip.status = "Canceled";
		
		if(updateFile << trip.origin<< " " << trip.destination << " " << trip.flighttime << " " << trip.arrivaltime << " " << trip.totalPassenger << " " << trip.ticketPrice << " " << trip.status)
		{
			cout << "\n-- Flight Has Been Canceled! -- \n";
		}
		else
		{
			cout << "Error: ** Something Wrong Happened! **";
		}
}



bool deleteUser()
{
	string tripId,phone;
	bool flag = false, flag2 = false;
	
	cout << "Enter Booked Flight Id or (n) If Not: ";
	cin >> tripId;
	
	string fileName;
	
	cout << "Enter User Phone: ";
	cin >> phone;
	
	fileName = "users\\" + phone+"User.dat";
	
	if(ifUserdown(fileName))
	{
		cout << "Sorry, This User is deleted!\n";
		return false;
	}
	
	if(!isexist(fileName))
	{
		cout << "This User Does Not Exist!";
		return false;
	}
	
	User usr;
	
	ifstream file1;
	file1.open(fileName.c_str());
	
	file1 >> usr.trip.tripId >> usr.fName >> usr.lName >> usr.phone >> usr.seat.seatNumber >> usr.tripStatus >> usr.status;
	file1.close();
	
	
	string tripFile = "flightsLists\\" + tripId +"List.dat";
	
	if(!isexist("flights\\" + tripId+".dat") && tripId != "n")
	{
		cout << "Flight Does Not Exist!";
		return false;
	}
	
    ifstream openFile;
	openFile.open(tripFile.c_str(),ios::in);
	
	ofstream temp;
	temp.open("users\\temp.dat");
	
	if(!openFile)
	{
		cout << "Flight Does not exist!\n";
		return false;
	}
	
	User line[100];
	int ctr = 0;
	
	while(!openFile.eof() && ctr < numberOfLines(fileName))
	{	
		openFile >> line[ctr].trip.tripId >> line[ctr].fName >> line[ctr].lName >> line[ctr].phone >> line[ctr].seat.seatNumber >> line[ctr].tripStatus >> line[ctr].status; 
		if(line[ctr].phone == phone)
		{
			temp << line[ctr].trip.tripId  << " " << line[ctr].fName << " " << line[ctr].lName << " " << line[ctr].phone << " " << line[ctr].seat.seatNumber << " Canceled"  << " Deleted-Account" <<  "\n";
		}
		temp << line[ctr].trip.tripId << " " << line[ctr].fName << " " << line[ctr].lName << " " << line[ctr].phone << " " << line[ctr].seat.seatNumber << " " << line[ctr].tripStatus << " " << line[ctr].status << "\n";	
		ctr++;
		flag = true;
	}
	
	temp.close();
	openFile.close();
	
	
	remove(fileName.c_str());
	rename("users\\temp.dat",fileName.c_str());
	
	if(tripId == "n" && flag)
	{
		cout << "- User Account Has Been Deleted! -";
		return true;
	}
		
			
	User userTrip[100];
	
	ifstream file;
	file.open(tripFile.c_str(),ios::in);
	
	ofstream temp2;
	temp2.open("flightsLists\\temp.dat");
	ctr = 0;
	while(!file.eof() && ctr < numberOfLines(tripFile))
	{	
		file >> userTrip[ctr].trip.tripId >> userTrip[ctr].fName >> userTrip[ctr].lName >> userTrip[ctr].phone >> userTrip[ctr].seat.seatNumber >> userTrip[ctr].tripStatus >> userTrip[ctr].status; 
		
		if(userTrip[ctr].phone == phone)
		{
			temp2 << userTrip[ctr].trip.tripId  << " " << userTrip[ctr].fName << " " << userTrip[ctr].lName << " " << userTrip[ctr].phone << " " << userTrip[ctr].seat.seatNumber << " Canceled"  << " Deleted-Account" <<  "\n";
		}
		
		
		else
		{
			temp2 << userTrip[ctr].trip.tripId << " " << userTrip[ctr].fName << " " << userTrip[ctr].lName << " " << userTrip[ctr].phone << " " << userTrip[ctr].seat.seatNumber << " " << userTrip[ctr].tripStatus << " " << userTrip[ctr].status << "\n";	
		}
		ctr++;
		flag2 = true;
	}
	
	temp2.close();
	file.close();
	
	
	remove(tripFile.c_str());
	
	rename("flightsLists\\temp.dat",tripFile.c_str());
	
	if(!flag || !flag2)
	{
		cout << "\n- Nothing Has changed -";
	}
	else
	{
		
		cout << "\n- User Account Has Been Deleted -\n";	
	}
}



bool updateUser()
{
	string tripId,phone;
	bool flag = false, flag2 = false;
	cout << "Enter Booked Flight Id or (n) If Not: ";
	cin >> tripId;
	
	string fileName;
	
	cout << "Enter User Phone: ";
	cin >> phone;
	
	fileName = "users\\" + phone+"User.dat";
	
	if(ifUserdown(fileName))
	{
		cout << "Sorry, This User is deleted!\n";
		return false;
	}
	if(!isexist(fileName))
	{
		cout << "This User Does Not Exist!";
		return false;
	}
	
	User usr;
	
	ifstream file1;
	file1.open(fileName.c_str());
	
	file1 >> usr.trip.tripId >> usr.fName >> usr.lName >> usr.phone >> usr.seat.seatNumber >> usr.tripStatus >> usr.status;
	file1.close();
	
	
	int tmp;
	
	cout << "What Do You Want To Update: ";
	cout << "\n------\n[1] First Name\n[2] Last Name\n[3] Phone Number\n";
	cout << "Your Choice: ";	
	
	tmp = validateInt(tmp,"Choice");
	
	switch(tmp)
	{
		// Update for past one just one file *User.dat
		case 1:
		
			cout << "Enter New First Name: ";
			cin >> usr.fName;
			flag = true;
			break;
		
		case 2:
		
			cout << "Enter New Last Name: ";
			cin >> usr.lName;
			flag = true;
			break;
		
		case 3:
			cout << "Enter New Phone Number: ";
			cin >> usr.phone;
			flag = true;
			break;
			
		default:
			cout << "Wrong Input!\n";
	}
	if(!flag)
	{
		cout << "\n- Nothing Has Changed! -\n";
		return false;
	}
	
	string tripFile = "flightsLists\\" + tripId +"List.dat";
	
	if(!isexist("flights\\" + tripId+".dat") && tripId != "n")
	{
		cout << "Flight Does Not Exist!";
		return false;
	}
	
    ifstream openFile;
	openFile.open(tripFile.c_str(),ios::in);
	
	ofstream temp;
	temp.open("users\\temp.dat");
	
	if(!openFile)
	{
		cout << "Flight Does not exist!\n";
		return false;
	}
	User line[100];
	int ctr = 0;
	
	while(!openFile.eof() && ctr < numberOfLines(fileName))
	{	
		openFile >> line[ctr].trip.tripId >> line[ctr].fName >> line[ctr].lName >> line[ctr].phone >> line[ctr].seat.seatNumber >> line[ctr].tripStatus >> line[ctr].status; 
		
		temp << line[ctr].trip.tripId << " " << usr.fName << " " << usr.lName << " " << usr.phone << " " << line[ctr].seat.seatNumber << " " << line[ctr].tripStatus << " " << line[ctr].status << "\n";	
		ctr++;
		flag = true;
	}
	
	temp.close();
	openFile.close();
	
	
	remove(fileName.c_str());
	rename("users\\temp.dat",fileName.c_str());
	
	if(tripId == "n" && flag)
	{
		cout << "- User Information Has Been Updated! -";
		return true;
	}
		
	if(tmp == 3)
		{
			string newPhone = "users\\" + usr.phone + "User.dat";
			rename(fileName.c_str(),newPhone.c_str());
		}
		
			
	User userTrip[100];
	
	ifstream file;
	file.open(tripFile.c_str(),ios::in);
	
	ofstream temp2;
	temp2.open("flightsLists\\temp.dat");
	ctr = 0;
	while(!file.eof() && ctr < numberOfLines(tripFile))
	{	
		file >> userTrip[ctr].trip.tripId >> userTrip[ctr].fName >> userTrip[ctr].lName >> userTrip[ctr].phone >> userTrip[ctr].seat.seatNumber >> userTrip[ctr].tripStatus >> userTrip[ctr].status; 
		temp2 << userTrip[ctr].trip.tripId  << " " << usr.fName << " " << usr.lName << " " << usr.phone << " " << userTrip[ctr].seat.seatNumber << " " << userTrip[ctr].tripStatus << " " << userTrip[ctr].status <<  "\n";
		ctr++;
		flag2 = true;
	}
	
	temp2.close();
	file.close();
	
	
	remove(tripFile.c_str());
	
	rename("flightsLists\\temp.dat",tripFile.c_str());
	
	if(!flag || !flag2)
	{
		cout << "\n- Nothing Has changed -";
	}
	else
	{
		
		cout << "\n- User Information Has Been Updated -\n";	
	}
}



bool updateTrip()
{
	string tripId;

	cout << "Enter Flight Id: ";
	cin >> tripId;
	
	string fileName;
	
	int tmp;
	
	cout << "What Do You Want To Update: ";
	cout << "\n[1] Drparture Place\n[2] Flight Destination \n[3] Flight Time\n[4] Arrival Time\n[5] Total Passenger\n[6] Ticket Price\n[7] Flight Status\n";
	cout << "Your Choice: ";
	
	string tripFile;
	tripFile = "flights\\" + tripId + ".dat";
	
	ifstream file;
	file.open(tripFile.c_str());
	
	if(!file)
	{
		cout << "Error: ** Flight Does Not Exist! **\n";
		return false;
	}
	
	int temp;
	bool flag = false;
	Trip trip;
	
	file >> trip.origin >> trip.destination >> trip.flighttime >> trip.arrivaltime >> trip.totalPassenger >> trip.ticketPrice >> trip.status;
	file.close();	
	
	switch(validateInt(tmp,"Choice"))
	{
		// Update for past one just one file *User.dat
			
		case 1:
		
			cout << "Enter New Departure Place : ";
			cin >> trip.origin;
			flag = true;
			break;
		
		case 2:
		
			cout << "Enter New Destination: ";
			cin >> trip.destination;
			flag = true;
			break;
			
		case 3:
		
			cout << "Enter New Flight Time: ";
			cin >> trip.flighttime;
			flag = true;
			break;
			
		case 4:
		
			cout << "Enter New Arrival Time: ";
			cin >> trip.arrivaltime;
			flag = true;
			break;
			
		case 5:
		
			cout << "Enter New Total Passenger: ";
			trip.totalPassenger = validateInt(trip.totalPassenger,"Total Passenger");
			flag = true;
			break;
		
		case 6:
		
			cout << "Enter New Ticket Price: ";
			trip.ticketPrice = validateInt(trip.ticketPrice,"Ticket Price");
			flag = true;
			break;
			
		case 7:
		
			cout << "Choose New Flight Status: \n";
			cout << "[1] Scheduled\n[2] Canceled\n[3] Delayed\n[4] In Air\n[5] Arrived\n";
			cout << "Your Choice: "; 
			int sts;
			sts = validateInt(sts,"Choice");
			switch(sts)
			{
				case 1:
					trip.status = "Scheduled";
					flag = true;
					break;
				case 2:
					trip.status = "Canceled";
					flag = true;
					break;
				case 3:
					trip.status = "Delayed";
					flag = true;
					break;
				case 4:
					trip.status = "In-Air";
					flag = true;
					break;
				case 5:
					trip.status = "Arrived";
					flag = true;
					break;
				}
			default:
				cout << "Wrong Input!\n";
	}
	
	
	ofstream updateFile;
	updateFile.open(tripFile.c_str());
		
		if(updateFile << trip.origin<< " " << trip.destination << " " << trip.flighttime << " " << trip.arrivaltime << " " << trip.totalPassenger << " " << trip.ticketPrice << " " << trip.status && flag)
		{
			cout << "\n--Flight Has Been Updated!-- \n";
		}
		else
		{
			cout << "\n--Error: Nothing Has Chaneg!--\n";
		}
}



int validateInt(int toCheck,string toEnter) 
{

int someVal;
    
	if(cin >> someVal)
    {
        return someVal;
    }
    while(!(cin >> someVal) || someVal < 0 ) 
    {
       	cout << "Enter a valid " << toEnter << ": ";
        cin.clear();
        cin.ignore(123,'\n');
    }
    return  someVal;
}


// check if a seat exist in a file
bool isSeatExist(string tripId,int seat)
{
	string fileName;
	bool flag = false;
	
	if(seat <= 0)
	{
		cout << "Not a valid Seat Number";
		return true;
	}
	
	fileName = "flightsLists\\" + tripId+"List.dat";
	
	if(!isexist("flights\\" + tripId+".dat"))
	{
		cout << "Flight Does Not Exist!\n";
		return true;
	}
	
    ifstream openFile;
	openFile.open(fileName.c_str(),ios::in);
	
	
	if(!openFile)
	{
		cout << "Flight Does Not Exist!";
		return true;
	}
	User line[100];
	int ctr = 0;
	while(!openFile.eof() && ctr < numberOfLines(fileName))
	{	
		openFile >> line[ctr].trip.tripId >> line[ctr].fName >> line[ctr].lName >> line[ctr].phone >> line[ctr].seat.seatNumber >> line[ctr].tripStatus >> line[ctr].status; 	
		if( line[ctr].seat.seatNumber == seat )
		{	
			flag = true;
			break;
		}
		ctr++;
	
	}
	openFile.close();
	if(flag)
	{
		cout << "Sorry This Seat Is Already Taken\n";
		return true;
	}
	else
		return false;
}


// check if user status is cancled and return bool value
bool ifUserdown(string user)
{
	string fileName = "users\\"+user+"User.dat";
	User usr;
	ifstream file;
	file.open(fileName.c_str());
	if(!file)
	{
		return false;
	}
	file >> usr.trip.tripId >> usr.fName >> usr.lName >> usr.phone >> usr.seat.seatNumber >> usr.tripStatus >> usr.status;
	
	if(usr.status != "Active-Account")
	{
		return true;
	}
	return false;
	
}


// validate phone number
bool validatePhone(string phone)
{
	phone.c_str();
	for(int i = 0; i < phone.length(); i++)
	{
		if(!isdigit(phone.at(i)))
		{
			return false;
		}
	}
	
	if(phone.length() < 7 || phone.length() > 12)
	{
		return false;
	}
	
	return true;
	
}
