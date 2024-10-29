/* The content of this file was generated using the C profile of libCellML 0.6.2. */

#pragma once

#include <stddef.h>

extern const char VERSION[];
extern const char LIBCELLML_VERSION[];

extern const size_t VARIABLE_COUNT;

typedef enum {
    CONSTANT,
    COMPUTED_CONSTANT,
    ALGEBRAIC,
    EXTERNAL
} VariableType;

typedef struct {
    char name[2];
    char units[14];
    char component[20];
    VariableType type;
} VariableInfo;

extern const VariableInfo VARIABLE_INFO[];

double * createVariablesArray();
void deleteArray(double *array);

typedef double (* ExternalVariable)(double *variables, size_t index);

void initialiseVariables(double *variables, ExternalVariable externalVariable);
void computeComputedConstants(double *variables);
void computeVariables(double *variables, ExternalVariable externalVariable);
