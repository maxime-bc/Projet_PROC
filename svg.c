#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "edge.h"

void dumpSVG(char *outputPath) {
    FILE *filePointer = fopen(outputPath, "w");

    if (filePointer == NULL) {
        printf("ERROR : file %s couldn't be opened.\n", outputPath);
        exit(1);
    }

    char const *svgHeader = "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
                            "width=\"800\" height=\"600\" viewBox=\"0 0 800 600\">\n\n"
                            "<rect x=\"0\" y=\"0\" width=\"800\" height=\"600\" fill=\"none\" "
                            "stroke=\"black\" stroke-width=\"2\" />";


    // TODO : generate svg

    char const *svgFooter = "</svg>";

    unsigned int const svgHeaderLen = strlen(svgHeader);
    unsigned int const svgFooterLen = strlen(svgFooter);

    char *concat = (char *) malloc(svgHeaderLen + svgFooterLen + 1);
    memcpy(concat, svgHeader, svgHeaderLen);
    memcpy(concat + svgHeaderLen, svgFooter, svgFooterLen);
    concat[svgHeaderLen + svgFooterLen] = '\0';

    fprintf(filePointer, "%s\n", concat);

    free(concat);

    fclose(filePointer);
}