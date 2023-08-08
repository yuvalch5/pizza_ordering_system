//***********************************//
//Student's name: Yuval Chait
//ID Number: 315232058
//***********************************//
//The program takes the user's details and preferences: id, number of pizzas required, pizza dimensions, dough type, toppings, delivery or pick up,
//Within certain limits and constraints. The program prints the details of each pizza, and prints a painting of each pizza.
//A recipt is printed with the details of the order: price with and without tax, id number, delivery/pick up.
//The programs asks for payment and returns change if needed.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

//defining constants
#define TAX_VALUE 0.17
#define BASIC_PIZZA_LENGTH 40
#define BASIC_PIZZA_WIDTH 50
#define BASIC_PIZZA_PRICE 70
#define OLIVES_PRICE 10
#define MUSHROOMS_PRICE 12
#define TOMATOES_PRICE 9
#define PINEAPPLE_PRICE 14
#define DELIVERY_PRICE 15
#define REGULAR_DOUGH 0
#define VEGAN_DOUGH 5 
#define WHOLE_WHEAT_DOUGH 3 
#define GLUTEN_FREE_DOUGH 4
#define PICK_UP_PRICE 0
#define NO_TOPPINGS 0
#define QUARTER_PIZZA_TOPPINGS 0.25
#define HALF_PIZZA_TOPPINGS 0.5
#define WHOLE_PIZZA_TOPPINGS 1


typedef struct Pizza {
	int length; // pizza length (cm)
	int width; // pizza width (cm)
	char doughType; // dough type ('r'/'v'/'w'/'f')
	double doughType_price;
	double olives; // olives amount (0/1/0.5/0.25)
	double olives_amount;
	double mushrooms; // mushrooms amount (0/1/0.5/0.25)
	double mushrooms_amount;
	double tomatoes; // tomatoes amount (0/1/0.5/0.25)
	double tomatoes_amount;
	double pineapple; // pineapple amount (0/1/0.5/0.25)
	double pineapple_amount;
	double overall_amount_toppings; // the surface of the pizza covered by toppings
	double respective_pizza_price;
	char q1; // topping type on first quarter ('O'/'M'/'T'/'P')
	char q2; // topping type on second quarter ('O'/'M'/'T'/'P')
	char q3; // topping type on third quarter ('O'/'M'/'T'/'P')
	char q4; // topping type on fourth quarter ('O'/'M'/'T'/'P')
	char doughTypeChoice;
	int delivery_price;
	int olives_for_picture, mushrooms_for_picture, tomatoes_for_picture, pineapple_for_picture;
	double price; // pizza price (without tax)
}PIZZA;


//Prints a welcome screen with a logo
void printWelcome()
{
	printf(" Welcome to MTA-Pizza!\n\n");
	printf("*****\n ***\n  *\n\n");
}

//Returns how many digits are in the id number the user typed 
int countDigits(int id_num)
{
	int counter = 0;

	while (id_num > 0)
	{
		id_num /= 10;
		counter++;
	}
	return counter;
}

//Taking each digit in the id (without the check digit), multiplies by 1 or 2 (based on were the digits appears in the id:
//last digit is multiplied by 2, the digit after the last is multiplied by 1, prepetually until all digits have been multiplied.
//Then each digit of the numbers created from this process is summed. The overall sum of all those digits is returned by the function.
int multThenSumCouplesOfDigits(int id_num)
{
	int i, j, digit1, digit2, mult_digit, count_digits, digit_for_sum = 0, sum = 0;
	
	id_num /= 10;

	count_digits = countDigits(id_num);


	if (count_digits % 2 == 0)
	{
		for (i = 1; i <= count_digits / 2; i++)
		{
			digit1 = id_num % 10;
			id_num /= 10;

			mult_digit = digit1 * 2;
			if (mult_digit >= 10)
			{
				digit_for_sum = mult_digit % 10;
				mult_digit /= 10;
				digit_for_sum += mult_digit;
			}
			else
			{
				digit_for_sum = mult_digit;
			}
			digit2 = id_num % 10;
			id_num /= 10;
			sum += digit_for_sum + digit2;
		}
		return sum;
	}
	else
	{
		for (i = 1; i <= (count_digits - 1) / 2; i++)
		{
			digit1 = id_num % 10;
			id_num /= 10;

			mult_digit = digit1 * 2;
			if (mult_digit >= 10)
			{
				digit_for_sum = mult_digit % 10;
				mult_digit /= 10;
				digit_for_sum += mult_digit;
			}
			else
			{
				digit_for_sum = mult_digit;
			}
			digit2 = id_num % 10;
			id_num /= 10;
			sum += digit_for_sum + digit2;
		}

		id_num *= 2;

		if (id_num >= 10)
		{
			digit_for_sum = id_num % 10;
			id_num /= 10;
			digit_for_sum += id_num;
		}

		sum += id_num;

		return sum;

	}

	
}

