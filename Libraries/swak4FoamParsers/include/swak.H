/*---------------------------------------------------------------------------*\
 ##   ####  ######     |
 ##  ##     ##         | Copyright: ICE Stroemungsfoschungs GmbH
 ##  ##     ####       |
 ##  ##     ##         | http://www.ice-sf.at
 ##   ####  ######     |
-------------------------------------------------------------------------------
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2008 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is based on OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class


Description
    Define versions and flags for swak to distinguish different features
    via #ifdef

SourceFiles

Contributors/Copyright:
    2012-2015 Bernhard F.W. Gschaider <bgschaid@ice-sf.at>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#ifndef SwakMacroHeader_H
#define SwakMacroHeader_H

#include "foamVersion4swak.H"
#if (FOAM_VERSION4SWAK_MAJOR < 2)
#error "This swak4Foam-version is only used for the 2.x-versions of OpenFOAM. For lower versions there is a special branch"
#endif

#define VERSION_NR(major,minor,patch) (     \
    10000 * major + \
    100   * minor + \
    patch )

#define VERSION_NR2(major,minor) (     \
    10000 * major + \
    100   * minor + \
    99 )

#define FOAM_VERSION4SWAK VERSION_NR(FOAM_VERSION4SWAK_MAJOR,FOAM_VERSION4SWAK_MINOR,FOAM_VERSION4SWAK_PATCH_NUM)

    #if (FOAM_VERSION4SWAK > VERSION_NR2(1,7) && !defined(FOAM_DEV)) || (FOAM_VERSION4SWAK > VERSION_NR2(3,0))
// Just to make sure that stuff that comes from 1.7 works correctly
#define FOAM_HAS_SORTED_TOC
#endif

#if !((FOAM_VERSION4SWAK_MAJOR > 1) || (FOAM_VERSION4SWAK_MINOR > 6))
#define FOAM_OLDTIME_PROBLEM
#endif

// OpenFOAM-dev version. Has no number. Is assumed to be 9.x
#if FOAM_VERSION4SWAK_MAJOR > 8
#define FOAM_OF_DEV_VERSION
#endif

// in 1.6-ext the operation s1 & s2 of two symmetrical tensor fields does not yield a symmetric tensor
#if defined(FOAM_DEV) || FOAM_VERSION4SWAK_MAJOR>1
#define FOAM_SYMMTENSOR_WORKAROUND
#endif

// in 1.6-ext nextRelease a different Macro is used for the creation of certain patch types
#ifdef FOAM_DEV
#define FOAM_USE_MAKE_TEMPLATE_PATCH_TYPE
#endif

// Certain OpenFOAM-versions don't have all tensor operations defined
#if FOAM_VERSION4SWAK < VERSION_NR(1,7,0) || defined(FOAM_DEV)
#define FOAM_INCOMPLETE_OPERATORS
#endif

#if FOAM_VERSION4SWAK <= VERSION_NR2(2,1) || defined(FOAM_DEV)
#define FOAM_DELTATCHEM_NOT_DIMENSIONED
#endif

// Versions before 2.1
#if FOAM_VERSION4SWAK < VERSION_NR(2,1,0) || defined(FOAM_DEV)
// what is later called mappedPatch is called directMappedPatch
#define FOAM_MAPPED_IS_DIRECTMAPPED

#else

// has basicSources
#define FOAM_HAS_BASICSOURCES

#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(3,2,0) && defined(FOAM_DEV)
#define FOAM_DEFAULTCOMMSTYPE_IS_METHOD
#endif

// this changed starting with 2.1
#if (FOAM_VERSION4SWAK >= VERSION_NR(2,1,0)) && !defined(FOAM_DEV)

// this Foam-Version now has ABI-patches
#define FOAM_HAS_ABI_PATCHES

// the coded function objects have an additional data entry
#define SWAK_FUNCTION_OBJECT_HAS_DATAPTR

#endif

// this changed starting with 2.2
#if FOAM_VERSION4SWAK > VERSION_NR2(2,1)

#if (FOAM_VERSION4SWAK > VERSION_NR(2,2,0)) && !defined(FOAM_DEV)
// this is NOT changed in 2.2.0 but in the earliest commits of 2.2.x
// lookupClass returns a non-const list
#define FOAM_LOOKUPCLASS_NO_CONST
#endif

#if !defined(FOAM_DEV)
// meshSearch parameter for sampledSet-constructor is now const
#define FOAM_MESHSEARCH_CONST_SAMPLEDSET
#else
#define FOAM_SAMPLEDSET_NEEDS_REFPOINT
#endif

#if !defined(FOAM_DEV)
// interpolate-method for meshToMesh needs a reduce-operation
#define FOAM_MESHTOMESH_INTERPOLATE_REDUCE
#endif

#if !defined(FOAM_DEV)
// functionObject now needs at least dummy-implementations of updateMesh and movePoints
#define FOAM_FUNCTIONOBJECT_NEEDS_UPDATEMESH
#endif

#ifndef FOAM_DEV
// new revised fluidThermo
#define FOAM_HAS_FLUIDTHERMO
#endif

#if (FOAM_VERSION4SWAK < VERSION_NR(2,3,0)) && !defined(FOAM_DEV)
#define FOAM_HAS_FLUIDTHERMO_CLOUD
#endif

// RR from the chemistry does no longer return a complete field
#define FOAM_RR_ONLY_DIMENSIONED_FIELD

// there is no mixed-BC for point patches
#define FOAM_NO_MIXED_POINT_PATCH

#ifndef FOAM_DEV
// this version has fvOptions
#define FOAM_HAS_FVOPTIONS
#endif

#ifndef FOAM_DEV
// movePoints now gets a polyMesh
#define FOAM_MOVEPOINTS_GETS_POLYMESH
#endif

#ifndef FOAM_DEV
// coordinates method of searchable surfaces uses a tmp as return
#define FOAM_SEARCHABLE_SURF_USES_TMP
#endif

#ifndef FOAM_DEV
// points method of searchable surfaces now part of interface
#define FOAM_SEARCHABLE_SURF_HAS_POINTS
#endif

#endif // version starting with 2.2

// Certain OpenFOAM-versions don't have this method in fvMesh
#if FOAM_VERSION4SWAK < VERSION_NR(1,7,0) || defined(FOAM_DEV)
#define FOAM_FV_MESH_HAS_NO_SOLVERDICT
#endif

#if (FOAM_VERSION4SWAK > VERSION_NR2(2,1)) && !defined(FOAM_DEV)
#define FOAM_HAS_ENERGY_HE
#endif

// Additional tensor types in nextRelease
#ifdef FOAM_DEV
#define FOAM_DEV_ADDITIONAL_TENSOR_TYPES
#endif

// The kineamticPArcel has no property active in 1.6-ext
#ifdef FOAM_DEV
#define FOAM_KINEMTATIC_HAS_NO_ACTIVE_PROPERTY
#endif

// mathematical constants have no separate namespace
#ifdef FOAM_DEV
#define FOAM_NO_SEPARATE_CONSTANT_NAMESPACE
#endif

#ifdef FOAM_DEV
#define FOAM_FUNCTIONOBJECT_EXECUTE_HAS_NO_FORCE
#endif

#ifdef FOAM_DEV
#define FOAM_ISTREAM_HAS_NO_STDSTREAM
#endif

#ifndef FOAM_DEV
#define FOAM_SURFACEWRITER_NOT_A_TEMPLATE
#endif

#ifdef FOAM_DEV
#define FOAM_PARTICLE_CLASS_IS_TEMPLATE
#endif

#ifdef FOAM_DEV
#define FOAM_HAS_NO_DATAENTRY_CLASS
#endif

#ifdef FOAM_DEV
#define FOAM_HAS_NO_CODED_CLASS
#endif

#ifdef FOAM_DEV
#define FOAM_JUMP_IS_JUMP_CYCLIC
#endif

#ifdef FOAM_DEV
#define FOAM_OLD_THERMOPHYSICS
#endif

#ifdef FOAM_DEV
#define FOAM_NO_SLG_THERMOPHYSICS
#endif

#ifndef FOAM_DEV
#define FOAM_TOPOSETSOURCE_HAS_SETTYPE
#endif

#ifndef FOAM_DEV
#define FOAM_HAS_STRINGOPS
#endif

#ifdef FOAM_DEV
#define FOAM_DLLIBRARY_USES_STATIC_METHODS
#endif

#ifndef FOAM_DEV
#define FOAM_COUPLEDPOLYPATCH_HAS_OWNER
#endif

#if FOAM_VERSION4SWAK > VERSION_NR2(2,2) && !defined(FOAM_DEV)
#define FOAM_NEW_MESH2MESH
#endif

#if FOAM_VERSION4SWAK > VERSION_NR2(2,2) && !defined(FOAM_DEV)
#define FOAM_VOLUMETYPE_IS_TYPE
#endif

#if FOAM_VERSION4SWAK < VERSION_NR(2,3,0) || defined(FOAM_DEV)
#define FOAM_CHEMISTRYMODEL_SOLVE_NEEDS_TIME
#endif

#if (FOAM_VERSION4SWAK > VERSION_NR2(2,1)) && !defined(FOAM_DEV)
#define FOAM_HAS_SCOPED_LOOKUP
#endif

#if !defined(FOAM_DEV)
#define FOAM_FACECELLWAVE_HAS_TRACKINGDATA
#endif

#if !defined(FOAM_DEV)
#define FOAM_FVMESH_IS_DATAOBJECT
#endif

#if defined(FOAM_DEV)
#define FOAM_ZONEMESH_HAS_NO_FINDINDEX
#endif

#if defined(FOAM_DEV)
#define FOAM_SOLUTION_HAS_NO_READ_WITH_DICT
#define FOAM_SCHEMES_HAS_NO_READ_WITH_DICT
#define FOAM_FVMESH_NOT_CHILD_OF_FVSCHEMES_SOLUTION
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(3,2,0) && defined(FOAM_DEV)
#define FOAM_HAS_LOCAL_DEBUGSWITCHES
#endif

#if FOAM_VERSION4SWAK < VERSION_NR2(2,2) && !defined(FOAM_DEV)
#define FOAM_LDUMATRIX_SOLVER_PERFORMANCE
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(3,0,0) && !defined(FOAM_DEV)
#define FOAM_WALLDIST_HAS_Y_METHOD
#endif

#if (FOAM_VERSION4SWAK > VERSION_NR2(2,2)) && !defined(FOAM_DEV)
#define FOAM_PTRAITS_HAS_ROOTMAX
#endif

#if (FOAM_VERSION4SWAK > VERSION_NR2(2,0)) && !defined(FOAM_DEV)
#define FOAM_DATAENTRY_CLASS_NEEDS_WRITEDATA
#endif

#if FOAM_VERSION4SWAK >= VERSION_NR(3,2,0) && defined(FOAM_DEV)
#define FOAM_MOVED_TIME_AND_STRING_HEADERS
#endif

#if !defined(FOAM_DEV)
#define FOAM_FV_HAS_SMOOTH_SWEEP_SPREAD
#endif

#if !defined(FOAM_DEV)
// currently the available version of interpolation2DTable have a syntax error
#define FOAM_NEEDS_PATCHED_INTERPOLATION2DTABLE
#endif

#if ((FOAM_VERSION4SWAK > VERSION_NR2(2,2)) && !defined(FOAM_DEV)) || defined(FOAM_NEEDS_PATCHED_INTERPOLATION2DTABLE)
#define FOAM_HAS_INTERPOLATION2DTABLE
#endif

#include "swakVersion.H"

#include "DebugOStream.H"

#endif

// ************************************************************************* //
