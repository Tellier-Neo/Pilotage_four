//*********************************************************************************************
//* Programme : Carte9111.cpp                                            Date : 16/11/2024 
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 16/11/2024 
//*
//* Programmeurs : Yann Fauquembergue                          Classe : BTS CIEL 2
//*                Valentin Rosier 
//*--------------------------------------------------------------------------------------------
//* But : G�rer une carte de type 9111 d�finie en tant qu'objet, par l'utilisation de fonctions
//*       et de son attribut de num�ro de carte
//* Programmes associ�s : Carte9111.h
//*********************************************************************************************

#include "Carte9111.h"

//---------------------------------------------------------------------------------------------
//* Constructeur de la classe `Carte9111`.
//* Initialise la carte de type 9111, avec un num�ro de carte d�fini.
//* Param�tres :
//*  - numeroCarte : Le num�ro de la carte. (Par d�faut, 0)
//* Valeur de retour : Aucune.
//---------------------------------------------------------------------------------------------
Carte9111::Carte9111(I16 numeroCarte)
{
	// Note : Le type de la carte est 9111, donc le param�tre CardType de la fonction
	//		  Register_Card est la constante PCI_9111DG.
	idCarte = Register_Card(PCI_9111DG, numeroCarte);
}

//---------------------------------------------------------------------------------------------
//* Fonction `ConfigurerCarte`.
//* Configuration de la carte
//* Param�tres : 
//*  - sourceTrigger : La source de d�clenchement.
//*  - modeTrigger : Le mode de d�clenchement.
//*  - TraceCnt : Le nombre de donn�es qui seront acc�d�es apr�s un �v�nement de d�clenchement
//     sp�cifique. (Par d�faut, 0)
//* Valeur de retour : Aucune.
//---------------------------------------------------------------------------------------------
void Carte9111::ConfigurerCarte(U16 sourceTrigger, U16 modeTrigger, U16 TraceCnt)
{
	AI_9111_Config(idCarte, sourceTrigger, modeTrigger, TraceCnt);
}

//---------------------------------------------------------------------------------------------
//* Fonction `LireChaine`.
//* Lit une cha�ne de la carte.
//* Param�tres : 
//*  - chaine : La cha�ne � lire.
//*  - *tension : Le pointeur de la valeur de la tension qui sera mesur�e.
//* Valeur de retour : La tension mesur�e, convertie en unit�s de tension.
//---------------------------------------------------------------------------------------------
I16 Carte9111::LireChaine(U16 chaine, F64* tension)
{
	return AI_VReadChannel(idCarte, chaine, AD_B_10_V, tension);
}

//---------------------------------------------------------------------------------------------
//* Fonction `EcrireChaine`.
//* Ecrit une cha�ne sur la carte.
//* Param�tres : 
//*  - chaine : La cha�ne � �crire.
//*  - tension : La valeur �crite dans la cha�ne de sortie analogique.
//* Valeur de retour : La tension mesur�e, convertie en unit�s de tension.
//---------------------------------------------------------------------------------------------
I16 Carte9111::EcrireChaine(U16 chaine, F64 tension)
{
	return AO_VWriteChannel(idCarte, chaine, tension);
}

//---------------------------------------------------------------------------------------------
//* Fonction `GetNumeroCarte`.
//* R�cup�re la valeur du num�ro de la carte.
//* Param�tres : Aucun.
//* Valeur de retour : Le num�ro de la carte.
//---------------------------------------------------------------------------------------------
I16 Carte9111::GetNumeroCarte()
{
	return idCarte;
}
