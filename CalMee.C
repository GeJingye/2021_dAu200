//---------------------从dAu200GeV_2016.root中提取直方图，并进行设置更改和元素添加----------------------
// Mee用MeV表示，范围0-500
#include "../2021_OO200/someFunction.h"
void CalMee(TString inFileName = "roots/1_20260816_dAu200_2016_DP.root", Int_t number = 1)//
{
	// 定义新的bin边界
	//vector<Double_t> Mee__newEdges = {0,10,15,15.1,15.2,15.3,15.4,15.5,15.6,15.7,15.8,15.9,16,16.1,16.2,16.3,16.4,16.5,16.55,16.6,16.65,16.7,16.75,16.8,16.85,16.9,16.95,17,17.05,17.1,17.15,17.2,17.25,17.3,17.35,17.4,17.45,17.5,17.6,17.7,17.8,17.9,18,18.1,18.2,18.3,18.4,18.5,19,19.5,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,300,500};//size()=
	vector<Double_t> Mee__newEdges = {0,10,15,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500};//size()=

	Int_t Mee_bins = Mee__newEdges.size() - 1;

	vector<Double_t> Pt__newEdges = {0,1.0,2.0,3.0,4.0,5.0};
	Int_t Pt_bins = Pt__newEdges.size() - 1;
	//                                 80   75   70   65   60   55   50   45   40   35   30    25    20    15    10    5     0   
	//vector<Double_t> Cen__newEdges = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
	vector<Double_t> Cen__newEdges = {0,16};
	Int_t Cen_bins = Cen__newEdges.size() - 1;
	// 从root文件中导入待拟合的直方图
	TFile *inFile = new TFile(inFileName);
	if (!inFile){cout << "The input file is not found! Exiting..." << endl; return;}
	// 导入直方图
	TH3F* h_Mee_Pt_Cen__unlikeSame  = (TH3F*)inFile->Get("h_Mee_Pt_Cen__unlikeSame");
	cout<<h_Mee_Pt_Cen__unlikeSame->GetYaxis()->GetBinWidth(1)<<endl;
	TH3F* h_Mee_Pt_Cen__likemm 	    = (TH3F*)inFile->Get("h_Mee_Pt_Cen__likemm");
	TH3F* h_Mee_Pt_Cen__likepp 	    = (TH3F*)inFile->Get("h_Mee_Pt_Cen__likepp");
	TH3F* h_Mee_Pt_Cen__likemmMixed = (TH3F*)inFile->Get("h_Mee_Pt_Cen__likemmMixed");
	TH3F* h_Mee_Pt_Cen__likeppMixed = (TH3F*)inFile->Get("h_Mee_Pt_Cen__likeppMixed");
	TH3F* h_Mee_Pt_Cen__unlikeMixed = (TH3F*)inFile->Get("h_Mee_Pt_Cen__unlikeMixed");

	// 创建直方图
	TH3F* h_Mee_Pt_Cen__likemm_Rebin	  = new TH3F("h_Mee_Pt_Cen__likemm_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__likepp_Rebin	  = new TH3F("h_Mee_Pt_Cen__likepp_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__unlikeSame_Rebin  = new TH3F("h_Mee_Pt_Cen__unlikeSame_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__likemmMixed_Rebin = new TH3F("h_Mee_Pt_Cen__likemmMixed_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__likeppMixed_Rebin = new TH3F("h_Mee_Pt_Cen__likeppMixed_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__unlikeMixed_Rebin = new TH3F("h_Mee_Pt_Cen__unlikeMixed_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());

	TH3F* h_Mee_Pt_Cen__temp_Rebin = new TH3F("h_Mee_Pt_Cen__temp_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__temp2_Rebin = new TH3F("h_Mee_Pt_Cen__temp2_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__LikeMixed_Rebin = new TH3F("h_Mee_Pt_Cen__LikeMixed_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__LikeSame_Rebin = new TH3F("h_Mee_Pt_Cen__LikeSame_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__CorrLS_Rebin = new TH3F("h_Mee_Pt_Cen__CorrLS_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__rmLS_Rebin = new TH3F("h_Mee_Pt_Cen__rmLS_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__rmLS_PSACcorr_Rebin = new TH3F("h_Mee_Pt_Cen__rmLS_PSACcorr_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());
	TH3F* h_Mee_Pt_Cen__rmUM_Rebin = new TH3F("h_Mee_Pt_Cen__rmUM_Rebin", ";M_{ee};p_{T};Cen", Mee_bins, Mee__newEdges.data(), Pt_bins, Pt__newEdges.data(), Cen_bins, Cen__newEdges.data());

	TH1F* h_Mee__temp_Rebin = new TH1F("h_Mee__temp_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	TH1F* h_Mee__temp2_Rebin = new TH1F("h_Mee__temp2_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	TH1F* h_Mee__LikeMixed_Rebin = new TH1F("h_Mee__LikeMixed_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	TH1F* h_Mee__LikeSame_Rebin = new TH1F("h_Mee__LikeSame_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	TH1F* h_Mee__LikeSame_PSACcorr_Rebin = new TH1F("h_Mee__LikeSame_PSACcorr_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	TH1F* h_Mee__rmLS_Rebin = new TH1F("h_Mee__rmLS_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	TH1F* h_Mee__rmLS_PSACcorr_Rebin = new TH1F("h_Mee__rmLS_PSACcorr_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	TH1F* h_Mee__rmUM_Rebin = new TH1F("h_Mee__rmUM_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	TH1F* h_Mee__CorrLS_Rebin = new TH1F("h_Mee__CorrLS_Rebin", ";M_{ee}", Mee_bins, Mee__newEdges.data());
	// Rebin
	RebinHist(h_Mee_Pt_Cen__likemm, h_Mee_Pt_Cen__likemm_Rebin);			//ResetBinContent(h_Mee_Pt_Cen__likemm_Rebin);
	RebinHist(h_Mee_Pt_Cen__likepp, h_Mee_Pt_Cen__likepp_Rebin);			//ResetBinContent(h_Mee_Pt_Cen__likepp_Rebin);
	RebinHist(h_Mee_Pt_Cen__unlikeSame, h_Mee_Pt_Cen__unlikeSame_Rebin);	//ResetBinContent(h_Mee_Pt_Cen__unlikeSame_Rebin);
	RebinHist(h_Mee_Pt_Cen__likemmMixed, h_Mee_Pt_Cen__likemmMixed_Rebin);  //ResetBinContent(h_Mee_Pt_Cen__likemmMixed_Rebin);
	RebinHist(h_Mee_Pt_Cen__likeppMixed, h_Mee_Pt_Cen__likeppMixed_Rebin);  //ResetBinContent(h_Mee_Pt_Cen__likeppMixed_Rebin);
	RebinHist(h_Mee_Pt_Cen__unlikeMixed, h_Mee_Pt_Cen__unlikeMixed_Rebin);  //ResetBinContent(h_Mee_Pt_Cen__unlikeMixed_Rebin);

	Float_t low_pt = 0.0, up_pt = 5.0, low_Cen = 0.0, up_Cen = 16.0;//model sum/11/12/13/14/22/23/24/33/34/44
	Int_t bin__low_pt = h_Mee_Pt_Cen__likepp_Rebin->GetYaxis()->FindBin(low_pt + 1e-3);
	Int_t bin__up_pt = h_Mee_Pt_Cen__likepp_Rebin->GetYaxis()->FindBin(up_pt - 1e-3);
	Int_t bin__low_Cen = h_Mee_Pt_Cen__likepp_Rebin->GetZaxis()->FindBin(low_Cen + 1e-3);
	Int_t bin__up_Cen = h_Mee_Pt_Cen__likepp_Rebin->GetZaxis()->FindBin(up_Cen - 1e-3);
	cout << bin__low_pt<<" "<<bin__up_pt<<" "<<bin__low_Cen<<" "<<bin__up_Cen<<endl;
	TH1F *h_Mee__likemm_Rebin	  = (TH1F*)h_Mee_Pt_Cen__likemm_Rebin->ProjectionX("h_Mee__likemm_Rebin", bin__low_pt, bin__up_pt, bin__low_Cen, bin__up_Cen);
	TH1F *h_Mee__likepp_Rebin	  = (TH1F*)h_Mee_Pt_Cen__likepp_Rebin->ProjectionX("h_Mee__likepp_Rebin", bin__low_pt, bin__up_pt, bin__low_Cen, bin__up_Cen);
	TH1F *h_Mee__unlikeSame_Rebin = (TH1F*)h_Mee_Pt_Cen__unlikeSame_Rebin->ProjectionX("h_Mee__unlikeSame_Rebin", bin__low_pt, bin__up_pt, bin__low_Cen, bin__up_Cen);
	TH1F *h_Mee__likemmMixed_Rebin = (TH1F*)h_Mee_Pt_Cen__likemmMixed_Rebin->ProjectionX("h_Mee__likemmMixed_Rebin", bin__low_pt, bin__up_pt, bin__low_Cen, bin__up_Cen);
	TH1F *h_Mee__likeppMixed_Rebin = (TH1F*)h_Mee_Pt_Cen__likeppMixed_Rebin->ProjectionX("h_Mee__likeppMixed_Rebin", bin__low_pt, bin__up_pt, bin__low_Cen, bin__up_Cen);
	TH1F *h_Mee__unlikeMixed_Rebin = (TH1F*)h_Mee_Pt_Cen__unlikeMixed_Rebin->ProjectionX("h_Mee__unlikeMixed_Rebin", bin__low_pt, bin__up_pt, bin__low_Cen, bin__up_Cen);

	// 3-D Like-SameEvent背景
	h_Mee_Pt_Cen__temp_Rebin->Multiply(h_Mee_Pt_Cen__likemm_Rebin, h_Mee_Pt_Cen__likepp_Rebin, 1.0, 1.0);//GA
	h_Mee_Pt_Cen__LikeSame_Rebin = SqrtHist(h_Mee_Pt_Cen__temp_Rebin, "h_Mee_Pt_Cen__LikeSame_Rebin");
	h_Mee_Pt_Cen__LikeSame_Rebin->Scale(2.0);
	h_Mee_Pt_Cen__LikeSame_Rebin->Add(h_Mee_Pt_Cen__likemm_Rebin, h_Mee_Pt_Cen__likepp_Rebin, 1.0, 1.0);//AA
		// 使用LM计算LS背景修正因子
	h_Mee_Pt_Cen__temp2_Rebin->Multiply(h_Mee_Pt_Cen__likemmMixed_Rebin, h_Mee_Pt_Cen__likeppMixed_Rebin, 1.0, 1.0);//GAcorr
	h_Mee_Pt_Cen__LikeMixed_Rebin = SqrtHist(h_Mee_Pt_Cen__temp2_Rebin,"h_Mee_Pt_Cen__LikeMixed_Rebin");
	h_Mee_Pt_Cen__LikeMixed_Rebin->Scale(2.0);
	h_Mee_Pt_Cen__CorrLS_Rebin->Divide(h_Mee_Pt_Cen__unlikeMixed_Rebin, h_Mee_Pt_Cen__LikeMixed_Rebin, 1.0, 1.0);
	h_Mee_Pt_Cen__LikeSame_Rebin->Multiply(h_Mee_Pt_Cen__CorrLS_Rebin);
	// 1-D Like-SameEvent背景
	h_Mee__temp_Rebin->Multiply(h_Mee__likemm_Rebin, h_Mee__likepp_Rebin, 1.0, 1.0);
	h_Mee__LikeSame_Rebin = SqrtHist(h_Mee__temp_Rebin, "h_Mee__LikeSame_Rebin");
	h_Mee__LikeSame_Rebin->Scale(2.0);
		// 使用LM计算LS背景修正因子
	h_Mee__temp2_Rebin->Multiply(h_Mee__likemmMixed_Rebin, h_Mee__likeppMixed_Rebin, 1.0, 1.0);//GAcorr
	h_Mee__LikeMixed_Rebin = SqrtHist(h_Mee__temp2_Rebin, "h_Mee__LikeMixed_Rebin");
	h_Mee__LikeMixed_Rebin->Scale(2.0);
	h_Mee__CorrLS_Rebin->Divide(h_Mee__unlikeMixed_Rebin, h_Mee__LikeMixed_Rebin, 1.0, 1.0);
	h_Mee__LikeSame_PSACcorr_Rebin = (TH1F*)h_Mee__LikeSame_Rebin->Clone("h_Mee__LikeSame_PSACcorr_Rebin");
	h_Mee__LikeSame_PSACcorr_Rebin->Multiply(h_Mee__CorrLS_Rebin);

	// 3-D Unlike-MixedEvent背景
	Float_t NR_low_M = 200, NR_up_M = 500, NR_low_pt = 0., NR_up_pt = 5.;
	Float_t scale = ComputeMixEventScale(h_Mee_Pt_Cen__likepp_Rebin, h_Mee_Pt_Cen__likemm_Rebin,h_Mee_Pt_Cen__likeppMixed_Rebin, h_Mee_Pt_Cen__likemmMixed_Rebin,h_Mee_Pt_Cen__unlikeMixed_Rebin, NR_low_M, NR_up_M, NR_low_pt, NR_up_pt, 1, 16);
	cout << "scale: " << scale << endl;
	// 3-D Unlike-MixedEvent背景
	h_Mee_Pt_Cen__unlikeMixed_Rebin->Scale(scale);
	// 1-D Unlike-MixedEvent背景
	h_Mee__unlikeMixed_Rebin->Scale(scale);

	// 去除背景，还原信号
	h_Mee_Pt_Cen__rmLS_Rebin->Add(h_Mee_Pt_Cen__unlikeSame_Rebin, h_Mee_Pt_Cen__LikeSame_Rebin, 1.0, -1.0);
	h_Mee_Pt_Cen__rmUM_Rebin->Add(h_Mee_Pt_Cen__unlikeSame_Rebin, h_Mee_Pt_Cen__unlikeMixed_Rebin, 1.0, -1.0);
	h_Mee__rmLS_Rebin->Add(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_Rebin, 1.0, -1.0);
	h_Mee__rmLS_PSACcorr_Rebin->Add(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, 1.0, -1.0);
	h_Mee__rmUM_Rebin->Add(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin, 1.0, -1.0);

	//计算dN/dM
	ResetBinContent(h_Mee__rmLS_Rebin);
	ResetBinContent(h_Mee__rmLS_PSACcorr_Rebin);
	ResetBinContent(h_Mee__rmUM_Rebin);
	ResetBinContent(h_Mee__unlikeSame_Rebin);
	ResetBinContent(h_Mee__LikeSame_Rebin);
	ResetBinContent(h_Mee__LikeSame_PSACcorr_Rebin);
	ResetBinContent(h_Mee__unlikeMixed_Rebin);

	// 计算不同背景下的信号显著性
	TH1F* h_Mee__Signif_LS = (TH1F*)CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, "h_Mee__Signif_LS");
	TH1F* h_Mee__Signif_UM = (TH1F*)CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin, "h_Mee__Signif_UM");
	Float_t x_low_LS = 30, x_up_LS = 80;
	auto[signif_LS, signif_err2_LS, N_LS, N_err2_LS, B_LS, B_err2_LS] = CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, x_low_LS, x_up_LS);
	Float_t x_low_LS2 = 15, x_up_LS2 = 80;
	auto[signif_LS2, signif_err2_LS2, N_LS2, N_err2_LS2, B_LS2, B_err2_LS2] = CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, x_low_LS2, x_up_LS2);
	
	Float_t x_low_UM = 30, x_up_UM = 80;
	auto[signif_UM, signif_err2_UM, N_UM, N_err2_UM, B_UM, B_err2_UM] = CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin, x_low_UM, x_up_UM);

	//计算各种比例
	TH1F *h_Mee__BKGRatio_Rebin = new TH1F(*h_Mee__LikeSame_PSACcorr_Rebin);
	*h_Mee__BKGRatio_Rebin = *h_Mee__LikeSame_PSACcorr_Rebin / *h_Mee__unlikeMixed_Rebin;//背景比

	TH1F *h_Mee__SBR_LS_Rebin = new TH1F(*h_Mee__rmLS_PSACcorr_Rebin);
	*h_Mee__SBR_LS_Rebin = *h_Mee__rmLS_PSACcorr_Rebin / *h_Mee__LikeSame_PSACcorr_Rebin;//LS信背比

	TH1F *h_Mee__SBR_UM_Rebin = new TH1F(*h_Mee__rmUM_Rebin);
	*h_Mee__SBR_UM_Rebin = *h_Mee__rmUM_Rebin / *h_Mee__unlikeMixed_Rebin;//UM信背比

	/**************************************画图***********************************/
	// 对3D直方图降维
	TH2F *h_Mee_Pt__rmLS_Rebin = (TH2F*)h_Mee_Pt_Cen__rmLS_Rebin->Project3D("yx");	ResetBinContent(h_Mee_Pt__rmLS_Rebin);
	TH2F *h_Mee_Pt__rmUM_Rebin = (TH2F*)h_Mee_Pt_Cen__rmUM_Rebin->Project3D("yx"); ResetBinContent(h_Mee_Pt__rmUM_Rebin);

	TH2F *h_Mee_Pt__likemm = (TH2F*)h_Mee_Pt_Cen__likemm->Project3D("yx");
	TH2F *h_Mee_Pt__likepp = (TH2F*)h_Mee_Pt_Cen__likepp->Project3D("yx");
	TH2F *h_Mee_Pt__unlikeSame = (TH2F*)h_Mee_Pt_Cen__unlikeSame->Project3D("yx");
	TH2F *h_Mee_Pt__likemm_Rebin = (TH2F*)h_Mee_Pt_Cen__likemm_Rebin->Project3D("yx");
	TH2F *h_Mee_Pt__likepp_Rebin = (TH2F*)h_Mee_Pt_Cen__likepp_Rebin->Project3D("yx");
	TH2F *h_Mee_Pt__LikeSame_Rebin = (TH2F*)h_Mee_Pt_Cen__LikeSame_Rebin->Project3D("yx");
	TH2F *h_Mee_Pt__unlikeSame_Rebin = (TH2F*)h_Mee_Pt_Cen__unlikeSame_Rebin->Project3D("yx");

	TH2F *h_Mee_Pt__likemmMixed = (TH2F*)h_Mee_Pt_Cen__likemmMixed->Project3D("yx");
	TH2F *h_Mee_Pt__likeppMixed = (TH2F*)h_Mee_Pt_Cen__likeppMixed->Project3D("yx");
	TH2F *h_Mee_Pt__unlikeMixed = (TH2F*)h_Mee_Pt_Cen__unlikeMixed->Project3D("yx");
	TH2F *h_Mee_Pt__likemmMixed_Rebin = (TH2F*)h_Mee_Pt_Cen__likemmMixed_Rebin->Project3D("yx");
	TH2F *h_Mee_Pt__likeppMixed_Rebin = (TH2F*)h_Mee_Pt_Cen__likeppMixed_Rebin->Project3D("yx");
	TH2F *h_Mee_Pt__unlikeMixed_Rebin = (TH2F*)h_Mee_Pt_Cen__unlikeMixed_Rebin->Project3D("yx");
	TH2F *h_Mee_Pt__LikeMixed_Rebin = (TH2F*)h_Mee_Pt_Cen__LikeMixed_Rebin->Project3D("yx");
	if (0)// 寻找normalized region
	{
		const int nPt = 5;
		TH1F* h_Mee__likemm_Rebin[nPt] = { nullptr };
		TH1F* h_Mee__likepp_Rebin[nPt] = { nullptr };
		TH1F* h_Mee__likemmMixed_Rebin[nPt] = { nullptr };
		TH1F* h_Mee__likeppMixed_Rebin[nPt] = { nullptr };

		for (int iPt = 0; iPt < nPt; iPt++) {
			// 投影 mm 和 pp（same-event）
			h_Mee_Pt_Cen__likemm_Rebin->GetYaxis()->SetRange(iPt + 1, iPt + 1);
			h_Mee__likemm_Rebin[iPt] = (TH1F*)h_Mee_Pt_Cen__likemm_Rebin->Project3D("x")->Clone(TString::Format("h_Mee__likemm_Rebin_pt%d", iPt));
			h_Mee__likemm_Rebin[iPt]->SetDirectory(nullptr);

			h_Mee_Pt_Cen__likepp_Rebin->GetYaxis()->SetRange(iPt + 1, iPt + 1);
			h_Mee__likepp_Rebin[iPt] = (TH1F*)h_Mee_Pt_Cen__likepp_Rebin->Project3D("x")->Clone(TString::Format("h_Mee__likepp_Rebin_pt%d", iPt));
			h_Mee__likepp_Rebin[iPt]->SetDirectory(nullptr);

			// 投影 mmMixed 和 ppMixed（Mixed-event）
			h_Mee_Pt_Cen__likemmMixed_Rebin->GetYaxis()->SetRange(iPt + 1, iPt + 1);
			h_Mee__likemmMixed_Rebin[iPt] = (TH1F*)h_Mee_Pt_Cen__likemmMixed_Rebin->Project3D("x")->Clone(TString::Format("h_Mee__likemmMixed_Rebin_pt%d", iPt));
			h_Mee__likemmMixed_Rebin[iPt]->SetDirectory(nullptr);

			h_Mee_Pt_Cen__likeppMixed_Rebin->GetYaxis()->SetRange(iPt + 1, iPt + 1);
			h_Mee__likeppMixed_Rebin[iPt] = (TH1F*)h_Mee_Pt_Cen__likeppMixed_Rebin->Project3D("x")->Clone(TString::Format("h_Mee__likeppMixed_Rebin_pt%d", iPt));
			h_Mee__likeppMixed_Rebin[iPt]->SetDirectory(nullptr);
		}

		// 恢复轴的 range（可选）
		h_Mee_Pt_Cen__likemm_Rebin->GetYaxis()->SetRange(1, -1);
		h_Mee_Pt_Cen__likepp_Rebin->GetYaxis()->SetRange(1, -1);
		h_Mee_Pt_Cen__likemmMixed_Rebin->GetYaxis()->SetRange(1, -1);
		h_Mee_Pt_Cen__likeppMixed_Rebin->GetYaxis()->SetRange(1, -1);

		TH1F* h_Mee__SamePMix_mm_Rebin[nPt] = { nullptr };
		TH1F* h_Mee__SamePMix_pp_Rebin[nPt] = { nullptr };

		for (int iPt = 0; iPt < nPt; ++iPt) {
			h_Mee__SamePMix_mm_Rebin[iPt] = (TH1F*)h_Mee__likemm_Rebin[iPt]->Clone(TString::Format("h_Mee__SamePMix_mm_Rebin_pt%d", iPt));
			h_Mee__SamePMix_mm_Rebin[iPt]->Divide(h_Mee__likemm_Rebin[iPt], h_Mee__likemmMixed_Rebin[iPt], 1.0, 1.0, "B");
			h_Mee__SamePMix_mm_Rebin[iPt]->SetDirectory(nullptr);
			h_Mee__SamePMix_mm_Rebin[iPt]->SetTitle(TString::Format("SamePMix mm, pT [%.1f,%.1f]", Pt__newEdges[iPt], Pt__newEdges[iPt + 1]));
			h_Mee__SamePMix_mm_Rebin[iPt]->GetXaxis()->SetTitle("M_{ee} (MeV/c^{2})");
			h_Mee__SamePMix_mm_Rebin[iPt]->GetYaxis()->SetTitle("Same/PMix");

			h_Mee__SamePMix_pp_Rebin[iPt] = (TH1F*)h_Mee__likepp_Rebin[iPt]->Clone(TString::Format("h_Mee__SamePMix_pp_Rebin_pt%d", iPt));
			h_Mee__SamePMix_pp_Rebin[iPt]->Divide(h_Mee__likepp_Rebin[iPt], h_Mee__likeppMixed_Rebin[iPt], 1.0, 1.0, "B");
			h_Mee__SamePMix_pp_Rebin[iPt]->SetDirectory(nullptr);
			h_Mee__SamePMix_pp_Rebin[iPt]->SetTitle(TString::Format("SamePMix pp, pT [%.1f,%.1f]", Pt__newEdges[iPt], Pt__newEdges[iPt + 1]));
			h_Mee__SamePMix_pp_Rebin[iPt]->GetXaxis()->SetTitle("M_{ee} (MeV/c^{2})");
			h_Mee__SamePMix_pp_Rebin[iPt]->GetYaxis()->SetTitle("Same/PMix");
		}

		TCanvas* c = new TCanvas("c", "Same/PMix per pT bin", 1200, 800);
		c->Divide(3, 2);
		// 设置全局图形样式（可选）
		gStyle->SetOptStat(0);
		gStyle->SetOptTitle(0);

		// 循环 pt bins
		for (int iPt = 0; iPt < nPt; ++iPt) {
			if (!h_Mee__SamePMix_mm_Rebin[iPt] || !h_Mee__SamePMix_pp_Rebin[iPt]) {
				printf("Warning: missing histogram for pT bin %d\n", iPt);
				continue;
			}

			c->cd(iPt + 1);
			TPad* pad = (TPad*)gPad;
			pad->SetGrid();  // 显示网格，便于观察比值

			// 绘制 mm（红色）
			h_Mee__SamePMix_mm_Rebin[iPt]->SetLineColor(kRed);
			h_Mee__SamePMix_mm_Rebin[iPt]->SetMarkerColor(kRed);
			h_Mee__SamePMix_mm_Rebin[iPt]->SetMarkerStyle(20);
			h_Mee__SamePMix_mm_Rebin[iPt]->SetMarkerSize(0.8);
			//h_Mee__SamePMix_mm_Rebin[iPt]->SetMaximum(0.012);
			//h_Mee__SamePMix_mm_Rebin[iPt]->SetMinimum(0.009);
			h_Mee__SamePMix_mm_Rebin[iPt]->Draw("E1");

			// 绘制 pp（蓝色）
			h_Mee__SamePMix_pp_Rebin[iPt]->SetLineColor(kBlue);
			h_Mee__SamePMix_pp_Rebin[iPt]->SetMarkerColor(kBlue);
			h_Mee__SamePMix_pp_Rebin[iPt]->SetMarkerStyle(21);
			h_Mee__SamePMix_pp_Rebin[iPt]->SetMarkerSize(0.8);
			h_Mee__SamePMix_pp_Rebin[iPt]->Draw("E1 SAME");

			// 添加 pt 信息文本
			TLatex tex;
			tex.SetNDC();
			tex.SetTextSize(0.06);
			tex.DrawLatex(0.2, 0.85, TString::Format("p_{T} = [%.1f, %.1f] GeV/c", Pt__newEdges[iPt], Pt__newEdges[iPt + 1]));

			// 添加图例
			TLegend* leg = new TLegend(0.2, 0.65, 0.48, 0.78);
			leg->SetBorderSize(0);
			leg->SetTextSize(0.05);
			leg->AddEntry(h_Mee__SamePMix_mm_Rebin[iPt], "R_{--} (like-sign)", "lp");
			leg->AddEntry(h_Mee__SamePMix_pp_Rebin[iPt], "R_{++} (like-sign)", "lp");
			leg->Draw();
		}
		c->SaveAs(Form("roots/%d_SamePMix_per_pt.png", number));
	}
	if (1)// Mee pT 2D-QA
	{
		TH2F *h_Mee_Pt__likemm = (TH2F*)h_Mee_Pt_Cen__likemm->Project3D("yx");
		TH2F *h_Mee_Pt__likepp = (TH2F*)h_Mee_Pt_Cen__likepp->Project3D("yx");
		TH2F *h_Mee_Pt__unlikeSame = (TH2F*)h_Mee_Pt_Cen__unlikeSame->Project3D("yx");
		TH2F *h_Mee_Pt__likemm_Rebin = (TH2F*)h_Mee_Pt_Cen__likemm_Rebin->Project3D("yx");
		TH2F *h_Mee_Pt__likepp_Rebin = (TH2F*)h_Mee_Pt_Cen__likepp_Rebin->Project3D("yx");
		TH2F *h_Mee_Pt__LikeSame_Rebin = (TH2F*)h_Mee_Pt_Cen__LikeSame_Rebin->Project3D("yx");
		TH2F *h_Mee_Pt__unlikeSame_Rebin = (TH2F*)h_Mee_Pt_Cen__unlikeSame_Rebin->Project3D("yx");

		TH2F *h_Mee_Pt__likemmMixed = (TH2F*)h_Mee_Pt_Cen__likemmMixed->Project3D("yx");
		TH2F *h_Mee_Pt__likeppMixed = (TH2F*)h_Mee_Pt_Cen__likeppMixed->Project3D("yx");
		TH2F *h_Mee_Pt__unlikeMixed = (TH2F*)h_Mee_Pt_Cen__unlikeMixed->Project3D("yx");
		TH2F *h_Mee_Pt__likemmMixed_Rebin = (TH2F*)h_Mee_Pt_Cen__likemmMixed_Rebin->Project3D("yx");
		TH2F *h_Mee_Pt__likeppMixed_Rebin = (TH2F*)h_Mee_Pt_Cen__likeppMixed_Rebin->Project3D("yx");
		TH2F *h_Mee_Pt__unlikeMixed_Rebin = (TH2F*)h_Mee_Pt_Cen__unlikeMixed_Rebin->Project3D("yx");

		TH2F *h_Mee_Pt__temp2_Rebin = (TH2F*)h_Mee_Pt_Cen__temp2_Rebin->Project3D("yx");
		TH2F *h_Mee_Pt__temp3_Rebin = (TH2F*)h_Mee_Pt_Cen__LikeMixed_Rebin->Project3D("yx");
		//画图
		TCanvas *c1 = new TCanvas("c1", "c1", 900, 900);
		c1->Divide(4, 4);
		c1->cd(1);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likemm->SetTitle("LmmS;");
		h_Mee_Pt__likemm->DrawClone("col z");

		c1->cd(2);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likepp->SetTitle("LppS;");
		h_Mee_Pt__likepp->DrawClone("col z");

		c1->cd(3);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__unlikeSame->SetTitle("US;");
		h_Mee_Pt__unlikeSame->DrawClone("col z");

		c1->cd(4);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		//h_Mee_Pt__rmLS_Rebin->SetMaximum(1e6);
		//h_Mee_Pt__rmLS_Rebin->SetMinimum(1e-4);
		h_Mee_Pt__rmLS_Rebin->SetTitle("US-LS(Rebin);");
		h_Mee_Pt__rmLS_Rebin->DrawClone("col z");

		c1->cd(5);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likemmMixed->SetTitle("LmmM(Rebin);");
		h_Mee_Pt__likemmMixed->DrawClone("col z");

		c1->cd(6);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likeppMixed->SetTitle("LppM(Rebin);");
		h_Mee_Pt__likeppMixed->DrawClone("col z");

		c1->cd(7);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__unlikeMixed->SetTitle("UM;");
		h_Mee_Pt__unlikeMixed->DrawClone("col z");

		c1->cd(8);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		//h_Mee_Pt__rmUM_Rebin->SetMaximum(1e6);
		//h_Mee_Pt__rmUM_Rebin->SetMinimum(1e-4);
		h_Mee_Pt__rmUM_Rebin->SetTitle("US-UM(Rebin);");
		h_Mee_Pt__rmUM_Rebin->DrawClone("col z");

		c1->cd(9);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likepp_Rebin->SetTitle("LppS(Rebin);");
		h_Mee_Pt__likepp_Rebin->DrawClone("col z");

		c1->cd(10);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likemm_Rebin->SetTitle("LmmS(Rebin);");
		h_Mee_Pt__likemm_Rebin->DrawClone("col z");

		c1->cd(11);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__unlikeSame_Rebin->SetTitle("US(Rebin);");
		h_Mee_Pt__unlikeSame_Rebin->DrawClone("col z");

		c1->cd(12);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__LikeSame_Rebin->SetTitle("LS(GA)(Rebin);");
		h_Mee_Pt__LikeSame_Rebin->DrawClone("col z");

		c1->cd(13);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likemmMixed_Rebin->SetTitle("LmmM(Rebin);");
		h_Mee_Pt__likemmMixed_Rebin->DrawClone("col z");

		c1->cd(14);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likeppMixed_Rebin->SetTitle("LppM(Rebin);");
		h_Mee_Pt__likeppMixed_Rebin->DrawClone("col z");

		c1->cd(15);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__temp3_Rebin->SetTitle("LM(GA)(Rebin);");
		h_Mee_Pt__temp3_Rebin->DrawClone("col z");

		c1->cd(16);
		gPad->SetLogz(1);
		gStyle->SetOptStat(0);
		h_Mee_Pt__unlikeMixed_Rebin->SetTitle("UM(Rebin);");
		//h_Mee_Pt__unlikeMixed_Rebin->SetMaximum(1e6);
		//h_Mee_Pt__unlikeMixed_Rebin->SetMinimum(1e-2);
		h_Mee_Pt__unlikeMixed_Rebin->DrawClone("col z");

		c1->SaveAs(Form("roots/%d_QA_Mee_pT.png", number));
	}

	if (1)//画信号，背景1/2，信号-背景1/2，背景1/背景2
	{
		//设置直方图格式
		h_Mee__unlikeSame_Rebin->SetLineColor(1);		h_Mee__unlikeSame_Rebin->SetMarkerStyle(kOpenCircle);	h_Mee__unlikeSame_Rebin->SetMarkerColor(1); h_Mee__unlikeSame_Rebin->SetMarkerSize(0.5);
		h_Mee__LikeSame_PSACcorr_Rebin->SetLineColor(2);h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerStyle(kOpenSquare);h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerColor(2);h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerSize(0.5);
		h_Mee__unlikeMixed_Rebin->SetLineColor(4);		h_Mee__unlikeMixed_Rebin->SetMarkerStyle(kCircle);		h_Mee__unlikeMixed_Rebin->SetMarkerColor(4);h_Mee__unlikeMixed_Rebin->SetMarkerSize(0.5);
		h_Mee__rmLS_Rebin->SetLineColor(6);				h_Mee__rmLS_Rebin->SetMarkerStyle(kOpenCross);			h_Mee__rmLS_Rebin->SetMarkerColor(6);h_Mee__rmLS_Rebin->SetMarkerSize(0.5);
		h_Mee__rmLS_PSACcorr_Rebin->SetLineColor(9);	h_Mee__rmLS_PSACcorr_Rebin->SetMarkerStyle(kOpenCross);	h_Mee__rmLS_PSACcorr_Rebin->SetMarkerColor(9);h_Mee__rmLS_PSACcorr_Rebin->SetMarkerSize(0.5);
		h_Mee__rmUM_Rebin->SetLineColor(3);				h_Mee__rmUM_Rebin->SetMarkerStyle(kOpenStar);			h_Mee__rmUM_Rebin->SetMarkerColor(3);h_Mee__rmUM_Rebin->SetMarkerSize(0.5);
		
		h_Mee__rmLS_Rebin->SetTitle(";M_{ee} (MeV/c^{2});dN/dM_{ee} (MeV/c^{2})^{-1}");
		h_Mee__rmUM_Rebin->SetTitle(";M_{ee} (MeV/c^{2});dN/dM_{ee} (MeV/c^{2})^{-1}");
		h_Mee__unlikeSame_Rebin->SetTitle(";M_{ee} (MeV/c^{2});dN/dM_{ee} (MeV/c^{2})^{-1}");
		h_Mee__LikeSame_PSACcorr_Rebin->SetTitle(";M_{ee} (MeV/c^{2});dN/dM_{ee} (MeV/c^{2})^{-1}");
		h_Mee__CorrLS_Rebin->SetTitle("PSAC vs M_{ee};M_{ee} (MeV/c^{2});PSAC");

		h_Mee__Signif_LS->SetTitle("Signifcance vs M_{ee};M_{ee} (MeV/c^{2});Significance");
		h_Mee__Signif_LS->SetLineColor(kBlack);   h_Mee__Signif_LS->SetMarkerStyle(kOpenCircle); h_Mee__Signif_LS->SetMarkerColor(kBlack);
		h_Mee__Signif_UM->SetLineColor(kRed);	  h_Mee__Signif_UM->SetMarkerStyle(kOpenSquare);   h_Mee__Signif_UM->SetMarkerColor(kRed);
		//画图
		TCanvas *c2 = new TCanvas("c2", "c2", 1400, 1200);
		c2->Divide(3, 3);
		c2->cd(1);//背景+信号
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Mee__rmLS_PSACcorr_Rebin->SetMaximum(1e8);
		h_Mee__rmLS_PSACcorr_Rebin->SetMinimum(1e1);

		h_Mee__rmUM_Rebin->DrawClone("PE");
		h_Mee__rmLS_Rebin->DrawClone("PE same");
		h_Mee__rmLS_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__LikeSame_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__unlikeMixed_Rebin->DrawClone("same PE");
		h_Mee__unlikeSame_Rebin->DrawClone("same PE");
		auto legend = new TLegend(0.60, 0.55, 0.85, 0.85);
		legend->SetFillColor(0); legend->SetBorderSize(0);legend->SetFillStyle(0);
		legend->AddEntry(h_Mee__rmLS_PSACcorr_Rebin, "\t US - LS", "lp");
		legend->AddEntry(h_Mee__rmUM_Rebin, "\t US - UM", "lp");
		legend->AddEntry(h_Mee__LikeSame_PSACcorr_Rebin, "\t LS", "lp");
		legend->AddEntry(h_Mee__unlikeMixed_Rebin, "\t UM", "lp");
		legend->AddEntry(h_Mee__unlikeSame_Rebin, "\t US", "lp");
		legend->SetMargin(0.20); //legend->SetTextAlign(12);
		gStyle->SetLegendTextSize(0.04);
		legend->Draw();

		c2->cd(2);//背景+信号
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Mee__rmLS_Rebin->SetMaximum(1e8);
		h_Mee__rmLS_Rebin->SetMinimum(1e1);
		auto legend2 = new TLegend(0.60, 0.75, 0.85, 0.85);
		legend2->SetFillColor(0);legend2->SetFillStyle(0); legend2->SetBorderSize(0);	legend2->SetMargin(0.20);	gStyle->SetLegendTextSize(0.04);
		legend2->AddEntry(h_Mee__rmLS_Rebin, "\t not PSAC corr", "lp");
		legend2->AddEntry(h_Mee__rmLS_PSACcorr_Rebin, "\t PSAC corr", "lp");
		h_Mee__rmLS_Rebin->DrawClone("PE");
		h_Mee__rmLS_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__LikeSame_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__unlikeSame_Rebin->DrawClone("same PE");
		legend2->Draw("same");
		TPaveText *pt2 = new TPaveText(0.18, 0.15, 0.50, 0.45, "NDC NB");
		pt2->SetFillColorAlpha(0, 0);   // 透明底
		pt2->SetFillStyle(0);
		pt2->SetBorderSize(0);
		pt2->SetTextFont(42);
		pt2->SetTextSize(0.04);
		pt2->SetTextAlign(12);
		//pt2->AddText("Au+Au@200GeV");
		pt2->AddText("Cen:0~80% 0<p_{T}^{ee}<5");
		//pt2->AddText("p_{T}^{e}>0.05,|#eta|<1.8, |y_{ee}|<1");
		pt2->AddText(Form("Focused region:%.1f<M_{ee}<%.1f", x_low_LS, x_up_LS));
		pt2->AddText(Form("S=%.1f B=%.1f", N_LS - B_LS, B_LS));
		pt2->AddText(Form("S/B=%.4f S/#sqrt{S+2B}=%.1f", (N_LS - B_LS) / B_LS, signif_LS));
		pt2->DrawClone("same");
		TPaveText *pt22 = new TPaveText(0.52, 0.15, 0.90, 0.45, "NDC NB");
		pt22->SetFillColorAlpha(0, 0);   // 透明底
		pt22->SetFillStyle(0);
		pt22->SetBorderSize(0);
		pt22->SetTextFont(42);
		pt22->SetTextSize(0.04);
		pt22->SetTextAlign(12);
		//pt22->AddText("Au+Au@200GeV");
		pt22->AddText("Cen:0~80% 0<p_{T}^{ee}<5");
		//pt22->AddText("p_{T}^{e}>0.05,|#eta|<1.8, |y_{ee}|<1");
		pt22->AddText(Form("Focused region:%.1f<M_{ee}<%.1f", x_low_LS2, x_up_LS2));
		pt22->AddText(Form("S=%.1f B=%.1f", N_LS2 - B_LS2, B_LS2));
		pt22->AddText(Form("S/B=%.4f S/#sqrt{S+2B}=%.1f", (N_LS2 - B_LS2) / B_LS2, signif_LS2));
		pt22->DrawClone("same");

		c2->cd(3);//背景+信号
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Mee__rmUM_Rebin->SetMaximum(1e8);
		h_Mee__rmUM_Rebin->SetMinimum(1e1);
		h_Mee__rmUM_Rebin->DrawClone("PE");
		h_Mee__unlikeMixed_Rebin->DrawClone("same PE");
		h_Mee__unlikeSame_Rebin->DrawClone("same PE");
		TPaveText *pt3 = new TPaveText(0.48, 0.65, 0.81, 0.96, "NDC NB");
		pt3->SetFillColorAlpha(0, 0);   // 透明底
		pt3->SetBorderSize(0);
		pt3->SetTextFont(42);
		pt3->SetTextSize(0.032);
		pt3->SetTextAlign(12);
		//pt3->AddText("Au+Au@200GeV");
		pt3->AddText("Cen:0~80% 0<p_{T}^{ee}<5");
		//pt3->AddText("p_{T}^{e}>0.05,|#eta|<1.8, |y_{ee}|<1");
		pt3->AddText(Form("NR:%.1f<M_{ee}<%.1f,%.1f<p_{T}^{ee}<%.1f,0~80%", NR_low_M, NR_up_M, NR_low_pt, NR_up_pt));
		pt3->AddText(Form("Focused region:%.1f<M_{ee}<%.1f", x_low_UM, x_up_UM));
		pt3->AddText(Form("S=%.1f B=%.1f", N_UM - B_UM, B_UM));
		pt3->AddText(Form("S/B=%.4f S/#sqrt{S+B}=%.1f", (N_UM - B_UM) / B_UM, signif_UM));
		//pt3->DrawClone("same");

		c2->cd(4);//信号-背景比例
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gPad->SetLogy(1);
		gStyle->SetOptStat(0);
		h_Mee__SBR_LS_Rebin->SetTitle(";M_{ee} (MeV/c^{2});SBR");
		h_Mee__SBR_LS_Rebin->SetLineColor(kBlack);  h_Mee__SBR_LS_Rebin->SetMarkerStyle(kOpenTriangleDown); h_Mee__SBR_LS_Rebin->SetMarkerColor(kBlack);
		h_Mee__SBR_UM_Rebin->SetLineColor(kRed);	h_Mee__SBR_UM_Rebin->SetMarkerStyle(kOpenCrossX); h_Mee__SBR_UM_Rebin->SetMarkerColor(kRed);
		//h_Mee__SBR_LS_Rebin->SetMaximum();
		//h_Mee__SBR_LS_Rebin->SetMinimum();
		h_Mee__SBR_LS_Rebin->DrawClone("PE");
		h_Mee__SBR_UM_Rebin->DrawClone("same PE");

		auto legend4 = new TLegend(0.55, 0.65, 0.80, 0.85);
		legend4->SetFillColor(0); legend4->SetBorderSize(0);legend4->SetFillStyle(0);
		legend4->AddEntry(h_Mee__SBR_LS_Rebin, "\t (US - LS) / LS", "lp");
		legend4->AddEntry(h_Mee__SBR_UM_Rebin, "\t (US - UM) / UM", "lp");
		legend4->SetMargin(0.20); //legend4->SetTextAlign(12);
		gStyle->SetLegendTextSize(0.04);

		c2->cd(5);//负信号_rmLS
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		TH1F* h_Mee__rmLS_Rebin_test = (TH1F*)h_Mee__rmLS_Rebin->Clone("h_Mee__rmLS_Rebin_test");
		TH1F* h_Mee__rmLS_PSACcorr_Rebin_test = (TH1F*)h_Mee__rmLS_PSACcorr_Rebin->Clone("h_Mee__rmLS_PSACcorr_Rebin_test");
		NegateBinContents(h_Mee__rmLS_Rebin_test);
		NegateBinContents(h_Mee__rmLS_PSACcorr_Rebin_test);
		h_Mee__rmLS_Rebin_test->SetTitle(";M_{ee} (MeV/c^{2});- dN/dM_{ee} (MeV/c^{2})^{-1}");
		//h_Mee__rmLS_Rebin_test->SetMaximum(1e9);
		//h_Mee__rmLS_Rebin_test->SetMinimum(10);
		h_Mee__rmLS_Rebin_test->DrawClone("PE");
		h_Mee__rmLS_PSACcorr_Rebin_test->DrawClone("PE same");

		c2->cd(6);//负信号_rmUM
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		TH1F* h_Mee__rmUM_Rebin_test = (TH1F*)h_Mee__rmUM_Rebin->Clone("h_Mee__rmUM_Rebin_test");
		NegateBinContents(h_Mee__rmUM_Rebin_test);
		h_Mee__rmUM_Rebin_test->SetTitle(";M_{ee} (MeV/c^{2});- dN/dM_{ee} (MeV/c^{2})^{-1}");
		//h_Mee__rmUM_Rebin_test->SetMaximum(1e9);
		//h_Mee__rmUM_Rebin_test->SetMinimum(10);
		h_Mee__rmUM_Rebin_test->DrawClone("PE");

		c2->cd(7);//LS背景修正因子check
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		TH2F* h_Mee_Pt__CorrLS_Rebin = (TH2F*)h_Mee_Pt_Cen__CorrLS_Rebin->Project3D("yx e");
		h_Mee_Pt__CorrLS_Rebin->SetTitle("PSAC distribution;Mee (MeV/c^{2});p_{T} (GeV/c)");
		h_Mee_Pt__CorrLS_Rebin->Scale(1.0 / (Cen__newEdges.size() - 1));
		//h_Mee_Pt__CorrLS_Rebin->SetMaximum(1.2);
		//h_Mee_Pt__CorrLS_Rebin->SetMinimum(0.8);
		h_Mee_Pt__CorrLS_Rebin->DrawClone("col z");

		c2->cd(8);//LS背景修正因子check
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		//h_Mee__CorrLS_Rebin->Scale(1.0 / ((Cen__newEdges.size() - 1)*(Pt__newEdges.size() - 1)));
		h_Mee__CorrLS_Rebin->SetLineColor(kBlack);  h_Mee__CorrLS_Rebin->SetMarkerStyle(kOpenCircle); h_Mee__CorrLS_Rebin->SetMarkerColor(kBlack);
		//h_Mee__CorrLS_Rebin->SetMaximum(1.02);
		//h_Mee__CorrLS_Rebin->SetMinimum(0.96);
		h_Mee__CorrLS_Rebin->DrawClone();

		c2->cd(9);
		gPad->SetLogy(1);
		gStyle->SetOptStat(0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		//h_Mee__Signif_LS->SetMinimum(0);
		//h_Mee__Signif_LS->SetMaximum(1000);
		h_Mee__Signif_LS->DrawClone();
		h_Mee__Signif_UM->DrawClone("same");
		auto legend9 = new TLegend(0.65, 0.55, 0.90, 0.85);
		legend9->SetFillColor(0);legend9->SetFillStyle(0); legend9->SetBorderSize(0);
		legend9->AddEntry(h_Mee__Signif_LS, "\t LS", "lp");
		legend9->AddEntry(h_Mee__Signif_UM, "\t UM", "lp");
		legend9->SetMargin(0.20); //legend9->SetTextAlign(12);
		gStyle->SetLegendTextSize(0.04);
		legend9->Draw();

		c2->SaveAs(Form("roots/%d_Mee_PSAC.png", number));
	}
	if (0){
		h_Mee__unlikeSame_Rebin->SetLineColor(1);		h_Mee__unlikeSame_Rebin->SetMarkerStyle(kOpenCircle);	h_Mee__unlikeSame_Rebin->SetMarkerColor(1); h_Mee__unlikeSame_Rebin->SetMarkerSize(0.5);
		h_Mee__LikeSame_PSACcorr_Rebin->SetLineColor(2);h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerStyle(kOpenSquare);h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerColor(2);h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerSize(0.5);
		h_Mee__unlikeMixed_Rebin->SetLineColor(4);		h_Mee__unlikeMixed_Rebin->SetMarkerStyle(kCircle);		h_Mee__unlikeMixed_Rebin->SetMarkerColor(4);h_Mee__unlikeMixed_Rebin->SetMarkerSize(0.5);
		h_Mee__rmLS_Rebin->SetLineColor(6);				h_Mee__rmLS_Rebin->SetMarkerStyle(kOpenCross);			h_Mee__rmLS_Rebin->SetMarkerColor(6);h_Mee__rmLS_Rebin->SetMarkerSize(0.5);
		h_Mee__rmLS_PSACcorr_Rebin->SetLineColor(9);	h_Mee__rmLS_PSACcorr_Rebin->SetMarkerStyle(kOpenCross);	h_Mee__rmLS_PSACcorr_Rebin->SetMarkerColor(9);h_Mee__rmLS_PSACcorr_Rebin->SetMarkerSize(0.5);
		h_Mee__rmUM_Rebin->SetLineColor(3);				h_Mee__rmUM_Rebin->SetMarkerStyle(kOpenStar);			h_Mee__rmUM_Rebin->SetMarkerColor(3);h_Mee__rmUM_Rebin->SetMarkerSize(0.5);
		
		h_Mee__rmLS_Rebin->SetTitle(";M_{ee} (MeV/c^{2});dN/dM_{ee} (MeV/c^{2})^{-1}");
		h_Mee__rmUM_Rebin->SetTitle(";M_{ee} (MeV/c^{2});dN/dM_{ee} (MeV/c^{2})^{-1}");
		h_Mee__unlikeSame_Rebin->SetTitle(";M_{ee} (MeV/c^{2});dN/dM_{ee} (MeV/c^{2})^{-1}");
		h_Mee__LikeSame_PSACcorr_Rebin->SetTitle(";M_{ee} (MeV/c^{2});dN/dM_{ee} (MeV/c^{2})^{-1}");
		h_Mee__CorrLS_Rebin->SetTitle("PSAC vs M_{ee};M_{ee} (MeV/c^{2});PSAC");

		TCanvas *c3 = new TCanvas("c3", "c3", 1200, 500);
		c3->Divide(2, 1);
		c3->cd(1);//背景+信号
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		//h_Mee__rmLS_Rebin->SetMaximum(1e9);
		//h_Mee__rmLS_Rebin->SetMinimum(1e1);
		auto legend2 = new TLegend(0.60, 0.75, 0.85, 0.85);
		legend2->SetFillColor(0); legend2->SetBorderSize(0);	legend2->SetMargin(0.20);	gStyle->SetLegendTextSize(0.04);
		legend2->SetFillStyle(0);
		legend2->AddEntry(h_Mee__rmLS_Rebin, "\t not PSAC corr", "lp");
		legend2->AddEntry(h_Mee__rmLS_PSACcorr_Rebin, "\t PSAC corr", "lp");
		h_Mee__rmLS_Rebin->DrawClone("PE");
		h_Mee__rmLS_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__LikeSame_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__unlikeSame_Rebin->DrawClone("same PE");
		legend2->Draw("same");
		TPaveText *pt2 = new TPaveText(0.18, 0.15, 0.50, 0.45, "NDC NB");
		pt2->SetFillColorAlpha(0, 0);   // 透明底
		pt2->SetFillStyle(0);
		pt2->SetBorderSize(0);
		pt2->SetTextFont(42);
		pt2->SetTextSize(0.032);
		pt2->SetTextAlign(12);
		//pt2->AddText("Au+Au@200GeV");
		pt2->AddText("Cen:0~80% 0<p_{T}^{ee}<5");
		//pt2->AddText("p_{T}^{e}>0.05,|#eta|<1.8, |y_{ee}|<1");
		pt2->AddText(Form("Focused region:%.1f<M_{ee}<%.1f", x_low_LS, x_up_LS));
		pt2->AddText(Form("S=%.1f B=%.1f", N_LS - B_LS, B_LS));
		pt2->AddText(Form("S/B=%.4f S/#sqrt{S+2B}=%.1f", (N_LS - B_LS) / B_LS, signif_LS));
		pt2->DrawClone("same");
		TPaveText *pt22 = new TPaveText(0.52, 0.15, 0.90, 0.45, "NDC NB");
		pt22->SetFillColorAlpha(0, 0);   // 透明底
		pt22->SetFillStyle(0);
		pt22->SetBorderSize(0);
		pt22->SetTextFont(42);
		pt22->SetTextSize(0.032);
		pt22->SetTextAlign (12);
		//pt22->AddText("Au+Au@200GeV");
		pt22->AddText("Cen:0~80% 0<p_{T}^{ee}<5");
		//pt22->AddText("p_{T}^{e}>0.05,|#eta|<1.8, |y_{ee}|<1");
		pt22->AddText(Form("Focused region:%.1f<M_{ee}<%.1f", x_low_LS2, x_up_LS2));
		pt22->AddText(Form("S=%.1f B=%.1f", N_LS2 - B_LS2, B_LS2));
		pt22->AddText(Form("S/B=%.4f S/#sqrt{S+2B}=%.1f", (N_LS2 - B_LS2) / B_LS2, signif_LS2));
		pt22->DrawClone("same");

		c3->cd(2);//背景+信号
		gPad->SetLogy(0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		h_Mee__rmLS_PSACcorr_Rebin->GetXaxis()->SetRangeUser(15,19);
		h_Mee__rmLS_PSACcorr_Rebin->DrawClone("PE");

		c3->SaveAs(Form("roots/%d_Mee_and_17MeV.png", number));
	}
}