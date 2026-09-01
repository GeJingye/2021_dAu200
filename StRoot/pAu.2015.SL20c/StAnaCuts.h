#ifndef StAnaCuts_H
#define StAnaCuts_H

/* **************************************************
 *
 *  Authors: Guannan Xie <guannanxie@lbl.gov>
 *           Mustafa Mustafa <mmustafa@lbl.gov>
 *
 * **************************************************
 */
/* ****************************************************************************************
 * read PicoDst document about p+Au200_2015 collision for produciton within TOF acceptance*
 * ****************************************************************************************
  */
#include "Rtypes.h"
#include <string>
#include <array>

namespace anaCuts
{
	const std::array<UInt_t, 6> trigNumber = {500202,		500206,				 500205,500215,		500001,		 	500904};
	//										  BHT1*VPDMB-30;BHT1*VPDMB-30_nobsmd;BHT2*BBCMB;		VPDMB-5-ssd; 	VPDMB-30;
	// event cuts 
	Float_t const Vz_up = 70;
	Float_t const Vz_low = -50;
	Float_t const Vr = 2; // 2cm
	Float_t const vzVpdVz = 10; // cm
	Float_t const Verr = 1e-5; // cm
	// tracks cuts
	Float_t const NHitsFitRatio = 0.52;
	Float_t const NHitsFit = 20;
	Float_t const NHitsDedx = 15;
	Float_t const Dca = 1;
	// border
	Float_t const Pt = 0.2;
	Float_t const Eta = 1.0;
	// beta cut
	Float_t const invBetaCut = 0.025;
	// phiV cut
    Float_t const PhiVCutMRange = 0.2;

	//P24iy, iTPCrmLowP  nsigma_e
	const Double_t etaCorr[40] = {0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.046,0.056,0.116,0.101,-0.028,-0.212,-0.410,-0.566,-0.653,-0.706,-0.706,-0.653,-0.541,-0.384,-0.217,-0.085,-0.024,-0.023,-0.055,-0.052,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000};
	const Double_t phiCorr[64] =	{-0.156,-0.190,-0.251,-0.272,-0.257,-0.199,-0.235,-0.337,-0.376,-0.364,-0.275,-0.260,-0.335,-0.378,-0.319,-0.206,-0.143,-0.185,-0.242,-0.274,-0.226,-0.144,-0.218,-0.289,-0.308,-0.288,-0.203,-0.179,-0.225,-0.241,-0.207,-0.086,-0.081,-0.174,-0.208,-0.249,-0.174,-0.144,-0.243,-0.314,-0.337,-0.244,-0.171,-0.237,-0.328,-0.329,-0.242,-0.154,-0.209,-0.304,-0.330,-0.278,-0.202,-0.238,-0.378,-0.439,-0.421,-0.341,-0.315,-0.360,-0.379,-0.357,-0.240,-0.159};
	const Double_t phiAverageCorr = -0.257;
}
#endif
