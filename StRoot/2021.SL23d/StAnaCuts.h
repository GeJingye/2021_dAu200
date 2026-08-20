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
 * read PicoDst document about d+Au200_2021 collision for produciton within TOF acceptance*
 * ****************************************************************************************
  */
#include "Rtypes.h"
#include <string>
#include <array>

namespace anaCuts
{
	const std::array<UInt_t, 8> trigNumber = {880021,880011,880001,	880141,880131,880121,880111,880101};
	//880021,880011,880001:zdce-mb;
	//880022,880012,880002:mb-hltgood;
	//880141,880131,880121,880111,880101:zdce-epde-central;
	//880142,880132,880122,880112,880102:central-hltgood;
	// event cuts 
	Float_t const Vz_up = 70;
	Float_t const Vz_low = -50;
	Float_t const Vr = 2; // 2cm
	Float_t const vzVpdVz = 5; // cm
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
}
#endif
