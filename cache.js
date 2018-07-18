
oop_data = [];
dod_data = [];
BUFFER_SIZE = 0;


function alloc_data(buffer_size)
{
	BUFFER_SIZE = buffer_size;
	oop_data = Array(BUFFER_SIZE).fill({});
	dod_data = Array(BUFFER_SIZE * 5 * 3).fill(0.0);
}

function oop_fill(base_num)
{
	for (i = 0; i < BUFFER_SIZE; ++i) {
		oop_data[i].a = oop_data[i].b = oop_data[i].c = oop_data[i].d = oop_data[i].e = parseFloat(base_num);
		oop_data[i].f = oop_data[i].g = oop_data[i].h = oop_data[i].i = oop_data[i].j = parseFloat(base_num * 2.0);
		oop_data[i].k = oop_data[i].l = oop_data[i].m = oop_data[i].n = oop_data[i].o = parseFloat(base_num * 3.0);
	}
}

function dod_fill(base_num)
{
	for (i = 0; i < BUFFER_SIZE * 5; i += 5) {
		dod_data[i] = parseFloat(base_num);
		dod_data[i + 1] = parseFloat(base_num);
		dod_data[i + 2] = parseFloat(base_num);
		dod_data[i + 3] = parseFloat(base_num);
		dod_data[i + 4] = parseFloat(base_num);

		dod_data[BUFFER_SIZE * 5 + i] = parseFloat(base_num * 2);
		dod_data[BUFFER_SIZE * 5 + i + 1] = parseFloat(base_num * 2);
		dod_data[BUFFER_SIZE * 5 + i + 2] = parseFloat(base_num * 2);
		dod_data[BUFFER_SIZE * 5 + i + 3] = parseFloat(base_num * 2);
		dod_data[BUFFER_SIZE * 5 + i + 4] = parseFloat(base_num * 2);

		dod_data[BUFFER_SIZE * 5 * 2 + i] = parseFloat(base_num * 3);
		dod_data[BUFFER_SIZE * 5 * 2 + i + 1] = parseFloat(base_num * 3);
		dod_data[BUFFER_SIZE * 5 * 2 + i + 2] = parseFloat(base_num * 3);
		dod_data[BUFFER_SIZE * 5 * 2 + i + 3] = parseFloat(base_num * 3);
		dod_data[BUFFER_SIZE * 5 * 2 + i + 4] = parseFloat(base_num * 3);
	}

}

function calculate_oop_abcde()
{
	result = 0;

	for (i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].a + oop_data[i].b + oop_data[i].c + oop_data[i].d + oop_data[i].e;

	return result;
}

function calculate_oop_fghij()
{
	result = 0;

	for (i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].f + oop_data[i].g + oop_data[i].h + oop_data[i].i + oop_data[i].j;

	return result;
}

function calculate_oop_klmno()
{
	result = 0.0;

	for (i = 0; i < BUFFER_SIZE; ++i)
		result += oop_data[i].k + oop_data[i].l + oop_data[i].m + oop_data[i].n + oop_data[i].o;

	return result;
}

function calculate_oop_combined()
{
	a = 0.0, f = 0.0, k = 0.0;
	for (i = 0; i < BUFFER_SIZE; ++i) {
		a += oop_data[i].a + oop_data[i].f + oop_data[i].k + oop_data[i].b + oop_data[i].g;
		f += oop_data[i].l + oop_data[i].c + oop_data[i].h + oop_data[i].m + oop_data[i].d;
		k += oop_data[i].i + oop_data[i].n + oop_data[i].e + oop_data[i].j + oop_data[i].o;
	}
	return { abcde: a, fghij: f, klmno: k };
}

function calculate_dod_abcde()
{
	result = 0.0;
	len = BUFFER_SIZE * 5;
	for (i = 0; i < len; i += 5)
		result += dod_data[i] + dod_data[i + 1] + dod_data[i + 2] + dod_data[i + 3] + dod_data[i + 4];

	return result;
}


function calculate_dod_fghij()
{
	result = 0.0;
	len = BUFFER_SIZE * 5;
	for (i = 0; i < len; i += 5) {
		result += dod_data[len + i] +
		          dod_data[len + i + 1] +
		          dod_data[len + i + 2] +
		          dod_data[len + i + 3] +
		          dod_data[len + i + 4];
	}

	return result;
}

function calculate_dod_klmno()
{
	result = 0.0;
	len = BUFFER_SIZE * 5;
	for (i = 0; i < len; i += 5) {
		result += dod_data[len * 2 + i] +
		          dod_data[len * 2 + i + 1] +
		          dod_data[len * 2 + i + 2] +
		          dod_data[len * 2 + i + 3] +
		          dod_data[len * 2 + i + 4];
	}

	return result;
}

function calculate_dod_combined()
{
	a = 0.0, f = 0.0, k = 0.0;
	
	for (i = 0; i < BUFFER_SIZE * 5; i += 5) {
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

	return {abcde: a, fghij: f, klmno: k};
}

function run_test(test_info, test_fun)
{
	const begin = new Date();
	const {abcde, fghij, klmno } = test_fun();
	const end = new Date();
	const ms = end.getTime() - begin.getTime();
	console.log("TEST: ", test_info, "\n",
	            "ABCDE: ", abcde, "\n",
	            "FGHIJ: ", fghij, "\n",
	            "KLMNO: ", klmno, "\n",
	            "TIME: ", (ms / 1000.0).toFixed(3), " secs\n",
	            "-----------------------------------");
}



if (process.argv.length < 6) {
	console.log(
	        "Usage: ", process.argv[1], " [oop separately base num] [oop combined base num] ",
	        "[dod separately base num] [dod combined base num] ",
	        "[buffer size]");
	process.exit();
}

base_nums = {
	BN_OOP_SEPARATELY: Number(process.argv[2]),
	BN_OOP_COMBINED: Number(process.argv[3]),
	BN_DOD_SEPARATELY: Number(process.argv[4]),
	BN_DOD_COMBINED: Number(process.argv[5])
};

alloc_data(Number(process.argv[6]));

/* OOP data layout is bad if we want to calculate data sets separately */
oop_fill(base_nums.BN_OOP_SEPARATELY);
console.log("TESTING OOP SEPARATELY CALCULATION");
run_test("OOP SEPARATELY", () => {
	return {
		abcde: calculate_oop_abcde(),
		fghij: calculate_oop_fghij(),
		klmno: calculate_oop_klmno()
	}
});

/* but OOP data layout is good if we want all the data at the same time */
oop_fill(base_nums.BN_OOP_COMBINED);
console.log("TESTING OOP COMBINED CALCULATION");
run_test("OOP COMBINED", calculate_oop_combined);

/* DOD data layout is great if we want to calculate data sets separately */
dod_fill(base_nums.BN_DOD_SEPARATELY);
console.log("TESTING DOD SEPARATELY CALCULATION");
run_test("DOD SEPARATELY", () => {
	return {
		abcde: calculate_dod_abcde(),
		fghij: calculate_dod_fghij(),
		klmno: calculate_dod_klmno()
	}
});

/* DOD COMBINED is awesome too */
dod_fill(base_nums.BN_DOD_COMBINED);
console.log("TESTING DOD COMBINED CALCULATION");
run_test("DOD COMBINED", calculate_dod_combined);


