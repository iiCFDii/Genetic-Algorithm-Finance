/*
Christopher Ciobanu
Professor Chadi
Comp 151 Artificial Intelligence 
9/26/21

Project 2 - Genetic Algorithms

***** Make sure to expand the window to see all comments, some are pushed back to look neater*****
*/

#include <iostream>			//	|
#include <string>			//	|
#include <limits>			//	| 	All the libraries needed for the program to work.
#include <iomanip>			//	|	
#include <windows.h>		//	|
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>
#include <ctime>

using namespace std;


double random() {		// this function provides the random numbers from a normal distribution with a mean of 0 and a standard deviation of 1.15
	double random;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	normal_distribution<double> distribution(0.0,1.15);

	random = distribution(generator);

	return random;

}

int random50() {		// this function provides a random number between 0 and 1 with a 50/50 chance
	double random1 = 0;
	int random2 = 0;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<double> distribution(0.0, 1.0);

	random1 = distribution(generator);
	if (random1 > 0.5) {
		random2 = 1;
	}
	else {
		random2 = 0;
	}
	return random2;
}

int trueRandom(int range) {		// this functions returns a random number within the range of the new population size for th tournament selection
	int num = 0;
	srand(time(NULL));
	if (range != 0) {
	num = rand() % range;
}
	else {
		num = 0;
	}
	return num;

}

float randomZ(float Z) {		// this function provides the Z% probablity functionality for mutations
	int num = 0;
	int num1 = 0;
	srand(time(NULL));
	num = 1 + (rand() % 100);
	if (num <= Z) {
		num1 = 1;
	}
	else {
		num1 = 0;
	}

	return num1;


}

class chromosome {		// this class defines my chromosome

private: 
	float pRange1;		// these variables are all the genes the chromosome needs
	float pRange2;
	float pChange1;
	float pChange2;
	int buy;
	vector <chromosome> ChromosomeV;		// this vector stores my chormosome population
	float fitness;
	vector <chromosome> firstH;		// this vector stores the next population

public: 

	chromosome()		// initilaizes class
	{
		pRange1 = 0;
		pRange2 = 0;
		pChange1 = 0;
		pChange2 = 0;
		buy = 0;
		fitness = 0;
	}

	chromosome(float range1, float range2, float change1, float change2, int buy1, float fitness1)        //  |    This allows the variables to be updated.
	{
		pRange1 = range1;
		pRange2 = range2;
		pChange1 = change1;
		pChange2 = change2;
		buy = buy1;
		fitness = fitness1;
	}

	void setRange1(float range1) { pRange1 = range1; }     //  |   these functions allow me to call and change the chomrosome defintions
	void setRange2(float range2) { pRange2 = range2; }         
	void setChange1(float change1) { pChange1 = change1; }
	void setChange2(float change2) { pChange2 = change2; }
	void setBuy(int buy1) { buy = buy1; }
	void setFit(float fitness1) { fitness = fitness1; }

	float getRange1() { return pRange1; }
	float getRange2() { return pRange2; }
	float getChange1() { return pChange1; }
	float getChange2() { return pChange2; }
	int getBuy() { return buy; }
	float getFit() { return fitness; }

	void createGene() {								// this functions creates a chromosome with all of its genes
		float test1, test2, test3, test4, temp;

		test1 = random();
		test2 = random();

		if (test2 < test1) {
			temp = test1;
			test1 = test2;
			test2 = temp;
		}

		test3 = random();
		test4 = random();

		if (test4 < test3) {
			temp = test3;
			test3 = test4;
			test4 = temp;
		}


		setRange1(test1);
		setRange2(test2);
		setChange1(test3);
		setChange2(test4);
		setBuy(random50());
		setFit(0);

	}

	template <typename T>												//	|	Since this function will be used by a two different kinds of classes, I made it arbitrary so it could be used by both
	int accountPartiton(vector <T>& cityVec, int i, int k) {			//	| This is the account parition, which is used in the quick sort algorithm for the account vector
		int l = 0;														//	| 
		int h = 0;
		int  midpoint = 0;
		T pivot;
		T temp;
		bool done = false;
		midpoint = i + (k - i) / 2;
		pivot = cityVec[midpoint];
		l = i;
		h = k;
		while (!done) {

			while (cityVec[l].getFit() < pivot.getFit())
			{
				++l;
			}
			while (pivot.getFit() < cityVec[h].getFit())
			{
				--h;
			}
			if (l >= h)
			{
				done = true;
			}
			else {
				temp = cityVec[l];
				cityVec[l] = cityVec[h];
				cityVec[h] = temp;
				++l;
				--h;
			}
		}
		return h;
	}


