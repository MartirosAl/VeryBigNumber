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

	unsigned int max_size;
	unsigned int min_size;

	if (bn1_->size > bn2_->size)
	{
		max_size = bn1_->size;
		min_size = bn2_->size;
	}
	else
	{
		max_size = bn2_->size;
		min_size = bn1_->size;
	}

	result->size = max_size + 1;
	int dif_size = max_size - min_size;

	result->digits = calloc(result->size, sizeof(digit));
	if (result->digits == NULL)
	{
		printf("Memory allocation error");
		free(result->digits);
		return 0;
	}
	
	if (bn1_->is_negative && bn2_->is_negative || (!MinBN(bn1_, bn2_) && !bn1_->is_negative) || (MinBN(bn1_, bn2_) && !bn1_->is_negative)) //Если оба положительные или если у максимального числа положительный знак, то знак результата положительный
		result->is_negative = 0;
	else
		result->is_negative = 1;

	for (int i = 0; i < MinBN_size(bn1_, bn2_) + dif_size; i++)
	{
		if (dif_size == 0)
		{
			result->digits[i] = bn1_->digits[i] + bn2_->digits[i];!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Сделать перенос, сделать знаки ( в том числе минус) решить проблему с тем, что в конце 0
		}
	}

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