//The function caculates the natural numbers that when this same number is added to the sum that "multThenSumCouplesOfDigits" function returns,
//the reulst is the closest multiple of ten. Then the function returns this number.
int getCheckDigit(int sum_digits)
{
	int check_digit, num_to_check;

	if (sum_digits < 10)
	{
		check_digit = 10 - sum_digits;
		return check_digit;
	}
	else
	{
		num_to_check = sum_digits % 10;
		check_digit = 10 - num_to_check;
		return check_digit;
	}
}

//Takes the check digit the user typed. Compares it to the check digit that was returned from "getCheckDigit" function.
//Returns "true" if they are the same. If not, returns "false".
bool isCheckDigitValid(int valid_check_digit, int id_num)
{
	int user_check_digit;

	user_check_digit = id_num % 10;

	return valid_check_digit == user_check_digit;
}

//Mendatory function.
//Gets the id number from the user and returns it.
int getIDNumber()
{
	int id, digits_count;

	printf("Please enter your ID number:");
	scanf("%d", &id);

	digits_count = countDigits(id);

	while (digits_count > 9 || id == 0)
	{
		printf("\nInvalid ID number! Try again. ");
		printf("\nPlease enter your ID number:");
		scanf(" %d", &id);
		digits_count = countDigits(id);
	}

	return id;
}


//Mendatory function.
//Prints to the screen the menu.
void printMenu()
{
	printf("\nOur menu:\n*********\n");
	printf("Basic pizza: 70.00 NIS for 40x50 size pizza\n");
	printf("Toppings for basic size pizza:\n");
	printf("Olives: 10 NIS\nMushrooms: 12 NIS\nTomatoes: 9 NIS\nPineapple: 14 NIS\n\n");
	printf("Dough type for basic size pizza:\nRegular: 0 NIS\nVegan: 5 NIS\nWhole wheat: 3 NIS\nGluten free: 4 NIS\n\n");
}

//Mendatory function.
//Gets the desired number of pizza from the user and returns it.
int getNumOfPizzas()
{
	int num_of_pizzas;

	printf("\nHow many pizzas would you like to order? ");
	scanf("%d", &num_of_pizzas);

	while (num_of_pizzas <= 0)
	{
		printf("\nInvalid choice! Try again. ");
		printf("\nHow many pizzas would you like to order? ");
		scanf("%d", &num_of_pizzas);
	}

	return num_of_pizzas;
}

