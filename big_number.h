#include <stdbool.h>

typedef unsigned char digit;

// Тип большого числа (>10 знаков)
typedef struct BigNumber
{
	unsigned int size;		// Размер числа
	digit* digits;  	// Массив из цифр числа
	bool is_negative;	// Знак числа
}BigNumber;

/*
* @brief Создание большого числа
* @param number_ : Строка с большим числом
* @return Указатель на выделенную память с большим числом 
*/
BigNumber* CreateBN(char* number_);

/*
* @brief Удаляет выбранное большое число
* @param bn_ : Указатель на большое число
*/
void DeleteBN(BigNumber** bn_);

/*
* @brief Печать большого числа
* @param bn_ : Указатель на большое число
*/
void PrintBN(BigNumber* bn_);

/*
* @brief Сумма двух больших чисел
* @param bn1_, bn2_ : Большие числа
* @return Большое число из суммы двух входных
*/
BigNumber* SumBN(BigNumber* bn1_, BigNumber* bn2_);

BigNumber* DiffBN(BigNumber* bn1_, BigNumber* bn2_);

BigNumber* ProdBN(BigNumber* bn1_, BigNumber* bn2_);

BigNumber* DivBN(BigNumber* bn1_, BigNumber* bn2_);
/*
* @brief Сравнение двух больших чисел по модулю
* @param bn1_, bn2_ : Большие числа
* @return 0, если большое число 1 < большого числа 2, 1 иначе
*/
int MinBN(BigNumber* bn1_, BigNumber* bn2_);

int MinBN_size(BigNumber* bn1_, BigNumber* bn2_);

int MaxBN_size(BigNumber* bn1_, BigNumber* bn2_);

void CopyBN(BigNumber* bn1_, BigNumber* bn2_);