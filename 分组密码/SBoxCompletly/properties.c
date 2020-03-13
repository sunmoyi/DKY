#include "header.h"

int hamming_weight (int x)
{
    int res;
    for (res = 0; x > 0; x = x >> 1)
        res = res + (x & 0x01);
    return res;
}

float get_robustness (uint *delta)
{
	uint i, j, R = 0;	
	uint **DDT;
	
	DDT = (uint **) malloc (m_shift * sizeof(uint *));
	
	for (i = 0; i < m_shift; i++)
	{
		DDT[i] = (uint *) malloc (n_shift * sizeof(uint));
		memset (DDT[i], 0, n_shift * sizeof(uint));
	}

	for (i = 0; i < m_shift; i++)
	{
		for (j = 0 ; j < n_shift; j++)
		{
			DDT [i ^ j] [input_array[i] ^ input_array[j]]++;			
		}
	}

	for (i = 0; i < m_shift; i++)
	{
		for (j = 0 ; j < n_shift; j++)
		{
			if (DDT [i][j] > *delta && (i != 0 && j != 0))
				*delta = DDT [i][j];	
		}
	}
	for (i = 1; i < n_shift; i++)
	{
		if (DDT [i][0] != 0)
			R++;
	}
	
	for (i = 0; i < m_shift; i++)
    {
    	free(DDT[i]);
    }
    free(DDT);

	return (1 - (R / (float)m_shift)) * (float)(1 - (*delta / (float)m_shift));
}


int get_delta_uniformity (float *robustness)
{
	uint i, j, delta = 0, R = 0;	
	uint **DDT;
	
	DDT = (uint **) malloc (m_shift * sizeof(uint *));
	
	for (i = 0; i < m_shift; i++)
	{
		DDT[i] = (uint *) malloc (n_shift * sizeof(uint));
		memset (DDT[i], 0, n_shift * sizeof(uint));
	}

	for (i = 0; i < m_shift; i++)
	{
		for (j = 0 ; j < n_shift; j++)
		{
			DDT [i ^ j] [input_array[i] ^ input_array[j]]++;			
		}
	}

	for (i = 0; i < m_shift; i++)
	{
		for (j = 0 ; j < n_shift; j++)
		{
			if (DDT [i][j] > delta && (i != 0 && j != 0))
				delta = DDT [i][j];	
		}
	}

	for (i = 1; i < n_shift; i++)
	{
		if (DDT [i][0] != 0)
			R++;
	}
	*robustness = (1 - (R / (float)m_shift)) * (float)(1 - (delta / (float)m_shift));
	
	for (i = 0; i < m_shift; i++)
    {
    	free(DDT[i]);
    }
    free(DDT);

	return delta;
}


void ddt ()
{
	uint i, j;	
	uint **DDT;
	
	DDT = (uint **) malloc (m_shift * sizeof(uint *));
	
	for (i = 0; i < m_shift; i++)
	{
		DDT[i] = (uint *) malloc (n_shift * sizeof(uint));
		memset (DDT[i], 0, n_shift * sizeof(uint));
	}

	for (i = 0; i < m_shift; i++)
	{
		for (j = 0 ; j < n_shift; j++)
		{
			DDT [i ^ j] [input_array[i] ^ input_array[j]]++;			
		}
	}

	for (i = 0; i < m_shift; i++)
    {
    	free(DDT[i]);
    }
    free(DDT);
}


void lat()
{
	uint i, j, z;	
	uint **LAT;
	
	LAT = (uint **) malloc (m_shift * sizeof(uint *));
	
	for (i = 0; i < m_shift; i++)
	{
		LAT[i] = (uint *) malloc (n_shift * sizeof(uint));
		memset (LAT[i], 0, n_shift * sizeof(uint));
	}

	for (i = 0; i < m_shift; i++)
	{
		for (j = 0; j < m_shift; j++)
		{
			for (z = 0; z < m_shift; z = z + 8)
			{
				//if ((hamming_weight (z & i) + hamming_weight(s_box[z] & j)) % 2 == 0)
				if (((hamming[z & i] + hamming[input_array[z] & j]) & 1) == 0)
					LAT[i][j]++;
				if (((hamming[(z + 1) & i] + hamming[input_array[z + 1] & j]) & 1) == 0)
					LAT[i][j]++;
				if (((hamming[(z + 2) & i] + hamming[input_array[z + 2] & j]) & 1) == 0)
					LAT[i][j]++;
				if (((hamming[(z + 3) & i] + hamming[input_array[z + 3] & j]) & 1) == 0)
					LAT[i][j]++;
				if (((hamming[(z + 4) & i] + hamming[input_array[z + 4] & j]) & 1) == 0)
					LAT[i][j]++;
				if (((hamming[(z + 5) & i] + hamming[input_array[z + 5] & j]) & 1) == 0)
					LAT[i][j]++;
				if (((hamming[(z + 6) & i] + hamming[input_array[z + 6] & j]) & 1) == 0)
					LAT[i][j]++;
				if (((hamming[(z + 7) & i] + hamming[input_array[z + 7] & j]) & 1) == 0)
					LAT[i][j]++;
			}
		}	
	}

	for (i = 0; i < m_shift; i++)
    {
    	free(LAT[i]);
    }
    free(LAT);
}

