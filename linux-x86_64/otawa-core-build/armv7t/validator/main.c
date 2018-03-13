
/*  standard header */
#include <errno.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef NDEBUG
#	define MARK
#else
#	define MARK		fprintf(stderr, "@%s:%d\n", __FILE__, __LINE__)
#endif

/* Exit Codes
 * 1	Command line error.
 * 2	ISS error.
 * 3	GDB initialization error.
 * 4	GDB communication error.
 * 5	Co-simulation error.
 */

#define startswith(buf, start)	(strncmp(buf, start, strlen(start)) == 0)

/* GLISS headers */
#include <arm/api.h>
#include <arm/loader.h>
#include <arm/debug.h>

/* state description */
typedef struct {
	const char *gdb_name;
	const char *gliss_name;
	int size;
	uint32_t flags;
#	define REL 	0x00000001
#	define FPR	0x00000002
#	define SR	0x00000004
#	define DONE	0x00000010
	int id;
	int idx;
} reg_t;

/**
 * List of registers descriptor.
 */
reg_t registers[] = {
	{ "r0", "R0", 32 },
	{ "r1", "R1", 32 },
	{ "r2", "R2", 32 },
	{ "r3", "R3", 32 },
	{ "r4", "R4", 32 },
	{ "r5", "R5", 32 },
	{ "r6", "R6", 32 },
	{ "r7", "R7", 32 },
	{ "r8", "R8", 32 },
	{ "r9", "R9", 32 },
	{ "r10", "R10", 32 },
	{ "r11", "R11", 32 },
	{ "r12", "R12", 32 },
	{ "sp", "R13", 32 },
	{ "lr", "R14", 32 },
	{ "pc", "R15", 32 },
	{ "cpsr", "APSR", 32, SR },
	{ 0 }
};

/**
 * Back-map from GDB indexes to validator indexes.
 */
int *gdb_map;

register_value_t state_store[4][17];			/** Actual storage of sim, GDB states. */
register_value_t *iss_cur = state_store[0];		/** Current state of simulator. */
register_value_t *iss_prv = state_store[1];		/** Previous state of simulator. */
register_value_t *gdb_cur = state_store[2];		/** Current state of GDB. */
register_value_t *gdb_prv = state_store[3];		/** Previous state of GDB. */
uint32_t iss_pc;								/** Current PC of simulator. */
uint32_t gdb_pc;								/** Current PC of GDB. */
uint32_t iss_ppc;								/** Previous PC of simulator. */
uint32_t gdb_ppc;								/** Previous PC of GDB. */

#ifdef ARM_MEM_IO
#	define MEM_ACCESS_MAX	16
	typedef struct mem_access_t {
		uint32_t addr;
		int size;
		register_value_t val;
	} mem_access_t;
	mem_access_t iss_accesses[MEM_ACCESS_MAX];		/* Record memory accesses. */
	int iss_access_cnt = 0;							/* Number of memory accesses. */
#endif


/* options */
char gdb_path[512] = "gdb";
char exe_path[512];
char log_path[512] = "log";
int list_inst = 0;
int list_gdb = 0;
int list_regs = 0;
int verbose = 0;
int cont = 0;
int max_err = 0;
int do_log = 0;
int max_sync = 8;


/* output */
FILE *log_file;


/* GLISS state */
arm_platform_t *iss_platform;
arm_state_t *iss_state;
arm_sim_t *iss;


/* GDB state */
int gdb_to[2], gdb_from[2];
int gdb_pid;
FILE *gdb_in, *gdb_out;
char gdb_buf[4096];


/**
 * Display the message to the required channels.
 * @param msg	Printf-format message.
 * @param ...	Argument of format.
 */
void display(const char *msg, ...) {
	va_list args;
	va_start(args, msg);
	if(do_log)
		vfprintf(log_file, msg, args);
	if(verbose)
		vfprintf(stderr, msg, args);
	va_end(args);
}


/**
 * Display usage of the command.
 * @param cmd	Current command.
 */
