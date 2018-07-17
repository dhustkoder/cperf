#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


#define INLINE


struct thread_arg {
	double (*const fun)(void);
	double* const dest; 
};

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
		a += oop_data[i].a + oop_data[i].f + oop_data[i].k + oop_data[i].b + oop_data[i].g;
		f += oop_data[i].l + oop_data[i].c + oop_data[i].h + oop_data[i].m + oop_data[i].d;
		k += oop_data[i].i + oop_data[i].n + oop_data[i].e + oop_data[i].j + oop_data[i].o;
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
		a += dod_data[i] +
		     dod_data[BUFFER_SIZE * 5 + i] +
		     dod_data[BUFFER_SIZE * 5 * 2 + i] +
		     dod_data[i + 1] +
		     dod_data[BUFFER_SIZE * 5 + i + 1];

		f += dod_data[BUFFER_SIZE * 5 * 2 + i + 1] +
		     dod_data[i + 2] +
		     dod_data[BUFFER_SIZE * 5 + i + 2] +
		     dod_data[BUFFER_SIZE * 5 * 2 + i + 2] +
		     dod_data[i + 3];

		k += dod_data[BUFFER_SIZE * 5 + i + 3] +
		     dod_data[BUFFER_SIZE * 5 * 2 + i + 3] +
		     dod_data[i + 4] +
		     dod_data[BUFFER_SIZE * 5 + i + 4] +
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


int main(int argc, char** argv)
{
	if (argc < 6) {
		fprintf(stderr, 
		        "Usage: %s [oop separately base num] [oop combined base num] "
		        "[dod separately base num] [dod combined base num] "
		        "[dod separately multi-thread base num] [buffer size]\n", argv[0]);
		return EXIT_FAILURE;
	}

	enum base_nums_index {
		BN_OOP_SEPARATELY,
		BN_OOP_COMBINED,
		BN_DOD_SEPARATELY,
		BN_DOD_COMBINED,
		BN_DOD_MULTITHREAD
	};
	const int base_nums[] = {
		[BN_OOP_SEPARATELY] = strtoll(argv[1], NULL, 10),
		[BN_OOP_COMBINED] = strtoll(argv[2], NULL, 10),
		[BN_DOD_SEPARATELY] = strtoll(argv[3], NULL, 10),
		[BN_DOD_COMBINED] = strtoll(argv[4], NULL, 10),
		[BN_DOD_MULTITHREAD] = strtoll(argv[5], NULL, 10)
	};

	alloc_data(strtoll(argv[6], NULL, 10));

	volatile clock_t begin, end;
	double abcde = 0, fghij = 0, klmno = 0;

	/* OOP data layout is bad if we want to calculate data sets separately */
	oop_fill(base_nums[BN_OOP_SEPARATELY]);
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
	oop_fill(base_nums[BN_OOP_COMBINED]);
	puts("TESTING OOP COMBINED CALCULATION");
	begin = clock();
	
	for (unsigned long long i = 0; i < 128; ++i)
		calculate_oop_combined(&abcde, &fghij, &klmno);
	
	end = clock();
	print_result("OOP COMBINED", abcde, fghij, klmno,
	             ((double)end - begin) / CLOCKS_PER_SEC);


	/* DOD data layout is great if we want to calculate data sets separately */
	dod_fill(base_nums[BN_DOD_SEPARATELY]);
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
	dod_fill(base_nums[BN_DOD_COMBINED]);
	puts("TESTING DOD COMBINED CALCULATION");
	begin = clock();

	for (unsigned long long i = 0; i < 128; ++i)
		calculate_dod_combined(&abcde, &fghij, &klmno);

	end = clock();
	print_result("DOD COMBINED", abcde, fghij, klmno,
	             ((double)end - begin) / CLOCKS_PER_SEC);


	/* DOD data layout is good for multi-threading */
	dod_fill(base_nums[BN_DOD_MULTITHREAD]);
	puts("TESTING DOD SEPARATELY MULTI-THREADED CALCULATION");
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
	print_result("DOD SEPARATELY MULTI-THREADED", abcde, fghij, klmno,
	             ((double)end - begin) / CLOCKS_PER_SEC);

	free_data();

	return EXIT_SUCCESS;
}


