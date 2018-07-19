#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <pthread.h>

/*
struct thread_arg {
	double (*const fun)(void);
	double* const dest; 
};
*/

static struct oop_data {
	double a, b, c, d, e;
	double f, g, h, i, j;
	double k, l, m, n, o;
} *oop_data = NULL;

static double* dod_data = NULL;

static unsigned long long BUFFER_SIZE = 0;


static void alloc_data(unsigned long long buffer_size)
{
	BUFFER_SIZE = buffer_size;
	oop_data = malloc(sizeof(struct oop_data) * BUFFER_SIZE);
	dod_data = malloc(sizeof(double) * 5 * 3 * BUFFER_SIZE);
}

static void free_data(void)
{
	free(dod_data);
	free(oop_data);
}

static void oop_fill(int base_num)
{

	for (unsigned long long i = 0; i < BUFFER_SIZE; ++i) {
		oop_data[i].a = oop_data[i].b = oop_data[i].c = oop_data[i].d = oop_data[i].e = base_num;
		oop_data[i].f = oop_data[i].g = oop_data[i].h = oop_data[i].i = oop_data[i].j = base_num * 2;
		oop_data[i].k = oop_data[i].l = oop_data[i].m = oop_data[i].n = oop_data[i].o = base_num * 3;
	}
}

static void dod_fill(int base_num)
{
	for (unsigned long long i = 0; i < BUFFER_SIZE * 5; i += 5) {
		dod_data[i] = base_num;
		dod_data[i + 1] = base_num;
		dod_data[i + 2] = base_num;
		dod_data[i + 3] = base_num;
		dod_data[i + 4] = base_num;

		dod_data[BUFFER_SIZE * 5 + i] = base_num * 2;
		dod_data[BUFFER_SIZE * 5 + i + 1] = base_num * 2;
		dod_data[BUFFER_SIZE * 5 + i + 2] = base_num * 2;
		dod_data[BUFFER_SIZE * 5 + i + 3] = base_num * 2;
		dod_data[BUFFER_SIZE * 5 + i + 4] = base_num * 2;

		dod_data[BUFFER_SIZE * 5 * 2 + i] = base_num * 3;
		dod_data[BUFFER_SIZE * 5 * 2 + i + 1] = base_num * 3;
		dod_data[BUFFER_SIZE * 5 * 2 + i + 2] = base_num * 3;
		dod_data[BUFFER_SIZE * 5 * 2 + i + 3] = base_num * 3;
		dod_data[BUFFER_SIZE * 5 * 2 + i + 4] = base_num * 3;
	}

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
		a += oop_data[i].a + oop_data[i].f + oop_data[i].k + oop_data[i].b + oop_data[i].g;
		f += oop_data[i].l + oop_data[i].c + oop_data[i].h + oop_data[i].m + oop_data[i].d;
		k += oop_data[i].i + oop_data[i].n + oop_data[i].e + oop_data[i].j + oop_data[i].o;
	}
	*abcde = a;
	*fghij = f;
	*klmno = k;
}

static double calculate_dod_abcde(void)
{
	double result = 0;
	const unsigned long long len = BUFFER_SIZE * 5;
	for (unsigned long long i = 0; i < len; i += 5)
		result += dod_data[i] + dod_data[i + 1] + dod_data[i + 2] + dod_data[i + 3] + dod_data[i + 4];

	return result;
}


static double calculate_dod_fghij(void)
{
	double result = 0;
	const unsigned long long len = BUFFER_SIZE * 5;
	for (unsigned long long i = 0; i < len; i += 5) {
		result += dod_data[len + i] +
		          dod_data[len + i + 1] +
		          dod_data[len + i + 2] +
		          dod_data[len + i + 3] +
		          dod_data[len + i + 4];
	}

	return result;
}

static double calculate_dod_klmno(void)
{
	double result = 0;
	const unsigned long long len = BUFFER_SIZE * 5;
	for (unsigned long long i = 0; i < len; i += 5) {
		result += dod_data[len * 2 + i] +
		          dod_data[len * 2 + i + 1] +
		          dod_data[len * 2 + i + 2] +
		          dod_data[len * 2 + i + 3] +
		          dod_data[len * 2 + i + 4];
	}

	return result;
}