	template <typename T>
	void accQuickSort(vector <T>& cityVec, int l, int u) {		//	| This uses the accountPartition above to actually sort the vector from smallest fitness to largest fitness.
		int j = 0;
		if (l >= u)
		{
			return;
		}
		j = accountPartiton(cityVec, l, u);
		accQuickSort(cityVec, l, j);
		accQuickSort(cityVec, j + 1, u);
	}

void run(int ChromeNum1, int genNum1, int algSelect1, int percentSelect1, int crossSelect1, int muteChoice1, int initmutationRate1, int muteRateDec1, int muteFixed1, vector<float> vec11, vector<float> vec22, vector<float> vec33) { // this functions actually creates and stores all the chromosomes into the vector and displays the inital population

	chromosome gene;
	const char separator = ' ';
	const int nameWidth = 6;
	const int numWidth = 8;

		for (int i = 0; i < ChromeNum1; i++) {		// itteraties through and creates chromeNum1 number of chomrosomes
			gene.createGene();
			ChromosomeV.push_back(gene);
		}

		cout << "Displaying Chromosomes of initial Population: " << endl;
		for (int i = 0; i < ChromeNum1; i++) {
			cout <<  "Chromosome " << i + 1 << ":  |" << left << setw(nameWidth) << setfill(separator) << fixed << setprecision(2) << ChromosomeV[i].getRange1() << "  |  " << left << setw(nameWidth) << setfill(separator) << fixed << setprecision(2) << ChromosomeV[i].getRange2() << "  |  " << left << setw(nameWidth) << setfill(separator) << fixed << setprecision(2) << ChromosomeV[i].getChange1() << "  |  " << left << setw(nameWidth) << setfill(separator) << fixed << setprecision(2) << ChromosomeV[i].getChange2() << "  |  " << left << setw(nameWidth) << setfill(separator) << ChromosomeV[i].getBuy() << "  |  " << endl;
		}
	}



void fit(vector<float> vec11, vector<float> vec22, vector<float> vec33, int counter1, int track1) {		// this functions calculates fitness of chromosomes
	vector <int> check1;
	vector <int> check2;

	int check3 = 0;
	int temp = 0;
	float temp2 = 0.0;


	for (float i = 0; i < ChromosomeV.size() ; i++) {
		for (int j = 0; j < vec11.size(); j++) {
			if ((ChromosomeV[i].getRange1() < vec11[j]) && (ChromosomeV[i].getRange2() > vec11[j]) && (ChromosomeV[i].getChange1() < vec22[j]) && (ChromosomeV[i].getChange2() > vec22[j])) {

				if (ChromosomeV[i].getBuy() == 1) {
					temp2 = ChromosomeV[i].getFit() + vec33[j];
					ChromosomeV[i].setFit(temp2);
				}
				else if (ChromosomeV[i].getBuy() == 0) {
					ChromosomeV[i].setFit(ChromosomeV[i].getFit() + (vec33[j] * -1));
				}
			}
			else {
				ChromosomeV[i].setFit(ChromosomeV[i].getFit() + 0);
			}
		}
	}

	for (int i = 0; i < ChromosomeV.size(); i++) {
		if (ChromosomeV[i].getFit() == 0) {
			ChromosomeV[i].setFit(-5000);
		}
	}
	accQuickSort(ChromosomeV, 0, ChromosomeV.size() - 1);		// sorts based off of fitness
	

	float average = 0;
	float average1;		
	for (int i = 0; i < ChromosomeV.size(); i++) {		// calcualtes average fitness
		average = average + ChromosomeV[i].getFit();
	}
	average1 = average / ChromosomeV.size();
	if (counter1 == 1 || counter1 % 10 == 0) {
		cout << "Displaying Fitness Stats of Generation " << counter1  << endl;
		cout << "Max: " << ChromosomeV.back().getFit() << endl;
		cout << "Min: " << ChromosomeV.front().getFit() << endl;
		cout << "Average: " << average1 << endl; 
	}

	}
void getMax() {				// gets the max fitness out of the population
	const char separator = ' ';
	const int nameWidth = 6;
	const int numWidth = 8;
	cout << "Best Chromosome:	| "  << left << setw(nameWidth) << setfill(separator) << fixed << setprecision(2) << ChromosomeV.back().getRange1() << "  |  " << left << setw(nameWidth) << setfill(separator) << fixed << setprecision(2) << ChromosomeV.back().getRange2() << "  |  " << left << setw(nameWidth) << setfill(separator) << fixed << setprecision(2) << ChromosomeV.back().getChange1() << "  |  " << left << setw(nameWidth) << setfill(separator) << fixed << setprecision(2) << ChromosomeV.back().getChange2() << "  |  " << left << setw(nameWidth) << setfill(separator) << ChromosomeV.back().getBuy() << "  |  " << endl;

}



int selection(int algSelect1, float percentSelect1) {		// performs the selection function
	int newPop = 0;
	float ran1;
	float ran2;
	firstH.clear();		// clears old child population
	int temp1, temp2;

	newPop = (percentSelect1 / 100.0) * ChromosomeV.size();		// defines the amount of chomrosomes to be selected
	if (percentSelect1 != 0) {
		if (algSelect1 == 0) { //performs elitist selection

			
			//newPop = ChromosomeV.size() - percentSelect1;
			for (int i = ChromosomeV.size() - 1; i >= newPop; i--) {
				firstH.push_back(ChromosomeV[i]);		// takes newPop number of chomrosomes from the sorted top and puts it into the new population vector
			}

		}
		else {		// performs tournament selection
			//newPop =  percentSelect1;
			for (int i = 0; i < newPop; i++) {
				temp1 = trueRandom(ChromosomeV.size() - 1);		
				temp2 = trueRandom(ChromosomeV.size() - 1);

				ran1 = ChromosomeV[temp1].getFit();
				ran2 = ChromosomeV[temp2].getFit();
				if (ran1 > ran2) {
					firstH.push_back(ChromosomeV[temp1]);
				}
				else {
					firstH.push_back(ChromosomeV[temp2]);
				}
			}
		}
	}
	//cout <<"Size of Child after Selection: " <<  firstH.size() << endl;
	return newPop;
}

void crossover(int crossSelect1, float percentSelect1, int newPop) {		// performs the cross over functions
	
	int Y;
	int temp1, temp2, temp3;
	float ran1;
	float ran2;
	float temp4;

	chromosome parent1;
	chromosome parent2;
	chromosome child;

	Y = ChromosomeV.size() - newPop;		// defines he number of remaining child population needed to be created
	//cout << "Y is " << Y << endl;
	//cout << "newpop is: " << newPop << endl;
	if (crossSelect1 == 0) {		//performs uniform corssover
		for (int i = 0; i < Y; i++) {
			temp1 = trueRandom(newPop);
			temp2 = trueRandom(newPop);

			parent1 = firstH[temp1];
			parent2 = firstH[temp2];


			temp3 = random50();	
			if (temp3 == 0) {									// all these if else statements care validates the new genes are within the right ranges
				child.setRange1(parent1.getRange1());
			}
			else {
				child.setRange1(parent2.getRange1());
			}



			temp3 = random50();
			if (temp3 == 0) {
				child.setRange2(parent1.getRange2());
			}
			else {
				child.setRange2(parent2.getRange2());
			}

			if (child.getRange2() < child.getRange1()) {
				temp4 = child.getRange1();
				child.setRange1(child.getRange2());
				child.setRange2(temp4);
			}
			

			temp3 = random50();
			if (temp3 == 0) {
				child.setChange1(parent1.getChange1());
			}
			else {
				child.setChange1(parent2.getChange1());
			}


			temp3 = random50();
			if (temp3 == 0) {
				child.setChange1(parent1.getChange2());
			}
			else {
				child.setChange1(parent2.getChange2());
			}

			if (child.getChange2() < child.getChange1()) {
				temp4 = child.getChange1();
				child.setChange1(child.getChange2());
				child.setChange2(temp4);
			}

			temp3 = random50();
			if (temp3 == 0) {
				child.setBuy(parent1.getBuy());
			}
			else {
				child.setBuy(parent2.getBuy());
			}

			firstH.push_back(child);
		}
	}
	else {				// performs k point selection
		for (int i = 0; i < Y; i++) {
			temp1 = trueRandom(newPop);
			temp2 = trueRandom(newPop);

			parent1 = firstH[temp1];
			parent2 = firstH[temp2];

			child.setRange1(parent1.getRange1());
			child.setRange2(parent1.getRange2());
			child.setChange1(parent2.getChange1());
			child.setChange2(parent2.getChange2());
			child.setBuy(parent2.getBuy());

			firstH.push_back(child);
		}
	}

}

void mutation(int muteChoice1, int muteFixed1,float initmutationRate1,float muteRateDec1) {		// mutation function
	float temp;
	float num;
	//cout <<endl  << "Size of child after cross over: " <<  firstH.size() << endl;

	if (muteChoice1 == 0) {
		for (int i = 0; i < firstH.size(); i++) {			
			if (randomZ(muteFixed1) == 1) {
				firstH[i].setRange1(random());
			}
			if (randomZ(muteFixed1) == 1) {
				firstH[i].setRange2(random());
			}
			if (randomZ(muteFixed1) == 1) {
				firstH[i].setChange1(random());
			}
			if (randomZ(muteFixed1) == 1) {
				firstH[i].setChange2(random());
			}
			if (randomZ(muteFixed1) == 1) {
				firstH[i].setBuy(random());
			}

			if (firstH[i].getRange2() < firstH[i].getRange1()) {
				temp = firstH[i].getRange1();
				firstH[i].setRange1(firstH[i].getRange2());
				firstH[i].setRange2(temp);
			}

			if (firstH[i].getChange2() < firstH[i].getChange1()) {
				temp = firstH[i].getChange1();
				firstH[i].setChange1(firstH[i].getChange2());
				firstH[i].setChange2(temp);
			}

		}
	}
	else {		// iterates though each gene and triggers a Z% probability a mutation occurs

		for (int i = 0; i < firstH.size(); i++) {
			if (randomZ(initmutationRate1) == 1) {
				firstH[i].setRange1(random());
			}
			if (randomZ(initmutationRate1) == 1) {
				firstH[i].setRange2(random());
			}
			if (randomZ(initmutationRate1) == 1) {
				firstH[i].setChange1(random());
			}
			if (randomZ(initmutationRate1) == 1) {
				firstH[i].setChange2(random());
			}
			if (randomZ(initmutationRate1) == 1) {
				firstH[i].setBuy(random());
			}

			if (firstH[i].getRange2() < firstH[i].getRange1()) {
				temp = firstH[i].getRange1();
				firstH[i].setRange1(firstH[i].getRange2());
				firstH[i].setRange2(temp);
			}

			if (firstH[i].getChange2() < firstH[i].getChange1()) {
				temp = firstH[i].getChange1();
				firstH[i].setChange1(firstH[i].getChange2());
				firstH[i].setChange2(temp);
			}

		}

		initmutationRate1 = (muteRateDec1 / 100.0) * initmutationRate1;

	}
}

void transfer() {		// this transfers the new population into the original chromosome vector so that the process can start all over for the next generation
	ChromosomeV.clear();		// clears old generation
	for (int i = 0; i < firstH.size(); i++) {
		ChromosomeV.push_back(firstH[i]);		// fills new generation
	}

}



};








