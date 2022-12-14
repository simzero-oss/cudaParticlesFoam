// Copyright (c) 2022 Carlos Peña-Monferrer. All rights reserved.
// Added integration of GPU-accelerated particle tracking in
// scalarTransportFoam
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    cudaParticlesUncoupledFoam

Group
    grpBasicSolvers

Description
    Particle tracking on GPU.

\*---------------------------------------------------------------------------*/

#include "cuda/common.h"
#include "cuda/DeviceTetMesh.cuh"
#include "cuda/HostTetMesh.h"
#include "query/ConvexQuery.h"
#include "query/RTQuery.h"
#include "optix/OptixQuery.h"

#include "fvCFD.H"
#include "fvOptions.H"
#include "simpleControl.H"
#include "globalMeshData.H"
#include "polyMeshTetDecomposition.H"
#include "globalIndex.H"
#include "vectorList.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace advect {

    extern "C" int main(int argc, char *argv[])
    {
        argList::addNote
        (
            "Passive scalar transport equation solver."
        );

        #include "addCheckCaseOptions.H"
        #include "setRootCaseLists.H"
        #include "createTime.H"
        #include "createMesh.H"

        simpleControl simple(mesh);

        #include "createFields.H"

        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        Info<< "\nCalculating scalar transport\n" << endl;

        #include "CourantNo.H"

        #include "initCuda.H"

        #include "advect.H"

        Info<< "End\n" << endl;

        return 0;
    }

}

// ************************************************************************* //
