#include "server.h"

extern ST_accountsDB_t accountsDB_arr[] = {
	{70000.30,"7992739871323651299"},{150000.26,"5649871022064986121"},{200.65,"6350214781254698745"},
	{0,"3020105060249367182"},{23456.96,"7418529637418529630"},{70500.30,"1234567893214567891"},
	{155000.26,"5569871022064986121"},{2001.65,"6350214781254698457"},{10,"3020105060249300100"},
	{987.45,"9517539638521456324"}
};     //10 accounts for testing

extern ST_transaction transaction_arr[255] = { 0 };

static uint8_t sequenceNumber;
ST_cardData_t cardTemp;

int checkIfAccountExists(ST_cardData_t* cardData)
{
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(cardData->primaryAccountNumber, accountsDB_arr[i].primaryAccountNumber) == 0)
			return i;        //returns el index bta3 el account lw l2a ay match 
	}
	return -1;
}

EN_transStat_t recieveTransactionData(ST_transaction* transData) {
	if (isValidAccount(&(transData->cardHolderData)))
	{
		printf("operation declined...account doesn't exist \n");
		transaction_arr[sequenceNumber].transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&(transData->terminalData)))
	{
		printf("operation declined...low balance\n");
		transaction_arr[sequenceNumber].transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (saveTransaction(transData))
	{
		printf("INTERNAL SERVER ERROR \n");
		transaction_arr[sequenceNumber].transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	
	
	else if (isaccountBlocked()) {
		printf("you wish to block your account, so we can't proceed with the transaction\n");
		transaction_arr[sequenceNumber].transState = DECLIINED_BLOCKED;
		return DECLIINED_BLOCKED;
	}
	
	else
	{
		accountsDB_arr[checkIfAccountExists(&cardTemp)].balance = accountsDB_arr[checkIfAccountExists(&cardTemp)].balance - transData->terminalData.transAmount;
		printf("ur new balance is: %.2f\n", accountsDB_arr[checkIfAccountExists(&cardTemp)].balance);
		transaction_arr[sequenceNumber].transState = APPROVED;
		printf("approved...operation sucessful\n");
		return APPROVED;
	}
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	cardTemp = *cardData;
	if (checkIfAccountExists(cardData) == -1)
	{
		return DECLINED_STOLEN_CARD;
	}
	else
		return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	if (termData->transAmount > accountsDB_arr[checkIfAccountExists(&cardTemp)].balance) {
		return LOW_BALANCE;
	}
	else
		return SERVER_OK;
}

EN_serverError_t isaccountBlocked() {
	uint8_t block;
	printf("do you wish to block your account or proceed with the transaction?\n press (Y/y) to block or press(N/n) to proceed: ");
	scanf_s(" %c", &block);
	if (block=='y' || block == 'Y') {
		return DECLIINED_BLOCKED;
	}
	else if (block == 'n' || block == 'N') {
		return SERVER_OK;
	}
}

EN_serverError_t saveTransaction(ST_transaction* transData) {
	if (sequenceNumber < 255)
	{
		transaction_arr[sequenceNumber] = *transData;
		transaction_arr[sequenceNumber].transactionSequenceNumber = sequenceNumber;
		transaction_arr[sequenceNumber].transState = APPROVED;
		sequenceNumber++;
		return SERVER_OK;
	}
	printf("SAVING FAILED\n");
	return SAVING_FAILED;
}
