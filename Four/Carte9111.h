#pragma once

#include "Include/Dask64.h"
#include <conio.h>
#include <iostream>

class Carte9111
{
public:
	Carte9111(I16 numeroCarte = 0);
	void LibererCarte();
	void ConfigurerCarte(U16 sourceTrigger, U16 modeTrigger, U16 TraceCnt = 0);
	I16 LireChaine(U16 chaine, F64* tension);
	I16 EcrireChaine(U16 chaine, F64 tension);

	I16 GetNumeroCarte();

private:
	I16 idCarte;
};