void usage(const char *cmd) {
	printf("USAGE: %s [-g GDB_PATH] EXECUTABLE\n", cmd);
	printf("Co-execute a GLISS simulator with an external debugger to validate ISA.\n\n");
	printf(
		"-h, --help			Display this message.\n"
		"-v, --version		Display version.\n"
		"-V, --verbose		Activate verbose mode.\n"
		"-l, --log			Activate log output (in \"log\" file).\n"
		"-L, --logpath=PATH	Activate log output in the given file.\n"
		"-g, --gdb=PATH		Select the path to GDB to use.\n"
		"-i, --inst			List instruction during simulation.\n"
		"-r, --regs			List register values during simulation.\n"
		"-c, --continue		Continue if the co-simulation fails.\n"
		"-C, --errors=N		Continue if the co-simulation fails at most N times.\n"
		"-G, --debug		Display messages exchanged with GDB.\n"
	);
}


/**
 * Parse the command line.
 * @param argc	Argument count.
 * @param argv	Argument list.
 */
void parse_args(int argc, char ** argv) {
	int longindex;
	char option;
	//extern int setenv (const char *name, const char *value, int overwrite);

	/* argument definition */
	struct option longopts[] = {
		{ "version",     	0,  NULL,   'v' },
		{ "help",        	0,  NULL,   'h' },
		{ "verbose",        0,  NULL,   'V' },
		{ "log", 			0,	NULL,  	'l' },
		{ "logpath", 		1,	NULL,  	'L' },
		{ "gdb",			1,  NULL,   'g' },
		{ "inst",			0,	NULL,	'i' },
		{ "regs",			0,	NULL,	'r' },
		{ "continue",		0,	NULL,	'c' },
		{ "errors",			1,	NULL,	'C'	},
		{ "debug",			0,	NULL,	'G' },
		{ NULL, 			0, 	NULL, 	0	}
	};
	char *optstring = "vhVlL:g:ircC:G";

	/* parse argument */
	while ((option = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1)
		switch (option) {
		case 'v':	printf("\n"); exit (1); break;
		case 'h': 	usage(argv[0]); exit(1); break;
		case 'V':	verbose = 1; break;
		case 'l':	do_log = 1; break;
		case 'L':	do_log = 1; strncpy(log_path, optarg, sizeof(log_path)); break;
		case 'g':	strncpy(gdb_path, optarg, sizeof(gdb_path)); break;
		case 'i':	list_inst = 1; break;
		case 'r':	list_regs = 1; break;
		case 'c':	cont = 1; break;
		case 'C':	cont = 1; max_err = strtol(optarg, NULL, 10); break;
		case 'G':	list_gdb = 1; break;
		default:
			fprintf(stderr, "ERROR: unknown option %c\n", optopt);
			usage(argv[0]);
			exit(1);
		}

	/* process free arguments */
	if(optind < argc)
		strncpy(exe_path, argv[optind], sizeof(exe_path));
	else {
		fprintf(stderr, "ERROR: at least, one executable must be given.\n");
		usage(argv[0]);
		exit(1);
	}

	/* open log output if requried */
	if(do_log) {
		log_file = fopen(log_path, "w");
		if(log_file == NULL) {
			fprintf(stderr, "ERROR: cannot open log file \"%s\": %s", log_path, strerror(errno));
			exit(1);
		}
	}
}


#ifdef ARM_MEM_IO
	/**
	 * Call-back to record memory accesses.
	 * @param addr			Accessed address.
	 * @param size			Accessed size.
	 * @param data			Read / written data.
	 * @param type_access	Read or write.
	 * @param cdata			Call-back data.
	 */
	void iss_memory_callback(arm_address_t addr, int size, void *data, int type_access, void *cdata) {
		int i;

		/* determine access array entry */
		if(type_access == ARM_MEM_READ)
			return;
		if(iss_access_cnt >= MEM_ACCESS_MAX) {
			fprintf(stderr, "WARNING: too many memory access, loosing information.\n");
			return;
		}
		if(size > 8) {
			fprintf(stderr, "WARNING: too big data access, information lost.\n");
			return;
		}
		i = iss_access_cnt++;

		/* store address and size */
		iss_accesses[i].addr = addr;
		iss_accesses[i].size = size;
		display("DEBUG: store %08x:%d\n", addr, size);
	}

#endif


/**
 * Start the GLISS simulator. Exit with code 2 in case of failure.
 */
void iss_init(void) {
	arm_address_t exit_addr = 0;

	/* make the platform */
	iss_platform = arm_new_platform();
	if(iss_platform == NULL) {
		fprintf(stderr, "ERROR: no more resources\n");
		exit(2);
	}

	/* load the image in the platform */
	display("INFO: loading executable %s\n", exe_path);
	arm_loader_t *loader = arm_loader_open(exe_path);
	if(loader == NULL) {
		fprintf(stderr, "ERROR: cannot load the executable \"%s\": %s\n", exe_path, strerror(errno));
		exit(2);
	}
	arm_load(iss_platform, loader);

	/* look for _exit symbol */
	{
		int i, cnt = arm_loader_count_syms(loader);
		for(i = 0; i < cnt; i++) {
			arm_loader_sym_t sym;
			arm_loader_sym(loader, i, &sym);
			if(strcmp(sym.name, "_exit") == 0) {
				exit_addr = sym.value;
				display("INFO: found exit at %08x\n", exit_addr);
				break;
			}
		}
	}

	/* cleanup loader */
	arm_loader_close(loader);

	/* make the state depending on the platform */
	iss_state = arm_new_state(iss_platform);
	if(iss_state == NULL)  {
		fprintf(stderr, "ERROR: no more resources\n");
		exit(2);
	}

	/* make the simulator */
	iss = arm_new_sim(iss_state, 0, exit_addr);
	if(iss == NULL) {
		fprintf(stderr, "ERROR: no more resources\n");
		exit(2);
	}

	/* make register mapping */
	{
		register_bank_t *bank = arm_get_registers();
		int i;
		if(verbose)
			display("INFO: scanning registers in GLISS simulator.\n");

		/* find matching between banks and registers */
		for(; bank->name; bank++) {

			// simple register
			if(bank->size == 1) {
				for(i = 0; registers[i].gdb_name; i++)
					if(strcmp(registers[i].gliss_name, bank->name) == 0) {
						registers[i].id = bank->id;
						registers[i].idx = 0;
						registers[i].flags |= DONE;
						break;
					}
			}

			/* bank of registers */
			else {
				int j;
				for(j = 0; j < bank->size; j++) {
					char buf[256];
					snprintf(buf, sizeof(buf), bank->format, j);
					for(i = 0; registers[i].gdb_name; i++)
						if(strcmp(registers[i].gliss_name, buf) == 0) {
							registers[i].id = bank->id;
							registers[i].idx = i;
							registers[i].flags |= DONE;
							break;
						}
				}
			}
		}

		/* check all registers have been found */
		for(i = 0; registers[i].gdb_name; i++)
			if(!(registers[i].flags & DONE)) {
				fprintf(stderr, "ERROR: register %s not found in GLISS debug API!\n", registers[i].gliss_name);
				exit(3);
			}

	}

	/* install memory callback if any */
#	ifdef ARM_MEM_IO
	arm_set_range_callback_ex(arm_get_memory(iss_platform, ARM_MAIN_MEMORY), 0, 0xffffffff, iss_memory_callback, 0, ARM_MEM_SPY);
#	endif
}


/**
 * Get the current PC of the simulator.
 * @return	Current PC.
 */
uint32_t iss_get_pc(void) {
	return arm_next_addr(iss);
}


/**
 * Execute one instruction in ISS.
 */
void iss_step(void) {
#	ifdef ARM_MEM_IO
		iss_access_cnt = 0;
#	endif
	arm_step(iss);
}


/**
 * Read a byte from memory.
 * @param addr		Address of the byte to read.
 * @return			Read byte.
 */
uint8_t iss_get_byte(arm_address_t addr) {
	return arm_mem_read8(arm_get_memory(iss_platform, ARM_MAIN_MEMORY), addr);
}


/**
 * Fill gdb_buf with a new line from GDB.
 * Exit with 4 in case if error.
 * @return	Read line.
 */
char *gdb_read(void) {
	char *r;
	r = fgets(gdb_buf, sizeof(gdb_buf), gdb_in);
	if(r == NULL) {
		fprintf(stderr, "ERROR: broken connection.\n");
		exit(4);
	}
	if(list_gdb)
		display("GDB: %s", gdb_buf);
	return r;
}


/**
 * Check for an error according to a start sequence.
 * If sequence is found, exit with code 5 and display error following the sequence.
 */
void gdb_check(const char *msg, const char *buf, const char *start) {
	if(startswith(buf, start)) {
		fprintf(stderr, "ERROR: GDB: %s: %s", msg, buf + strlen(start));
		exit(5);
	}
}

/**
 * Perform a read on GDB and process error (exiting with code 5).
 * @return		Filled buffer.
 */
char *gdb_read_with_error(void) {
	char *buf = gdb_read();

	/* eat prompt */
	while(startswith(buf, "(gdb)"))
		buf += sizeof("gdb");

	/* manage an error */
	if(strstr(buf, "^error")) {
		fprintf(stderr, "ERROR: GDB: error raised: %s", buf + 6);
		exit(5);
	}

	/* manager simulator exception */
	gdb_check("simulator error", buf, "~\"sim: exception: ");

	/* return buf else */
	return buf;
}


/**
 * Wait for GDB prompt "(gdb)".
 * Exit with 4 if error.
 */
void gdb_prompt(void) {
	char *buf;
	do {
		buf = gdb_read();
	} while(!strstr(buf, "(gdb)"));
}


/**
 * Send a command to GDB (do not forget \n at end).
 * Exit with 4 in case of error.
 * @param cmd	Command to send.
 */
void gdb_command(const char *cmd) {
	write(gdb_to[1], cmd, strlen(cmd));
	if(list_gdb)
		display("CMD: %s", cmd);
}


/**
 * Wait GDB to answer the given acknowledge (prefix of ack is tested).
 * Exit with 4 in case of error.
 * @return		Text after acknowledge.
 */
char *gdb_acknowledge(const char *ack) {
	char *buf;

	// loop until getting ack
	do {
		buf = gdb_read_with_error();
	} while(*buf != '*' && *buf != '^');

	/* unexpected acknowledge */
	if(!strstr(buf, ack)) {
		fprintf(stderr, "ERROR: GDB: unexpected acknoledge: %s", buf + sizeof(ack));
		exit(4);
	}

	/* return information text */
	return buf + sizeof(ack);
}


/**
 * Wait for the given acknowledge message
 * ignoring other result messages except error (exit with code 4).
 * @param ack		Acknowledge prefix.
 */
void gdb_wait(const char *ack) {
	char *buf;

	// loop until getting ack
	do {
		buf = gdb_read_with_error();
	} while(!strstr(buf, ack));

}


/**
 * Eat a string from the buffer and increment buf accordingly.
 * If c does not match, exit with code 4.
 * @param buf	Buffer pointer (in / out).
 * @param c		String to match.
 */
void gdb_buffer_eat(char **buf, const char *c) {
	int n = strlen(c);
	if(strncmp(*buf, c, n) != 0) {
		fprintf(stderr, "ERROR: malformed GDB answer\n");
		exit(4);
	}
	*buf += n;
}


/**
 * Test if a string match a buffer and then eat it.
 * If it doesn't match, return false.
 * If c does not match, exit with code 4.
 * @param buf	Buffer pointer (in / out).
 * @param c		Character to match.
 * @return		0 if doesn't match, false else.
 */
int gdb_buffer_match(char **buf, const char *c) {
	int n= strlen(c);
	if(strncmp(*buf, c, n) == 0) {
		*buf += n;
		return 1;
	}
	else
		return 0;
}


/**
 * Look for a character in the buffer.
 * If c cannot be found, exit with code 4.
 * @param buf	Buffer pointer (in/out).
 * @param c		String to match.
 */
void gdb_buffer_find(char **buf, const char *c) {
	*buf = strstr(*buf, c);
	if(!*buf) {
		fprintf(stderr, "ERROR: malformed GDB answer\n");
		exit(4);
	}
}


/**
 * Start GDB: launch GDB command, make pipe to communicate,
 * put breakpoint on "_start" or the address given in the parameter
 * and run until this breakpoint.
 * Exit with code 3 in case of failure.
 */
void gdb_start(uint32_t _start) {

	/* creating pipes to redirect GDB I/O */
	display("INFO: running GDB: %s\n", gdb_path);
	if(pipe(gdb_to)) {
		fprintf(stderr, "ERROR: couldn't create pipe to communicate with gdb driving process: %s\n", strerror(errno));
		exit(3);
	}
	if(pipe(gdb_from)) {
		fprintf(stderr, "ERROR: Couldn't create pipe to communicate with gdb driving process: %s\n", strerror(errno));
		exit(-1);
	}

	/* GDB process */
	if((gdb_pid = fork()) == 0) {
		char *argv[] = { gdb_path, "--interpreter", "mi",  "--quiet", exe_path, NULL };

		/* prepare buffered I/O */
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stdin, NULL, _IONBF, 0);

		/* install stdin */
		close(gdb_to[1]);
		if(dup2(gdb_to[0], STDIN_FILENO) == -1) {
			fprintf(stderr, "ERROR: GDB: cannot set stdin: %s\n", strerror(errno));
			exit(3);
		}
		close(gdb_to[0]);

		/* install stdout */
		close(gdb_from[0]);

		/* redirecting stdout */
		if(dup2(gdb_from[1], STDOUT_FILENO) == -1) {
			fprintf(stderr, "ERROR: cannot set stdout: %s\n", strerror(errno));
			exit(3);
		}
		close(gdb_from[1]);

		/* now we launch GDB with M/I interpreter */
		execvp(argv[0], argv);
		fprintf(stderr, "ERROR: launching GDB failed: %s", strerror(errno));

		/* cleaning pipes */
		close(gdb_to[0]);
		close(gdb_from[1]);
		exit(3);
	}

	/* validator process */
	else {

		/* cleanup pipes */
		close(gdb_to[0]);
		close(gdb_from[1]);
		gdb_in = fdopen(gdb_from[0], "r");

		/* wait for the command prompt, discard the rest */
		gdb_prompt();

		/* command: -target-select sim */
		gdb_command("-target-select sim\n");
		gdb_acknowledge("^connected");

		/* command: -target-download */
		gdb_command("-target-download\n");
		gdb_acknowledge("^done");

		/* command: -break-insert _start */
		if (_start) {
			char buf[256];
			snprintf(buf, sizeof(buf), "-break-insert *0x%08x\n", _start);
			gdb_command(buf);
		}
		else
			gdb_command("-break-insert _start\n");
		gdb_acknowledge("^done");

		/* command: -exec-run */
		gdb_command("-exec-run\n");
		gdb_acknowledge("^running");
		gdb_wait("*stopped,reason=\"breakpoint-hit\"");

		/* get register names */
		{
			if(verbose)
				display("INFO: scanning GDB registers\n");

			/* get the list of names */
			char *buf;
			gdb_command("-data-list-register-names\n");
			buf = gdb_acknowledge("^done");

			/* allocate map */
			{
				int c = 1, i;
				char *p;
				for(p = buf; p; p = strchr(p + 1, ','))
					c++;
				gdb_map = (int *)malloc(sizeof(int) * c);
				for(i = 0; i < c; i++)
					gdb_map[i] = -1;
			}

			/* scan the register list */
			{
				char *p;
				int i = 0, j;
				gdb_buffer_find(&buf, "[");
				buf++;
				while(1) {

					// scan the register
					gdb_buffer_eat(&buf, "\"");
					p = buf;
					gdb_buffer_find(&buf, "\"");
					*buf++ = '\0';

					// process name
					for(j = 0; registers[j].gdb_name; j++)
						if(strcmp(p, registers[j].gdb_name) == 0) {
							gdb_map[i] = j;
							break;
						}
					i++;

					// scan end
					if(!gdb_buffer_match(&buf, ","))
						break;
				}
			}
		}

	}

}


