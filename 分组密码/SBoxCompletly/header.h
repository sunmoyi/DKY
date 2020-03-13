#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

typedef unsigned char u8;
typedef unsigned int uint;

typedef struct													//struct for algebraic immunity
{
	int _n, _m, **_v;
} MAT;

uint *hamming;
uint M, N, m_shift, n_shift;
FILE *fin;
char name[100];
uint *input_array;


//memory allocation/deallocation
int ** allocate_matrix (uint, uint);
long long ** allocate_matrix_long(uint, uint);
u8 ** allocate_matrix_u8 (uint, uint);
void allocate_memory_multi (int, int, ...);
uint * allocate_memory (int);
void deallocate_memory_multi (int, ...);
void deallocate_memory (uint **);


//helper functions

void header();
void read_from_file(int);
uint check_data_format ();
void hamming_weights (uint *);									//create hamming weight array
int hamming_weight (int);										//calculate Hamming weightvoid header();
void s_box_info(char *name);
double get_time (clock_t, clock_t);
int evaluate_box (u8 **, int, int);						//evaluate S-box for the derivative of F in direction of a
int inner_product (int, int);								//calculate inner product of two vectors
void set_to_zero_u8 (u8 **, uint, uint);
void set_to_zero (int **, uint, uint);
void set_to_zero_long (long long **, uint, uint);
void xor_elements (u8 **, u8 **, u8 **, uint, uint);
void check(uint *input_array, int columns);
void prepare(char *, int, char **);
int compare (const void *, const void *);
MAT* initialize_mat (MAT*, int, int);							//for algebraic immunity
MAT* deallocate_mat (MAT*);										//for algebraic immunity
MAT* swap_columns (MAT*, int, int);								//for algebraic immunity
MAT* add_line (MAT*, int, int);									//for algebraic immunity
int* get_monomials (int, int, int*, int*);						//for algebraic immunity
int* get_support (const u8 **, int, int*, int*, int);			//for algebraic immunity
MAT* get_matrix (const u8 **, int, MAT*, int*, int, int, int);	//for algebraic immunity
int solve_matrix (MAT*, int*, int);								//for algebraic immunity
int* sort_increasing_deg (int *, int);

void output_array_to_file (char *, int *, int, int);
void output_matrix (int **, uint, uint);
void output_matrix_u8 (u8 **, uint, uint);
void output_matrix_transpose (int **, uint, uint);
void output_matrix_u8_transpose (u8 **, uint, uint);
void store_matrix (int **, uint, uint, char *);
void store_matrix_u8 (u8 **, uint, uint, char *);

//representations
void truth_table (u8 **);
int walsh_transform_naive (u8 **, int **);
int autocorrelation_fast (u8 **, int **, int **);
int walsh_transform (u8 **, int **);
int autocorrelation (u8 **, int **);
void linear_combinations (u8 **, u8 **);


//properties
int balance_naive (uint *);
void balancedness (int);
float get_transparency ();							//calculate transparency order of S-box
float get_transparency_fast ();							//calculate transparency order of S-box, another formula, faster execution
float get_snr_dpa (u8 **);								//calculate SNR (DPA) (F)
float get_robustness (uint *);					//calculate robustness to differential cryptanalysis, also calculate delta-uniformity
int get_delta_uniformity (float *);
int get_branch_number();
void lat ();
void ddt ();
int balance (int **, uint *);
int nonlinearity (int **, uint *);
int correlation_immunity (int **, uint *);
unsigned int absolute_indicator (int **, uint *); 
unsigned int sum_of_square_indicator (int **, uint *);
int propagation_characteristics ();
void coordinate_function_values (int *);
int algebraic_normal_form (u8 **, int **);
int algebraic_degree (int **, uint *);
int algebraic_term (int **anf, uint *components);
int algebraic_immunity (u8 **, uint *);
uint get_num_fixed_points (uint);						//finds number of fixed points
uint get_num_opposite_fixed_points (uint);			//finds number of opposite fixed points
void get_derivative (uint *, uint *, uint, uint);
void strict_avalanche_criterion (uint);
float computeKappaCPA(int, int, int);
void computeKappaDPA(int, int, int, int);

//Boolean function only
int bias_nonlinearity (int);								//bias of nonlinearity for Boolean functions, usually called internaly
int is_bent (int);											//check if Boolean function is bent, usually called internaly
void wt_boolean (u8 *);								//checking if Boolean function is bent, linearity and bias of nonlinearity
void polar_representation (int *);							//polar representation of a Boolean function


#endif