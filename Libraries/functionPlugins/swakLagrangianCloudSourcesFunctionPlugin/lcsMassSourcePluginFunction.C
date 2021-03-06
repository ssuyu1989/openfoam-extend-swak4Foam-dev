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

Contributors/Copyright:
    2012-2013 Bernhard F.W. Gschaider <bgschaid@ice-sf.at>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#include "lcsMassSourcePluginFunction.H"

#include "addToRunTimeSelectionTable.H"

#include "swakCloudTypes.H"

#ifdef FOAM_REACTINGCLOUD_TEMPLATED
#include "BasicReactingCloud.H"
#include "BasicReactingMultiphaseCloud.H"
#else
#include "basicReactingCloud.H"
#include "basicReactingMultiphaseCloud.H"
#endif

namespace Foam {

defineTypeNameAndDebug(lcsMassSourcePluginFunction,0);
addNamedToRunTimeSelectionTable(FieldValuePluginFunction,lcsMassSourcePluginFunction , name, lcsMassSource);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

lcsMassSourcePluginFunction::lcsMassSourcePluginFunction(
    const FieldValueExpressionDriver &parentDriver,
    const word &name
):
    LagrangianCloudSourcePluginFunction(
        parentDriver,
        name,
        "volScalarField"
    )
{
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

autoPtr<lcsMassSourcePluginFunction::dimScalarField> lcsMassSourcePluginFunction::internalEvaluate()
{
    // pick up the first fitting class
#ifdef FOAM_REACTINGCLOUD_TEMPLATED
    tryCall(dimScalarField,constThermoReactingCloud,reactingCloud,Srho());
    tryCall(dimScalarField,thermoReactingCloud,reactingCloud,Srho());
    tryCall(dimScalarField,icoPoly8ThermoReactingCloud,reactingCloud,Srho());
    tryCall(dimScalarField,constThermoReactingMultiphaseCloud,reactingMultiphaseCloud,Srho());
    tryCall(dimScalarField,thermoReactingMultiphaseCloud,reactingMultiphaseCloud,Srho());
    tryCall(dimScalarField,icoPoly8ThermoReactingMultiphaseCloud,reactingMultiphaseCloud,Srho());
#else
    tryCall(dimScalarField,basicReactingCloud,reactingCloud,Srho());
    tryCall(dimScalarField,basicReactingMultiphaseCloud,reactingMultiphaseCloud,Srho());
#endif

    return autoPtr<dimScalarField>();
}

void lcsMassSourcePluginFunction::doEvaluation()
{

    autoPtr<dimScalarField> pSrho=internalEvaluate();

    noCloudFound(pSrho);

    const dimScalarField &Srho=pSrho();

    autoPtr<volScalarField> pSource(
        new volScalarField(
            IOobject(
                cloudName()+"MassSource",
                mesh().time().timeName(),
                mesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh(),
            Srho.dimensions(),
            "zeroGradient"
        )
    );

    pSource->internalField()=Srho.field();

    result().setObjectResult(pSource);
}

// * * * * * * * * * * * * * * * Concrete implementations * * * * * * * * * //


} // namespace

// ************************************************************************* //
