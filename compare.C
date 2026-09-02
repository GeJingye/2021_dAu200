// compare.C
// 比较光转换电子与非光转换电子的性质
// 运行方式：root -l -q 'compare.C("./roots/test.root")'

#include <TCanvas.h>
#include <TH1F.h>
#include <TFile.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TPad.h>
#include <TLatex.h>
#include <iostream>

void compare(const char* filename = "roots/7_20260902_He3Au2014_TOF_cutPEbyTagSingle.root", Int_t number = 7)
{
    gStyle->SetOptStat(0);
    gStyle->SetLegendFont(42);
    
    TFile* file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }
    
    // ============================================================
    // 画布1: 前3个性质 (pT, eta, phi)
    // cd(1) = 光电子 pT, cd(2) = 光电子 eta, cd(3) = 光电子 phi
    // cd(4) = 非光电子 pT, cd(5) = 非光电子 eta, cd(6) = 非光电子 phi
    // ============================================================
    TCanvas* c1 = new TCanvas("c1", "Electron Properties: pT, eta, phi", 1800, 1200);
    c1->Divide(3, 2, 0.005, 0.005);
    
    // ---- cd(1): 光电子 pT ----
    c1->cd(1);
    TH1F* h1 = (TH1F*)file->Get("h_pT__electrons_in_PhiV_Cut");
    if (h1) {
        h1->SetLineColor(kRed);
        h1->SetLineWidth(2);
        h1->SetTitle("Photonic e^{-}: p_{T}");
        h1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
        h1->Draw();
    }
    
    // ---- cd(2): 光电子 eta ----
    c1->cd(2);
    TH1F* h2 = (TH1F*)file->Get("h_eta__electrons_in_PhiV_Cut");
    if (h2) {
        h2->SetLineColor(kRed);
        h2->SetLineWidth(2);
        h2->SetTitle("Photonic e^{-}: #eta");
        h2->GetXaxis()->SetTitle("#eta");
        h2->Draw();
    }
    
    // ---- cd(3): 光电子 phi ----
    c1->cd(3);
    TH1F* h3 = (TH1F*)file->Get("h_phi__electrons_in_PhiV_Cut");
    if (h3) {
        h3->SetLineColor(kRed);
        h3->SetLineWidth(2);
        h3->SetTitle("Photonic e^{-}: #phi");
        h3->GetXaxis()->SetTitle("#phi");
        h3->Draw();
    }
    
    // ---- cd(4): 非光电子 pT ----
    c1->cd(4);
    TH1F* h4 = (TH1F*)file->Get("h_pT__electrons_w_PhiV_Cut");
    if (h4) {
        h4->SetLineColor(kBlue);
        h4->SetLineWidth(2);
        h4->SetTitle("Non-photonic e^{-}: p_{T}");
        h4->GetXaxis()->SetTitle("p_{T} (GeV/c)");
        h4->Draw();
    }
    
    // ---- cd(5): 非光电子 eta ----
    c1->cd(5);
    TH1F* h5 = (TH1F*)file->Get("h_eta__electrons_w_PhiV_Cut");
    if (h5) {
        h5->SetLineColor(kBlue);
        h5->SetLineWidth(2);
        h5->SetTitle("Non-photonic e^{-}: #eta");
        h5->GetXaxis()->SetTitle("#eta");
        h5->Draw();
    }
    
    // ---- cd(6): 非光电子 phi ----
    c1->cd(6);
    TH1F* h6 = (TH1F*)file->Get("h_phi__electrons_w_PhiV_Cut");
    if (h6) {
        h6->SetLineColor(kBlue);
        h6->SetLineWidth(2);
        h6->SetTitle("Non-photonic e^{-}: #phi");
        h6->GetXaxis()->SetTitle("#phi");
        h6->Draw();
    }
    
    c1->Update();
    c1->SaveAs(Form("roots/%d_compare_pt_eta_phi.png",number));
    
    // ============================================================
    // 画布2: 后4个性质 (nHitsFit, nHitsDedx, nHitsMax, DCA)
    // cd(1) = 光电子 nHitsFit,   cd(2) = 光电子 nHitsDedx
    // cd(3) = 光电子 nHitsMax,   cd(4) = 光电子 DCA
    // cd(5) = 非光电子 nHitsFit, cd(6) = 非光电子 nHitsDedx
    // cd(7) = 非光电子 nHitsMax, cd(8) = 非光电子 DCA
    // ============================================================
    TCanvas* c2 = new TCanvas("c2", "Electron Properties: nHitsFit, nHitsDedx, nHitsMax, DCA", 2400, 1200);
    c2->Divide(4, 2, 0.005, 0.005);
    
    // ---- cd(1): 光电子 nHitsFit ----
    c2->cd(1);
    TH1F* h7 = (TH1F*)file->Get("h_nHitsFit__electrons_in_PhiV_Cut");
    if (h7) {
        h7->SetLineColor(kRed);
        h7->SetLineWidth(2);
        h7->SetTitle("Photonic e^{-}: nHitsFit");
        h7->GetXaxis()->SetTitle("nHitsFit");
        h7->Draw();
    }
    
    // ---- cd(2): 光电子 nHitsDedx ----
    c2->cd(2);
    TH1F* h8 = (TH1F*)file->Get("h_nHitsDedx__electrons_in_PhiV_Cut");
    if (h8) {
        h8->SetLineColor(kRed);
        h8->SetLineWidth(2);
        h8->SetTitle("Photonic e^{-}: nHitsDedx");
        h8->GetXaxis()->SetTitle("nHitsDedx");
        h8->Draw();
    }
    
    // ---- cd(3): 光电子 nHitsMax ----
    c2->cd(3);
    TH1F* h9 = (TH1F*)file->Get("h_nHitsMax__electrons_in_PhiV_Cut");
    if (h9) {
        h9->SetLineColor(kRed);
        h9->SetLineWidth(2);
        h9->SetTitle("Photonic e^{-}: nHitsMax");
        h9->GetXaxis()->SetTitle("nHitsMax");
        h9->Draw();
    }
    
    // ---- cd(4): 光电子 DCA ----
    c2->cd(4);
    TH1F* h10 = (TH1F*)file->Get("h_DCA__electrons_in_PhiV_Cut");
    if (h10) {
        h10->SetLineColor(kRed);
        h10->SetLineWidth(2);
        h10->SetTitle("Photonic e^{-}: DCA");
        h10->GetXaxis()->SetTitle("DCA (cm)");
        h10->Draw();
    }
    
    // ---- cd(5): 非光电子 nHitsFit ----
    c2->cd(5);
    TH1F* h11 = (TH1F*)file->Get("h_nHitsFit__electrons_w_PhiV_Cut");
    if (h11) {
        h11->SetLineColor(kBlue);
        h11->SetLineWidth(2);
        h11->SetTitle("Non-photonic e^{-}: nHitsFit");
        h11->GetXaxis()->SetTitle("nHitsFit");
        h11->Draw();
    }
    
    // ---- cd(6): 非光电子 nHitsDedx ----
    c2->cd(6);
    TH1F* h12 = (TH1F*)file->Get("h_nHitsDedx__electrons_w_PhiV_Cut");
    if (h12) {
        h12->SetLineColor(kBlue);
        h12->SetLineWidth(2);
        h12->SetTitle("Non-photonic e^{-}: nHitsDedx");
        h12->GetXaxis()->SetTitle("nHitsDedx");
        h12->Draw();
    }
    
    // ---- cd(7): 非光电子 nHitsMax ----
    c2->cd(7);
    TH1F* h13 = (TH1F*)file->Get("h_nHitsMax__electrons_w_PhiV_Cut");
    if (h13) {
        h13->SetLineColor(kBlue);
        h13->SetLineWidth(2);
        h13->SetTitle("Non-photonic e^{-}: nHitsMax");
        h13->GetXaxis()->SetTitle("nHitsMax");
        h13->Draw();
    }
    
    // ---- cd(8): 非光电子 DCA ----
    c2->cd(8);
    TH1F* h14 = (TH1F*)file->Get("h_DCA__electrons_w_PhiV_Cut");
    if (h14) {
        h14->SetLineColor(kBlue);
        h14->SetLineWidth(2);
        h14->SetTitle("Non-photonic e^{-}: DCA");
        h14->GetXaxis()->SetTitle("DCA (cm)");
        h14->Draw();
    }
    
    c2->Update();
    c2->SaveAs(Form("roots/%d_compare_nhits_dca.png", number));

    file->Close();
}