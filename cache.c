#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


#define INLINE
#define BUFFER_SIZE (2048ull * 2048ull)


struct thread_arg {
	double(* const fun)(void);
	double* const dest; 
};

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

	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i) {
		oop_data[i].a = oop_data[i].b = oop_data[i].c = oop_data[i].d = oop_data[i].e = randnum;
		oop_data[i].f = oop_data[i].g = oop_data[i].h = oop_data[i].i = oop_data[i].j = randnum * 2;
		oop_data[i].k = oop_data[i].l = oop_data[i].m = oop_data[i].n = oop_data[i].o = randnum * 3;
	}

	for (unsigned long long i = 0; i < BUFFER_SIZE * 5; i += 5) {
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

static double INLINE calculate_oop_abcde(void)
{
	double result = 0;

	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].a + oop_data[i].b + oop_data[i].c + oop_data[i].d + oop_data[i].e;

	return result;
}

static double INLINE calculate_oop_fghij(void)
{
	double result = 0;

	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].f + oop_data[i].g + oop_data[i].h + oop_data[i].i + oop_data[i].j;

	return result;
}

static double INLINE calculate_oop_klmno(void)
{
	double result = 0;

	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].k + oop_data[i].l + oop_data[i].m + oop_data[i].n + oop_data[i].o;

	return result;
}

static void INLINE calculate_oop_combined(double* const abcde,
                                   double* const fghij,
                                   double* const klmno)
{
	double a = 0, f = 0, k = 0;
	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i) {
		a += oop_data[i].a + oop_data[i].b + oop_data[i].c + oop_data[i].d + oop_data[i].e;
		f += oop_data[i].f + oop_data[i].g + oop_data[i].h + oop_data[i].i + oop_data[i].j;
		k += oop_data[i].k + oop_data[i].l + oop_data[i].m + oop_data[i].n + oop_data[i].o;
	}
	*abcde = a;
	*fghij = f;
	*klmno = k;
}


static double INLINE calculate_dod_abcde(void)
{
	double result = 0;
	
	for (unsigned long long i = 0; i < BUFFER_SIZE * 5; i += 5)
		result += dod_data[i] + dod_data[i + 1] + dod_data[i + 2] + dod_data[i + 3] + dod_data[i + 4];

	return result;
}


static double INLINE calculate_dod_fghij(void)
{
	double result = 0;
	
	for (unsigned long long i = 0; i < BUFFER_SIZE * 5; i += 5) {
		result += dod_data[BUFFER_SIZE * 5 + i] +
		          dod_data[BUFFER_SIZE * 5 + i + 1] +
		          dod_data[BUFFER_SIZE * 5 + i + 2] +
		          dod_data[BUFFER_SIZE * 5 + i + 3] +
		          dod_data[BUFFER_SIZE * 5 + i + 4];
	}

	return result;
}

static double INLINE calculate_dod_klmno(void)
{
	double result = 0;
	
	for (unsigned long long i = 0; i < BUFFER_SIZE * 5; i += 5) {
		result += dod_data[BUFFER_SIZE * 5 * 2 + i] +
		          dod_data[BUFFER_SIZE * 5 * 2 + i + 1] +
		          dod_data[BUFFER_SIZE * 5 * 2 + i + 2] +
		          dod_data[BUFFER_SIZE * 5 * 2 + i + 3] +
		          dod_data[BUFFER_SIZE * 5 * 2 + i + 4];
	}

	return result;
}

static void INLINE calculate_dod_combined(double* const abcde,
                                   double* const fghij,
				   double* const klmno)
{
	double a = 0, f = 0, k = 0;
	
	for (unsigned long long i = 0; i < BUFFER_SIZE * 5; i += 5) {
		a += dod_data[i] + dod_data[i + 1] + dod_data[i + 2] + dod_data[i + 3] + dod_data[i + 4];

		f += dod_data[BUFFER_SIZE * 5 + i] +
		     dod_data[BUFFER_SIZE * 5 + i + 1] +
		     dod_data[BUFFER_SIZE * 5 + i + 2] +
		     dod_data[BUFFER_SIZE * 5 + i + 3] +
		     dod_data[BUFFER_SIZE * 5 + i + 4];

		k += dod_data[BUFFER_SIZE * 5 * 2 + i] +
		     dod_data[BUFFER_SIZE * 5 * 2 + i + 1] +
		     dod_data[BUFFER_SIZE * 5 * 2 + i + 2] +
		     dod_data[BUFFER_SIZE * 5 * 2 + i + 3] +
		     dod_data[BUFFER_SIZE * 5 * 2 + i + 4];
	}

	*abcde = a;
	*fghij = f;
	*klmno = k;

}