/**
 * Get the PC of GDB.
 * @return	GDB PC.
 */
uint32_t gdb_get_pc(void) {
	char *buf;
	uint32_t pc;

	/* perform command */
	gdb_command("-data-evaluate-expression $pc\n");
	do {
		buf = gdb_read();
	} while(gdb_buffer_match(&buf, "(gdb)"));

	/* scan the output */
	strtol(buf, &buf, 10);
	gdb_buffer_eat(&buf, "^done,value=\"0x");
	pc = strtol(buf, &buf, 16);
	return pc;
}


/**
 * Perform an instruction step in GDB.
 */
void gdb_step(void) {
	gdb_command("-exec-step-instruction\n");
	gdb_wait("*stopped,reason=\"end-stepping-range\"");
}


/**
 * Get byte from GDB memory.
 * @param addr	Accessed address.
 * @return		Byte at this address.
 */
uint8_t gdb_get_byte(arm_address_t addr) {

	/* send command */
	{
		char buf[256];
		snprintf(buf, sizeof(buf), "-data-read-memory 0x%08x d 1 1 1\n", addr);
		gdb_command(buf);
	}

	/* scan the result */
	{
		uint8_t data;
		char *buf = gdb_acknowledge("^done,addr=");
		gdb_buffer_find(&buf, ",memory=[");
		gdb_buffer_find(&buf, ",data=[\"");
		buf += 8;
		data = strtoul(buf, NULL, 10);
		return data;
	}
}


