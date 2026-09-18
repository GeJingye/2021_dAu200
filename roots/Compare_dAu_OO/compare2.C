// compare2.C
// 比较dAu与OO的raw signal，背景采用异号混合事件(Unlike-Sign Mixed-Event, UM)：
//     raw signal = US - scale*UM
//     其中scale由like-sign同/混事件在归一化区间 NR(默认 0.5<M<2.0, 0<pT<2) 的积分比给出(ComputeMixEventScale)
// 之后做"事件归一化"：除以 h_passEvtcut 第9个bin(0-80%通过全部cut的事例数)。
// 在同一张图(对数y)上画出两条 (US-UM)/N_evt，
// 对 1.2-1.8, 1.8-2.3, 2.3-2.8 (GeV/c^2) 三个子区间分别给出 dAu/OO 积分与 OO/dAu 比值(含误差)，
// 并给出总区间 1.2-2.8 的积分与比值(图内TPaveText + 控制台打印)。
// 运行(在 2021_dAu200 目录下执行)：
//   root -l -q 'roots/Compare_dAu_OO/compare2.C()'

#include "../../../2021_OO200/someFunction.h"
#include <vector>
#include <iostream>

// 定义与 compare.C 相同的 bin 边界
vector<Double_t> Mee__newEdges = {0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.16,0.20,0.30,0.35,0.40,0.50,0.60,0.64,0.68,0.72,0.76,0.82,0.86,0.96,1.0,1.02,1.04,1.06,1.1,1.2,1.6,2.0,2.3,2.8,3.0, 3.04,3.08,3.10,3.12,3.14,3.18,3.20,3.26,3.3,4.0};//size()=38
static Int_t Mee_bins = Mee__newEdges.size() - 1;

static std::vector<Double_t> Pt__newEdges = {0, 0.3, 1.0, 2.0, 3.0, 4.0, 5.0};
static Int_t Pt_bins = Pt__newEdges.size() - 1;

static std::vector<Double_t> Cen__newEdges = {0, 2, 4, 8, 16};
static Int_t Cen_bins = Cen__newEdges.size() - 1;

// ---- UM背景的归一化(NR)区间：用like-sign同事件/混合事件积分比求scale ----
static const Double_t NR_low_M  = 1;   // GeV/c^2
static const Double_t NR_up_M   = 2.3;
static const Double_t NR_low_pT = 0.3;   // GeV/c
static const Double_t NR_up_pT  = 5.0;   // dAu CalMee 用 0-2；OO 如需可改 0-5

// ---- 积分区间：分成3个子区间，总区间为其并集(用于TPaveText显示与控制台打印) ----
static const Int_t    nReg          = 3;
static const Double_t RegLow[nReg]  = { 1.2, 1.8, 2.3 };   // GeV/c^2
static const Double_t RegHigh[nReg] = { 1.8, 2.3, 2.8 };
static const Double_t Int_low       = RegLow[0];            // 总区间下界
static const Double_t Int_high      = RegHigh[nReg - 1];    // 总区间上界

// ---- h_passEvtcut 中代表最终(0-80%)事例数的bin ----
static const Int_t EvtBin = 9;

//----------------------------------------------------------------------
// 读取文件中的事件数：h_passEvtcut 第EvtBin个bin的内容
Double_t GetNEvt(TString filename, TString prefix = "")
{
    TFile* inFile = TFile::Open(filename);
    if (!inFile || inFile->IsZombie()) {
        std::cerr << "Error: cannot open " << filename << std::endl;
        return -1.0;
    }
    TH1F* h_evt = (TH1F*)inFile->Get(prefix + "h_cen");
    if (!h_evt) {
        std::cerr << "Error: cannot find h_cen in " << filename << std::endl;
        inFile->Close();
        return -1.0;
    }
    Double_t nEvt = h_evt->GetEntries() - h_evt->GetBinContent(1);
    std::cout << Form("N_evt (h_cen bin %d) = %f  in %s", EvtBin, nEvt, filename.Data()) << std::endl;
    inFile->Close();
    return nEvt;
}

