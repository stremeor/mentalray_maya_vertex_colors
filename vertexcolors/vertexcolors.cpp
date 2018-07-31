//
//  vertexcolors.cpp
//  mr customshader
//
//  Created by Steffen on 16.04.18.
//  Copyright © 2018 NVIDIA. All rights reserved.
//


#include "string.h"
#include "shader.h"
#include "geoshader.h"
#include "vertexcolors.h"

const int vertexMagic_ = 0x4d695678;      // 'MiVx'

/*
 * Get user data.
 */
void *get_userdata(
    miInteger	magic,		/* magic to look for */
    miTag		item,		/* scene item/user data */
    miTag		*outData,	/* user data tag (to unpin) */
    miBoolean	*hasBadEndian)	/* whether magic has wrong endian */
{
    miTag data;
    int   realType;
    miInteger badMg =
    ((magic << 24) | ((magic & 0xff00) << 8) |
     ((magic >>  8) & 0xff00) | (magic >> 24));

    data = item;

    // iterate through (potential chain of) data blocks
    while (data) {
        void *dataPtr = mi_db_access_type(&realType, data);
        
        /* Make sure that it is really user data. */
        if (realType != miSCENE_USERDATA) {
            mi_db_unpin(data);
            return NULL;
        }
        
        /* Check the block's integer magic. */
        if (magic == *((int  *)((miUserdata *) dataPtr)->parameters)) {
            if (outData)
                *outData = data;
            if (hasBadEndian)
                *hasBadEndian = miFALSE;
            return (void *)((miUserdata *) dataPtr)->parameters;
        }
        else
            if (hasBadEndian &&
                badMg == *((int  *)((miUserdata *) dataPtr)->parameters)) {
                if (outData)
                    *outData = data;
                *hasBadEndian =  miTRUE;
                return (void *)((miUserdata *) dataPtr)->parameters;
            }
            else {
                /* It isn't our user data block. Continue search. */
                miTag nextBlk = ((miUserdata *) dataPtr)->next_data;
                mi_db_unpin(data);
                data = nextBlk;
            }
    }
    
    return NULL;
}

// Vertex Data - data block

/* Declaration:

 # Custom Vertex Data
 #
 declare data
	"maya_vertexdata" (
     integer		"magic",	# 'MiVx' = 1298749048
     array struct	"data" {
         string		"name",
         integer		"type",
         integer		"size",
         integer		"offset"
     },
     array struct	"uvs" {
         string		"name",
         integer		"type",
         integer		"size",
         integer		"offset"
     },
     array struct	"cpv" {
         string		"name",
         integer		"type",
         integer		"size",
         integer		"offset"
     }
 )
	version	2
 end declare
 
 Example .mi :
 
 data "pSphereShape1:vxdata"
 "maya_vertexdata" (
	"magic" 1298749048,
	"uvs" [{
        "name" "map1",
        "type" 2,
        "size" 3,
        "offset" 0
        }
    ],
	"cpv" [{
        "name" "myCustomColors",
        "type" 3,
        "size" 3,
        "offset" 0
        }
    ]
	)
 */

typedef struct DataTypeInfo {
    miTag   name;
    int     type;
    int     size;
    int     offset;
} DataTypeInfo;

typedef struct VertexDataInfo {
    int     magic;
    int		i_dataSets;
    int		n_dataSets;
    DataTypeInfo    dataSets[1];
    int		i_uvsSets;
    int		n_uvsSets;
    DataTypeInfo    uvsSets[1];
    int		i_cpvSets;
    int		n_cpvSets;
    DataTypeInfo    cpvSets[1];
} VertexDataInfo;

typedef struct CPVParms {
    miTag   cpvSet; // string type
} CPVParms;

EXPORT
int print_vertexcolors_version(void) { return 1; }

/*
 * Vertex Colors shader
 */

EXPORT
miBoolean
print_vertexcolors(

    miColor         *result,
    miState         *state,
    CPVParms        *parms)
{
    miTag   usrTag;

    if (mi_query(miQ_INST_ITEM, NULL, state->instance, &usrTag) && usrTag != miNULLTAG)
    if (mi_query(miQ_OBJ_DATA, NULL, usrTag, &usrTag) && usrTag != miNULLTAG) {
        const VertexDataInfo *usrPtr =
                (const VertexDataInfo *) get_userdata(vertexMagic_, usrTag, &usrTag, 0);
        if (usrPtr) {
            mi_info("print_vertexcolors(): found custom vertex data block.");
            mi_info("print_vertexcolors(): data sets: %d, uv sets: %d, color sets: %d.",
                     usrPtr->n_dataSets, usrPtr->n_uvsSets, usrPtr->n_cpvSets);

            if (const char* cpvSet = (const char*) mi_db_access(parms->cpvSet)) {
                const DataTypeInfo* entry = usrPtr->cpvSets + usrPtr->i_cpvSets;
                for (int numEntries=usrPtr->n_cpvSets; numEntries--; entry++) {
                    if (const char* str = (const char*) mi_db_access(entry->name)) {
                        mi_info("print_vertexcolors(): found vertex color set: %s", str);
                        if (!strcmp(str, cpvSet)) {
                            mi_info("print_vertexcolors(): >>> color set %s, type: %d", str, entry->type);
                            mi_info("print_vertexcolors(): >>> color set %s, size: %d", str, entry->size);
                            mi_info("print_vertexcolors(): >>> color set %s, offset: %d", str, entry->offset);
                            /* use "type", "size, and "index" to address vertex data
                               when calling mi_tri_vectors(), for example
                             */
                            break;
                            }

                        mi_db_unpin(entry->name);
                        }
                    }

                mi_db_unpin(parms->cpvSet);
                }

            mi_db_unpin(usrTag);
            }
        }

    return miTRUE;
}