/**
 * Record state from simulator.
 */
void iss_record_state(void) {
	int i;

	/* exchange state storage */
	{
		register_value_t *aux = iss_cur;
		iss_cur = iss_prv;
		iss_prv = aux;
	}

	/* record the state */
	for(i = 0; registers[i].gdb_name; i++)
		iss_cur[i] = arm_get_register(iss_state, registers[i].id, registers[i].idx);
}


/**
 * Record state from GDB.
 */
void gdb_record_state(void) {
	char *buf;

	/* exchange state storage */
	{
		register_value_t *aux = gdb_cur;
		gdb_cur = gdb_prv;
		gdb_prv = aux;
	}

	/* get registers line from GDB */
	gdb_command("-data-list-register-values x\n");
	buf = gdb_acknowledge("^done");

	/* find beginning of register value list */
	gdb_buffer_find(&buf, "[");
	buf++;
	do {
		int idx;
		int32_t val;

		// scan the value
		gdb_buffer_eat(&buf, "{number=\"");
		idx = strtol(buf, &buf, 10);
		gdb_buffer_eat(&buf, "\",value=\"0x");
		val = strtol(buf, &buf, 16);

		// store the value
		if(gdb_map[idx] >= 0)
			gdb_cur[gdb_map[idx]].iv = val;

	} while(gdb_buffer_match(&buf, "\"},"));
}


