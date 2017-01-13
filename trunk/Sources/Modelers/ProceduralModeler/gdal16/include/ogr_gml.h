/******************************************************************************
 * $Id: ogr_gml.h 10645 2007-01-18 02:22:39Z warmerdam $
 *
 * Project:  GML Reader
 * Purpose:  Declarations for OGR wrapper classes for GML, and GML<->OGR
 *           translation of geometry.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 2002, Frank Warmerdam
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef _OGR_GML_H_INCLUDED
#define _OGR_GML_H_INCLUDED

#include "ogrsf_frmts.h"
#include "gmlreader.h"

class OGRGMLDataSource;

/************************************************************************/
/*                            OGRGMLLayer                               */
/************************************************************************/

class OGRGMLLayer : public OGRLayer
{
    OGRSpatialReference *poSRS;
    OGRFeatureDefn     *poFeatureDefn;

    int                 iNextGMLId;
    int                 nTotalGMLCount;

    int                 bWriter;

    OGRGMLDataSource    *poDS;

    GMLFeatureClass     *poFClass;

  public:
                        OGRGMLLayer( const char * pszName, 
                                     OGRSpatialReference *poSRS, 
                                     int bWriter,
                                     OGRwkbGeometryType eType,
                                     OGRGMLDataSource *poDS );

                        ~OGRGMLLayer();

    void                ResetReading();
    OGRFeature *        GetNextFeature();

    int                 GetFeatureCount( int bForce = TRUE );
    OGRErr              GetExtent(OGREnvelope *psExtent, int bForce = TRUE);

    OGRErr              CreateFeature( OGRFeature *poFeature );
    
    OGRFeatureDefn *    GetLayerDefn() { return poFeatureDefn; }

    virtual OGRErr      CreateField( OGRFieldDefn *poField,
                                     int bApproxOK = TRUE );

    virtual OGRSpatialReference *GetSpatialRef();
    
    int                 TestCapability( const char * );
};

/************************************************************************/
/*                           OGRGMLDataSource                           */
/************************************************************************/

class OGRGMLDataSource : public OGRDataSource
{
    OGRGMLLayer     **papoLayers;
    int                 nLayers;
    
    char                *pszName;
    
    OGRGMLLayer         *TranslateGMLSchema( GMLFeatureClass * );

    char               **papszCreateOptions;

    // output related parameters 
    FILE                *fpOutput;
    OGREnvelope         sBoundingRect;
    int                 nBoundedByLocation;
    
    int                 nSchemaInsertLocation;

    // input related parameters.
    IGMLReader          *poReader;

    void                InsertHeader();

  public:
                        OGRGMLDataSource();
                        ~OGRGMLDataSource();

    int                 Open( const char *, int bTestOpen );
    int                 Create( const char *pszFile, char **papszOptions );

    const char          *GetName() { return pszName; }
    int                 GetLayerCount() { return nLayers; }
    OGRLayer            *GetLayer( int );

    virtual OGRLayer    *CreateLayer( const char *, 
                                      OGRSpatialReference * = NULL,
                                      OGRwkbGeometryType = wkbUnknown,
                                      char ** = NULL );

    int                 TestCapability( const char * );

    FILE                *GetOutputFP() { return fpOutput; }
    IGMLReader          *GetReader() { return poReader; }

    void                GrowExtents( OGREnvelope *psGeomBounds );
};

/************************************************************************/
/*                             OGRGMLDriver                             */
/************************************************************************/

class OGRGMLDriver : public OGRSFDriver
{
  public:
                ~OGRGMLDriver();
                
    const char *GetName();
    OGRDataSource *Open( const char *, int );

    virtual OGRDataSource *CreateDataSource( const char *pszName,
                                             char ** = NULL );
    
    int                 TestCapability( const char * );
};

#endif /* _OGR_GML_H_INCLUDED */