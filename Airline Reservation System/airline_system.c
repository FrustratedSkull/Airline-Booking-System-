/*
 * airline_system.c
 *
 *  Created on: Aug 15, 2019
 *      Author: Nikhil
 */

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include<time.h>
// Global Structure
struct FlightDetails{
    char name[20];
    char number[7];
    int seats;
    int price;
    int time[6];
    struct FlightDetails* next;
};
struct Passengers{
    char name[20];
    int  PNR;
    int  price;
    struct FlightDetails* flight;
    struct Passengers* next;
};
// Global Variables
int userChoice;
int date[3];
char flightNumber[7];
int PNR_List[50];
int RandPNR;
int count;
time_t t ;
struct tm tm;
struct FlightDetails* Head	 = NULL;			// To access all the flight nodes
// Separate Flight Nodes
struct FlightDetails* Indigo = NULL;
struct FlightDetails* JetAir = NULL;
struct FlightDetails* AirInd = NULL;
struct FlightDetails* Vistara= NULL;
// Passengers Nodes
struct Passengers* traveller = NULL;
struct Passengers* PassHead = NULL;
// Function Declaration
void initialization();
int takeInput();
void searchFlight();
void checkPNR();
void cancelTicket();
void bookTicket();
void loadFlights();
int payment();
// Main Function starts here
int main(){
	initialization();
    userChoice = takeInput();
    return 0;
}
// Function Definition
void initialization(){
	// Initializing time
	t = time(NULL);
	tm = *localtime(&t);
	RandPNR = 62654789;
	count = 0;

	// Giving memory to node the in the heap
	Head   = (struct FlightDetails*)malloc(sizeof(struct FlightDetails));
	PassHead = (struct Passengers*)malloc(sizeof(struct Passengers));
	Indigo = (struct FlightDetails*)malloc(sizeof(struct FlightDetails));
	JetAir = (struct FlightDetails*)malloc(sizeof(struct FlightDetails));
	AirInd = (struct FlightDetails*)malloc(sizeof(struct FlightDetails));
	Vistara = (struct FlightDetails*)malloc(sizeof(struct FlightDetails));
	// Inserting Data into Flight Nodes
	Head->next = Indigo;
    strcpy(Indigo->name,"Indigo");
    strcpy(Indigo->number, "277-833");
    Indigo->seats = 180;
    Indigo->price = 3499;
    Indigo->time[0] = 05;			// Departure Hour
    Indigo->time[1] = 30;			// Departure Minute
    Indigo->time[2] = 07;			// Arrival Hour
    Indigo->time[3] = 45;			// Arrival Minute
    Indigo->time[4] = 02;			// Journey Hour
    Indigo->time[5] = 15;			// Journey Minute
    Indigo->next = JetAir;

    strcpy(JetAir->name,"Jet Airways");
    strcpy(JetAir->number, "325-779");
    JetAir->seats = 180;
    JetAir->price = 3699;
    JetAir->time[0] = 9;
    JetAir->time[1] = 30;
    JetAir->time[2] = 12;
    JetAir->time[3] = 00;
    JetAir->time[4] = 02;
    JetAir->time[5] = 30;
    JetAir->next = AirInd;

	strcpy(AirInd->name,"Air India");
	strcpy(AirInd->number, "277-558");
	AirInd->seats = 180;
	AirInd->price = 4199;
    AirInd->time[0] = 11;
    AirInd->time[1] = 15;
    AirInd->time[2] = 14;
    AirInd->time[3] = 00;
    AirInd->time[4] = 02;
    AirInd->time[5] = 45;
	AirInd->next = Vistara;

	strcpy(Vistara->name,"Vistara");
	strcpy(Vistara->number, "277-466");
	Vistara->seats = 180;
	Vistara->price = 4599;
    Vistara->time[0] = 13;
    Vistara->time[1] = 30;
    Vistara->time[2] = 17;
    Vistara->time[3] = 15;
    Vistara->time[4] = 3;
    Vistara->time[5] = 45;
	Vistara->next = NULL;
	// End of Insertion
	PassHead->next = NULL;
}
int takeInput(){
	system("cls");		// Clear the screen
    userChoice = 0;
    while(userChoice != 5){
    	system("cls");
        printf("\n\t Welcome to Indian Airlines");
        printf("\n\n\t Services Provided by us:");
        printf("\n\t 1. Book Ticket");
        printf("\n\t 2. Check PNR");
        printf("\n\t 3. Cancel Ticket");
        printf("\n\t 5. Exit\n\t ->");
        scanf("%d", &userChoice);
        if(userChoice == 1){
            searchFlight();
        }
        else if(userChoice == 2){
            checkPNR();
        }
        else if(userChoice == 3){
            cancelTicket();
        }
    }

    return userChoice;
}
void searchFlight(){
	system("cls");		// Clear the screen
//	system("COLOR 15");
	printf("\n\n\t\t\t\t Today: %d/%d/%d",tm.tm_mday, tm.tm_mon, tm.tm_year + 1900);
	printf("\n\n\t Attention: As per our Airline Policy, You can not book flight for more than 3 month gap from today");
    printf("\n\n\t Enter the Date:");
    scanf("%d",&date[0]);
    printf("\n\t Enter the Month:");
    scanf("%d",&date[1]);
    if((date[1]==1 || date[1]==3 || date[1]==5 || date[1]==7 || date[1]==8 || date[1]==10 || date[1]==12 ) && (date[1]< tm.tm_mon + 3 )){
    	if(date[0] <=31){
    		loadFlights();
    	}
    	else{
    		system("cls");
//    		system("COLOR 4");
        	printf("\n\t Invalid Date \n Press any key to Re-Enter the Date\n");
        	fflush(stdin);
        	getchar();
        	searchFlight();
    	}
    }
    else if((date[1]==4 || date[1]==6 || date[1]==9 || date[1]==11) && (date[1]< tm.tm_mon + 3 )){
    	if(date[0] <=30){
    		loadFlights();
    	}
    	else{
        	printf("\n\t Invalid Date \n\t Press any key to Re-Enter the Date\n");
        	fflush(stdin);
        	getchar();
        	searchFlight();
    	}
    }
    else if(date[1] == 2 && (date[1]< tm.tm_mon + 3 )){
    	if(date[0] <= 29){
    		loadFlights();
    	}
    	else{
        	printf("\n\t Invalid Date \n\t Press any key to Re-Enter the Date\n");
        	printf("\n\t Please read out policy again");
        	fflush(stdin);
        	getchar();
        	searchFlight();
    	}

    }
    else if(date[1] > tm.tm_mon + 3){
    	printf("\n\t Invalid Date \n\t Press any key to Re-Enter the Date\n");
    	printf("\n\t Please read out policy again");
    	fflush(stdin);
    	getchar();
    	searchFlight();
    }
    else{
    	printf("\n\t Invalid Date \n\t Press any key to Re-Enter the Date\n");
    	printf("\n\t Please read out policy again");
    	fflush(stdin);
    	getchar();
    	searchFlight();
    }
}
void checkPNR(){
	system("cls");
	int lv_pnr = 0;
	printf("\n\n\t Please enter your PNR number:");
	scanf("%d",&lv_pnr);
	struct Passengers* trav = NULL;
	trav = (struct Passengers*)malloc(sizeof(struct Passengers));
	trav = PassHead->next;
	if(PassHead->next == NULL){
		printf("\n\n\t Sorry PNR doesn't Exist");
		fflush(stdin);
		getchar();
	}
	while(trav != NULL){
		if(trav->PNR == lv_pnr){
			printf("\n\n\t Congratulations!, Your ticket has been booked ");
			printf("\n\n\t PNR number is\t\t: %d", trav->PNR);
			printf("\n\n\t Name\t\t\t: %s", trav->name);
			printf("\n\n\t Flight Name\t\t: %s", trav->flight->name);
			printf("\n\n\t Flight Number\t\t: %s", trav->flight->number);
			printf("\n\n\t Flight Departure\t: %d:%d", trav->flight->time[0],trav->flight->time[1]);
			printf("\n\n\t Flight Arrival\t\t: %d:%d", trav->flight->time[2],trav->flight->time[3]);
			printf("\n\n\t Flight Journey\t\t: %d:%d", trav->flight->time[4],trav->flight->time[5]);
			fflush(stdin);
			printf("\n\n\t Press any key to go back");
			getchar();
			break;
		}
		else if(trav->next == NULL){
			printf("\n\n\t Sorry PNR doesn't Exist");
			fflush(stdin);
			getchar();
		}
		else{
			trav = trav->next;
		}
	}
}
void cancelTicket(){

}
void bookTicket(){
	system("cls");
	int flag = 0;
	struct FlightDetails *temp = NULL;
	struct Passengers* tempPass = (struct Passengers*)malloc(sizeof(struct Passengers));
	temp = (struct FlightDetails*)malloc(sizeof(struct FlightDetails));
	temp = Head->next;
	// This loop will book the ticket and decrease the seat number  of that flight
	while(temp != NULL){
		if(strcmp(temp->number , flightNumber ) == 0){
			traveller = (struct Passengers*)malloc(sizeof(struct Passengers));
			printf("\n\n\t\t Please Enter Your Name: ");
			gets(traveller->name);
			RandPNR = RandPNR + rand();			//generating random PNR number
			traveller->PNR = RandPNR;
			traveller->flight = temp;
			traveller->price  =  temp->price;
			if(payment() == 1){
			system("cls");
			// Decreasing the seats for that particular flight

			if(strcmp(temp->name, "Indigo") == 0 ){
				Indigo->seats--;
			}
			if(strcmp(temp->name, "Jet Airways") == 0 ){
				JetAir->seats--;
			}
			if(strcmp(temp->name, "Air India") == 0 ){
				AirInd->seats--;
			}
			if(strcmp(temp->name, "Vistara") == 0 ){
				Vistara->seats--;
			}
			//
			printf("\n\n\t Congratulations!, Your ticket has been booked ");
			printf("\n\n\t PNR number is\t\t: %d", traveller->PNR);
			printf("\n\n\t Name\t\t\t: %s", traveller->name);
			printf("\n\n\t Flight Name\t\t: %s", traveller->flight->name);
			printf("\n\n\t Flight Number\t\t: %s", traveller->flight->number);
			printf("\n\n\t Flight Departure\t: %d:%d", traveller->flight->time[0],traveller->flight->time[1]);
			printf("\n\n\t Flight Arrival\t\t: %d:%d", traveller->flight->time[2],traveller->flight->time[3]);
			printf("\n\n\t Flight Journey\t\t: %d:%d", traveller->flight->time[4],traveller->flight->time[5]);
			tempPass = PassHead->next;
			if(tempPass == NULL){
				PassHead->next = traveller;
				traveller->next = NULL;
			}else{
				while(tempPass != NULL){		// Linking current passenger to last passenger node
					if(tempPass->next == NULL){
						tempPass->next = traveller;
						traveller->next = NULL;
					}
					tempPass = tempPass->next;
				}
			}

				// Flushing and clearing the screen
				printf("\n\n\t Press any key to go back to main menu");
				fflush(stdin);
				getchar();
				break;
			}			//  Payment Check Ends here
			else{
				printf("\n\n\t Payment Unsuccessful");
				fflush(stdin);
				getchar();
			}
		}
		else{
			if(temp->next == NULL){
				flag = 1;
				break;
			}
			else{
				temp = temp->next;
			}
		}
	}
	if(flag == 1){
		printf("\n\n Invalid Flight Number");
		fflush(stdin);
		getchar();
		loadFlights();
	}
}
void loadFlights(){
	system("cls");		// Clear the screen
	struct FlightDetails* temp = NULL;
	temp = (struct FlightDetails*)malloc(sizeof(struct FlightDetails));
	temp = Head->next;
    printf("\n\t Showing Flights for : %d/%d/%d", date[0],date[1],tm.tm_year + 1900);
    printf("\n\n\t Flight Name\t\t Flight Number \t\t Seats Available ");
    printf("\t\t Departure \t\t Arrival \t\t Journey \t Price\n");
    while(temp != NULL){
        printf("\n\n\t %s \t\t %s \t\t %d", temp->name, temp->number, temp->seats);
        printf("\t\t\t\t %d:%d \t\t\t %d:%d \t\t\t %d:%d \t\t%d",
        		temp->time[0],temp->time[1],
        		temp->time[2],temp->time[3],
				temp->time[4],temp->time[5],
				temp->price);
        temp = temp->next;
    }
	fflush(stdin);
	printf("\n\n\t Enter the Flight Number you want to book:");
	//scanf("%s",&flightNumber);
	gets(flightNumber);
	bookTicket() ;
	//getchar();
}

