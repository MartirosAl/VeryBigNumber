#include "big_number.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_string.h"

BigNumber* CreateBN(char* number_)
{
	if (number_ == NULL || strlen(number_) == 0 ||
			!IsIntString(number_))
		return NULL;
	
	BigNumber* bn = (BigNumber*)malloc(sizeof(BigNumber));
	if (bn == NULL)
		return NULL;
	
	size_t size = strlen(number_);
	if (*number_ == '-')
	{
		bn->size = size - 1;
		bn->is_negative = true;
		number_++;
	}
	else
	{
		bn->size = size;
		bn->is_negative = false;
	}
	
	bn->digits = (digit*)calloc(bn->size, sizeof(digit));
	if (bn->digits == NULL)
	{
		free(bn);
		return NULL;
	}
	
	for (size_t i = 0; i < bn->size; ++i)
		bn->digits[i] = number_[i] - '0';
	
	return bn;
}

void DeleteBN(BigNumber** bn_)
{
    free((*bn_)->digits);
    free(*bn_);
    
    *bn_ = NULL;
}

void PrintBN(BigNumber* bn_)
{
    if (bn_ == NULL)
    {
        printf("BigNumber is empty!\n");
        return;
    }
    
    if (bn_->is_negative)
        printf("-");
    
    for (size_t i = 0; i < bn_->size; ++i)
        printf("%u", bn_->digits[i]);
        
    printf("\n");
}

BigNumber* SumBN(BigNumber* bn1_, BigNumber* bn2_)
{

	
	BigNumber* result = malloc(sizeof(BigNumber));
	if (result == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}
	result->digits = (digit*)calloc(MaxBN_size(bn1_, bn2_) + 1, sizeof(digit));

	if (!(bn1_->is_negative == bn2_->is_negative))
		return -20;

	result->is_negative = bn1_->is_negative;

	unsigned int rank = 0;
	int digit = 0;
	int dif = abs(bn1_->size - bn2_->size);

	char* minbn = NULL;
	char* maxbn = NULL;
	if (MinBN(bn1_, bn2_) == 0)
	{
		minbn = bn1_->digits;
		maxbn = bn2_->digits;
	}
	else
	{
		minbn = bn2_->digits;
		maxbn = bn1_->digits;
	}


	for (long int i = (long int)(MinBN_size(bn1_, bn2_)) - 1; i >= 0; i--)
	{
		digit = (int)(maxbn[i + dif]) + (int)(minbn[i]) + rank;
		result->digits[i + dif + 1] = digit % 10;
		rank = digit / 10;
	}
	for (long int i = dif - 1; i >= 0; i--)
	{
		digit = (int)(maxbn[i] + rank);
		result->digits[i + 1] = digit % 10;
		rank = digit / 10;
	}
	result->digits[0] = rank;

	PrintBN(result);
	
}

int MinBN(BigNumber* bn1_, BigNumber* bn2_)
{
	if (bn1_->size < bn2_->size)
		return 0;
	else if (bn1_->size > bn2_->size)
		return 1;
	else
		for (unsigned int i = 0; i < bn1_->size; i++)
			if (bn1_->digits[i] < bn2_->digits[i])
				return 0;
			else if (bn1_->digits[i] > bn2_->digits[i])
				return 1;

	return 0;
}

int MinBN_size(BigNumber* bn1_, BigNumber* bn2_)
{
	if (bn1_->size < bn2_->size)
		return bn1_->size;
	else if (bn1_->size > bn2_->size)
		return bn2_->size;
	else
		for (unsigned int i = 0; i < bn1_->size; i++)
			if (bn1_->digits[i] < bn2_->digits[i])
				return bn1_->size;
			else if (bn1_->digits[i] > bn2_->digits[i])
				return bn2_->size;

	return bn1_->size;
}

int MaxBN_size(BigNumber* bn1_, BigNumber* bn2_)
{
	if (bn1_->size > bn2_->size)
		return bn1_->size;
	else if (bn1_->size < bn2_->size)
		return bn2_->size;
	else
		for (unsigned int i = 0; i < bn1_->size; i++)
			if (bn1_->digits[i] > bn2_->digits[i])
				return bn1_->size;
			else if (bn1_->digits[i] < bn2_->digits[i])
				return bn2_->size;

	return bn1_->size;
}


