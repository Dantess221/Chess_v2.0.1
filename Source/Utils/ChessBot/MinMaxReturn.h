#pragma once
#include "Move.h"


// luokka, jonka avulla saadaan palautettua minmax:ssa sekä siirto-olio että evaluointifunktion arvo
// Struct ajaisi saman asian. Kun ei rakenneta gettereitä ja settereitä, niin ei tarvita toteutus .cpp tiedostoa
class MinMaxReturn {
public:
	double _evaluationValue = 0;
	Move _bestMove;
};