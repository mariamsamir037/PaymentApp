#include "app.h"

void appStart(void)
{
	ST_transaction transactionData;
	ST_cardData_t* cardData = &transactionData.cardHolderData;
	ST_terminalData_t* terminalData = &transactionData.terminalData;
	
	while (getCardHolderName(cardData));
	while (getCardExpiryDate(cardData));
	while (getCardPAN(cardData));

	/*********************************/

	while (getTransactionDate(terminalData));
	if (isCardExpired(cardData, terminalData)) {
		printf("operation declined\n");
		return;
	}

	/************************************/

	while (setMaxAmount(terminalData));
	while (getTransactionAmount(terminalData));

	if (isBelowMaxAmount(terminalData)) {
		printf("operation declined as it exceeds the max limit\n");
		return;
	}

	/*******************************************/
	/*
	//this works
	if (checkIfAccountExists(cardData) == -1) {
		printf("account does not exist\n");
		return;
	}
	printf("account exists\n");
	*/
	/*
	if (isValidAccount(cardData)) {
		printf("invalid account\n");
		return;
	}
	printf("valid account\n");

	if (isAmountAvailable(terminalData)) {
		printf("insufficient funds\n");
		return;
	}
	printf("sufficient fund\n");

	if (isaccountBlocked()) {
		printf("this account is blocked\n");
		return;
	}
	printf("this account is not blocked\n");
	*/
	
	if (recieveTransactionData(&transactionData))
		return;

	/*
	printf("PAN : %s\n",transactionDataDB.cardHolderData.primaryAccountNumber);
	printf("CardHolder name: %s\n",transactionDataDB.cardHolderData.cardHolderName);
	printf("***********************\n");
	*/

}