//Mendatory function.
//Gets the desired pizza dimensions from the customers within certain limits ands constraints. 
//The function also calculates the price of the pizza (without dough type and toppings) based on the selected dimensions.
//Returns the pizza struct.
PIZZA getPizzaDimensions()
{
	PIZZA pizza;

	printf("\nPlease enter your pizza's length (cm):");
	scanf("%d", &pizza.length);

	while (pizza.length < 10 || pizza.length > 40 || pizza.length % 2 != 0)
	{
		printf(" Invalid length! Try again.");
		printf("\nPlease enter your pizza's length (cm):");
		scanf("%d", &pizza.length);
	}


	printf(" Please enter your pizza's width (cm):");
	scanf("%d", &pizza.width);
	while (pizza.width < 10 || pizza.width > 80 || pizza.width % 2 != 0)
	{
		printf(" Invalid width! Try again.");
		printf("\nPlease enter your pizza's width (cm): ");
		scanf("%d", &pizza.width);
	}
	pizza.price = ((pizza.length * pizza.width) / (double)(BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * BASIC_PIZZA_PRICE;
	return pizza;
}

//Mendatory function.
//Takes the user's preferences for dough type. Calculates the price of the dough type and adds it to the pizza price.
//Returns the pizza struct.
PIZZA getDoughType(PIZZA pizza)
{
	bool isDoughTypeOver = false;

	while (isDoughTypeOver == false)
	{
		printf("\n\nPlease enter the pizza's dough type:\nr - for regular\nv - for vegan\nw - for whole wheat\nf - for gluten-free\n");
		scanf(" %c", &pizza.doughTypeChoice);

		switch (pizza.doughTypeChoice)
		{
		case 'r':
			isDoughTypeOver = true;
			pizza.price += ((double)(pizza.length * pizza.width) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * REGULAR_DOUGH;
			break;
		case 'v':
			isDoughTypeOver = true;
			pizza.price += ((double)(pizza.length * pizza.width) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * VEGAN_DOUGH;
			break;
		case 'w':
			isDoughTypeOver = true;
			pizza.price += ((double)(pizza.length * pizza.width) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * WHOLE_WHEAT_DOUGH;
			break;
		case 'f':
			isDoughTypeOver = true;
			pizza.price += ((double)(pizza.length * pizza.width) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * GLUTEN_FREE_DOUGH;
			break;
		default:
			printf("\nInvalid choice! Try again.");
			break;
		}
	}
	return pizza;
}

//************************************************//
//The next four functions get the user's preferences get the user's preferences for toppings,
//within certain limits ands constraints.

PIZZA getOlives(PIZZA pizza)
{
	char olives_choice;
	bool isOlivesDone = false;

	printf("\n\nOlives (choose 0-3):\n");

	while (isOlivesDone == false)
	{
		printf("\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
		scanf(" %c", &olives_choice);

		switch (olives_choice)
		{
		case '0':
			isOlivesDone = true;
			pizza.olives = (((pizza.length * pizza.width) * NO_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * OLIVES_PRICE;
			pizza.olives_amount = 0;
			pizza.olives_for_picture = 0;
			break;
		case '1':
			isOlivesDone = true;
			pizza.olives = (((pizza.length * pizza.width) * (float)WHOLE_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * OLIVES_PRICE;
			pizza.olives_amount = 1;
			pizza.olives_for_picture = 4;
			break;
		case '2':
			isOlivesDone = true;
			pizza.olives = (((pizza.length * pizza.width) * HALF_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * OLIVES_PRICE;
			pizza.olives_amount = 0.5;
			pizza.olives_for_picture = 2;
			break;
		case '3':
			isOlivesDone = true;
			pizza.olives = (((pizza.length * pizza.width) * QUARTER_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * OLIVES_PRICE;
			pizza.olives_amount = 0.25;
			pizza.olives_for_picture = 1;
			break;
		default:
			printf("\nInvalid choice! Try again.");
			break;
		}
	}

	pizza.overall_amount_toppings = pizza.olives_amount;
	return pizza;
}

PIZZA getMushrooms(PIZZA pizza)
{
	char mushrooms_choice;
	bool isMushroomsDone = false;

	printf("\n\nMushrooms (choose 0-3):\n");

	while (isMushroomsDone == false)
	{
		printf("\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
		scanf(" %c", &mushrooms_choice);

		switch (mushrooms_choice)
		{
		case '0':
			isMushroomsDone = true;
			pizza.mushrooms = (((pizza.length * pizza.width) * NO_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * MUSHROOMS_PRICE;
			pizza.mushrooms_amount = 0;
			pizza.mushrooms_for_picture = 0;
			break;
		case '1':
			pizza.mushrooms_amount = 1;
			if (pizza.mushrooms_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isMushroomsDone = true;
				pizza.mushrooms = (((pizza.length * pizza.width) * (double)WHOLE_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * MUSHROOMS_PRICE;
				pizza.mushrooms_for_picture = 4;
				break;
			}
		case '2':
			pizza.mushrooms_amount = 0.5;
			if (pizza.mushrooms_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isMushroomsDone = true;
				pizza.mushrooms = (((pizza.length * pizza.width) * HALF_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * MUSHROOMS_PRICE;
				pizza.mushrooms_for_picture = 2;
				break;
			}
		case '3':
			pizza.mushrooms_amount = 0.25;
			if (pizza.mushrooms_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isMushroomsDone = true;
				pizza.mushrooms = (((pizza.length * pizza.width) * QUARTER_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * MUSHROOMS_PRICE;
				pizza.mushrooms_for_picture = 1;
				break;
			}
		default:
			printf("\nInvalid choice! Try again.");
			break;
		}
	}
	pizza.overall_amount_toppings += pizza.mushrooms_amount;
	return pizza;
}

PIZZA getTomatoes(PIZZA pizza)
{
	char tomatoes_choice;
	bool isTomatoesDone = false;

	printf("\n\nTomatos (choose 0-3):\n");

	while (isTomatoesDone == false)
	{
		printf("\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
		scanf(" %c", &tomatoes_choice);

		switch (tomatoes_choice)
		{
		case '0':
			isTomatoesDone = true;
			pizza.tomatoes = (((pizza.length * pizza.width) * NO_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * TOMATOES_PRICE;
			pizza.tomatoes_amount = 0;
			pizza.tomatoes_for_picture = 0;
			break;
		case '1':
			pizza.tomatoes_amount = 1;
			if (pizza.tomatoes_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isTomatoesDone = true;
				pizza.tomatoes = (((pizza.length * pizza.width) * (double)WHOLE_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * TOMATOES_PRICE;
				pizza.tomatoes_for_picture = 4;
				break;
			}
		case '2':
			pizza.tomatoes_amount = 0.5;
			if (pizza.tomatoes_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isTomatoesDone = true;
				pizza.tomatoes = (((pizza.length * pizza.width) * HALF_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * TOMATOES_PRICE;
				pizza.tomatoes_for_picture = 2;
				break;
			}
		case '3':
			pizza.tomatoes_amount = 0.25;
			if (pizza.tomatoes_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isTomatoesDone = true;
				pizza.tomatoes = (((pizza.length * pizza.width) * QUARTER_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * TOMATOES_PRICE;
				pizza.tomatoes_for_picture = 1;
				break;
			}
		default:
			printf("\nInvalid choice! Try again.");
			break;
		}
	}
	pizza.overall_amount_toppings += pizza.tomatoes_amount;
	return pizza;
}

PIZZA getPineapple(PIZZA pizza)
{
	char pineapple_choice;
	bool isPineappleDone = false;

	printf("\n\nPineapple (choose 0-3):\n");

	while (isPineappleDone == false)
	{
		printf("\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
		scanf(" %c", &pineapple_choice);

		switch (pineapple_choice)
		{
		case '0':
			isPineappleDone = true;
			pizza.pineapple = (((pizza.length * pizza.width) * NO_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * PINEAPPLE_PRICE;
			pizza.pineapple_amount = 0;
			pizza.pineapple_for_picture = 0;
			break;
		case '1':
			pizza.pineapple_amount = 1;
			if (pizza.pineapple_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isPineappleDone = true;
				pizza.pineapple = (((pizza.length * pizza.width) * (double)WHOLE_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * PINEAPPLE_PRICE;
				pizza.pineapple_for_picture = 4;
				break;
			}
		case '2':
			pizza.pineapple_amount = 0.5;
			if (pizza.pineapple_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isPineappleDone = true;
				pizza.pineapple = (((pizza.length * pizza.width) * HALF_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * PINEAPPLE_PRICE;
				pizza.pineapple_for_picture = 2;
				break;
			}
		case '3':
			pizza.pineapple_amount = 0.25;
			if (pizza.pineapple_amount + pizza.overall_amount_toppings > 1)
			{
				printf("\nYou have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				break;
			}
			else
			{
				isPineappleDone = true;
				pizza.pineapple = (((pizza.length * pizza.width) * QUARTER_PIZZA_TOPPINGS) / (BASIC_PIZZA_LENGTH * BASIC_PIZZA_WIDTH)) * PINEAPPLE_PRICE;
				pizza.pineapple_for_picture = 1;
				break;
			}
		default:
			printf("\nInvalid choice! Try again.");
			break;
		}
	}
	pizza.overall_amount_toppings += pizza.pineapple_amount;
	return pizza;
}

//Mendatory function.
//Calculates the price of the toppings and adds it to the pizza price.
PIZZA getToppings(PIZZA pizza)
{
	printf("\n\nPlease choose the toppings:");

	pizza = getOlives(pizza);


	if (pizza.overall_amount_toppings >= 1)
	{
		pizza.price = pizza.price + pizza.olives;
		return pizza;
	}
	else
	{
		pizza = getMushrooms(pizza);
	}

	if (pizza.overall_amount_toppings >= 1)
	{
		pizza.price = pizza.price + pizza.olives + pizza.mushrooms;
		return pizza;
	}
	else
	{
		pizza = getTomatoes(pizza);
	}

	if (pizza.overall_amount_toppings >= 1)
	{
		pizza.price = pizza.price + pizza.olives + pizza.mushrooms + pizza.tomatoes;
		return pizza;
	}
	else
	{
		pizza = getPineapple(pizza);
	}

	pizza.price = pizza.price + pizza.olives + pizza.mushrooms + pizza.tomatoes + pizza.pineapple;

	return pizza;
}

//Mendatory function.
//Prints each individual pizza's details.
void printPizzaDetails(PIZZA pizza, int i)
{
	printf("\n\nPizza #%d details:\n", i);
	printf("*******************");
	printf("\nPizza size: %dx%d", pizza.length, pizza.width);
	printf("\nPizza price (without tax): %.2lf", pizza.price);
}

//Prints a line made of the character that represents the dough type the user chose.
//r - regular, v - vegan, w - whole wheat, f - glutten free.
void printLineOfDough(PIZZA pizza)
{
	int i, j;

	for (i = 0; i < pizza.width; i++)
	{
		printf("%c", pizza.doughTypeChoice);
	}
}


//Determins which toppings should be printed in each quarter of the pizza (for the printPizza function).
PIZZA toppingsForEachQuarter(PIZZA pizza)
{

	//What is q1
	if (pizza.olives_for_picture && pizza.mushrooms_for_picture && pizza.tomatoes_for_picture && pizza.pineapple_for_picture == 0);
	{
		pizza.q1 = ' ';
	}
	if (pizza.olives_for_picture > 0)
	{
		pizza.q1 = 'O';
		pizza.olives_for_picture--;
	}
	else if (pizza.mushrooms_for_picture > 0)
	{
		pizza.q1 = 'M';
		pizza.mushrooms_for_picture--;
	}
	else if (pizza.tomatoes_for_picture > 0)
	{
		pizza.q1 = 'T';
		pizza.tomatoes_for_picture--;
	}
	else if (pizza.pineapple_for_picture > 0)
	{
		pizza.q1 = 'P';
		pizza.pineapple_for_picture--;
	}

	//What is q2
	if (pizza.olives_for_picture && pizza.mushrooms_for_picture && pizza.tomatoes_for_picture && pizza.pineapple_for_picture == 0);
	{
		pizza.q2 = ' ';
	}
	if (pizza.olives_for_picture > 0)
	{
		pizza.q2 = 'O';
		pizza.olives_for_picture--;
	}
	else if (pizza.mushrooms_for_picture > 0)
	{
		pizza.q2 = 'M';
		pizza.mushrooms_for_picture--;
	}
	else if (pizza.tomatoes_for_picture > 0)
	{
		pizza.q2 = 'T';
		pizza.tomatoes_for_picture--;
	}
	else if (pizza.pineapple_for_picture > 0)
	{
		pizza.q2 = 'P';
		pizza.pineapple_for_picture--;
	}

	//What is q3
	if (pizza.olives_for_picture && pizza.mushrooms_for_picture && pizza.tomatoes_for_picture && pizza.pineapple_for_picture == 0);
	{
		pizza.q3 = ' ';
	}
	if (pizza.olives_for_picture > 0)
	{
		pizza.q3 = 'O';
		pizza.olives_for_picture--;
	}
	else if (pizza.mushrooms_for_picture > 0)
	{
		pizza.q3 = 'M';
		pizza.mushrooms_for_picture--;
	}
	else if (pizza.tomatoes_for_picture > 0)
	{
		pizza.q3 = 'T';
		pizza.tomatoes_for_picture--;
	}
	else if (pizza.pineapple_for_picture > 0)
	{
		pizza.q3 = 'P';
		pizza.pineapple_for_picture--;
	}

	//What is q4
	if (pizza.olives_for_picture && pizza.mushrooms_for_picture && pizza.tomatoes_for_picture && pizza.pineapple_for_picture == 0);
	{
		pizza.q4 = ' ';
	}
	if (pizza.olives_for_picture > 0)
	{
		pizza.q4 = 'O';
		pizza.olives_for_picture--;
	}
	else if (pizza.mushrooms_for_picture > 0)
	{
		pizza.q4 = 'M';
		pizza.mushrooms_for_picture--;
	}
	else if (pizza.tomatoes_for_picture > 0)
	{
		pizza.q4 = 'T';
		pizza.tomatoes_for_picture--;
	}
	else if (pizza.pineapple_for_picture > 0)
	{
		pizza.q4 = 'P';
		pizza.pineapple_for_picture--;
	}

	return pizza;
}

//Mendatroy function.
//Prints a painting of each pizza the user ordered.
void printPizza(PIZZA pizza)
{
	int i, j;


	printf("\n");

	printLineOfDough(pizza);

	printf("\n");



	for (j = 1; j <= ((pizza.length - 2) / 2); j++)
	{
		printf("%c", pizza.doughTypeChoice);
		for (i = 0; i < ((pizza.width - 2) / 2); i++)
		{
			printf("%c", pizza.q4);
		}
		for (i = ((pizza.width - 2) / 2); i < pizza.width - 2; i++)
		{
			printf("%c", pizza.q1);
		}
		printf("%c", pizza.doughTypeChoice);
		printf("\n");
	}

	for (j = (((pizza.length - 2) / 2) + 1); j <= pizza.length - 2; j++)
	{
		printf("%c", pizza.doughTypeChoice);
		for (i = 0; i < ((pizza.width - 2) / 2); i++)
		{
			printf("%c", pizza.q3);
		}
		for (i = ((pizza.width - 2) / 2); i < (pizza.width - 2); i++)
		{
			printf("%c", pizza.q2);
		}
		printf("%c", pizza.doughTypeChoice);
		printf("\n");
	}
	printLineOfDough(pizza);

}




//Mendatory function.
//Takes the users preferences for delivery.
int getDelivery()
{
	int isDelivery;
	bool isChoiceValid = false;

	while (isChoiceValid == false)
	{
		printf("\nDo you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
		scanf("%d", &isDelivery);
		if (isDelivery == 1)
		{
			return 1;
		}
		else if (isDelivery == 0)
		{
			return 0;
		}
		else
		{
			printf("Invalid choice! Try again.\n");
		}
	}
	return isDelivery;
}

//Prints the details of the user's order.
void printOrderDetails(int isDelivery, int id, int num_of_pizzas, double order_price, int order_price_with_tax)
{
	if (isDelivery == 0)
	{
		printf("\n\nYour order details:\n*******************\nID number: %09d\nNumber of pizzas: %d\nPick-up\nTotal price: %.2lf\nTotal price with tax (rounded down): %d", id,
			num_of_pizzas, order_price, (int)order_price_with_tax);
	}
	else if (isDelivery == 1)
	{
		printf("\n\nYour order details:\n*******************\nID number: %09d\nNumber of pizzas: %d\nDelivery\nTotal price: %.2lf\nTotal price with tax (rounded down): %d", id,
			num_of_pizzas, order_price, (int)order_price_with_tax);
	}

}

//Mendatory function.
//Asks for payment from the user. Keeps asking until the user meets the required amount. Gives change if needed, in the smallest amount of coins possible.
void getPayment(int totalPrice)
{
	int customer_payment, payment_remaining, change, amount_tens, amount_fives, amount_twos, amount_ones;
	bool isPaymentDone;

	printf("\n\nPlease enter your payment: ");
	scanf("%d", &customer_payment);

	payment_remaining = totalPrice - customer_payment;


	if (customer_payment == (int)totalPrice)
	{
		printf("\nThank you for your order!");
		return;
	}
	else if (customer_payment > (int)totalPrice)
	{
		payment_remaining = totalPrice;
		isPaymentDone = true;
	}
	else if (customer_payment < totalPrice)
	{
		isPaymentDone = false;
	}

	while (isPaymentDone == false)
	{
		if (payment_remaining == 0)
		{
			break;
		}
		else
		{
			printf("Your remaining balance is: %d", payment_remaining);
			printf("\nPlease enter your payment: ");
			scanf("%d", &customer_payment);

			if (customer_payment < payment_remaining)
			{
				payment_remaining -= customer_payment;
			}
			else if (customer_payment >= payment_remaining)
			{
				isPaymentDone = true;
			}
		}

	}

	if (payment_remaining == 0)
	{
		printf("\nThank you for your order!");
		return;
	}

	
	change = customer_payment - payment_remaining;

	if (change > 0)
	{
		printf("Your change is %d NIS using:", change);

		amount_tens = change / 10;
		change %= 10;
		amount_fives = change / 5;
		change %= 5;
		amount_twos = change / 2;
		change %= 2;
		amount_ones = change / 1;
		change %= 1;

		if (amount_tens > 0)
		{
			printf("\n%d coin(s) of ten\n", amount_tens);
		}
		if (amount_fives > 0)
		{
			printf("\n%d coin(s) of five\n", amount_fives);
		}
		if (amount_twos > 0)
		{
			printf("\n%d coin(s) of two\n", amount_twos);
		}
		if (amount_ones > 0)
		{
			printf("\n%d coin(s) of one\n", amount_ones);
		}
	}
	printf("Thank you for your order!");
	}




void main()
{
	int j, id, count, sum_of_id_digits, check_digit, valid_check_digit, num_of_pizzas, isDelivery, int_order_price_with_tax;
	int order_price_with_tax;
	double overall_amount_toppings;
	double order_price = 0;
	PIZZA pizza;


	printWelcome();

	id = getIDNumber();

	sum_of_id_digits = multThenSumCouplesOfDigits(id);

	check_digit = getCheckDigit(sum_of_id_digits);

	valid_check_digit = isCheckDigitValid(check_digit, id);

	//As long as the check digit the user enters is false, the program keeps asking for the user to type his id again.
	while (valid_check_digit == false)
	{
		printf("\nInvalid check digit! Try again. \n");

		id = getIDNumber();

		sum_of_id_digits = multThenSumCouplesOfDigits(id);

		check_digit = getCheckDigit(sum_of_id_digits);

		valid_check_digit = isCheckDigitValid(check_digit, id);
	}

	printMenu();

	num_of_pizzas = getNumOfPizzas();

	//Based on the value returned from "getNumOfPizzas" function, the program take the users preferences for the amount of pizzas they required.
	for (j = 1; j <= num_of_pizzas; j++)
	{
		printf("\n\n*************************************************");
		printf("\nPizza #%d:\n\n", j);
		pizza = getPizzaDimensions();

		pizza = getDoughType(pizza);

		pizza = getToppings(pizza);

		printPizzaDetails(pizza, j);

		pizza = toppingsForEachQuarter(pizza);

		printPizza(pizza);

		order_price += pizza.price;
	}

	printf("\n\n*************************************************");
	isDelivery = getDelivery();

	if (isDelivery == 0)
	{
		pizza.delivery_price = PICK_UP_PRICE;
	}
	else if (isDelivery == 1)
	{
		pizza.delivery_price = DELIVERY_PRICE;
	}

	order_price += pizza.delivery_price;

	order_price_with_tax = order_price + (order_price * TAX_VALUE);

	printOrderDetails(isDelivery, id, num_of_pizzas, order_price, order_price_with_tax);

	int_order_price_with_tax = (int)order_price_with_tax;

	getPayment(int_order_price_with_tax);

}
