#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define BUFFER_SIZE (2048ull * 1024ull)

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

static double calculate_oop_abcde(void)
{
	double result = 0;

	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].a + oop_data[i].b + oop_data[i].c + oop_data[i].d + oop_data[i].e;

	return result;
}

static double calculate_oop_fghij(void)
{
	double result = 0;

	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].f + oop_data[i].g + oop_data[i].h + oop_data[i].i + oop_data[i].j;

	return result;
}

static double calculate_oop_klmno(void)
{
	double result = 0;

	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].k + oop_data[i].l + oop_data[i].m + oop_data[i].n + oop_data[i].o;

	return result;
}

static void calculate_oop_combined(double* const abcde,
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


static double calculate_dod_abcde(void)
{
	double result = 0;
	
	for (unsigned long long i = 0; i < BUFFER_SIZE * 5; i += 5)
		result += dod_data[i] + dod_data[i + 1] + dod_data[i + 2] + dod_data[i + 3] + dod_data[i + 4];

	return result;
}


static double calculate_dod_fghij(void)
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

static double calculate_dod_klmno(void)
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

static void* thread_fun(const struct thread_arg* const ta)
{
	double r = 0;
	for (unsigned long long i = 0; i < 128; ++i)
		r = ta->fun();
	*ta->dest = r;
	return NULL;
}


int main(void)
{
	init_data();

	clock_t begin, end;
	double dod_time, dod_multithread_time, oop_single_time, oop_combined_time;

	double oop_abcde = 0, oop_fghij = 0, oop_klmno = 0;
	double dod_abcde = 0, dod_fghij = 0, dod_klmno = 0;

	pthread_t thrd_abcde, thrd_fghij, thrd_klmno;

	/* OOP data layout is bad if we want to calculate data sets separately */
	begin = clock();
	
	for (unsigned long long i = 0; i < 128; ++i) {
		oop_abcde = calculate_oop_abcde();
		oop_fghij = calculate_oop_fghij();
		oop_klmno = calculate_oop_klmno();
	}
	
	end = clock();
	oop_single_time = ((double)end - begin) / CLOCKS_PER_SEC;
	printf("%lf\n%lf\n%lf\r", oop_abcde, oop_fghij, oop_klmno);

	/* but OOP data layout is good if we want all the data at the same time */
	begin = clock();
	
	for (unsigned long long i = 0; i < 128; ++i)
		calculate_oop_combined(&oop_abcde, &oop_fghij, &oop_klmno);
	
	end = clock();
	oop_combined_time = ((double)end - begin) / CLOCKS_PER_SEC;


	/* DOD data layout is great if we want to calculate data sets separately */
	begin = clock();
	for (unsigned long long i = 0; i < 128; ++i) {
		dod_abcde = calculate_dod_abcde();
		dod_fghij = calculate_dod_fghij();
		dod_klmno = calculate_dod_klmno();
	}
	end = clock();
	dod_time = ((double)end - begin) / CLOCKS_PER_SEC;
	printf("\n%lf\n%lf\n%lf\r", dod_abcde, dod_fghij, dod_klmno);

	/* DOD data layout is good for multi-threading */
	begin = clock();
	
	struct thread_arg thrd_abcde_arg = { calculate_dod_abcde, &dod_abcde };
	struct thread_arg thrd_fghij_arg = { calculate_dod_fghij, &dod_fghij };
	struct thread_arg thrd_klmno_arg = { calculate_dod_klmno, &dod_klmno };
	pthread_create(&thrd_abcde,  NULL, (void*)thread_fun, &thrd_abcde_arg);
	pthread_create(&thrd_fghij, NULL, (void*)thread_fun, &thrd_fghij_arg);
	thread_fun(&thrd_klmno_arg);
	pthread_join(thrd_abcde, NULL);
	pthread_join(thrd_fghij, NULL);

	end = clock();
	dod_multithread_time = ((double)end - begin) / CLOCKS_PER_SEC;

	printf("OOP ABCDE: %lf\n"
	       "OOP FGHIJ: %lf\n"
	       "OOP KLMNO: %lf\n"
	       "OOP SINGLE TIME: %lf secs\n"
	       "OOP COMBINED TIME: %lf secs\n"
	       "-----------------------------------\n"
	       "DOD ABCDE: %lf\n"
	       "DOD FGHIJ: %lf\n"
	       "DOD KLMNO: %lf\n"
	       "DOD TIME: %lf secs\n"
	       "DOD MULTI-THREADED TIME: %lf\n"
	       "-----------------------------------\n",
	       oop_abcde, oop_fghij, oop_klmno,  oop_single_time, oop_combined_time,
	       dod_abcde, dod_fghij, dod_klmno, dod_time, dod_multithread_time);

	free_data();

	return EXIT_SUCCESS;
}


