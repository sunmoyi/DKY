#include "header.h"

uint check_data_format ()
{
	uint type = 0, check = 0;
	if (N != 1)
	{
		type = 1;
		while ((check = (int) fgetc(fin)) != EOF)
		{
			if ((check >= 65 && check <= 70) || (check >= 97 && check <= 102)) //then it is decimal
			{
				type = 0;
				break;
			}
		}
	}
	return type;
}

void read_from_file (int type)
{
	int i = 0;
	fseek(fin, 0, SEEK_SET);
	while (!feof(fin))
	{
		if (type == 1)
		{
			fscanf(fin, "%d", &input_array[i]);
		}
		else
		{
			fscanf(fin, "%x", &input_array[i]);
		}
		i++;
	}
	fclose (fin);
}

uint * allocate_memory (int dim)
{
	uint *_array;
	_array = (uint *) malloc (sizeof(uint) * dim);
	return _array;
}


void allocate_memory_multi (int dim, int n, ...)
{
	int i;
	uint ** temp;
	va_list arguments;

	va_start (arguments, n);
	
	for (i = 0; i < n; i++)
	{
		temp = va_arg(arguments, uint **);
		*temp  = (uint *) malloc (sizeof(uint) * dim);
	}
	va_end (arguments);
}

void deallocate_memory_multi (int n, ...)
{
	int i;
	uint ** temp;
	va_list arguments;

	va_start (arguments, n);
	
	for (i = 0; i < n; i++)
	{
		temp = va_arg(arguments, uint **);
		free(*temp);
	}
	va_end (arguments);
}

void deallocate_memory (uint **_array)
{
	free(*_array);
}

int ** allocate_matrix (uint rows, uint columns)
{
	uint i;
	int **matrix;
	matrix = (int **) malloc (rows * sizeof(int *));
	for (i = 0; i < rows; i++)
		matrix[i] = (int*) malloc (columns * sizeof(int));
	set_to_zero (matrix, rows, columns);
	return matrix;
}


long long ** allocate_matrix_long (uint rows, uint columns)
{
	uint i;
	long long **matrix;
	matrix = (long long **) malloc (rows * sizeof(long long *));
	for (i = 0; i < rows; i++)
		matrix[i] = (long long*) malloc (columns * sizeof(long long));
	set_to_zero_long (matrix, rows, columns);
	return matrix;
}


u8 ** allocate_matrix_u8 (uint rows, uint columns)
{
	uint i;
	u8 **matrix;
	matrix = (u8 **) malloc (rows * sizeof(u8 *));
	for (i = 0; i < rows; i++)
		matrix[i] = (u8*) malloc (columns * sizeof(u8));
	set_to_zero_u8 (matrix, rows, columns);
	return matrix;
}

int inner_product (int a, int b)
{
	uint i;
	int res = 0;
	for (i = 0; i < M; i++)
	{
		res ^=  (((a >> i) & 0x01) & ((b >> i) & 0x01));
	}
	return res;
}

void balancedness (int min_balance)
{
	if (min_balance == 0)
		if (N > 1)
			printf("S-box is balanced.\n");
		else
			printf("Boolean functions is balanced.\n");
	else
		if (N > 1)
			printf("S-box is unbalanced for a value of %d.\n", min_balance);
		else
			printf("Boolean function is unbalanced for a value of %d.\n", min_balance);
}

void output_array_to_file (char *name, int *_array, int n, int count)
{
	FILE *fout;
	int i;

	if ((fout = fopen(name,"w+")) == NULL)
	{
		printf("Error while writing to file %s\n", name);
	}
	
	for (i = 0; i < n; i++)
	{
		if (i % count == 0)
			fprintf(fout, "\n");
		fprintf(fout,"%d\t", _array[i]);
	}
	fclose(fout);
}

void store_matrix (int **_matrix, uint rows, uint columns, char *name)
{
	FILE *fout;
	uint i, j;

	if ((fout = fopen(name,"w+")) == NULL)
	{
		printf("Error while writing to file %s\n", name);
	}

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			fprintf(fout, "%d, ",_matrix[i][j]);
		}
		fprintf(fout, "\n");
	}

	fclose (fout);

}

void store_matrix_u8 (u8 **_matrix, uint rows, uint columns, char *name)
{
	FILE *fout;
	uint i, j;

	if ((fout = fopen(name,"w+")) == NULL)
	{
		printf("Error while writing to file %s\n", name);
	}

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			fprintf(fout, "%d, ",_matrix[i][j]);
		}
		fprintf(fout, "\n");
	}

	fclose (fout);

}


void output_matrix (int **_matrix, uint rows, uint columns)
{
	uint i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			printf("%d\t",_matrix[i][j]);
		}
		printf("\n");
	}

}