//----------------------------------------------------------------------
// 对直方图在[low, high]区间做积分(按bin与区间的重叠比例加权)
Double_t IntegrateRange(TH1F* h, Double_t low, Double_t high, Double_t* errOut = nullptr)
{
    if (!h) return 0.0;
    Double_t sum = 0.0;
    Double_t sumErr2 = 0.0;
    Int_t nBins = h->GetNbinsX();
    for (Int_t i = 1; i <= nBins; ++i) {
        Double_t lo = h->GetXaxis()->GetBinLowEdge(i);
        Double_t hi = h->GetXaxis()->GetBinUpEdge(i);
        if (hi <= low || lo >= high) continue;   // 与区间无交叠
        Double_t overlap = TMath::Min(hi, high) - TMath::Max(lo, low);
        Double_t w = (hi > lo) ? overlap / (hi - lo) : 0.0;
        sum     += h->GetBinContent(i) * w;
        sumErr2 += h->GetBinError(i) * h->GetBinError(i) * w * w;
    }
    if (errOut) *errOut = TMath::Sqrt(sumErr2);
    return sum;
}

//----------------------------------------------------------------------
// 计算 OO/dAu 比值及其误差传递
// sigma_ratio = |ratio| * sqrt((errOO/IOO)^2 + (errdAu/IdAu)^2)
void RatioOOoverdAu(Double_t intOO, Double_t errOO, Double_t intdAu, Double_t errdAu,
                    Double_t& ratio, Double_t& errRatio)
{
    ratio = (intdAu != 0) ? (intOO / intdAu) : 0.0;
    errRatio = 0.0;
    if (intdAu != 0 && intOO != 0 && ratio != 0) {
        Double_t relOO  = errOO / intOO;    // 分子 OO
        Double_t reldAu = errdAu / intdAu;  // 分母 dAu
        errRatio = ratio * TMath::Sqrt(relOO * relOO + reldAu * reldAu);
    }
}