static void* INLINE thread_fun(const struct thread_arg* const ta)
{
	double r = 0;
	for (unsigned long long i = 0; i < 128; ++i)
		r = ta->fun();
	*ta->dest = r;
	return NULL;
}

static void print_result(const char* const info,
                         const double abcde,
                         const double fghij,
                         const double klmno,
                         const double secs)
{
	printf("TEST: %s\n"
	       "ABCDE: %lf\n"
	       "FGHIJ: %lf\n"
	       "KLMNO: %lf\n"
	       "TIME: %lf secs\n"
	       "-----------------------------------\n",
	       info, abcde, fghij, klmno, secs);
}


int main(void)
{
	init_data();

	volatile clock_t begin, end;
	double abcde = 0, fghij = 0, klmno = 0;


	/* OOP data layout is bad if we want to calculate data sets separately */
	puts("TESTING OOP SEPARATELY CALCULATION");
	begin = clock();
	
	for (unsigned long long i = 0; i < 128; ++i) {
		abcde = calculate_oop_abcde();
		fghij = calculate_oop_fghij();
		klmno = calculate_oop_klmno();
	}
	
	end = clock();
	print_result("OOP SEPARATELY", abcde, fghij, klmno,
	             ((double)end - begin) / CLOCKS_PER_SEC);


	/* but OOP data layout is good if we want all the data at the same time */
	puts("TESTING OOP COMBINED CALCULATION");
	begin = clock();
	
	for (unsigned long long i = 0; i < 128; ++i)
		calculate_oop_combined(&abcde, &fghij, &klmno);
	
	end = clock();
	print_result("OOP COMBINED", abcde, fghij, klmno,
	             ((double)end - begin) / CLOCKS_PER_SEC);

	
	/* DOD data layout is great if we want to calculate data sets separately */
	puts("TESTING DOD SEPARATELY CALCULATION");
	begin = clock();

	for (unsigned long long i = 0; i < 128; ++i) {
		abcde = calculate_dod_abcde();
		fghij = calculate_dod_fghij();
		klmno = calculate_dod_klmno();
	}

	end = clock();
	print_result("DOD SEPARATELY", abcde, fghij, klmno,
	             ((double)end - begin) / CLOCKS_PER_SEC);


	/* DOD COMBINED ?? */
	puts("TESTING DOD COMBINED CALCULATION");
	begin = clock();

	for (unsigned long long i = 0; i < 128; ++i)
		calculate_dod_combined(&abcde, &fghij, &klmno);

	end = clock();
	print_result("DOD COMBINED", abcde, fghij, klmno,
	             ((double)end - begin) / CLOCKS_PER_SEC);


	/* DOD data layout is good for multi-threading */
	puts("TESTING DOD MULTI-THREADED CALCULATION");
	begin = clock();

	pthread_t thrd_abcde, thrd_fghij, thrd_klmno;
	struct thread_arg thrd_abcde_arg = { calculate_dod_abcde, &abcde };
	struct thread_arg thrd_fghij_arg = { calculate_dod_fghij, &fghij };
	struct thread_arg thrd_klmno_arg = { calculate_dod_klmno, &klmno };
	pthread_create(&thrd_abcde,  NULL, (void*)thread_fun, &thrd_abcde_arg);
	pthread_create(&thrd_fghij, NULL, (void*)thread_fun, &thrd_fghij_arg);
	thread_fun(&thrd_klmno_arg);
	pthread_join(thrd_abcde, NULL);
	pthread_join(thrd_fghij, NULL);

	end = clock();
	print_result("DOD MULTI-THREADED", abcde, fghij, klmno,
	             ((double)end - begin) / CLOCKS_PER_SEC);

	free_data();

	return EXIT_SUCCESS;
}