void output_matrix_u8 (u8 **_matrix, uint rows, uint columns)
{
	uint i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			printf("%d\t",_matrix[i][j]);
		}
		printf("\n");
	}
}

void output_matrix_transpose (int **_matrix, uint rows, uint columns) //transpose for easier output to screen
{
	uint i, j;
	for (i = 0; i < columns; i++)
	{
		for (j = 0; j < rows; j++)
		{
			printf("%d\t",_matrix[j][i]);
		}
		printf("\n");
	}

}

void output_matrix_u8_transpose (u8 **_matrix, uint rows, uint columns) //transpose for easier output to screen
{
	uint i, j;
	for (i = 0; i < columns; i++)
	{
		for (j = 0; j < rows; j++)
		{
			printf("%d\t",_matrix[j][i]);
		}
		printf("\n");
	}
}

void xor_elements (u8 **_matrix1, u8 **truth_table, u8 **_matrix2, uint column_ll, uint column_tt)
{
	uint i;
	for (i = 0; i < m_shift; i++)
		_matrix2[i][column_ll] = _matrix1[i][column_ll] ^ truth_table[i][column_tt];
}

void set_to_zero_u8 (u8 **_matrix, uint rows, uint columns)		//set array elements to zero value
{
	uint i;
	for (i = 0; i < rows; i++)
		memset (_matrix[i], 0, columns * sizeof(u8));
}

void set_to_zero (int **_matrix, uint rows, uint columns)		//set array elements to zero value
{
	uint i;
	for (i = 0; i < rows; i++)
		memset (_matrix[i], 0, columns * sizeof(int));
}


void set_to_zero_long (long long **_matrix, uint rows, uint columns)		//set array elements to zero value
{
	uint i;
	for (i = 0; i < rows; i++)
		memset (_matrix[i], 0, columns * sizeof(long long));
}


//by Frederic Laffite, from boolfun
int choose (int n, int k)
{
    int i, num = 1, den = 1;

    if (k < 0 || k > n) 
		return 0;
    for (i = 0; i < k; ++i) 
	{
        num *= n--;
        den *= (k-i); 
	}
    return (num/den);
}


int preceq (int a, int b)
{
    int res = 1;

    while ((a > 0 || b > 0) && (res ==1)) 
	{
        if ((a & 1) > (b & 1)) res = 0;
        a >>= 1; 
		b >>= 1; 
	}
    return res;
}


int* sort_increasing_deg (int* v, int len)
{
    int i,j,tmp;

    for (i = 0; i < len-1; ++i)
        for (j = i+1; j < len; ++j)
            //if(hamming_weight(v[j]) < hamming_weight(v[i])) 
			if(hamming[v[j]] < hamming[v[i]]) 
			{
                tmp = v[j];
                v[j] = v[i];
                v[i] = tmp;
            }
    return v;
}


MAT* initialize_mat (MAT* mat, int nrow, int ncol)
{
    int i,j;

    mat = (MAT*) malloc (sizeof(MAT));
    mat->_n = nrow;
    mat->_m = ncol;
    mat->_v = (int**) malloc (nrow * sizeof(int*));
    for(i = 0; i < nrow; ++i) 
	{
        mat->_v[i] = (int*) malloc (ncol * sizeof(int));
        for(j=0; j < ncol; ++j)
            mat->_v[i][j] = 0;
    }
    return mat;
}

MAT* deallocate_mat (MAT* mat)
{
    int i;

    if(mat != NULL) 
	{
        if(mat->_v != NULL) 
		{
            for(i = 0; i < mat->_n; ++i)
                free(mat->_v[i]);
            free(mat->_v);
        }
        free(mat);
    }
    return NULL;
}


MAT* swap_columns (MAT* mat, int a, int b)
{
    int* tmp,i;

    tmp = (int*) malloc (mat->_n * sizeof(int));
    for (i = 0; i < mat->_n; ++i) 
		tmp[i] = mat->_v[i][a];
    for (i = 0; i < mat->_n; ++i) 
		mat->_v[i][a] = mat->_v[i][b];
    for (i = 0; i < mat->_n; ++i) 
		mat->_v[i][b] = tmp[i];
    free(tmp);
    return mat;
}


MAT* add_line (MAT* mat, int dst, int src)
{
    int j;

    for (j = 0; j < mat->_m; ++j)
        mat->_v[dst][j] = (mat->_v[dst][j] + mat->_v[src][j]) & 1;
    return mat;
}


int* get_monomials (int n, int d, int* res, int* N)
{
    int i, k;

    for (*N = 0, k = 0; k <= d; ++k)
        *N = *N + choose(n, k);
    res = (int *) malloc (*N * sizeof(int));
    for (k = 0, i = 0; i<(1<<n); ++i)
        //if (hamming_weight(i) <= d)
		if (hamming[i] <= d)
           res[k++] = i;
    return res;
}