uint get_num_fixed_points (uint output)
{
	uint i, res = 0, rows = 1 << M;

	for (i = 0; i < rows; i++)
	{
		if ((input_array[i] ^ i) == 0)
		{
			res++;
			if (output)
			printf("Fixed point is %x on position %d.\n", input_array[i], i);
		}
	}
	return res;
}


uint get_num_opposite_fixed_points (uint output)
{
	uint i, res = 0, rows = 1 << M;

	for (i = 0; i < rows; i++)
	{
		if (input_array[i] == (~i & (rows - 1)))
		{
			res++;
			if (output)
				printf("Opposite fixed point is %x on position %d.\n", input_array[i], i);
		}
	}
	return res;
}

float get_snr_dpa (u8 **tt)
{
	float sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, help = 0.0;
	uint k, i, x, temp;
	
	temp = (1 << (2 * M)) * N;
	
	for (k = 0; k < m_shift; k++)
	{
		sum2 = 0.0;
		for (i = 0; i < N; i++)
		{
			sum3 = 0.0;
			for (x = 0; x < m_shift; x++)
			{
				sum3 += ((1 - 2 * inner_product(x, k)) * (1 - 2 * tt[x][i]));
			}
			sum2 += sum3;
		}
		sum2 = sum2 * sum2 * sum2 * sum2;
		sum1 += sum2;
	}
	sum1 = (float) pow (sum1, (float) - 0.5);
	return sum1 * temp;
}

float get_transparency ()
{
	uint b, a, v, x, tmp = 0;
	float res = 0.0;
	float sigma1, sigma2, sigma3 = 0, C;
	
	if (N > 1)
		return get_transparency_fast ();
	
	C = (float) ((1 << (2 * M)) - m_shift);

	for (b = 0; b < n_shift; b++)
	{
		sigma1 = 0;
		for (a = 1; a < m_shift; a++)
		{
			sigma2 = 0;
			for (v = 1; v < n_shift; v = v << 1) //can go from 1 since we need Hamming weight to be 1
			{
				sigma3 = 0;
				for (x = 0; x < m_shift; x++)
				{
					sigma3 += (float) (1 - 2 * inner_product(v, input_array[x]^input_array[x^a]));
				}
				sigma2 += (float) (1 - 2 * inner_product(v, b)) * sigma3;
			}

			if (sigma2 < 0)
				sigma2 = sigma2 * (-1);

			sigma1 += sigma2;
		}
		//tmp = 2 * hamming_weight(b);
		tmp = 2 * hamming[b];
		if (res < abs((int)N - tmp) - sigma1/C)
			res = abs((int)N - tmp) - sigma1/C;
	}
	return res;
}


float get_transparency_fast()
{
	int tmp = 0;
	uint b, a, x;
	float res = 0.0, z = 0.0, temp = 0.0, sigma1 = 0.0, sigma2 = 0.0, treshold = 0.0;
	float C = (float) ((1 << (2 * N)) - n_shift);
	float K = (float) (N * n_shift);

	for (b = 0; b < n_shift; b++)
	{
		treshold = (float) (N - 2 * hamming[b]);
		if (treshold < 0)
			treshold = treshold * (-1);
		treshold = (treshold - res) * C;
		if (treshold >= 0)
		{
			sigma2 = 0;
			for (a = 1; a < n_shift; a++)
			{
				sigma1 = 0;
				for (x = 0; x < n_shift; x++)
				{
					//sigma1 = sigma1 + hamming_weight(b ^ (evaluate_box(tt,x,a, N)));
					//sigma1 = sigma1 + hamming[b ^ (evaluate_box(tt, x, a))];
					sigma1 = sigma1 + hamming[b ^ (input_array[x]^input_array[x^a])];
				}
				z = K - 2 * sigma1;
				if (sigma1 > treshold)
					break;
				temp = treshold - (sigma1/C);
			
				if (z < 0)
					z = z * (-1);
				sigma2 += z;
			}
			//tmp = 2 * hamming_weight(b);
			tmp = 2 * hamming[b];
			if (res < abs((int)N - tmp) - sigma2/C)
				res = abs((int)N - tmp) - sigma2/C;
		}
	}
	return res;
}

