#include "card.h"
#define _CRT_SECURE_NO_WARNINGS

int validMonth(int month) {
	int flagMONTH = 0;
	if (month > 12 || month < 1) {
		flagMONTH++;
	}
	return flagMONTH;
}

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("please enter the cardholder's fullname: ");
	gets_s(&(cardData->cardHolderName), 30);

	//condition to allow only letters and spaces 
	int flag = 0;
	for (int i = 0; i < strlen(cardData->cardHolderName) - 1;i++) {
		if (!((cardData->cardHolderName[i] >= 'a' && cardData->cardHolderName[i] <= 'z') || (cardData->cardHolderName[i] >= 'A' && cardData->cardHolderName[i] <= 'Z') || cardData->cardHolderName[i] == ' ')) {
			flag++;
		}
		continue;
	}
	if (flag != 0) {
		printf("u can only enter letters\n");
		return WRONG_NAME;
	}
	else if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
		return WRONG_NAME;

	else {
		//	printf("*******************\n");
		//	printf("this cardholder's name is: %s \n", cardData->cardHolderName);
		return CARD_OK;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("please enter the card expiry date in this format\"MM/YY\": ");
	gets_s(&(cardData->cardExpirationDate), 10);

	int month = ((cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0'));

	if ((strlen(cardData->cardExpirationDate) != 5)) {
		printf("wrong expiry date\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != '/')
	{
		printf("wrong expiry date\n");
		return WRONG_EXP_DATE;
	}
	else if (validMonth(month))
	{
		printf("wrong expiry date\n");
		return WRONG_EXP_DATE;
	}
	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("please enter the card's Primary Account Number(PAN): ");
	gets_s(&(cardData->primaryAccountNumber), 21);

	//condition 34an myd5l4 7aga 8er numbers; no letters no symbols
	int flagPAN = 0;
	for (int i = 0; i < strlen(cardData->primaryAccountNumber) - 1; i++) {
		if (!isdigit(cardData->primaryAccountNumber[i]))
			//flagPAN++;

			return  WRONG_PAN;

		/*   correct method too
		if (!(cardData->primaryAccountNumber[i] >= '0' && cardData->primaryAccountNumber[i] <= '9')) {
			flagPAN++;
		}
*/

		continue;
	}
	if (flagPAN != 0) {
		printf("wrong PAN\n");
		return WRONG_PAN;
	}
	else if ((strlen(cardData->primaryAccountNumber) < 16) || (strlen(cardData->primaryAccountNumber) > 19))
	{
		printf("wrong PAN\n");
		return WRONG_PAN;
	}
	else
		return CARD_OK;

}