int* get_support (const u8 ** tt, int n, int* res, int* N, int b)
{
    int i, k, len;

    len = 1 << n;
    for (*N = 0, i = 0; i < len; ++i)
        *N = *N + (tt[i][0] != b);
    res = (int *) malloc (*N * sizeof(int));
    for (k = 0, i = 0; i < len; ++i)
        if (tt[i][0] != b)
            res[k++] = i;
    return res;
}


MAT* get_matrix (const u8 ** tt, int n, MAT *m, int *monomials, int Nm, int ai, int b)
{
    int Ns, i, j, len, *support;
    len = 1 << n;
    support = NULL;
    support = get_support(tt, n, support, &Ns, b);
    if (Ns == 0 || Ns == len)
        m = NULL;
    else 
	{
        m = (Nm > Ns) ? initialize_mat(m, Nm, Nm): initialize_mat(m, Nm, Ns);
        for (i = 0; i < Nm; ++i)
            for (j = 0; j < Ns; ++j)
                m->_v[i][j] = preceq(monomials[i], support[j]);
    }
    free(support);
    return m;
}


int solve_matrix (MAT *m, int *monomials, int b)
{
    int i, j, l, res, *deg, processed_lines, zero_lines;

    deg = (int *) malloc (m->_n * sizeof(int));
    for (res = 0, i = 0; i < m->_n; ++i) 
	{
        //deg[i] = hamming_weight(monomials[i]);
		deg[i] = hamming[monomials[i]];
        if (deg[i] > res) 
			res = deg[i];
    }
    processed_lines = zero_lines = 0;
    for (i = 0; i < m->_n; ++i) 
	{
        for (j = 0; j < m->_m && m->_v[i][j] == 0; ++j);
        if (j == m->_m) 
		{
            ++ zero_lines;
            if (deg[i] < res && deg[i] != 0)
                res = deg[i];
        } 
		else 
		{
            ++ processed_lines;
            if (i != j && i < m->_m && j < m->_m)
                m = swap_columns(m, i, j);
            for (l = i+1; l < m->_n && i < m->_m; ++l) 
			{
                if (i < m->_m && m->_v[l][i] != 0) 
				{
                    m = add_line(m, l, i);
                    deg[l] = (deg[i] > deg[l]) ? deg[i] : deg[l];
                }
            }
        }
    }
    free (deg);
    return res;
}

void prepare(char *name, int argc, char *argv[])
{
	header();
	if (argc == 4)
	{
		M = atoi (argv[1]);
		N = atoi (argv[2]);
		sprintf (name, "%s", argv[3]);
	}
	else
	{
		printf("\nEnter input dimension M\n");
 		scanf("%d", &M);
		printf("Enter output dimension N\n");
 		scanf("%d", &N);
		printf("\nEnter filename\nFile must be *.txt where values are tab separated.\nProgram assumes that the values are in lexicographical order.\n");
		scanf("%s", name);
	}
	
	m_shift = 1 << M;
	n_shift = 1 << N;
	
	hamming = allocate_memory (m_shift);
	hamming_weights(hamming);

	if ((fin = fopen(name, "r")) == NULL)
	{
		printf("Error while opening file\n");
		exit(1);
	}
	input_array = allocate_memory (m_shift);
	read_from_file (check_data_format());
}


int compare (const void * a, const void * b)
{
  return (*(int*)a - *(int*)b);
}


/*
int find_min_value (int *tt, int x_shift)
{
	int i, res = 0;
	res = tt[0];
	for (i = 1; i < x_shift - 1; i++)
	{
		if (tt[i] < res)
			res = tt[i];
	}
	return res;
}


int find_max_value (int *tt, int x_shift)
{
	int i, res = 0;
	res = tt[0];
	for (i = 1; i < x_shift - 1; i++)
	{
		if (tt[i] > res)
			res = tt[i];
	}
	return res;
}


void set_to_zero (u8 *res, int x_shift)		//set array elements to zero value
{
	int i;
	for (i = 0; i < x_shift; i++)
		res[i] = 0;
}


void xor_elements (u8 *a1, u8 *a2, u8 *res, int x_shift)
{
	int z;
	for (z = 0; z < x_shift; z++)
	{
		res[z] = a1[z] ^ a2[z];
	}
}


int evaluate_box (u8 **tt, int x, int a)
{
 	int i, res1 = 0, res2 = 0;

	for (i = 0; i < N; i++)
	{
		res1 |= ((tt[i][x]) << i);
	}

	x = x ^ a;
	for (i = 0; i < N; i++)
		res2 |= ((tt[i][x]) << i);

	return res1 ^ res2;
}

*/