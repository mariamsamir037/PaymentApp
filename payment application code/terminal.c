#include "terminal.h"
#include <time.h>

int validDay(int day) {
	if (day > 30 || day < 1)
		return WRONG_DATE;
	return TERMINAL_OK;
}

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("kindly enter transaction date in this format \"DD/MM/YYYY\":");
	gets_s(&(termData->transactionDate), 20);
	
	int day = ((int)termData->transactionDate[0] - '0') * 10 + ((int)termData->transactionDate[1] - '0');
	int month = ((int)termData->transactionDate[3] - '0') * 10 + ((int)termData->transactionDate[4] - '0');

	if (strlen(termData->transactionDate) != 10)
	{
		printf("WRONG_DATE\n");
		return WRONG_DATE;
	}
	else if (termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/')
	{
		printf("WRONG_DATE\n");
		return WRONG_DATE;
	}
	else if (validDay(day) || validMonth(month))
	{
		printf("WRONG_DATE \n");
		return WRONG_DATE;
	}
	return TERMINAL_OK;
}

// fucntion 34an compare dates ;expiry w transaction
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	//convert kol character l integer 
	uint8_t expMon = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	uint8_t transMon = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');
	uint8_t expYear = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
	uint8_t transYear = (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');

	if (expYear < transYear)       /*  MM/YY             DD/MM/YYYY   */
	{
		printf("EXPIRED CARD\n");
		return EXPIRED_CARD;
	}
	else
	{
		if (expYear == transYear)
		{
			if (expMon < transMon)
			{
				printf("EXPIRED CARD\n");
				return EXPIRED_CARD;
			}
			else
				return TERMINAL_OK;
		}
		else
			return TERMINAL_OK;
	}
}

/*
uint32_t expirationDateInt = 100 * atoi(expirationDateYears) + atoi(expirationDateMonths);
uint32_t terminalDateInt = 100 * atoi(transactionDateYears) + atoi(transactionDateMonths);
*/

/*
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	uint8_t reversedPAN[20];
	uint8_t newrevPAN[20];
	int temp = 0, i = 0;
	uint32_t sum = 0;


	for (i = 0; reversedPAN[i] != '0'; i++) {
		reversedPAN[i] = cardData->primaryAccountNumber[strlen(cardData->primaryAccountNumber) - i - 1];
	}
	printf("%s",reversedPAN);
	
	for (i = 0; reversedPAN[i] != '0'; i + 2) {
		int reversedpan = reversedPAN[i + 1] - '0';
		temp = reversedpan * 2;
		if (temp > 9)
		{
			temp = (temp % 10) + 1;
		}

		sum = temp  + (reversedPAN[i] - '0');
	}
	if (sum % 10 == 0) {
		printf("valid PAN number\n");
		return TERMINAL_OK;
	}
	else
	{
		printf("invalid PAN number\n");
		return INVALID_CARD;
	}
	
}
*/

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("max transaction amount: ");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0) {
		printf("INVALID_MAX_AMOUNT\n");
		return INVALID_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("please enter the needed transaction amount:");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0) {
		printf("INVALID_AMOUNT\n");
		return INVALID_AMOUNT;
	}
	return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		printf("EXCEEDED_MAX_AMOUNT\n");
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}
