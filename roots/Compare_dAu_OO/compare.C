// compare.C
// 比较两个ROOT文件中的双电子信号，在J/psi区间(3.0-3.2 GeV/c²)归一化后对比
// 运行：root -l -q 'compare.C("file1.root", "file2.root")'
// 默认文件名为示例，请根据实际情况修改

#include "../../../2021_OO200/someFunction.h"
#include <vector>
#include <iostream>

// 定义与 CalMee.C 相同的 bin 边界
static vector<Double_t> Mee__newEdges = {0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.16,0.20,0.30,0.35,0.40,0.50,0.60,0.64,0.68,0.72,0.76,0.82,0.86,0.96,1.0,1.02,1.04,1.06,1.1,1.2,1.6,2.0,2.3,2.8,3.0, 3.04,3.08,3.10,3.12,3.14,3.18,3.20,3.26,3.3,4.0};//size()=38
//static std::vector<Double_t> Mee__newEdges = {0.00,0.10,0.20,0.4,0.76,1.2,1.8,2.3,2.8,3.0,3.20,4.0};
static Int_t Mee_bins = Mee__newEdges.size() - 1;

static std::vector<Double_t> Pt__newEdges = {0, 0.3, 1.0, 2.0, 3.0, 4.0, 5.0};
static Int_t Pt_bins = Pt__newEdges.size() - 1;

static std::vector<Double_t> Cen__newEdges = {0, 2, 4, 8, 16};
static Int_t Cen_bins = Cen__newEdges.size() - 1;

// J/psi 归一化区间 (可根据实际峰位置调整)
static const Double_t Jpsi_low  = 3.0;   // GeV/c²
static const Double_t Jpsi_high = 3.2;   // GeV/c²

