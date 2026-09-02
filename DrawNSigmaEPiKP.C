//---------------------从dAu200GeV_2016.root中提取直方图，并进行设置更改和元素添加----------------------
#include "../2021_OO200/someFunction.h"
#include "StRoot/dAu.2021.SL23d/StAnaCuts.h"
void DrawNSigmaEPiKP(TString inFilename = "roots/6_20260831_He3Au2014_TOF.root", Int_t number = 6) //
{
	// 从root文件中导入待拟合的直方图
	TFile *inFile = new TFile(inFilename);
	if (!inFile)
	{
		cout << "The input file is not found! Exiting..." << endl;
		return;
	}
	TH1F *h_cen = (TH1F *)inFile->Get("h_cen");
	TH1F *h_Vz = (TH1F *)inFile->Get("h_Vz");
	TH1F *h_Vr = (TH1F *)inFile->Get("h_Vr");
	TH1F *h_VpdVz = (TH1F *)inFile->Get("h_VpdVz");
	TH1F *h_VpdVzmVz = (TH1F *)inFile->Get("h_VpdVzmVz");//h_VpdVzmVz->GetXaxis()->SetRangeUser(-20,20);
	Double_t underflow = h_VpdVz->GetBinContent(0);  // underflow bin 索引为 0
	Double_t overflow  = h_VpdVz->GetBinContent(h_VpdVz->GetNbinsX() + 1);  // overflow bin 索引为 n+1
	// std::cout << "Underflow: " << underflow << std::endl;
	// std::cout << "Overflow:  " << overflow << std::endl;

	// Int_t binLow  = h_VpdVzmVz->FindBin(-10.0);   // 找到 -10 对应的 bin
	// Int_t binHigh = h_VpdVzmVz->FindBin( 10.0);   // 找到  10 对应的 bin
	// Double_t countInRange = h_VpdVzmVz->Integral(binLow, binHigh);
	// Double_t totalCount = h_VpdVzmVz->Integral(1, h_VpdVzmVz->GetNbinsX());
	// Double_t totalCount1 = h_VpdVzmVz->Integral(0, h_VpdVzmVz->GetNbinsX() + 1);
	// std::cout << "Count in [-10, 10] cm: " << countInRange << std::endl;
	// std::cout << "Total count: " << totalCount << std::endl;
	// std::cout << "Total count (including under/overflow): " << totalCount1 << std::endl;
	// std::cout << "Fraction in range: " << countInRange / totalCount * 100 << "%" << std::endl;
	
	TH1F *h_nTofMat_RefMul = (TH1F *)inFile->Get("h_nTofMat_RefMul");if(!h_nTofMat_RefMul) {cout<<"h_nTofMat_RefMul not found! Exiting..."<<endl; return;}
	TH1F *h_passEvtcut = (TH1F *)inFile->Get("h_passEvtcut");if(!h_passEvtcut) {cout<<"h_passEvtcut not found! Exiting..."<<endl; return;}
	TH1F *h_passTrkcut = (TH1F *)inFile->Get("h_passTrkcut");if(!h_passTrkcut) {cout<<"h_passTrkcut not found! Exiting..."<<endl; return;}
	TH2F *h_VpdVz_Vz = (TH2F *)inFile->Get("h_VpdVz_Vz");if(!h_VpdVz_Vz) {cout<<"h_VpdVz_Vz not found! Exiting..."<<endl; return;}
	TH2F *h_Vx_Vy = (TH2F *)inFile->Get("h_Vx_Vy");if(!h_Vx_Vy) {cout<<"h_Vx_Vy not found! Exiting..."<<endl; return;}

	TH3F *h_nHitsFit_Pt_Eta = (TH3F *)inFile->Get("h_nHitsFit_Pt_Eta");if(!h_nHitsFit_Pt_Eta) {cout<<"h_nHitsFit_Pt_Eta not found! Exiting..."<<endl; return;}
	TH3F *h_nHitsDEdx_Pt_Eta = (TH3F *)inFile->Get("h_nHitsDEdx_Pt_Eta");if(!h_nHitsDEdx_Pt_Eta) {cout<<"h_nHitsDEdx_Pt_Eta not found! Exiting..."<<endl; return;}
	TH3F *h_pDca_Pt_Eta = (TH3F *)inFile->Get("h_pDca_Pt_Eta");if(!h_pDca_Pt_Eta) {cout<<"h_pDca_Pt_Eta not found! Exiting..."<<endl; return;}
	TH1F *h_ppT = (TH1F *)inFile->Get("h_ppT");if(!h_ppT) {cout<<"h_ppT not found! Exiting..."<<endl; return;}
	TH1F *h_pEta = (TH1F *)inFile->Get("h_pEta");if(!h_pEta) {cout<<"h_pEta not found! Exiting..."<<endl; return;}
	TH1F *h_pPhi = (TH1F *)inFile->Get("h_pPhi");if(!h_pPhi) {cout<<"h_pPhi not found! Exiting..."<<endl; return;}
	TH2F *h_pP_ppT = (TH2F *)inFile->Get("h_pP_ppT");if(!h_pP_ppT) {cout<<"h_pP_ppT not found! Exiting..."<<endl; return;}
	TH2F *h_ppTc_pEta = (TH2F *)inFile->Get("h_ppTc_pEta");if(!h_ppTc_pEta) {cout<<"h_ppTc_pEta not found! Exiting..."<<endl; return;}
	TH2F *h_ppTc_pPhi = (TH2F *)inFile->Get("h_ppTc_pPhi");if(!h_ppTc_pPhi) {cout<<"h_ppTc_pPhi not found! Exiting..."<<endl; return;}

	TH2F *h_nSigmaElectron_P = (TH2F *)inFile->Get("h_nSigmaElectron_P");if(!h_nSigmaElectron_P) {cout<<"h_nSigmaElectron_P not found! Exiting..."<<endl; return;}
	TH2F *h_nSigmaEcorr_P = (TH2F *)inFile->Get("h_nSigmaEcorr_P");if(!h_nSigmaEcorr_P) {cout<<"h_nSigmaEcorr_P not found! Exiting..."<<endl; return;}
	// group 1
	TH1F *h_pT__TOFMatch = (TH1F *)inFile->Get("h_pT__TOFMatch");if(!h_pT__TOFMatch) {cout<<"h_pT__TOFMatch not found! Exiting..."<<endl; return;}
	TH1F *h_Eta__TOFMatch = (TH1F *)inFile->Get("h_Eta__TOFMatch");if(!h_Eta__TOFMatch) {cout<<"h_Eta__TOFMatch not found! Exiting..."<<endl; return;}
	TH1F *h_Phi__TOFMatch = (TH1F *)inFile->Get("h_Phi__TOFMatch");if(!h_Phi__TOFMatch) {cout<<"h_Phi__TOFMatch not found! Exiting..."<<endl; return;}
	TH2F *h_nSigmaElectron_P__1 = (TH2F *)inFile->Get("h_nSigmaElectron_P__1");if(!h_nSigmaElectron_P__1) {cout<<"h_nSigmaElectron_P__1 not found! Exiting..."<<endl; return;}
	TH2F *h_invBeta_P__TOFMatch = (TH2F *)inFile->Get("h_invBeta_P__TOFMatch");if(!h_invBeta_P__TOFMatch) {cout<<"h_invBeta_P__TOFMatch not found! Exiting..."<<endl; return;}
	TH2F *h_nSigmaElectron_P__TOFMatch = (TH2F *)inFile->Get("h_nSigmaElectron_P__TOFMatch");if(!h_nSigmaElectron_P__TOFMatch) {cout<<"h_nSigmaElectron_P__TOFMatch not found! Exiting..."<<endl; return;}
	TH2F *h_nSigmaElectron_P__EIDcut_1 = (TH2F *)inFile->Get("h_nSigmaElectron_P__EIDcut_1");if(!h_nSigmaElectron_P__EIDcut_1) {cout<<"h_nSigmaElectron_P__EIDcut_1 not found! Exiting..."<<endl; return;}
	// phiV cut
	TH2F *h_Mee_PhiV__unlikeSame = (TH2F *)inFile->Get("h_Mee_PhiV__unlikeSame");if(!h_Mee_PhiV__unlikeSame) {cout<<"h_Mee_PhiV__unlikeSame not found! Exiting..."<<endl; return;}
	TH1F *h_Mee__unlikeSame = (TH1F *)inFile->Get("h_Mee__unlikeSame");if(!h_Mee__unlikeSame) {cout<<"h_Mee__unlikeSame not found! Exiting..."<<endl; return;}
	TH1F *h_Mee__unlikeSame__w_PhiV_Cut = (TH1F *)inFile->Get("h_Mee__unlikeSame__w_PhiV_Cut");if(!h_Mee__unlikeSame__w_PhiV_Cut) {cout<<"h_Mee__unlikeSame__w_PhiV_Cut not found! Exiting..."<<endl; return;}
	auto fphiVcut = new TF1("fphiVcut", "0.84326*exp(-49.4819*x)-0.996609*x+0.19801", 0, 0.5);
	fphiVcut->SetNpx(1000);
	
	if (0) // clear plot
	{
		TCanvas *c_temp = new TCanvas("c_temp", "c_temp", 1200, 900);
		c_temp->Divide(3, 2);

		c_temp->cd(1);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_ppTc_pPhi->GetXaxis()->SetRangeUser(0.0, 5.0);
		h_ppTc_pPhi->DrawClone("col z");

		c_temp->cd(2);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_ppTc_pPhi->GetXaxis()->SetRangeUser(-5.0, 0.0);
		h_ppTc_pPhi->DrawClone("col z");

		c_temp->SaveAs(Form("roots/%d_temp.png", number));
	}
	if (0) // h_passEvtcut,h_passTrkcut,h_nHitsFit_Pt_Eta,h_nHitsDEdx_Pt_Eta,h_pDca_Pt_Eta
	{
		// 投影
		TH2F *h_nHitsFit_Pt = (TH2F *)h_nHitsFit_Pt_Eta->Project3D("zx");if(!h_nHitsFit_Pt) {cout<<"h_nHitsFit_Pt not found! Exiting..."<<endl; return;}
		TH2F *h_nHitsFit_Eta = (TH2F *)h_nHitsFit_Pt_Eta->Project3D("zy");if(!h_nHitsFit_Eta) {cout<<"h_nHitsFit_Eta not found! Exiting..."<<endl; return;}
		TH2F *h_nHitsDEdx_Pt = (TH2F *)h_nHitsDEdx_Pt_Eta->Project3D("zx");if(!h_nHitsDEdx_Pt) {cout<<"h_nHitsDEdx_Pt not found! Exiting..."<<endl; return;}
		TH2F *h_nHitsDEdx_Eta = (TH2F *)h_nHitsDEdx_Pt_Eta->Project3D("zy");if(!h_nHitsDEdx_Eta) {cout<<"h_nHitsDEdx_Eta not found! Exiting..."<<endl; return;}
		TH2F *h_pDca_Pt = (TH2F *)h_pDca_Pt_Eta->Project3D("xy");if(!h_pDca_Pt) {cout<<"h_pDca_Pt not found! Exiting..."<<endl; return;}
		TH2F *h_pDca_Eta = (TH2F *)h_pDca_Pt_Eta->Project3D("xz");if(!h_pDca_Eta) {cout<<"h_pDca_Eta not found! Exiting..."<<endl; return;}
		// 误差条，设置Marker形状颜色，设置线条颜色，设置图例，设置坐标轴标题，设置对数Y坐标）
		//h_Vx_Vy->SetTitle("V_{z} vs V_{x};V_{x} (cm);V_{z} (cm)");
		//h_VpdVz_Vz->SetTitle("V_{z}(TPC) vs V_{z}(VPD);V_{z}(VPD) (cm);V_{z}(TPC) (cm)");
		TCanvas *c_temp = new TCanvas("c_temp", "c_temp", 900, 800);
		c_temp->Divide(4, 4);

		c_temp->cd(1);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_ppTc_pPhi->GetXaxis()->SetRangeUser(0.0, 5.0);
		h_ppTc_pPhi->DrawClone("col z");

		c_temp->cd(2);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_ppTc_pPhi->GetXaxis()->SetRangeUser(-5.0, 0.0);
		h_ppTc_pPhi->DrawClone("col z");

		c_temp->cd(3);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Vz->DrawClone("col z");
		TLine *line_Vz1 = new TLine(anaCuts::Vz_up, 0, anaCuts::Vz_up, 1e8);
		line_Vz1->SetLineColor(kRed);
		TLine *line_Vz2 = new TLine(anaCuts::Vz_low, 0, anaCuts::Vz_low, 1e8);
		line_Vz2->SetLineColor(kRed);
		line_Vz1->Draw("same");
		line_Vz2->Draw("same");

		c_temp->cd(4);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_VpdVzmVz->DrawClone("col z");
		TLine *line_VPDmVz1 = new TLine(anaCuts::vzVpdVz, 0, anaCuts::vzVpdVz, 1e8);
		line_VPDmVz1->SetLineColor(kRed);
		TLine *line_VPDmVz2 = new TLine(-anaCuts::vzVpdVz, 0, -anaCuts::vzVpdVz, 1e8);
		line_VPDmVz2->SetLineColor(kRed);
		line_VPDmVz1->Draw("same");
		line_VPDmVz2->Draw("same");

		c_temp->cd(5);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Vx_Vy->DrawClone("col z");

		c_temp->cd(6);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_VpdVz_Vz->GetYaxis()->SetTitleOffset(1.5);
		h_Vr->DrawClone("col z");
		TLine *line_Vr = new TLine(anaCuts::Vr, 0, anaCuts::Vr, 1e8);
		line_Vr->SetLineColor(kRed);
		line_Vr->Draw("same");

		c_temp->cd(7);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		//h_passEvtcut->SetMaximum(1e8);
		h_passEvtcut->DrawClone("TEXT");
		h_passEvtcut->DrawClone("same");

		c_temp->cd(8);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_passTrkcut->DrawClone("TEXT0");
		h_passTrkcut->DrawClone("same");

		c_temp->cd(9);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_nHitsFit_Pt->SetTitle("nHitsFit vs p_{T}");
		h_nHitsFit_Pt->GetXaxis()->SetRangeUser(0.0, 3.0);
		h_nHitsFit_Pt->DrawClone("col z");

		c_temp->cd(10);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_nHitsDEdx_Pt->SetTitle("nHitsDEdx vs p_{T}");
		h_nHitsDEdx_Pt->GetXaxis()->SetRangeUser(0.0, 3.0);
		h_nHitsDEdx_Pt->DrawClone("col z");

		c_temp->cd(11);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_pDca_Pt->SetTitle("DCA vs p_{T}");
		h_pDca_Pt->GetXaxis()->SetRangeUser(0.0, 3.0);
		h_pDca_Pt->DrawClone("col z");

		c_temp->cd(12);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_nTofMat_RefMul->DrawClone("col z");

		c_temp->cd(13);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_nHitsFit_Pt->SetTitle("nHitsFit vs p_{T}");
		h_nHitsFit_Pt->GetXaxis()->SetRangeUser(0.0, 5);
		h_nHitsFit_Pt->DrawClone("col z");
		TLine *line_Fit1 = new TLine(0.2, anaCuts::NHitsFit, 5, anaCuts::NHitsFit);
		line_Fit1->SetLineColor(kRed);
		line_Fit1->Draw("same");

		c_temp->cd(14);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_nHitsDEdx_Pt->SetTitle("nHitsDEdx vs p_{T}");
		h_nHitsDEdx_Pt->GetXaxis()->SetRangeUser(0.0, 5);
		h_nHitsDEdx_Pt->DrawClone("col z");
		TLine *line_DEdx1 = new TLine(0.2, anaCuts::NHitsDedx, 5, anaCuts::NHitsDedx);
		line_DEdx1->SetLineColor(kRed);
		line_DEdx1->Draw("same");

		c_temp->cd(15);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_pDca_Pt->SetTitle("DCA vs p_{T}");
		h_pDca_Pt->GetXaxis()->SetRangeUser(0.0, 5);
		h_pDca_Pt->DrawClone("col z");
		TLine *line_DCA1 = new TLine(0.2, anaCuts::Dca, 5, anaCuts::Dca);
		line_DCA1->SetLineColor(kRed);
		line_DCA1->Draw("same");

		c_temp->cd(16);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_cen->DrawClone();

		c_temp->SaveAs(Form("roots/%d_Track_and_Event_Check.png", number));
	}
	if (0) // track QA and TOF track check
	{
		TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
		c1->Divide(3, 2);
		c1->cd(1);
		gPad->SetLogy(1);
		h_ppT->GetXaxis()->SetRangeUser(0., 3.0);
		// h_ppT->GetYaxis()->SetRangeUser(1., 1e8);
		h_ppT->Draw();

		c1->cd(2);
		gPad->SetLogy(1);
		// h_pEta->GetYaxis()->SetRangeUser(1., 1e8);
		h_pEta->Draw();

		c1->cd(3);
		gPad->SetLogy(1);
		h_pPhi->GetXaxis()->SetRangeUser(-TMath::Pi() * 4 / 3, TMath::Pi() * 4 / 3);
		// h_pPhi->GetYaxis()->SetRangeUser(1., 1e8);
		h_pPhi->GetXaxis()->SetNdivisions(-108);						   // 负号 = 用户自定义，202 = π 刻度
		h_pPhi->GetXaxis()->ChangeLabel(1, -1, -1, -1, -1, -1, "-4#pi/3"); // 让 ROOT 自动写 kπ
		h_pPhi->GetXaxis()->ChangeLabel(2, -1, -1, -1, -1, -1, "-#pi");
		h_pPhi->GetXaxis()->ChangeLabel(3, -1, -1, -1, -1, -1, "-2#pi/3");
		h_pPhi->GetXaxis()->ChangeLabel(4, -1, -1, -1, -1, -1, "-#pi/3");
		h_pPhi->GetXaxis()->ChangeLabel(5, -1, -1, -1, -1, -1, "0");
		h_pPhi->GetXaxis()->ChangeLabel(-4, -1, -1, -1, -1, -1, "#pi/3");
		h_pPhi->GetXaxis()->ChangeLabel(-3, -1, -1, -1, -1, -1, "2#pi/3");
		h_pPhi->GetXaxis()->ChangeLabel(-2, -1, -1, -1, -1, -1, "#pi");
		h_pPhi->GetXaxis()->ChangeLabel(-1, -1, -1, -1, -1, -1, "4#pi/3"); // 让 ROOT 自动写 kπ
		h_pPhi->Draw();

		c1->cd(4);
		gPad->SetLogy(1);
		h_pT__TOFMatch->GetXaxis()->SetRangeUser(0., 3.0);
		// h_pT__TOFMatch->GetYaxis()->SetRangeUser(1., 1e8);
		h_pT__TOFMatch->Draw();

		c1->cd(5);
		gPad->SetLogy(1);
		// h_Eta__TOFMatch->GetYaxis()->SetRangeUser(1., 1e8);
		h_Eta__TOFMatch->Draw();

		c1->cd(6);
		gPad->SetLogy(1);
		h_Phi__TOFMatch->GetXaxis()->SetRangeUser(-TMath::Pi() * 4 / 3, TMath::Pi() * 4 / 3);
		// h_Phi__TOFMatch->GetYaxis()->SetRangeUser(1., 1e8);
		h_Phi__TOFMatch->GetXaxis()->SetNdivisions(-108);							// 负号 = 用户自定义，202 = π 刻度
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(1, -1, -1, -1, -1, -1, "-4#pi/3"); // 让 ROOT 自动写 kπ
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(2, -1, -1, -1, -1, -1, "-#pi");
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(3, -1, -1, -1, -1, -1, "-2#pi/3");
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(4, -1, -1, -1, -1, -1, "-#pi/3");
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(5, -1, -1, -1, -1, -1, "0");
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(-4, -1, -1, -1, -1, -1, "#pi/3");
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(-3, -1, -1, -1, -1, -1, "2#pi/3");
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(-2, -1, -1, -1, -1, -1, "#pi");
		h_Phi__TOFMatch->GetXaxis()->ChangeLabel(-1, -1, -1, -1, -1, -1, "4#pi/3"); // 让 ROOT 自动写 kπ
		h_Phi__TOFMatch->Draw();

		c1->SaveAs(Form("roots/%d_TrackQA_and_TrackTOFMatch.png", number));
	}
	if (1) // check PhiV cut
	{
		h_Mee__unlikeSame->SetLineColor(kBlack);
		h_Mee__unlikeSame->GetYaxis()->SetTitleOffset(1.5);
		h_Mee__unlikeSame__w_PhiV_Cut->SetLineColor(kBlue);
		h_Mee__unlikeSame->SetTitle("M_{ee} w/wo #phi_{V} cut;M_{ee} (GeV/c^{2});Counts");

		TCanvas* c_temp = new TCanvas("c_temp", "c_temp", 1000, 800);
		c_temp->Divide(2, 2);
		c_temp->cd(1);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Mee_PhiV__unlikeSame->GetXaxis()->SetRangeUser(0, 0.2);
		h_Mee_PhiV__unlikeSame->DrawClone("col z");
		fphiVcut->DrawClone("same");
		TPaveText *pt2 = new TPaveText(0.15, 0.79, 0.85, 0.86, "NDC NB");
		pt2->SetFillColorAlpha(0, 0);   // 透明底
		pt2->SetFillStyle(0);
		pt2->SetBorderSize(0);
		pt2->SetTextFont(42);
		pt2->SetTextSize(0.04);
		pt2->SetTextAlign(12);
		pt2->AddText("#phi_{V}=0.8433*Exp(-49.4819*M)-0.9966*M+0.1980");
		pt2->DrawClone("same");

		c_temp->cd(2);
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Mee__unlikeSame->GetXaxis()->SetRangeUser(0, 0.2);
		h_Mee__unlikeSame->DrawClone("");
		h_Mee__unlikeSame__w_PhiV_Cut->DrawClone("same");
		auto legend = new TLegend(0.53, 0.58, 0.78, 0.68);
		legend->SetFillColor(0); legend->SetBorderSize(0);
		legend->AddEntry(h_Mee__unlikeSame, "\t without #phi_{V} cut", "lp");
		legend->AddEntry(h_Mee__unlikeSame__w_PhiV_Cut, "\t with #phi_{V} cut", "lp");
		legend->SetMargin(0.20);
		gStyle->SetLegendTextSize(0.04);
		legend->DrawClone("same");

		c_temp->cd(3);
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Mee__unlikeSame->GetXaxis()->SetRangeUser(0, 0.5);
		h_Mee__unlikeSame__w_PhiV_Cut->GetXaxis()->SetRangeUser(0, 0.5);
		h_Mee__unlikeSame->DrawClone("");
		h_Mee__unlikeSame__w_PhiV_Cut->DrawClone("same");
		legend->DrawClone("same");

		c_temp->cd(4);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);

		c_temp->SaveAs(Form("roots/%d_PhiV_Check.png", number));
	}

	if (0) // EID in group1(pT>0.2, |eta|<1)
	{
		// 设置直方图格式
		// 去除误差条，设置Marker形状颜色，设置线条颜色，设置图例，设置坐标轴标题，设置对数Y坐标）
		//h_nSigmaElectron_P__1->SetTitle("n#sigma_{e} in p_{T}>0.2&|#eta|<0.9;p (GeV/c);n#sigma_{e}");
		h_invBeta_P__TOFMatch->GetYaxis()->SetRangeUser(0.0, 3.5);
		//h_nSigmaElectron_P__TOFMatch->SetTitle("n#sigma_{e} with TOF cut;p (GeV/c);n#sigma_{e}");
		// 画图
		TCanvas *c4 = new TCanvas("c4", "c4", 1200, 800);
		c4->Divide(3, 2);
		c4->cd(1); // nSigmaE
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_nSigmaElectron_P__1->Draw("col z");

		c4->cd(2);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_invBeta_P__TOFMatch->Draw("col z");
		TLine *line1_beta1 = new TLine(0.0, 1 - 0.025, 5.0, 1 - 0.025);
		line1_beta1->SetLineColor(kRed);
		line1_beta1->Draw("same");
		TLine *line1_beta2 = new TLine(0.0, 1 + 0.025, 5.0, 1 + 0.025);
		line1_beta2->SetLineColor(kRed);
		line1_beta2->Draw("same");

		c4->cd(3);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_nSigmaElectron_P__TOFMatch->Draw("col z");
		TLine *line1_TOF1 = new TLine(0.0, 3.0, 5.0, 3.0);
		line1_TOF1->SetLineColor(kRed);
		line1_TOF1->Draw("same");
		TLine *line1_TOF2 = new TLine(1.0, -1.0, 5.0, -1.0);
		line1_TOF2->SetLineColor(kRed);
		line1_TOF2->Draw("same");
		TLine *line1_TOF3 = new TLine(0.0, -3.5, 1.0, -1.0);
		line1_TOF3->SetLineColor(kRed);
		line1_TOF3->Draw("same");

		c4->cd(4);
		gPad->SetLogz(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_nSigmaElectron_P__EIDcut_1->Draw("col z");

		c4->SaveAs(Form("roots/%d_group1.png", number));
	}
	}
