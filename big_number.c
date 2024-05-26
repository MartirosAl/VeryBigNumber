#include "big_number.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "my_string.h"

BigNumber* CreateBN(char* number_)
{
	if (number_ == NULL || strlen(number_) == 0 ||
			!IsIntString(number_))
		return NULL;
	
	BigNumber* bn = (BigNumber*)malloc(sizeof(BigNumber));
	if (bn == NULL)
		return NULL;
	
	unsigned int size = (unsigned int)strlen(number_);
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
	if (result->digits == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}

	if (!(bn1_->is_negative == bn2_->is_negative))
	{
		if (MinBN(bn1_, bn2_) == 0)
			if (bn1_->is_negative == 1)
			{
				CopyBN(bn1_, result);
				result->is_negative = 0;
				result = DiffBN(bn2_, result);
			}
			else
			{
				CopyBN(bn1_, result);
				result->is_negative = 1;
				result = DiffBN(bn2_, result);
			}
		else
			if (bn2_->is_negative == 1)
			{
				CopyBN(bn2_, result);
				result->is_negative = 0;
				result = DiffBN(bn1_, result);
			}
			else
			{
				CopyBN(bn2_, result);
				result->is_negative = 1;
				result = DiffBN(bn1_, result);
			}
		return result;
	}

	result->is_negative = bn1_->is_negative;

	unsigned int rank = 0;
	int num = 0;
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

	for (long int i = MinBN_size(bn1_, bn2_) - 1; i >= 0; i--)
	{
		num = (int)(maxbn[i + dif]) + (int)(minbn[i]) + rank;
		result->digits[i + dif + 1] = (char)(num % 10);
		rank = num / 10;
	}
	for (long int i = dif - 1; i >= 0; i--)
	{
		num = (int)(maxbn[i] + rank);
		result->digits[i + 1] = (char)(num % 10);
		rank = num / 10;
	}
	result->digits[0] = (char)(rank);

	unsigned int maxsize = MaxBN_size(bn1_, bn2_);
	if (result->digits[0] == 0)
	{
		for (long int i = 1; i <= (long)maxsize; i++)
			result->digits[i - 1] = result->digits[i];
		result->size = MaxBN_size(bn1_, bn2_);
	}
	else
		result->size = MaxBN_size(bn1_, bn2_) + 1;

	PrintBN(result);
	return result;
}

BigNumber* DiffBN(BigNumber* bn1_, BigNumber* bn2_)
{
	BigNumber* result = malloc(sizeof(BigNumber));
	if (result == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}

	result->digits = (digit*)calloc(MaxBN_size(bn1_, bn2_), sizeof(digit));

	if (result->digits == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}

	if (!(bn1_->is_negative == bn2_->is_negative))
	{
		if (bn1_->is_negative == 1)
		{
			CopyBN(bn2_, result);
			result->is_negative = 1;
			result = SumBN(bn1_, result);
		}
		else
		{
			CopyBN(bn2_, result);
			result->is_negative = 0;
			result = SumBN(bn1_, result);
		}
		return result;
	}

	result->is_negative = bn1_->is_negative;
	result->size = MaxBN_size(bn1_, bn2_);

	unsigned int rank = 0;
	int num = 0;
	int dif = abs(bn1_->size - bn2_->size);

	if (MinBN(bn1_, bn2_) == 1)
	{
		for (long int i = bn2_->size - 1; i >= 0; i--)
		{
			num = (int)(bn1_->digits[i + dif]) - (int)(bn2_->digits[i]) - rank;

			if (num < 0)
			{
				num = 10 - abs(num) - rank;
				rank = 1;
			}
			else
				rank = 0;

			result->digits[i + dif + 1] = (char)(num % 10);
		}
		for (long int i = dif - 1; i >= 0; i--)
		{
			num = (int)(bn1_->digits[i] - rank);
			if (num < 0)
			{
				num = 10 - rank;
				rank = 1;
			}
			else
				rank = 0;
			result->digits[i + 1] = (char)(num % 10);
		}
		
		unsigned int maxsize = MaxBN_size(bn1_, bn2_);
		while (result->digits[0] == 0 && maxsize > 0)
		{
			for (long int i = 1; i <= (long)maxsize; i++)
				result->digits[i - 1] = result->digits[i];
			result->size = maxsize;
			maxsize--;
		}

		if (result->size == 0)
		{
			result->size = 1;
			result->digits[0] = 0;
		}
	}
	else
	{
		BigNumber* temp = malloc(sizeof(BigNumber));
		if (temp == NULL)
		{
			printf("Memory allocation error");
			return 0;
		}
		temp->digits = (digit*)calloc(MaxBN_size(bn1_, bn2_), sizeof(digit));
		if (temp->digits == NULL)
		{
			printf("Memory allocation error");
			return 0;
		}
		CopyBN(bn1_, result);
		result->is_negative = !(bn1_->is_negative);
		CopyBN(bn2_, temp);
		temp->is_negative = !(bn2_->is_negative);
		result = DiffBN(temp, result);

		return result;
	}

	PrintBN(result);
	return result;
}

BigNumber* ProdBN(BigNumber* bn1_, BigNumber* bn2_)
{
	BigNumber* result = malloc(sizeof(BigNumber));
	if (result == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}
	
	result->digits = (digit*)calloc(2*MaxBN_size(bn1_, bn2_), sizeof(digit));
	if (result->digits == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}

	if (bn2_->digits == 0 || bn1_->digits == 0)
	{
		result->is_negative = 0;
		result->size = 1;
		result->digits = 0;
	}

	BigNumber* temp1 = malloc(sizeof(BigNumber));
	if (temp1 == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}
	temp1->digits = (digit*)calloc(2 * MaxBN_size(bn1_, bn2_), sizeof(digit));
	if (temp1->digits == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}
	temp1->is_negative = 0;
	temp1->size = 1;

	BigNumber* temp2 = malloc(sizeof(BigNumber));
	if (temp2 == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}
	temp2->digits = (digit*)calloc(2 * MaxBN_size(bn1_, bn2_), sizeof(digit));
	if (temp2->digits == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}
	temp2->is_negative = 0;
	temp2->size = 1;

	int left_shift = 0;

	for (long int i = bn2_->size - 2; i >= 0; i--)
	{
		int carry = 0, k = left_shift;
		for (long int j = bn1_->size - 2; j >= 0; j--)
		{
			int partial_result = (bn1_->digits[j] - '0') * (bn2_->digits[i] - '0') + carry;
			if (result_arr[k])
				partial_result += result_arr[k] - '0';
			result_arr[k++] = partial_result % 10 + '0';
			carry = partial_result / 10;
		}
		if (carry > 0)
			result_arr[k] = carry + '0';
		left_sh
	

	if (bn1_->is_negative == bn2_->is_negative)
		result->is_negative = 0;
	else
		result->is_negative = 1;
	PrintBN(result);
	return(result);
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

void CopyBN(BigNumber* bn1_, BigNumber* bn2_)
{
	bn2_->size = bn1_->size;
	bn2_->is_negative = bn1_->is_negative;
	for (unsigned int i = 0; i < bn1_->size; i++)
		bn2_->digits[i] = bn1_->digits[i];
}