int get_branch_number()
{
	uint i, j, temp = 0;	
	uint branch = 10000;

	for (i = 0; i < m_shift; i++)
	{
		for (j = 0; j < m_shift; j++)
		{
			if (i != j)
			{
				//temp = hamming_weight(i ^ j) + hamming_weight(sbox[i] ^ sbox[j]);
				temp = hamming[i ^ j] + hamming[input_array[i] ^ input_array[j]];
				if (temp < branch)
					branch = temp;
			}
		}
	}
	
	return branch;
}


int nonlinearity (int **wt, uint *components)
{
	uint  i, j, rows, columns, value = 0, temp = 0, min = 10000;
	rows = m_shift;
	columns = n_shift - 1;

	for (j = 0; j < columns; j++)
	{
		if (wt[0][j] < 0)
			temp = wt[0][j] * (-1);
		for (i = 1; i < rows; i++)
		{
			if (abs(wt[i][j]) > temp)
				temp = abs(wt[i][j]);
		}
		components[j] = (m_shift - temp) >> 1;
		if (components[j] < min)
			min = components[j];
	}
	return min;
}

int correlation_immunity (int **wt, uint *components)
{
	uint  i, j, columns, order, rows, min = 100000;
	columns = n_shift - 1;
	rows = m_shift;

	for (j = 0; j < columns; j++)
	{
		order = 1;
		for (i = 1; i < rows; i++)
		{
			//if (order == hamming_weight(i) && wt[i][j] != 0)
			if (order == hamming[i] && wt[i][j] != 0)
			{
				components[j] = order - 1;
				break;
			}
			if (i == (rows - 1) && order <= M)
			{
				i = 1;
				order++;
			}
			components[j] = order - 2;
		}
		if (components[j] < min)
			min = components[j];
	}
	return min;
}

//works with walsh spectrum
int balance (int **wt, uint *components)
{
	uint  j, columns, balance = 0;
	columns = n_shift - 1;

	for (j = 0; j < columns; j++)
	{
		if (wt[0][j] != 0)
			balance++;
	} 
	return balance;
}

//just counts zeros/ones
int balance_naive (uint *input_array)
{
	uint i, res = 0;

	for (i = 0; i < m_shift; i++)
	{
		if (input_array[i] == 0) //count zeros
			res = res + 1;
	}
	if (res == (1 << (M - 1)))
		return 0;
	else
		return m_shift - res; //broj jedinica
}


unsigned int absolute_indicator (int **ac, uint *components) //the smaller, the bettter
{
	uint i, j, rows, columns;
	unsigned int max = 0, temp = 0, temp2 = 0;

	rows = m_shift;
	columns = n_shift - 1;

	for (j = 0; j < columns; j++)
	{
		temp = abs(ac[1][j]); //disregard first value since it is 2^n
		for (i = 2; i < rows; i++)	
		{
			temp2 = abs(ac[i][j]);
			if (temp2 > temp)
				temp = temp2;
		}
		components[j] = temp;
		if (temp > max)
			max = temp;
	}
	return max;
}


unsigned int sum_of_square_indicator (int **ac, uint *components) //the smaller, the bettter
{
	int i, j, rows, columns;
	unsigned int max = 0, sum = 0;

	rows = m_shift;
	columns = n_shift - 1;

	for (j = 0; j < columns; j++)
	{
		for (i = 0; i < rows; i++)	
		{
			sum += ac[i][j] * ac[i][j];
		}
		components[j] = sum;
		if (sum > max)
			max = sum;
		sum = 0;
	}
	return max;
}

int propagation_characteristics () //the higher the better
{
	uint i, j, z, order = 1, count = 0;
	uint *help;

	help = (uint*) malloc(sizeof(uint) * m_shift);
	
	do 
	{
		for (i = 1; i < m_shift; i++)
		{
			//if (order == hamming_weight(i))
			if (order == hamming[i])
			{
				get_derivative(input_array, help, i, m_shift);
				
				//could be done with tt, wt, balance
				for (j = 0; j < m_shift; j++)
				{
					for (z = 0; z < m_shift; z++)
					{
						if (help[z] == j)
							count++;
					}
					if (count != 1)
						return order - 1;
					count = 0;
				}
			}
		}
		order++;
	} while (order <= N);
	return order-1;
}