int payment(){
	system("cls");
	int lv_payment = 0;
	int lv_cardNumber = 0;
	int lv_cardDate = 0;
	int lv_cvv = 0;
	int lv_custNumber = 0;
	int lv_password = 0;
	int lv_UPI = 0;
	printf("\n\n\t ________ Payment Gateway_____");
	printf("\n\n\t 1. Credit/Debit Card");
	printf("\n\n\t 2. Net Banking");
	printf("\n\n\t 3. UPI ID");
	printf("\n\n\t Choose Payment Method: ");
	scanf("%d",&lv_payment);
	if(lv_payment == 1){
		printf("\n\n\t Enter Credit/Debit Card Number: ");
		scanf("%d",&lv_cardNumber);
		printf("\n\n\t Expiry Date\t: ");
		scanf("%d",&lv_cardDate);
		printf("\n\n\t CVV:");
		scanf("%d",&lv_cvv);
		return 1;
	}
	else if(lv_payment == 2){
		printf("\n\n\t Enter Your Customer Number: ");
		scanf("%d",&lv_custNumber);
		printf("\n\n\t Password: ");
		scanf("%d",&lv_password);
		return 1;
	}
	else if(lv_payment == 3){
		printf("\n\n\t Enter UPI ID: ");
		scanf("%d",&lv_UPI);
		printf("\n\n\t PIN: ");
		scanf("%d",&lv_password);
		return 1;
	}
	else{
		printf("\n\n\t Invalid Choice");
		fflush(stdin);
		getchar();
		return payment();
	}
return 0;
}





