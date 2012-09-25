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

 ICE Revision: $Id$
\*---------------------------------------------------------------------------*/

#include "lcsVolumeFractionPluginFunction.H"

#include "addToRunTimeSelectionTable.H"

#include "basicKinematicCloud.H"
#include "basicThermoCloud.H"
#include "BasicReactingCloud.H"
#include "BasicReactingMultiphaseCloud.H"

namespace Foam {

defineTypeNameAndDebug(lcsVolumeFractionPluginFunction,0);
addNamedToRunTimeSelectionTable(FieldValuePluginFunction,lcsVolumeFractionPluginFunction , name, lcsVolumeFraction);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

lcsVolumeFractionPluginFunction::lcsVolumeFractionPluginFunction(
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

void lcsVolumeFractionPluginFunction::doEvaluation()
{
    autoPtr<volScalarField> ptheta;

    // pick up the first fitting class
    castAndCall(ptheta,volScalarField,basicKinematicCloud,kinematicCloud,theta());
    castAndCall(ptheta,volScalarField,basicThermoCloud,thermoCloud,theta());
    castAndCall(ptheta,volScalarField,constThermoReactingCloud,reactingCloud,theta());
    castAndCall(ptheta,volScalarField,thermoReactingCloud,reactingCloud,theta());
    castAndCall(ptheta,volScalarField,icoPoly8ThermoReactingCloud,reactingCloud,theta());
    castAndCall(ptheta,volScalarField,constThermoReactingMultiphaseCloud,reactingMultiphaseCloud,theta());
    castAndCall(ptheta,volScalarField,thermoReactingMultiphaseCloud,reactingMultiphaseCloud,theta());
    castAndCall(ptheta,volScalarField,icoPoly8ThermoReactingMultiphaseCloud,reactingMultiphaseCloud,theta());

    noCloudFound(ptheta);

    result().setObjectResult(ptheta);
}

// * * * * * * * * * * * * * * * Concrete implementations * * * * * * * * * //


} // namespace

// ************************************************************************* //