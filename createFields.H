Info<< "Reading field T\n" << endl;

volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading diffusivity DT\n" << endl;

volScalarField DT
(
    IOobject
    (
        "DT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimViscosity, Zero)
);

if (!DT.headerOk())
{
    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );
    DT = dimensionedScalar("DT", dimViscosity, transportProperties);
}

IOdictionary transportProperties
(
	IOobject
	(
	    "transportProperties",
	    runTime.constant(),
	    mesh,
	    IOobject::MUST_READ_IF_MODIFIED,
	    IOobject::NO_WRITE
	)
);

dimensionedScalar k
(
	"k",
	dimArea/dimTime,
	transportProperties
);

Info<< "Creating kgradT field\n" << endl;

volVectorField gradT(fvc::grad(T));

volVectorField kgradT
(
    IOobject
    (
        "kgradT",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    k*gradT
);

#include "createFvOptions.H"