/**
 * Dump comparative state of ISS and GDB.
 */
void dump_state(void) {
	int i;
	printf("\033[1m          ISS               | GDB\033[0m\n");
	printf("\033[1m          Previous Current  | Previous Current\033[0m\n");
	for(i = 0; registers[i].gdb_name; i++) {
		if(iss_cur[i].iv != gdb_cur[i].iv)
			printf("\033[1m\033[31m");
		printf("%8s  %08x %08x | %08x %08x\033[0m\n",
			registers[i].gdb_name,
			iss_prv[i].iv, iss_cur[i].iv,
			gdb_prv[i].iv, gdb_cur[i].iv);
		if(iss_cur[i].iv != gdb_cur[i].iv)
			printf("\033[0m");
	}
}


/**
 * Dump and disassemble current instruction of ISS.
 */
void dump_inst(uint32_t addr) {
	char buf[256];
	arm_inst_t *inst = arm_decode(iss->decoder, addr);
	arm_disasm(buf, inst);
	arm_free_inst(inst);
	printf("%08x\t%s\n", addr, buf);
}


int main(int argc, char **argv) {
	int cnt, i, err;

	/* initialization */
	parse_args(argc, argv);
	iss_init();
	iss_pc = iss_get_pc();
	gdb_start(iss_pc);
	gdb_pc = gdb_get_pc();

	/* PC synchronization */
	if(verbose)
		display("INFO: synchronizing PCs (sim pc = %08x, gdb pc = %08x)\n", iss_pc, gdb_pc);
	cnt = 0;
	while(iss_pc != gdb_pc) {

		/* check synchronization limit */
		if(cnt >= max_sync) {
			fprintf(stderr, "ERROR: cannot synchronize PCs after %d steps (sim pc = %08x, GDB pc = %08x). Stopping.",
				max_sync, iss_pc, gdb_pc);
		}
		cnt++;

		/* do one more step */
		iss_step();
		iss_pc = iss_get_pc();
	}

	/* initial state synchronization */
	if(verbose)
		display("INFO: synchronizing states\n");
	iss_record_state();
	gdb_record_state();
	for(i = 0; registers[i].gdb_name; i++)
		if(iss_cur[i].iv != gdb_cur[i].iv) {
			fprintf(stderr, "WARNING: setting ISS %s (%08x) to GDB value %08x\n", registers[i].gdb_name, iss_cur[i].iv, gdb_cur[i].iv);
			iss_cur[i].iv = gdb_cur[i].iv;
			arm_set_register(iss_state, registers[i].id, registers[i].idx, gdb_cur[i]);
		}

	/* co-simulation */
	iss_ppc = ~iss_pc; // just to make them different
	while(!arm_is_sim_ended(iss) && iss_ppc != iss_pc) {

		// list instruction if required
		if(list_inst)
			dump_inst(iss_pc);

		// step forward
		iss_step();
		gdb_step();
		iss_ppc = iss_pc;
		gdb_ppc = gdb_pc;
		iss_pc = iss_get_pc();
		gdb_pc = gdb_get_pc();

		// compare states
		iss_record_state();
		gdb_record_state();
		err = 0;
		for(i = 0; registers[i].gdb_name; i++)
			if(iss_cur[i].iv != gdb_cur[i].iv) {
				err++;
				fprintf(stderr, "ERROR: difference found for register %s: %08x (ISS), %08x (GDB)\n",
					registers[i].gdb_name, iss_cur[i].iv, gdb_cur[i].iv);
			}
		if (err) {
			if(!list_inst) {
				display("INFO: stopping due to %d errors after the instruction:\n", err);
				dump_inst(iss_ppc);
			}
			printf("Current state:\n");
			dump_state();
			exit(5);
		}
		
		/* compare memory accesses */
#		ifdef ARM_MEM_IO
		for(i = 0; i < iss_access_cnt; i++) {
			int j;

			/* collect information */
			uint8_t iss_bytes[iss_accesses[i].size];
			uint8_t gdb_bytes[iss_accesses[i].size];
			for(j = 0; j <  iss_accesses[i].size; j++) {
				iss_bytes[j] = iss_get_byte(iss_accesses[i].addr + j);
				gdb_bytes[j] = gdb_get_byte(iss_accesses[i].addr + j);
			}

			/* compare data */
			for(j = 0; j <  iss_accesses[i].size; j++) {
				if(iss_bytes[j] != gdb_bytes[j]) {
					fprintf(stderr, "ERROR: difference found for bytes at address %08x:%x ", iss_accesses[i].addr + j, iss_accesses[i].size);
					for(j = 0; j <  iss_accesses[i].size; j++)
						printf("%02x", iss_bytes[j]);
					printf(" (ISS), ");
					for(j = 0; j <  iss_accesses[i].size; j++)
						printf("%02x", gdb_bytes[j]);
					printf(" (GDB)\n");
					dump_inst(iss_ppc);
					printf("Current state:\n");
					dump_state();
					exit(5);
				}
				else if(verbose)
					fprintf(stderr, "INFO: memory checking OK for the byte at %08x %02x\n", iss_accesses[i].addr + j, iss_bytes[j]);
			}
		}
#		endif

	}

	/* all is fine */
	fprintf(stderr, "SUCCESS: co-simulation successful!");
	if(!list_inst) {
		display("INFO: last executed instruction:\n");
		dump_inst(iss_ppc);
	}
	return 0;
}