//----------------------------------------------------------------------
// 从指定文件中提取raw signal (1D Mee)：raw = US - scale*UM
TH1F* GetSignal(TString filename, TString prefix = "")
{
    TFile* inFile = TFile::Open(filename);
    if (!inFile || inFile->IsZombie()) {
        std::cerr << "Error: cannot open " << filename << std::endl;
        return nullptr;
    }

    // 读取原始三维直方图
    TH3F* h_US  = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__unlikeSame");
    TH3F* h_mm  = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__likemm");
    TH3F* h_pp  = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__likepp");
    TH3F* h_mmM = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__likemmMixed");
    TH3F* h_ppM = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__likeppMixed");
    TH3F* h_UM  = (TH3F*)inFile->Get(prefix + "h_Mee_Pt_Cen__unlikeMixed");

    if (!h_US || !h_mm || !h_pp || !h_mmM || !h_ppM || !h_UM) {
        std::cerr << "Error: missing histograms in " << filename << std::endl;
        inFile->Close();
        return nullptr;
    }

    // 创建重分bin后的三维直方图
    TH3F* h_US_R  = new TH3F("h_US_R",  "", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_mm_R  = new TH3F("h_mm_R",  "", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_pp_R  = new TH3F("h_pp_R",  "", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_mmM_R = new TH3F("h_mmM_R", "", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_ppM_R = new TH3F("h_ppM_R", "", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    TH3F* h_UM_R  = new TH3F("h_UM_R",  "", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());

    RebinHist(h_mm,  h_mm_R);
    RebinHist(h_pp,  h_pp_R);
    RebinHist(h_US,  h_US_R);
    RebinHist(h_mmM, h_mmM_R);
    RebinHist(h_ppM, h_ppM_R);
    RebinHist(h_UM,  h_UM_R);

    // ---- 用like-sign同事件/混合事件求UM的scale，把UM缩放到same-event水平 ----
    Float_t scale = ComputeMixEventScale(h_pp_R, h_mm_R, h_ppM_R, h_mmM_R, h_UM_R,
                                         NR_low_M, NR_up_M, NR_low_pT, NR_up_pT,
                                         Cen__newEdges.front(), Cen__newEdges.back());
    std::cout << Form("UM scale (%s) = %f", filename.Data(), scale) << std::endl;

    // ---- raw signal = US - scale*UM ----
    TH3F* h_signal = new TH3F("h_signal", "", Mee_bins, Mee__newEdges.data(),
                               Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
    h_UM_R->Scale(scale);
    h_signal->Add(h_US_R, h_UM_R, 1.0, -1.0);

    // 投影到Mee(积分所有pT和Cen)，"e"确保误差被正确计算
    TH1F* h_Mee = (TH1F*)h_signal->ProjectionX("h_Mee", 1, Pt_bins, 1, Cen_bins, "e");
    ResetBinContent(h_Mee);
    h_Mee->SetDirectory(nullptr);

    inFile->Close();
    return h_Mee;
}

//----------------------------------------------------------------------
// 主函数
void compare2(TString file1 = "roots/Compare_dAu_OO/13_20260912_dAu2021_TOF_onlyMB.root",
             TString file2 = "roots/Compare_dAu_OO/20260910_iTPC11_P24ia_SameWithZihanNoVPDcut.root", Int_t number = 13)
{
    // 1) 提取两个系统的raw signal (US-UM)
    TH1F* h1_raw = GetSignal(file1);   // dAu
    TH1F* h2_raw = GetSignal(file2);   // OO
    if (!h1_raw || !h2_raw) {
        std::cerr << "Failed to get signals. Exiting." << std::endl;
        return;
    }

    // 2) 事件数归一化：除以h_passEvtcut第EvtBin个bin(0-80%)的事例数
    Double_t nEvt1 = GetNEvt(file1);
    Double_t nEvt2 = GetNEvt(file2);
    if (nEvt1 <= 0 || nEvt2 <= 0) {
        std::cerr << "Error: invalid event numbers nEvt1=" << nEvt1
                  << ", nEvt2=" << nEvt2 << ". Exiting." << std::endl;
        return;
    }
    h1_raw->Scale(1.0 / nEvt1);
    h2_raw->Scale(1.0 / nEvt2);

    // 3) 分别计算3个子区间与总区间的积分和OO/dAu比值(含误差)；h1_raw=dAu, h2_raw=OO
    Double_t intDau[nReg], errDau[nReg];
    Double_t intOO[nReg],  errOO[nReg];
    Double_t ratioR[nReg], errRatioR[nReg];
    Double_t intDauTot = 0.0, errDauTot = 0.0;
    Double_t intOOTot  = 0.0, errOOTot  = 0.0;
    for (Int_t ir = 0; ir < nReg; ++ir) {
        intDau[ir] = IntegrateRange(h1_raw, RegLow[ir], RegHigh[ir], &errDau[ir]);
        intOO[ir]  = IntegrateRange(h2_raw, RegLow[ir], RegHigh[ir], &errOO[ir]);
        RatioOOoverdAu(intOO[ir], errOO[ir], intDau[ir], errDau[ir], ratioR[ir], errRatioR[ir]);
        intDauTot += intDau[ir];                       // 总区间积分 = 子区间积分之和
        errDauTot += errDau[ir] * errDau[ir];
        intOOTot  += intOO[ir];
        errOOTot  += errOO[ir] * errOO[ir];
    }
    errDauTot = TMath::Sqrt(errDauTot);
    errOOTot  = TMath::Sqrt(errOOTot);
    Double_t ratioTot = 0.0, errRatioTot = 0.0;
    RatioOOoverdAu(intOOTot, errOOTot, intDauTot, errDauTot, ratioTot, errRatioTot);

    // 4) 设置样式
    h1_raw->SetLineColor(kRed);
    h1_raw->SetMarkerColor(kRed);
    h1_raw->SetMarkerStyle(20);
    h1_raw->SetMarkerSize(1.0);
    h1_raw->SetTitle("Raw Signal per Event;M_{ee} (GeV/c^{2});dN/dMee/N_{evt} (GeV/c^{2})^{-1}");

    h2_raw->SetLineColor(kBlue);
    h2_raw->SetMarkerColor(kBlue);
    h2_raw->SetMarkerStyle(21);
    h2_raw->SetMarkerSize(1.0);

    // 5) 画在同一张图上(对数y)，自动设定y范围(取两谱中>0 bin的最大/最小正含量)
    Double_t yMax = 0.0, yMin = -1.0;
    TH1F* hs[2] = { h1_raw, h2_raw };
    for (Int_t j = 0; j < 2; ++j) {
        for (Int_t i = 1; i <= hs[j]->GetNbinsX(); ++i) {
            Double_t c = hs[j]->GetBinContent(i);
            Double_t e = hs[j]->GetBinError(i);
            if (c + e > yMax) yMax = c + e;
            if (c - e > 0 && (yMin < 0 || c - e < yMin)) yMin = c - e;
        }
    }
    if (yMax <= 0) yMax = 1.0;
    if (yMin <= 0) yMin = yMax * 1e-4;
    h1_raw->SetMaximum(yMax * 3.0);
    h1_raw->SetMinimum(yMin * 0.5);
    h2_raw->SetMaximum(yMax * 3.0);
    h2_raw->SetMinimum(yMin * 0.5);

    TCanvas* c = new TCanvas("c", "Raw signal per event (US-UM)", 900, 650);
    gPad->SetLogy(1);
    gPad->SetLeftMargin(0.13);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    h1_raw->Draw("PE");
    h2_raw->Draw("PE same");

    TLegend* leg = new TLegend(0.13, 0.72, 0.45, 0.90);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.035);
    leg->AddEntry(h1_raw, "d+Au@200 (US-UM)/N_{evt}", "lp");
    leg->AddEntry(h2_raw, "O+O@200 (US-UM)/N_{evt}", "lp");
    leg->Draw();

    // 6) TPaveText：3个子区间与总区间的积分(dAu/OO)及OO/dAu比值
    TPaveText* pt = new TPaveText(0.50, 0.40, 0.94, 0.92, "NDC NB");
    pt->SetFillColorAlpha(0, 0);
    pt->SetFillStyle(0);
    pt->SetLineColor(0);
    pt->SetBorderSize(0);
    pt->SetTextFont(42);
    pt->SetTextSize(0.023);
    pt->SetTextAlign(12);
    for (Int_t ir = 0; ir < nReg; ++ir) {
        pt->AddText(Form("[%.1f,%.1f] dAu=%.2e OO=%.2e", RegLow[ir], RegHigh[ir], intDau[ir], intOO[ir]));
        pt->AddText(Form("           OO/dAu=%.3f+/-%.3f", ratioR[ir], errRatioR[ir]));
    }
    pt->AddText(Form("[%.1f,%.1f] dAu=%.2e OO=%.2e", Int_low, Int_high, intDauTot, intOOTot));
    pt->AddText(Form("           OO/dAu=%.3f+/-%.3f", ratioTot, errRatioTot));
    pt->Draw();

    c->SaveAs(Form("roots/Compare_dAu_OO/%d_compare_rawsignal_Nevt.png", number));

    // 7) 控制台打印3个子区间与总区间的积分及OO/dAu比值
    std::cout << "\n--- Event-normalized raw signal (US-UM) integrals ---" << std::endl;
    for (Int_t ir = 0; ir < nReg; ++ir) {
        std::cout << Form("[%.1f, %.1f] GeV/c^2 : dAu = %.6e +/- %.3e | OO = %.6e +/- %.3e | OO/dAu = %.4f +/- %.4f",
                          RegLow[ir], RegHigh[ir],
                          intDau[ir], errDau[ir], intOO[ir], errOO[ir],
                          ratioR[ir], errRatioR[ir]) << std::endl;
    }
    std::cout << Form("[%.1f, %.1f] GeV/c^2 (total): dAu = %.6e +/- %.3e | OO = %.6e +/- %.3e | OO/dAu = %.4f +/- %.4f",
                      Int_low, Int_high,
                      intDauTot, errDauTot, intOOTot, errOOTot,
                      ratioTot, errRatioTot) << std::endl;
}