void coordinate_function_values (int *_array)
{
	uint i, columns;
	columns = n_shift -1;
	for (i = 0; i < columns; i++)
		//if (hamming_weight(i) == 1)
		if (hamming[i] == 1)
			printf ("%d, ", _array[i]);
}

int algebraic_term (int **anf, uint *components)
{
	int terms;
	int min = 0;
	int columns = n_shift - 1;
	for(int j = 0; j < columns; j++){
		for(int i = 0; i < m_shift; i++){
			terms += anf[i][j];
		}
		components[j] = terms;
		terms = 0;
		if (j == 0){
			min = components[j];
		}
		else{
			if (components[j] < min){
				min = components[j];
			}
		}
		
	}
	return min;

}

int algebraic_degree (int **anf, uint *components)
{
    int  tmp, weight, deg;
	uint i, j, rows, columns, max = 0;
	
	rows = m_shift;
	columns = n_shift - 1;

	for (j = 0; j < columns; j++)
	{
		if (anf[rows - 1][j] != 0)
			deg = M;
		else
		{
			for (deg = 0, i = 1; i < (rows - 1); ++i)
				if (anf[i][j] != 0) 
				{
					for (weight = 0, tmp = i; tmp > 0; tmp >>= 1)
						weight = weight + tmp % 2;
					if (weight > deg)
						deg = weight;
				}
		}
		components[j] = deg;
		if (components[j] > max)
			max = components[j];
	}
	return max;
}

void get_derivative (uint *input_array, uint *output_array, uint shift, uint columns)
{
	uint i;
	for (i = 0; i < columns; i++)
	{
		output_array[i] = input_array[i] ^ input_array[i ^ shift];
	}
}

//experimental
/*void check(uint *input_array, int elements)
{
	uint i, a, sum = 0, max = 0, min = 1000;
	uint output_array[16];
	for (a = 1; a < 16; a++)
	{
		for (i = 0; i < elements; i++)
		{
			output_array[i] = input_array[i] ^ input_array[i^a];
			printf("%d, ", hamming_weight(output_array[i]));
			sum+=hamming_weight(output_array[i]);
			if (hamming_weight(output_array[i]) < min)
				min = hamming_weight(output_array[i]);
			if (hamming_weight(output_array[i]) > max)
				max = hamming_weight(output_array[i]);
		}
		printf("%d, ", sum);
		printf("%d ", max - min);
		sum = 0;
		max = 0;
		min = 0;
		printf("\n");
	}
}
*/

//by Frederic Lafitte, from boolfun
int algebraic_immunity (u8 **ll, uint *components)
{
	MAT *m0 = NULL, *m1 = NULL;
    int *monomials = NULL;
    int a, b, res = 0, deg, Nm;
	uint i, columns, rows, min = 100000;
	rows = 1 << M;
	columns = (1 << N) - 1;
	
	deg = (M >> 1) + (M & 1);
    monomials = get_monomials(M, deg, monomials, &Nm);
    monomials = sort_increasing_deg(monomials, Nm);

	for (i = 0; i < columns; i++)
	{
		m0 = get_matrix(ll, M, m0, monomials, Nm, deg, 0);
		if (m0 == NULL)
			res = 0;
		else 
		{
			m1 = get_matrix(ll, M, m1, monomials, Nm, deg, 1);
			a = solve_matrix(m0, monomials, 0);
			b = solve_matrix(m1, monomials, 1);
			res = (a < b) ? a : b;
		}
		components[i] = res;
		if (res < min)
			min = res;
	}

    free(monomials);
    deallocate_mat(m0);
    deallocate_mat(m1);
    return min;
}

void hamming_weights (uint *hamming)
{
	uint i;
	for (i = 0; i < m_shift; i++)
	{
		hamming[i] = hamming_weight(i);
	}

}

void strict_avalanche_criterion (uint pc)
{
	if (pc == 1)
		printf("Strict Avalanche Criterion is satisfied.\n");
	else
		printf("Strict Avalanche Criterion is not satisfied.\n");
}



