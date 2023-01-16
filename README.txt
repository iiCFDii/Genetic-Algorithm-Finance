README

** 
Author - Chris Ciobanu
Professor Chadi
Comp 151 Artificial Intelligence 
9/26/21

Project 2 - Genetic Algorithms
**

--  This program was written in C++. I used visual studio as a compiler. 
--  Make sure when entering the txt file, you enter it with the .txt extention
	Exmaple: 	genAlgData1.txt
--  Make sure the file for the txt data is in the same folder as the program solution. 

-- Using each parameter is as simple as reading the instructions in the GUI when running the program.
-- Modify each paramter by selecting a number from the menu and entering a value. The program only takes numerical values,
   unless you want to run the simulation at which point you would hit "r". 

-- You can go back and change any paramter before you run the simulation. 
-- By default the paramters are initilized to default values so you can run the program without changing any of the
   parameters if you wanted to. 


I found the best paramters to set to get the best results is to use at least 50 chromosomes in a population, and run the 
simulation at least 50 times. Use an Elitiest selection (0) and form 50% of the next population using this selection.

I used a fixed mutation rate of 10. 

I found this combo of paramters yielded fitness scores that increased significantly every 10 generations. 