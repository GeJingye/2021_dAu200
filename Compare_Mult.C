// Compare normalized reference-multiplicity distributions from two ROOT files.
#include <iostream>

#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TStyle.h"
#include "TVirtualPad.h"

void Compare_Mult(
	TString firstFileName = "roots/dAu/13_20260912_dAu2021_TOF_onlyMB.root",
	TString secondFileName = "roots/He3Au/11_20260908_He3Au2014_TOF_ZDCETg_Vz40.root",
	Int_t number = 13,
	TString thirdFileName = "roots/Compare_dAu_OO/20260910_iTPC11_P24ia_SameWithZihanNoVPDcut.root")
{
	TFile* firstFile = TFile::Open(firstFileName, "READ");
	TFile* secondFile = TFile::Open(secondFileName, "READ");
	TFile* thirdFile = TFile::Open(thirdFileName, "READ");

	TH1* firstRefMult = nullptr;
	TH1* secondRefMult = nullptr;
	TH1* thirdRefMult = nullptr;
	TH1* firstCen = nullptr;
	TH1* secondCen = nullptr;
	TH1* thirdCen = nullptr;
	firstFile->GetObject("h_RefMult", firstRefMult);
	secondFile->GetObject("h_RefMult", secondRefMult);
	thirdFile->GetObject("h_RefMult", thirdRefMult);
	firstFile->GetObject("h_cen", firstCen);
	secondFile->GetObject("h_cen", secondCen);
	thirdFile->GetObject("h_cen", thirdCen);

	const Double_t firstEvents = firstCen->GetEntries() - firstCen->GetBinContent(1);
	const Double_t secondEvents = secondCen->GetEntries() - secondCen->GetBinContent(1);
	const Double_t thirdEvents = thirdCen->GetEntries() - thirdCen->GetBinContent(1);

	TH1* firstNormalized = (TH1*)firstRefMult->Clone("h_RefMult_firstNormalized");
	TH1* secondNormalized = (TH1*)secondRefMult->Clone("h_RefMult_secondNormalized");
	TH1* thirdNormalized = (TH1*)thirdRefMult->Clone("h_RefMult_thirdNormalized");
	firstNormalized->SetDirectory(nullptr);
	secondNormalized->SetDirectory(nullptr);
	thirdNormalized->SetDirectory(nullptr);
    firstNormalized->Sumw2();
    secondNormalized->Sumw2();
	thirdNormalized->Sumw2();
    
	firstNormalized->Scale(1.0 / firstEvents);
	secondNormalized->Scale(1.0 / secondEvents);
	thirdNormalized->Scale(1.0 / thirdEvents);

	TH1* ratio = (TH1*)firstNormalized->Clone("h_RefMult_ratio");
	ratio->SetDirectory(nullptr);
	ratio->SetTitle(";RefMult;dAu / OO");
	ratio->Divide(thirdNormalized);
	TH1* ratio2 = (TH1*)secondNormalized->Clone("h_RefMult_ratio2");
	ratio2->SetDirectory(nullptr);
	ratio2->SetTitle(";RefMult;He3+Au / OO");
	ratio2->Divide(thirdNormalized);

	firstNormalized->SetTitle(";RefMult;Events / total events");
	firstNormalized->SetLineColor(kRed + 1);
	firstNormalized->SetMarkerColor(kRed + 1);
	firstNormalized->SetMarkerStyle(kOpenCircle);
	firstNormalized->SetMarkerSize(0.7);

	secondNormalized->SetLineColor(kBlue + 1);
	secondNormalized->SetMarkerColor(kBlue + 1);
	secondNormalized->SetMarkerStyle(kOpenSquare);
	secondNormalized->SetMarkerSize(0.7);

	thirdNormalized->SetLineColor(kGreen + 2);
	thirdNormalized->SetMarkerColor(kGreen + 2);
	thirdNormalized->SetMarkerStyle(kOpenDiamond);
	thirdNormalized->SetMarkerSize(0.7);

	ratio->SetLineColor(kRed + 1);
	ratio->SetMarkerColor(kRed + 1);
	ratio->SetMarkerStyle(kOpenCircle);
	ratio->SetMarkerSize(0.7);
	ratio->SetMinimum(0.0);
	ratio->SetMaximum(5.0);
	ratio2->SetLineColor(kBlue + 1);
	ratio2->SetMarkerColor(kBlue + 1);
	ratio2->SetMarkerStyle(kOpenSquare);
	ratio2->SetMarkerSize(0.7);
	ratio2->SetMinimum(0.0);
	ratio2->SetMaximum(5.0);

	TCanvas* c_BR = new TCanvas("c_BR", "c_BR", 800, 800);
	c_BR->Divide(1, 2);

	TVirtualPad* pad1 = c_BR->cd(1);
	pad1->SetPad(0.0, 0.25, 1.0, 1.0);
	pad1->SetBottomMargin(0);
	pad1->SetLogy(1);
	pad1->cd();
	pad1->Clear();
	gStyle->SetOptStat(0);
    firstNormalized->SetMaximum(1.0);
    firstNormalized->GetXaxis()->SetRangeUser(0, 100);
	firstNormalized->Draw("E1");
	secondNormalized->Draw("E1 SAME");
	thirdNormalized->Draw("E1 SAME");

	TLegend* legend = new TLegend(0.55, 0.70, 0.90, 0.90);
	legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.04);
	legend->AddEntry(firstNormalized, "dAu@200GeV", "lp");
	legend->AddEntry(secondNormalized, "He3+Au@200GeV", "lp");
	legend->AddEntry(thirdNormalized, "O+O@200GeV", "lp");
	legend->Draw();

	TPaveText* meanText = new TPaveText(0.15, 0.05, 0.50, 0.38, "NDC NB");
	meanText->SetFillStyle(0);
	meanText->SetBorderSize(0);
	meanText->SetTextAlign(12);
	meanText->SetTextSize(0.04);
	meanText->AddText(Form("dAu events: %.0fM", firstEvents / 1.0e6));
	meanText->AddText(Form("He3+Au events: %.0fM", secondEvents / 1.0e6));
	meanText->AddText(Form("O+O events: %.0fM", thirdEvents / 1.0e6));
	meanText->AddText(Form("dAu: #LTRefMult#GT = %.2f #pm %.2f",
		firstNormalized->GetMean(), firstNormalized->GetMeanError()));
	meanText->AddText(Form("He3+Au: #LTRefMult#GT = %.2f #pm %.2f",
		secondNormalized->GetMean(), secondNormalized->GetMeanError()));
	meanText->AddText(Form("O+O: #LTRefMult#GT = %.2f #pm %.2f",
		thirdNormalized->GetMean(), thirdNormalized->GetMeanError()));
	meanText->Draw();

	TVirtualPad* pad2 = c_BR->cd(2);
	pad2->SetPad(0.0, 0.0, 1.0, 0.25);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.25);
	pad2->SetLogy(0);
	pad2->cd();
	pad2->Clear();
	gStyle->SetOptStat(0);
    ratio->GetXaxis()->SetRangeUser(0, 100);
	ratio->GetXaxis()->SetLabelSize(0.12);
	ratio->GetXaxis()->SetTitleSize(0.13);
	ratio->GetXaxis()->SetTitleOffset(0.85);
	ratio->GetYaxis()->SetLabelSize(0.10);
	ratio->GetYaxis()->SetTitleSize(0.10);
	ratio->GetYaxis()->SetTitleOffset(0.45);
	ratio->GetYaxis()->SetNdivisions(505);
	ratio->Draw("E1");
	ratio2->Draw("E1 SAME");

	TLegend* ratioLegend = new TLegend(0.55, 0.55, 0.90, 0.90);
	ratioLegend->SetBorderSize(0);
	ratioLegend->SetFillStyle(0);
	ratioLegend->SetTextSize(0.10);
	ratioLegend->AddEntry(ratio, "dAu / O+O", "lp");
	ratioLegend->AddEntry(ratio2, "He3+Au / O+O", "lp");
	ratioLegend->Draw();

	TLine* unityLine = new TLine(
		ratio->GetXaxis()->GetXmin(), 1.0,
		ratio->GetXaxis()->GetXmax(), 1.0);
	unityLine->SetLineStyle(2);
	unityLine->Draw("SAME");

	c_BR->SaveAs(Form("roots/%d_Compare_RefMult.png", number));
}
