//*********************************************************************************************
//* Programme : Carte9111.cpp                                            Date : 16/11/2024 
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 16/11/2024 
//*
//* Programmeurs : Yann Fauquembergue                          Classe : BTS CIEL 2
//*                Valentin Rosier 
//*--------------------------------------------------------------------------------------------
//* But : Gérer une carte de type 9111 définie en tant qu'objet, par l'utilisation de fonctions
//*       et de son attribut de numéro de carte
//* Programmes associés : Carte9111.h
//*********************************************************************************************

#include "Carte9111.h"

//---------------------------------------------------------------------------------------------
//* Constructeur de la classe `Carte9111`.
//* Initialise la carte de type 9111, avec un numéro de carte défini.
//* Paramètres :
//*  - numeroCarte : Le numéro de la carte. (Par défaut, 0)
//* Valeur de retour : Aucune.
//---------------------------------------------------------------------------------------------
Carte9111::Carte9111(I16 numeroCarte)
{
	// Note : Le type de la carte est 9111, donc le paramètre CardType de la fonction
	//		  Register_Card est la constante PCI_9111DG.
	idCarte = Register_Card(PCI_9111DG, numeroCarte);
}

//---------------------------------------------------------------------------------------------
//* Fonction `ConfigurerCarte`.
//* Configuration de la carte
//* Paramètres : 
//*  - sourceTrigger : La source de déclenchement.
//*  - modeTrigger : Le mode de déclenchement.
//*  - TraceCnt : Le nombre de données qui seront accédées après un évènement de déclenchement
//     spécifique. (Par défaut, 0)
//* Valeur de retour : Aucune.
//---------------------------------------------------------------------------------------------
void Carte9111::ConfigurerCarte(U16 sourceTrigger, U16 modeTrigger, U16 TraceCnt)
{
	AI_9111_Config(idCarte, sourceTrigger, modeTrigger, TraceCnt);
}

//---------------------------------------------------------------------------------------------
//* Fonction `LireChaine`.
//* Lit une chaîne de la carte.
//* Paramètres : 
//*  - chaine : La chaîne à lire.
//*  - *tension : Le pointeur de la valeur de la tension qui sera mesurée.
//* Valeur de retour : La tension mesurée, convertie en unités de tension.
//---------------------------------------------------------------------------------------------
I16 Carte9111::LireChaine(U16 chaine, F64* tension)
{
	return AI_VReadChannel(idCarte, chaine, AD_B_10_V, tension);
}

//---------------------------------------------------------------------------------------------
//* Fonction `EcrireChaine`.
//* Ecrit une chaîne sur la carte.
//* Paramètres : 
//*  - chaine : La chaîne à écrire.
//*  - tension : La valeur écrite dans la chaîne de sortie analogique.
//* Valeur de retour : La tension mesurée, convertie en unités de tension.
//---------------------------------------------------------------------------------------------
I16 Carte9111::EcrireChaine(U16 chaine, F64 tension)
{
	return AO_VWriteChannel(idCarte, chaine, tension);
}

//---------------------------------------------------------------------------------------------
//* Fonction `GetNumeroCarte`.
//* Récupère la valeur du numéro de la carte.
//* Paramètres : Aucun.
//* Valeur de retour : Le numéro de la carte.
//---------------------------------------------------------------------------------------------
I16 Carte9111::GetNumeroCarte()
{
	return idCarte;
}
