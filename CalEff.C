// CalEff.C
// 计算 EID cut 对电子的效率 vs 动量
// 输入: 8_20260902_dAu2021_TOF_keepSamewithzih_nsigmaEcutEffCal.root 中的 h_P_Cen__nSigmaE
// 步骤: 投影到 P-nSigmaE，对每个动量 bin 拟合 nSigmaE 高斯分布（均值限制[-1,1]），
//       计算在 cut 区间（默认 -2 ~ 2）内的高斯积分占总积分的比例即为效率。
// 运行: root -l -q 'CalEff.C("input.root", "h_P_Cen__nSigmaE", -2.0, 2.0)'
// 或直接运行默认: root -l CalEff.C

#include "../2021_OO200/someFunction.h"
void CalEff(const char* filename = "roots/8_20260902_dAu2021_TOF_keepSamewithzih_nsigmaEcutEffCal.root", Int_t number =8)
{
    if(0)
    {
    TFile* file = TFile::Open(filename);
    TH3F* h_P_Cen_nSigmaE = (TH3F*)file->Get("h_P_Cen_nSigmaE");

    vector<Double_t> P__newEdges = {0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.6,1.8,2.0,2.5,3.0,5.0};
	Int_t P_bins = P__newEdges.size() - 1;
    vector<Double_t> Cen__newEdges = {0,2,4,6,8,10,12,14,16};
	Int_t Cen_bins = Cen__newEdges.size() - 1;
    vector<Double_t> nsigmaE__newEdges = {-10.0, -9.9, -9.8, -9.7, -9.6, -9.5, -9.4, -9.3, -9.2, -9.1,-9.0, -8.9, -8.8, -8.7, -8.6, -8.5, -8.4, -8.3, -8.2, -8.1,-8.0, -7.9, -7.8, -7.7, -7.6, -7.5, -7.4, -7.3, -7.2, -7.1,-7.0, -6.9, -6.8, -6.7, -6.6, -6.5, -6.4, -6.3, -6.2, -6.1,-6.0, -5.9, -5.8, -5.7, -5.6, -5.5, -5.4, -5.3, -5.2, -5.1,-5.0, -4.9, -4.8, -4.7, -4.6, -4.5, -4.4, -4.3, -4.2, -4.1,-4.0, -3.9, -3.8, -3.7, -3.6, -3.5, -3.4, -3.3, -3.2, -3.1,-3.0, -2.9, -2.8, -2.7, -2.6, -2.5, -2.4, -2.3, -2.2, -2.1,-2.0, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1,-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1,0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9,2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9,3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9,4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9,5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9,6.0, 6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9,7.0, 7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8, 7.9,8.0, 8.1, 8.2, 8.3, 8.4, 8.5, 8.6, 8.7, 8.8, 8.9,9.0, 9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9, 10.0};
	Int_t nsigmaE_bins = nsigmaE__newEdges.size() - 1;

    TH3F* h_P_Cen_nSigmaE_Rebin = new TH3F("h_P_Cen_nSigmaE__Rebin", ";p;Cen;nSigmaE", P_bins, P__newEdges.data(), Cen_bins, Cen__newEdges.data(), nsigmaE_bins, nsigmaE__newEdges.data());
    RebinHist(h_P_Cen_nSigmaE, h_P_Cen_nSigmaE_Rebin);
    // 投影到 P vs nSigmaE (忽略中心度)
    TH2F* h2 = (TH2F*)h_P_Cen_nSigmaE_Rebin->Project3D("zx");
    h2->SetName("h_P_nSigmaEcorr");
    h2->SetTitle("P vs nSigmaEcorr");
    //h2->Draw("colz");
    //h2->SaveAs("roots/8_P_vs_nSigmaEcorr.root");
    // 获取动量轴信息
    TAxis* pAxis = h2->GetXaxis();
    Int_t nPBins = pAxis->GetNbins();
    std::vector<Double_t> pCenter, eff, effErr;

    // 循环每个动量 bin
    for (Int_t i = 1; i <= nPBins; ++i) {
        // 获取该 bin 的 nSigmaE 投影
        TH1D* hProj = h2->ProjectionY(Form("proj_%d", i), i, i);

        // 拟合高斯，限制均值在 [-1, 1]
        TF1* gaus = new TF1(Form("gaus_%d", i), "gaus", -5, 5);
        gaus->SetParameter(0, hProj->GetMaximum());
        gaus->SetParameter(1, 0.0);
        gaus->SetParameter(2, 1.0);
        gaus->SetParLimits(1, -1.0, 1.0);   // 均值限制
        gaus->SetParLimits(2, 0.2, 5.0);    // sigma 限制，避免发散

        // 拟合 (使用 Q 选项安静，LL 或 空)
        Int_t fitResult = hProj->Fit(gaus, "QN", "", -5, 5);
        if (fitResult != 0 || gaus->GetParameter(2) <= 0) {
            // 拟合失败，跳过
            delete hProj;
            delete gaus;
            continue;
        }

        // 获取拟合参数
        Double_t mean = gaus->GetParameter(1);
        Double_t sigma = gaus->GetParameter(2);

        // 计算在 cut 区间内的高斯积分（与全区间积分之比）
        // 高斯总积分 = 1 (归一化后)，但我们的直方图未归一化，所以用积分比。
        // 更严谨：计算 cut 内面积 / 总面积 (由参数决定)
        Double_t pVal = pAxis->GetBinCenter(i);
        Double_t totalArea = gaus->Integral(-10, 10); // 足够宽
        Double_t cutArea = (pVal < 1) ? gaus->Integral(2.3 * pVal - 3.55, 3) : gaus->Integral(-1.25, 3);
        Double_t efficiency = (totalArea > 0) ? cutArea / totalArea : 0;
        //cout<< "P = " << pVal << " GeV/c, Efficiency = " << efficiency << endl;
        pCenter.push_back(pVal);
        eff.push_back(efficiency);
        effErr.push_back(0); // 误差暂不计算

        //TCanvas* cProj = new TCanvas(Form("cProj_%d", i), Form("P = %.2f GeV/c", pVal), 800, 600);
        //hProj->Draw();
        //gaus->Draw("same");
        //cProj->SaveAs(Form("roots/%d_efficiency_fit_P_%d.png", number, i));
        // 清理
        delete hProj;
        delete gaus;
        //delete cProj;
        
    }
// 7. 创建 TGraph 并绘制
    TGraph* gr = new TGraph(pCenter.size(), &pCenter[0], &eff[0]);
    gr->SetTitle("Efficiency of EID cut;P (GeV/c);Efficiency");
    gr->SetMarkerStyle(20);
    gr->SetMarkerSize(1.2);
    gr->SetLineColor(kBlack);

    TCanvas* c = new TCanvas("cEff", "Efficiency", 800, 600);
    c->SetGrid();
    gr->Draw("AP");

    // 8. 分段拟合
    // 注意：拟合范围需在数据点范围内，且至少有一个点
    TF1* f1 = new TF1("f_pol1", "pol1", 1.0, 3.0);   // P >= 1
    TF1* f2 = new TF1("f_pol2", "pol2", 0.2, 1.0);   // 0.2 <= P <= 1.0

    // 拟合（使用 "RNQ" 选项：不绘图、不打印、安静）
    gr->Fit(f1, "RNQ", "", 1.0, 3.0);
    gr->Fit(f2, "RNQ", "", 0.2, 1.0);

    // 设置拟合曲线样式
    f1->SetLineColor(kRed);
    f1->SetLineWidth(2);
    f2->SetLineColor(kBlue);
    f2->SetLineWidth(2);

    // 将拟合曲线画在原有画布上
    f1->Draw("same");
    f2->Draw("same");


    c->SaveAs(Form("roots/%d_efficiency_vs_P.png", number));


    file->Close();
    }
    
}