void error() {		// functions used for input error checking in menus
	cout << "Error! Bad input! Please Try again!: " << endl;
	cin.clear();
	cin.ignore(128, '\n');
}

char menu() {				// functions that displays menu choices
	char choice;
	cout << endl << "This menu allows the User to set the parameters for the Genetic Algorithm" << endl << endl;
	cout << "1. Number of Chromosomes in Each Generation" << endl;
	cout << "2. Number of Generations before Termination" << endl;
	cout << "3. Elitist or Tournament selection Algorithm" << endl;
	cout << "4. Percentage of Next Generation to be formed using selection" << endl;
	cout << "5. Uniform or kpoint Crossover Algorithm" << endl;
	cout << "6. Mutation Rate Parameters" << endl;
	cout << "R. Run the program" << endl << endl;
	cout << "If a parameter is not set, a default value will be Selected!" << endl << endl;
	cout << "Enter the Parameter(number) you would like to Adjust: " << endl;
	cin >> choice;

	while (cin.fail() || ((choice != '1') && (choice != '2') && (choice != '3')&& (choice != '4')&& (choice != '5') && (choice != '6') && (choice != 'R') && (choice != 'r')))
	{
		error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
		cin >> choice;
	}

	return choice;
}






int main()					//	|  Main functions that ties together all the headers and functions
{
	string filename;
	int ChromeNum = 50;
	int genNum = 50;
	int algSelect = 0;
	float percentSelect = 40;
	int crossSelect = 0;
	int muteChoice = 0;
	float initmutationRate = 50;
	float muteRateDec = 10;
	int muteFixed = 50;
	int counter = 0;
	int track = 0;
	int newPop= 0;

	vector<float> vec1, vec2, vec3;		// vectors to store data from txt file
	float x, y, z;
	
	char choice = 'N';

	chromosome get;
	
	cout << "Welcome to the Genetic Algorithm Program" << endl << "This program was created by Christopher Ciobanu, for Comp 151." << endl << "Click any button to begin!" << endl << endl;
	system("pause");

	ifstream myfile;
	do {		// code that makes sure correct file is being opened
	cout << "Please Enter the filename containing the training data: " << endl;
	cin >> filename;
	cin.clear();
	cin.ignore(128, '\n');
	myfile.open(filename);
		
	if (!myfile) {
		cout << "Unable to open file!" << endl;
	}
			
	} while (!myfile);

	cout << "Reading in File Data!" << endl;
			
	while (myfile >> x >> y >> z) {		// reads in txt data and stores in vectors
		vec1.push_back(x);
		vec2.push_back(y);
		vec3.push_back(z);
	}


	do {		// main do loop that calls the functions
		choice = menu();
		switch (choice) {

		case '1':
			cout << "Please enter the number of chromosomes you would like in each generation: " << endl;
			cin >> ChromeNum;

			while (cin.fail())
			{
				error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
				cin >> ChromeNum;
			}

			break;

		case '2':
			cout << "Please enter the Number of Generations before the program Terminates: " << endl;
			cin >> genNum;

			while (cin.fail())
			{
				error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
				cin >> genNum;
			}

			break;

		case '3':
			cout << "Please enter a selection algorithm Elitist (0) or Torunament (1): " << endl;
			cin >> algSelect;

			while (cin.fail())
			{
				error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
				cin >> algSelect;
			}


			break;

		case '4':
			cout << "Please enter the Percentage of Next Generation to be formed using selection: " << endl;
			cin >> percentSelect;

			while (cin.fail())
			{
				error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
				cin >> percentSelect;
			}

			break;

		case '5':
			cout << "Please enter the crossover algorithm, Uniform (0) or kpoint (1): " << endl;
			cin >> crossSelect;

			while (cin.fail())
			{
				error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
				cin >> crossSelect;
			}

			break;

		case '6':
			cout << "Would you like a fixed mutation rate (0) or a gradual one (1): " << endl;
			cin >> muteChoice;

			while (cin.fail())
			{
				error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
				cin >> muteChoice;
			}

			if (muteChoice == 0) {
				cout << "What would you like the fixed mutation rate to be: " << endl;
				cin >> muteFixed;

				while (cin.fail())
				{
					error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
					cin >> muteFixed;
				}

			}
			else {
				cout << "Please enter the initial mutation rate: " << endl;
				cin >> initmutationRate;

				while (cin.fail())
				{
					error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
					cin >> initmutationRate;
				}
				cout << "Please enter the how much to change the mutation rate each generation: " << endl;
				cin >> muteRateDec;

				while (cin.fail())
				{
					error();				//	|  This sections validates the users input, and if the user inputs an incorrect menu choice, then they are prompted as such.
					cin >> muteRateDec;
				}
			}
			break;

		case 'R': case 'r':		// runs the program and calls all the functions
			counter = 1;
			get.run(ChromeNum, genNum, algSelect, percentSelect, crossSelect, muteChoice, initmutationRate, muteRateDec, muteFixed, vec1, vec2, vec3);
			get.fit(vec1, vec2, vec3, counter, track);

			while(genNum != 0 ){		// runs through until user defined generation stopage
			newPop = get.selection(algSelect, percentSelect);
			get.crossover(crossSelect, percentSelect, newPop);
			get.mutation(muteChoice, muteFixed, initmutationRate, muteRateDec);
			initmutationRate = (muteRateDec / 100.0) * initmutationRate;
			get.transfer();
			counter++;
			get.fit(vec1, vec2, vec3, counter, track);
			genNum--;
		}
			get.getMax();		// after simulation is done being run, the max chromosome is retrieved
			break;

		default:

			break;

		}
	} while (!(choice == 'R' || choice == 'r'));






	myfile.close();			// closes txt file
	system("Pause");		//	| Pauses the console
	return 0;				//	| Tells the program it can terminate.
}