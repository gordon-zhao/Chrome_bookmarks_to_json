#include "core.h"

int main(int argc, char*argv[]) {
	string buf4Arguments;
	string outputFileName;
	string inputFileName;

	coreutils execute;
	if (argc == 1) {

	}

	if (argc > 1 && argc <= 2) {
		buf4Arguments = argv[1];
		if (buf4Arguments == "--help") {
			printf("sort-vlan-info by LBYPatrick\n");
			printf("Here are parameters available for use:\n");
			printf("    -i or --input-file  : specify origin log file.\n");
			printf("    -o or --output-file : specify output file.\n");
			return 0;
			//Some READMEs
			return 0;
		}
		printf("Oops, something went wrong...Please double-check arguments you typed.\n");
		return 0;
	}
	if (argc > 2) {
		bool gotInputCommand = 0;
		bool gotOutputCommand = 0;
		for (int i = 1; i < argc; i++) {
			if (argv[i]) {
				buf4Arguments = argv[i];
				if (buf4Arguments == "--input-file" || buf4Arguments == "-i") { gotInputCommand = 1;   execute.inputFile = argv[i + 1]; }
				if (buf4Arguments == "--output-file" || buf4Arguments == "-o") { gotOutputCommand = 1; execute.outputFile = argv[i + 1]; }
			}
		}
		if (!gotInputCommand || !gotOutputCommand) {
			printf("ERROR:No enough vaild arguments received, please try again.");
			return 0;
		}
		if (gotInputCommand && gotOutputCommand) {
			printf("Start Converting...\n");
			execute.makeJSON();
		}
		printf("Done.\n");

	}
}