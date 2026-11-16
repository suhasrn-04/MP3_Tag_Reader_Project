#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

typedef enum
{
    success,  
    failure   
} Status;

typedef enum
{
    view,       
    edit,       
    unsupported   
} OperationType;

#endif