float computeKappaCPA(int inputBits, int outputBits, int keyBits)
{ 
	int inputSize = 1 << inputBits;
	int outputSize = 1 << outputBits;
	int keySize = 1 << keyBits;
	int coefficientSize = (keySize * (keySize-1)) >> 1; // combinatorics on key picks i and j
	int confusionCounter = 0; //# of times we observe confusion
	int outi,outj; // Sbox output	
	int coefficientCounter = 0; //how many coefficients have we computed
	int keyi, keyj, input, i = 0, j = 0, k = 0, coefficientSum = 0, temp = 0, fcounter = 0, in = 0;
	float mean = 0.0, var = 0.0;
	
	float *reducedCoefficients = (float *) malloc (coefficientSize * sizeof (float));
	float *frequency = (float *) malloc (coefficientSize * sizeof (float));
	float *confusionCharacteristic = (float *) malloc (coefficientSize * sizeof (float)); 
	

	for (keyi = 0; keyi < keySize; keyi++)
	{
		for (keyj = keyi + 1; keyj < keySize; keyj++)
		{		
			for (input = 0; input < inputSize ; input++)
			{
				outi = input_array[keyi ^ input];
				outj = input_array[keyj ^ input];
				
				temp = hamming[outi] - hamming[outj]; 
				temp *=  temp;
				coefficientSum += temp;
			}	
			//input set is over, lets compute confusion coefficient for (keyi, keyj)
			confusionCharacteristic[coefficientCounter]=(float)coefficientSum / (float)inputSize;
			coefficientCounter ++;
			confusionCounter = 0; //dpa
			coefficientSum = 0; //cpa
		}
	}

	fcounter = 0;
	for (i = 0; i < coefficientSize; i++)
	{
		if(confusionCharacteristic[10] == confusionCharacteristic[i])
		{
			fcounter++;
		}
		mean = mean + confusionCharacteristic[i];
	}
	
	mean = mean / (float)coefficientSize;

	for (i = 0; i < coefficientSize; i++)
		var = (float) (var + (float) pow((confusionCharacteristic[i] - (float) mean), 2));

	var = var / (float)coefficientSize;
	
	return var;
}


void computeKappaDPA(int inputBits, int outputBits, int keyBits, int bit)
{
	int inputSize = 1 << inputBits;
	int outputSize = 1 << outputBits;
	int keySize = 1 << keyBits;
	int coefficientSize = (keySize * (keySize-1)) >> 1; // combinatorics on key picks i and j
	int confusionCounter = 0; //# of times we observe confusion
	int singleBiti, singleBitj; //DPA related bits- first bit of the Sbox output
	int outi,outj; // Sbox output	
	int coefficientCounter = 0; //how many coefficients have we computed
	int keyi, keyj, input, i = 0, j = 0, k = 0;	
	
	float *reducedCoefficients = (float *) malloc (coefficientSize * sizeof (float));
	float *frequency = (float *) malloc (coefficientSize * sizeof (float));
	float *confusionCharacteristic = (float *) malloc (coefficientSize * sizeof (float));
	

	for(keyi = 0; keyi < keySize; keyi++)
	{
		for(keyj = 0; (keyj < keySize) && (keyi != keyj); keyj++)
		{			
			for (input = 0; input < inputSize; input++)
			{
				outi = input_array[keyi ^ input];
				outj = input_array[keyj ^ input];
				// Isolate desired bit of the Sbox to focus on DPA
				singleBiti = outi & bit;
				singleBitj = outj & bit;
				//NOTE: collision coefficient can be produced by replacing '!=' with '=='
				if (singleBiti != singleBitj) // check if we have "confusion" or "collision"
					confusionCounter++;
			}	
			//input set is over, lets compute confusion coefficient for (keyi, keyj)
			confusionCharacteristic[coefficientCounter] = (float)confusionCounter / (float)inputSize;
			coefficientCounter ++;
			confusionCounter = 0; //dpa
		}
	}

	
	qsort (confusionCharacteristic, coefficientSize, sizeof(float), compare);

	for (i = 0; i < coefficientCounter; i++)
	{
		if (confusionCharacteristic[i] == confusionCharacteristic[i+1])
			j++;
		else
		{
			reducedCoefficients[k] = confusionCharacteristic[i];
			frequency[k] = (float)j/(float) coefficientSize;
			j = 0;
			k++;
		}
	}
	
	for (i = 0; i < k; i++)
		printf ("%f, ", reducedCoefficients[i]); 
	printf("\n");
	for (i = 0; i < k; i++)
		printf ("%f, ", frequency[i]); 
}