static void calculate_dod_combined(double* const abcde,
                                   double* const fghij,
                                   double* const klmno)
{
	double a = 0, f = 0, k = 0;
	const unsigned long long len = BUFFER_SIZE * 5;
	for (unsigned long long i = 0; i < len; i += 5) {
		a += dod_data[i] +
		     dod_data[len + i] +
		     dod_data[len * 2 + i] +
		     dod_data[i + 1] +
		     dod_data[len + i + 1];

		f += dod_data[len * 2 + i + 1] +
		     dod_data[i + 2] +
		     dod_data[len + i + 2] +
		     dod_data[len * 2 + i + 2] +
		     dod_data[i + 3];

		k += dod_data[len + i + 3] +
		     dod_data[len * 2 + i + 3] +
		     dod_data[i + 4] +
		     dod_data[len + i + 4] +
		     dod_data[len * 2 + i + 4];
	}

	*abcde = a;
	*fghij = f;
	*klmno = k;

}

/*
static void* thread_fun(const struct thread_arg* const ta)
{
	*ta->dest = ta->fun();
	return NULL;
}
*/

static void run_test(const char* const test_info, void(*const test_fun)(double*,double*,double*))
{
	double abcde, fghij, klmno;
	const clock_t begin = clock();
	test_fun(&abcde, &fghij, &klmno);
	const clock_t end = clock();
	const double secs = ((double)end - begin) / CLOCKS_PER_SEC;
	printf("TEST: %s\n"
	       "ABCDE: %lf\n"
	       "FGHIJ: %lf\n"
	       "KLMNO: %lf\n"
	       "TIME: %.3lf secs\n"
	       "-----------------------------------\n",
	       test_info, abcde, fghij, klmno, secs);
}


static void test_fun_oop_separately(double* const abcde,
                                    double* const fghij,
                                    double* const klmno)
{
	*abcde = calculate_oop_abcde();
	*fghij = calculate_oop_fghij();
	*klmno = calculate_oop_klmno();
}


static void test_fun_dod_separately(double* const abcde,
                                    double* const fghij,
                                    double* const klmno)
{
	*abcde = calculate_dod_abcde();
	*fghij = calculate_dod_fghij();
	*klmno = calculate_dod_klmno();
}

/*
static void test_fun_dod_multithreaded(double* const abcde,
                                       double* const fghij,
                                       double* const klmno)
{
	pthread_t thrd_abcde, thrd_fghij, thrd_klmno;
	struct thread_arg thrd_abcde_arg = { calculate_dod_abcde, abcde };
	struct thread_arg thrd_fghij_arg = { calculate_dod_fghij, fghij };
	struct thread_arg thrd_klmno_arg = { calculate_dod_klmno, klmno };
	pthread_create(&thrd_abcde,  NULL, (void*)thread_fun, &thrd_abcde_arg);
	pthread_create(&thrd_fghij,  NULL, (void*)thread_fun, &thrd_fghij_arg);
	thread_fun(&thrd_klmno_arg);
	pthread_join(thrd_abcde, NULL);
	pthread_join(thrd_fghij, NULL);
}
*/

int main(int argc, char** argv)
{
	if (argc < 6) {
		fprintf(stderr, 
		        "Usage: %s [oop separately base num] [oop combined base num] "
		        "[dod separately base num] [dod combined base num] "
		        "[buffer size]\n", argv[0]);
		return EXIT_FAILURE;
	}

	const int oop_separately_base_num = strtoll(argv[1], NULL, 10);
	const int oop_combined_base_num = strtoll(argv[2], NULL, 10);
	const int dod_separately_base_num = strtoll(argv[3], NULL, 10);
	const int dod_combined_base_num = strtoll(argv[4], NULL, 10);

	alloc_data(strtoll(argv[5], NULL, 10));

	/* OOP data layout is bad if we want to calculate data sets separately */
	oop_fill(oop_separately_base_num);
	puts("TESTING OOP SEPARATELY CALCULATION");
	run_test("OOP SEPARATELY CALCULATION", test_fun_oop_separately);

	/* but OOP data layout is good if we want all the data at the same time */
	oop_fill(oop_combined_base_num);
	puts("TESTING OOP COMBINED CALCULATION");
	run_test("OOP COMBINED CALCULATION", calculate_oop_combined);
	
	/* DOD data layout is great if we want to calculate data sets separately */
	dod_fill(dod_separately_base_num);
	puts("TESTING DOD SEPARATELY CALCULATION");
	run_test("DOD SEPARATELY CALCULATION", test_fun_dod_separately);
	
	/* DOD COMBINED is awesome too */
	dod_fill(dod_combined_base_num);
	puts("TESTING DOD COMBINED CALCULATION");
	run_test("DOD COMBINED CALCULATION", calculate_dod_combined);

	/* DOD data layout is good for multi-threading */
	/*
	dod_fill(base_nums[BN_DOD_MULTITHREAD]);
	puts("TESTING DOD SEPARATELY MULTI-THREADED CALCULATION");
	run_test("DOD MULTI-THREADED CALCULATION", test_fun_dod_multithreaded);
	*/

	free_data();

	return EXIT_SUCCESS;
}