//----------------------------------------------------------------------
// 从指定文件中提取信号直方图 (1D Mee)
TH1F* GetSignal(TString filename, TString prefix = "")
{
    TFile* inFile = TFile::Open(filename);
    if (!inFile || inFile->IsZombie()) {
        std::cerr << "Error: cannot open " << filename << std::endl;
        return nullptr;
    }

    // 读取原始三维直方图
    TH3F* h_US = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__unlikeSame");
    TH3F* h_mm = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__likemm");
    TH3F* h_pp = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__likepp");
    TH3F* h_mmM = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__likemmMixed");
    TH3F* h_ppM = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__likeppMixed");
    TH3F* h_UM = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__unlikeMixed");

    if (!h_US || !h_mm || !h_pp || !h_mmM || !h_ppM || !h_UM) {
        std::cerr << "Error: missing histograms in " << filename << std::endl;
        inFile->Close();
        return nullptr;
    }

    // 创建重分 bin 后的三维直方图
    TH3F* h_mm_R = new TH3F("h_mm_R", "", Mee_bins, Mee__newEdges.data(),
                             Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_pp_R = new TH3F("h_pp_R", "", Mee_bins, Mee__newEdges.data(),
                             Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_US_R = new TH3F("h_US_R", "", Mee_bins, Mee__newEdges.data(),
                             Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_mmM_R = new TH3F("h_mmM_R", "", Mee_bins, Mee__newEdges.data(),
                              Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_ppM_R = new TH3F("h_ppM_R", "", Mee_bins, Mee__newEdges.data(),
                              Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_UM_R = new TH3F("h_UM_R", "", Mee_bins, Mee__newEdges.data(),
                             Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());

    RebinHist(h_mm, h_mm_R);
    RebinHist(h_pp, h_pp_R);
    RebinHist(h_US, h_US_R);
    RebinHist(h_mmM, h_mmM_R);
    RebinHist(h_ppM, h_ppM_R);
    RebinHist(h_UM, h_UM_R);

    // ---- 计算 LS 背景 (PSAC 修正) ----
    TH3F* h_temp = new TH3F("h_temp", "", Mee_bins, Mee__newEdges.data(),
                             Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    h_temp->Multiply(h_mm_R, h_pp_R, 1.0, 1.0);
    TH3F* h_LS = SqrtHist(h_temp, "h_LS");
    h_LS->Scale(2.0);
    h_LS->Add(h_mm_R, h_pp_R, 1.0, 1.0);

    TH3F* h_tempM = new TH3F("h_tempM", "", Mee_bins, Mee__newEdges.data(),
                              Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    h_tempM->Multiply(h_mmM_R, h_ppM_R, 1.0, 1.0);
    TH3F* h_LM = SqrtHist(h_tempM, "h_LM");
    h_LM->Scale(2.0);
    h_LM->Add(h_mmM_R, h_ppM_R, 1.0, 1.0);

    TH3F* h_Corr = new TH3F("h_Corr", "", Mee_bins, Mee__newEdges.data(),
                             Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    h_Corr->Divide(h_UM_R, h_LM, 1.0, 1.0);

    TH3F* h_LS_corr = (TH3F*)h_LS->Clone("h_LS_corr");
    h_LS_corr->Multiply(h_Corr);

    TH3F* h_signal = new TH3F("h_signal", "", Mee_bins, Mee__newEdges.data(),
                               Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    h_signal->Add(h_US_R, h_LS_corr, 1.0, -1.0);

    // 投影到 Mee (积分所有 Pt 和 Cen)
    TH1F* h_Mee = (TH1F*)h_signal->ProjectionX("h_Mee", 1, Pt_bins, 1, Cen_bins);
    h_Mee->SetDirectory(nullptr);
    ResetBinContent(h_Mee);
    inFile->Close();
    return h_Mee;
}

//----------------------------------------------------------------------
// 在 J/psi 区间对直方图进行归一化
struct NormalizedHistogram
{
    TH1F* histogram;
    Double_t factor;
};

NormalizedHistogram NormalizeInJpsi(TH1F* h, const char* name = nullptr)
{
    if (!h) return {nullptr, 0.0};

    // 确定 J/psi 区间对应的 bin 范围
    Int_t binLow  = h->GetXaxis()->FindBin(Jpsi_low  + 0.0001);   // 加小偏移避免边界问题
    Int_t binHigh = h->GetXaxis()->FindBin(Jpsi_high - 0.0001);
    if (binLow < 1) binLow = 1;
    if (binHigh > h->GetNbinsX()) binHigh = h->GetNbinsX();

    // 计算 J/psi 区间的积分及其误差 (假设泊松统计)
    Double_t integral = 0.0;
    Double_t err_integral = 0.0;
    for (Int_t i = binLow; i <= binHigh; ++i) {
        integral += h->GetBinContent(i);
        err_integral += h->GetBinError(i) * h->GetBinError(i);
    }
    err_integral = TMath::Sqrt(err_integral);

    // 若积分太接近零，不做归一化 (打印警告)
    if (integral < 1e-12) {
        std::cerr << "Warning: J/psi integral is zero or negative. Skipping normalization." << std::endl;
        return {(TH1F*)h->Clone(name ? name : "h_norm"), 1.0};
    }

    // 克隆直方图并缩放
    TH1F* h_norm = (TH1F*)h->Clone(name ? name : "h_norm");
    Double_t normalizationFactor = 1.0 / integral;
    h_norm->Scale(normalizationFactor);

    // 误差传递：σ_scaled = σ_original / integral  (忽略归一化因子自身的误差)
    // 更精确的误差传递应考虑归一化因子的误差，但通常忽略
    for (Int_t i = 1; i <= h_norm->GetNbinsX(); ++i) {
        Double_t err_orig = h->GetBinError(i);
        h_norm->SetBinError(i, err_orig / integral);
    }

    // 可选：将归一化区间的误差设为0（使数据点更清晰）
    // for (Int_t i = binLow; i <= binHigh; ++i) {
    //     h_norm->SetBinError(i, 0.0);
    // }


    std::cout << "Normalized: integral = " << integral << " +- " << err_integral 
              << " in J/psi region [" << Jpsi_low << ", " << Jpsi_high << "]" << std::endl;
    return {h_norm, normalizationFactor};
}

//----------------------------------------------------------------------
// 主函数
void compare(TString file1 = "roots/Compare_dAu_OO/13_20260912_dAu2021_TOF_onlyMB.root",
             TString file2 = "roots/Compare_dAu_OO/20260910_iTPC11_P24ia_SameWithZihanNoVPDcut.root", Int_t number = 13)
{
    // 获取两个信号直方图
    TH1F* h1_raw = GetSignal(file1);
    TH1F* h2_raw = GetSignal(file2);
    if (!h1_raw || !h2_raw) {
        std::cerr << "Failed to get signals. Exiting." << std::endl;
        return;
    }

    // ---- 在 J/psi 区间归一化 ----
    NormalizedHistogram normalized1 = NormalizeInJpsi(h1_raw, "h1_norm");
    NormalizedHistogram normalized2 = NormalizeInJpsi(h2_raw, "h2_norm");
    TH1F* h1 = normalized1.histogram;
    TH1F* h2 = normalized2.histogram;
    if (!h1 || !h2) return;

    // 设置样式
    h1->SetLineColor(kRed);
    h1->SetMarkerColor(kRed);
    h1->SetMarkerStyle(20);
    h1->SetTitle(";M_{ee} (GeV/c^{2});Normalized dN/dM_{ee} (arb. units)");

    h2->SetLineColor(kBlue);
    h2->SetMarkerColor(kBlue);
    h2->SetMarkerStyle(21);

    // ---------- 画布1：左右并排显示归一化信号 ----------
    TCanvas* c1 = new TCanvas("c1", "Normalized Signals", 1200, 600);
    c1->Divide(2, 1);

    c1->cd(1);
    gPad->SetLogy(1);
    gStyle->SetOptStat(0);
    h1->Draw("PE");
    TLatex* tex1 = new TLatex(0.15, 0.85, "d+Au@200 GeV (norm. to J/#psi)");
    tex1->SetNDC();
    tex1->SetTextSize(0.04);
    tex1->Draw();
    TPaveText* normBox1 = new TPaveText(0.55, 0.70, 0.88, 0.78, "NDC");
    normBox1->SetFillStyle(0);
    normBox1->SetBorderSize(0);
    normBox1->AddText(Form("Norm. factor = %.4g", normalized1.factor));
    normBox1->Draw();

    c1->cd(2);
    gPad->SetLogy(1);
    gStyle->SetOptStat(0);
    h2->Draw("PE");
    TLatex* tex2 = new TLatex(0.15, 0.85, "O+O@200 GeV (norm. to J/#psi)");
    tex2->SetNDC();
    tex2->SetTextSize(0.04);
    tex2->Draw();
    TPaveText* normBox2 = new TPaveText(0.55, 0.70, 0.88, 0.78, "NDC");
    normBox2->SetFillStyle(0);
    normBox2->SetBorderSize(0);
    normBox2->AddText(Form("Norm. factor = %.4g", normalized2.factor));
    normBox2->Draw();

    c1->SaveAs(Form("roots/Compare_dAu_OO/%d_compare_signals_normalized.png", number));

    // ---------- 画布2：比值 h1/h2 (归一化后) ----------
    TH1F* hRatio = (TH1F*)h1->Clone("hRatio");
    hRatio->Divide(h2);
    hRatio->SetTitle(";M_{ee} (GeV/c^{2});d+Au / O+O (norm. to J/#psi)");
    hRatio->SetLineColor(kBlack);
    hRatio->SetMarkerColor(kBlack);
    hRatio->SetMarkerStyle(20);

    // 在 J/psi 区间附近添加参考线 y=1
    TF1* f_ref = new TF1("f_ref", "1", Jpsi_low, Jpsi_high);
    f_ref->SetLineColor(kGreen+2);
    f_ref->SetLineStyle(2);

    TCanvas* c2 = new TCanvas("c2", "Ratio after J/psi Normalization", 800, 600);
    gPad->SetLogy(1);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    c2->SetGrid();
    hRatio->SetMaximum(4.0);
    hRatio->SetMinimum(1e-1);
    hRatio->Draw("PE");
    f_ref->Draw("same");

    TLatex* tex_ratio = new TLatex(0.15, 0.85, Form("Normalized in J/#psi [%.2f, %.2f]", Jpsi_low, Jpsi_high));
    tex_ratio->SetNDC();
    tex_ratio->SetTextSize(0.04);
    tex_ratio->Draw();

    c2->SaveAs(Form("roots/Compare_dAu_OO/%d_compare_ratio_normalized.png", number));
}