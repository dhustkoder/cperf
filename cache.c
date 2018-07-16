#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE (1024 * 2048)


static struct oop_data {
	double a, b, c, d, e;
	double f, g, h, i, j;
	double k, l, m, n, o;
} *oop_data = NULL;

static double* dod_data = NULL;


static void init_data(void)
{
	oop_data = malloc(sizeof(struct oop_data) * BUFFER_SIZE);
	dod_data = malloc(sizeof(double) * 5 * 3 * BUFFER_SIZE);

	srand(time(NULL));
	const double randnum = rand();

	for (int i = 0; i < BUFFER_SIZE; ++i) {
		oop_data[i].a = oop_data[i].b = oop_data[i].c = oop_data[i].d = oop_data[i].e = randnum;
		oop_data[i].f = oop_data[i].g = oop_data[i].h = oop_data[i].i = oop_data[i].j = randnum * 2;
		oop_data[i].k = oop_data[i].l = oop_data[i].m = oop_data[i].n = oop_data[i].o = randnum * 3;
	}

	for (int i = 0; i < BUFFER_SIZE * 5; i += 5) {
		dod_data[i] = randnum;
		dod_data[i + 1] = randnum;
		dod_data[i + 2] = randnum;
		dod_data[i + 3] = randnum;
		dod_data[i + 4] = randnum;

		dod_data[BUFFER_SIZE * 5 + i] = randnum * 2;
		dod_data[BUFFER_SIZE * 5 + i + 1] = randnum * 2;
		dod_data[BUFFER_SIZE * 5 + i + 2] = randnum * 2;
		dod_data[BUFFER_SIZE * 5 + i + 3] = randnum * 2;
		dod_data[BUFFER_SIZE * 5 + i + 4] = randnum * 2;

		dod_data[BUFFER_SIZE * 5 * 2 + i] = randnum * 3;
		dod_data[BUFFER_SIZE * 5 * 2 + i + 1] = randnum * 3;
		dod_data[BUFFER_SIZE * 5 * 2 + i + 2] = randnum * 3;
		dod_data[BUFFER_SIZE * 5 * 2 + i + 3] = randnum * 3;
		dod_data[BUFFER_SIZE * 5 * 2 + i + 4] = randnum * 3;
	}

}

static void free_data(void)
{
	free(dod_data);
	free(oop_data);
}

static double calculate_oop_abcde(void)
{
	double result = 0;

	for (int i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].a + oop_data[i].b + oop_data[i].c + oop_data[i].d + oop_data[i].e;

	return result;
}

static double calculate_oop_fghij(void)
{
	double result = 0;

	for (int i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].f + oop_data[i].g + oop_data[i].h + oop_data[i].i + oop_data[i].j;

	return result;
}

static double calculate_oop_klmno(void)
{
	double result = 0;

	for (int i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].k + oop_data[i].l + oop_data[i].m + oop_data[i].n + oop_data[i].o;

	return result;
}

static void calculate_oop_optimized(double* const abcde, double* const fghij, double* const klmno)
{
	double a = 0, f = 0, k = 0;
	for (int i = 0; i < BUFFER_SIZE; ++i) {
		a += oop_data[i].a + oop_data[i].b + oop_data[i].c + oop_data[i].d + oop_data[i].e;
		f += oop_data[i].f + oop_data[i].g + oop_data[i].h + oop_data[i].i + oop_data[i].j;
		k += oop_data[i].k + oop_data[i].l + oop_data[i].m + oop_data[i].n + oop_data[i].o;
	}
	*abcde = a;
	*fghij = f;
	*klmno = k;
}


static double calculate_dod_abcde(void)
{
	double result = 0;
	
	for (int i = 0; i < BUFFER_SIZE * 5; i += 5)
		result += dod_data[i] + dod_data[i + 1] + dod_data[i + 2] + dod_data[i + 3] + dod_data[i + 4];

	return result;
}


static double calculate_dod_fghij(void)
{
	double result = 0;
	
	for (int i = 0; i < BUFFER_SIZE * 5; i += 5) {
		result += dod_data[BUFFER_SIZE * 5 + i] +
		          dod_data[BUFFER_SIZE * 5 + i + 1] +
		          dod_data[BUFFER_SIZE * 5 + i + 2] +
		          dod_data[BUFFER_SIZE * 5 + i + 3] +
		          dod_data[BUFFER_SIZE * 5 + i + 4];
	}

	return result;
}

static double calculate_dod_klmno(void)
{
	double result = 0;
	
	for (int i = 0; i < BUFFER_SIZE * 5; i += 5) {
		result += dod_data[BUFFER_SIZE * 5 * 2 + i] +
		          dod_data[BUFFER_SIZE * 5 * 2 + i + 1] +
		          dod_data[BUFFER_SIZE * 5 * 2 + i + 2] +
		          dod_data[BUFFER_SIZE * 5 * 2 + i + 3] +
		          dod_data[BUFFER_SIZE * 5 * 2 + i + 4];
	}

	return result;
}

int main(void)
{
	init_data();

	volatile clock_t begin, end, dod_time, oop_time;

	double oop_abcde, oop_fghij, oop_klmno;
	double dod_abcde, dod_fghij, dod_klmno;

	for (int i = 0; i < 255; ++i) {
		begin = clock();
		dod_abcde = calculate_dod_abcde();
		dod_fghij = calculate_dod_fghij();
		dod_klmno = calculate_dod_klmno();
		end = clock();
		dod_time = end - begin;
	}

	/*

	for (int i = 0; i < 255; ++i) {
		begin = clock();
		oop_abcde = calculate_oop_abcde();
		oop_fghij = calculate_oop_fghij();
		oop_klmno = calculate_oop_klmno();
		end = clock();
		oop_time = end - begin;
	}

	*/


	/* optimized OOP data parse */
	for (int i = 0; i < 255; ++i) {
		begin = clock();
		calculate_oop_optimized(&oop_abcde, &oop_fghij, &oop_klmno);
		end = clock();
		oop_time = end - begin;
	}


	printf("OOP ABCDE: %lf\n"
	       "OOP FGHIJ: %lf\n"
	       "OOP KLMNO: %lf\n"
	       "OOP TIME: %lf secs\n"
	       "-----------------------------------\n"
	       "DOD ABCDE: %lf\n"
	       "DOD FGHIJ: %lf\n"
	       "DOD KLMNO: %lf\n"
	       "DOD TIME: %lf secs\n"
	       "-----------------------------------\n",
	       oop_abcde, oop_fghij, oop_klmno, ((double)oop_time / (double)CLOCKS_PER_SEC),
	       dod_abcde, dod_fghij, dod_klmno, ((double)dod_time / (double)CLOCKS_PER_SEC));

	free_data();

	return EXIT_SUCCESS;
}


