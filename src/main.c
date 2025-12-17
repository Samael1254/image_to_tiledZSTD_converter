#include "itzstd.h"
#include "stb_image.h"
#include <bits/getopt_core.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void help()
{
	fprintf(stderr, "Usage: itzstd [OPTION]... INFILE [OUTDIR]\n");
	fprintf(stderr, "Converts a jpeg or png image into zstd compressed tiles\n\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "  -n subdivs	number of subdivisions (default: 5). Produces 2^(2n) tiles\n");
	fprintf(stderr, "  -b bpp		bits per pixel of the resulting data\n");
	fprintf(stderr, "  -h 			display this help\n");
}

void readOpts(int argc, char **argv, uint16_t *subdivs, uint16_t *bpp)
{
	int opt;
	do
	{
		opt = getopt(argc, argv, ":n:b:h");
		switch (opt)
		{
		case -1:
			break;
		case 'n':
			*subdivs = atoi(optarg);
			break;
		case 'b':
			*bpp = atoi(optarg);
			break;
		case 'h':
			help();
			break;
		case ':':
			fprintf(stderr, "error: option requires argument: %s\n", argv[optind - 1]);
			exit(EXIT_FAILURE);
		default:
			fprintf(stderr, "error: unknown option: %s\n", argv[optind - 1]);
			exit(EXIT_FAILURE);
		}
	} while (opt != -1);

	// TODO: Remove
	printf("subdivs: %hu\n", *subdivs);
	printf("bpp: %hu\n", *bpp);
}

void readArgs(int argc, char **argv, char *infile, char *outdir)
{
	if (argc <= optind)
	{
		fprintf(stderr, "error: missing input file\n");
		exit(EXIT_FAILURE);
	}
	if (argc > optind + 2)
	{
		fprintf(stderr, "error: too many arguments\n");
		exit(EXIT_FAILURE);
	}

	if (strlen(argv[optind]) > 255)
		fprintf(stderr, "error: input file path too long\n");
	strcpy(infile, argv[optind]);
	printf("input file: %s\n", infile); // TODO: Remove

	if (argc <= optind + 1)
		return;
	if (strlen(argv[optind + 1]) > 255)
		fprintf(stderr, "error: output directory path too long\n");
	strcpy(outdir, argv[optind + 1]);
	printf("output dir: %s\n", outdir); // TODO: Remove
}

int main(int argc, char **argv)
{
	uint16_t subdivs = SUBDIV;
	uint16_t bpp = BITS_PER_PIXEL;
	char     infile[256];
	char     outdir[256];

	readOpts(argc, argv, &subdivs, &bpp);
	readArgs(argc, argv, infile, outdir);
}
