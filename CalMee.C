//---------------------从dAu200GeV.root中提取直方图，并进行设置更改和元素添加----------------------
//Diff. with OO/CalMee.C: 1.没有混合背景；2.没有Rotation背景；3.没有UM-LM test
#include "../2021_OO200/someFunction.h"
void CalMee(TString inFileName = "roots/15_20260909_He3Au2014_TOF_ZDCETg_rmP0p5.root", Int_t number =15)
{
	//vector<Double_t> Mee__newEdges = {0.25,0.27,0.28,0.29,0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37, 0.38,0.39, 0.40,0.41,0.42,0.6};//pion mass
	// 定义新的bin边界
	//vector<Double_t> Mee__newEdges = {0, 0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.085, 0.09, 0.095, 0.1, 0.105, 0.11, 0.115, 0.12, 0.125, 0.13, 0.135, 0.14, 0.145, 0.15, 0.155, 0.16, 0.165, 0.17, 0.175, 0.18, 0.185, 0.19, 0.195, 0.2, 0.205, 0.21, 0.215, 0.22, 0.225, 0.23, 0.235, 0.24, 0.245, 0.25, 0.255, 0.26, 0.265, 0.27, 0.275, 0.28, 0.285, 0.29, 0.295, 0.3, 0.305, 0.31, 0.315, 0.32, 0.325, 0.33, 0.335, 0.34, 0.345, 0.35, 0.355, 0.36, 0.365, 0.37, 0.375, 0.38, 0.385, 0.39, 0.395, 0.4, 0.405, 0.41, 0.415, 0.42, 0.425, 0.43, 0.435, 0.44, 0.445, 0.45, 0.455, 0.46, 0.465, 0.47, 0.475, 0.48, 0.485, 0.49, 0.495, 0.5, 0.505, 0.51, 0.515, 0.52, 0.525, 0.53, 0.535, 0.54, 0.545, 0.55, 0.555, 0.56, 0.565, 0.57, 0.575, 0.58, 0.585, 0.59, 0.595, 0.6, 0.605, 0.61, 0.615, 0.62, 0.625, 0.63, 0.635, 0.64, 0.645, 0.65, 0.655, 0.66, 0.665, 0.67, 0.675, 0.68, 0.685, 0.69, 0.695, 0.7, 0.705, 0.71, 0.715, 0.72, 0.725, 0.73, 0.735, 0.74, 0.745, 0.75, 0.755, 0.76, 0.765, 0.77, 0.775, 0.78, 0.785, 0.79, 0.795, 0.8, 0.805, 0.81, 0.815, 0.82, 0.825, 0.83, 0.835, 0.84, 0.845, 0.85, 0.855, 0.86, 0.865, 0.87, 0.875, 0.88, 0.885, 0.89, 0.895, 0.9, 0.905, 0.91, 0.915, 0.92, 0.925, 0.93, 0.935, 0.94, 0.945, 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1, 1.005, 1.01, 1.015, 1.02, 1.025, 1.03, 1.035, 1.04, 1.045, 1.05, 1.055, 1.06, 1.065, 1.07, 1.075, 1.08, 1.085, 1.09, 1.095, 1.1, 1.105, 1.11, 1.115, 1.12, 1.125, 1.13, 1.135, 1.14, 1.145, 1.15, 1.155, 1.16, 1.165, 1.17, 1.175, 1.18, 1.185, 1.19, 1.195, 1.2, 1.205, 1.21, 1.215, 1.22, 1.225, 1.23, 1.235, 1.24, 1.245, 1.25, 1.255, 1.26, 1.265, 1.27, 1.275, 1.28, 1.285, 1.29, 1.295, 1.3, 1.305, 1.31, 1.315, 1.32, 1.325, 1.33, 1.335, 1.34, 1.345, 1.35, 1.355, 1.36, 1.365, 1.37, 1.375, 1.38, 1.385, 1.39, 1.395, 1.4, 1.405, 1.41, 1.415, 1.42, 1.425, 1.43, 1.435, 1.44, 1.445, 1.45, 1.455, 1.46, 1.465, 1.47, 1.475, 1.48, 1.485, 1.49, 1.495, 1.5, 1.505, 1.51, 1.515, 1.52, 1.525, 1.53, 1.535, 1.54, 1.545, 1.55, 1.555, 1.56, 1.565, 1.57, 1.575, 1.58, 1.585, 1.59, 1.595, 1.6, 1.605, 1.61, 1.615, 1.62, 1.625, 1.63, 1.635, 1.64, 1.645, 1.65, 1.655, 1.66, 1.665, 1.67, 1.675, 1.68, 1.685, 1.69, 1.695, 1.7, 1.705, 1.71, 1.715, 1.72, 1.725, 1.73, 1.735, 1.74, 1.745, 1.75, 1.755, 1.76, 1.765, 1.77, 1.775, 1.78, 1.785, 1.79, 1.795, 1.8, 1.805, 1.81, 1.815, 1.82, 1.825, 1.83, 1.835, 1.84, 1.845, 1.85, 1.855, 1.86, 1.865, 1.87, 1.875, 1.88, 1.885, 1.89, 1.895, 1.9, 1.905, 1.91, 1.915, 1.92, 1.925, 1.93, 1.935, 1.94, 1.945, 1.95, 1.955, 1.96, 1.965, 1.97, 1.975, 1.98, 1.985, 1.99, 1.995, 2, 2.005, 2.01, 2.015, 2.02, 2.025, 2.03, 2.035, 2.04, 2.045, 2.05, 2.055, 2.06, 2.065, 2.07, 2.075, 2.08, 2.085, 2.09, 2.095, 2.1, 2.105, 2.11, 2.115, 2.12, 2.125, 2.13, 2.135, 2.14, 2.145, 2.15, 2.155, 2.16, 2.165, 2.17, 2.175, 2.18, 2.185, 2.19, 2.195, 2.2, 2.205, 2.21, 2.215, 2.22, 2.225, 2.23, 2.235, 2.24, 2.245, 2.25, 2.255, 2.26, 2.265, 2.27, 2.275, 2.28, 2.285, 2.29, 2.295, 2.3, 2.305, 2.31, 2.315, 2.32, 2.325, 2.33, 2.335, 2.34, 2.345, 2.35, 2.355, 2.36, 2.365, 2.37, 2.375, 2.38, 2.385, 2.39, 2.395, 2.4, 2.405, 2.41, 2.415, 2.42, 2.425, 2.43, 2.435, 2.44, 2.445, 2.45, 2.455, 2.46, 2.465, 2.47, 2.475, 2.48, 2.485, 2.49, 2.495, 2.5, 2.505, 2.51, 2.515, 2.52, 2.525, 2.53, 2.535, 2.54, 2.545, 2.55, 2.555, 2.56, 2.565, 2.57, 2.575, 2.58, 2.585, 2.59, 2.595, 2.6, 2.605, 2.61, 2.615, 2.62, 2.625, 2.63, 2.635, 2.64, 2.645, 2.65, 2.655, 2.66, 2.665, 2.67, 2.675, 2.68, 2.685, 2.69, 2.695, 2.7, 2.705, 2.71, 2.715, 2.72, 2.725, 2.73, 2.735, 2.74, 2.745, 2.75, 2.755, 2.76, 2.765, 2.77, 2.775, 2.78, 2.785, 2.79, 2.795, 2.8, 2.805, 2.81, 2.815, 2.82, 2.825, 2.83, 2.835, 2.84, 2.845, 2.85, 2.855, 2.86, 2.865, 2.87, 2.875, 2.88, 2.885, 2.89, 2.895, 2.9, 2.905, 2.91, 2.915, 2.92, 2.925, 2.93, 2.935, 2.94, 2.945, 2.95, 2.955, 2.96, 2.965, 2.97, 2.975, 2.98, 2.985, 2.99, 2.995, 3, 3.005, 3.01, 3.015, 3.02, 3.025, 3.03, 3.035, 3.04, 3.045, 3.05, 3.055, 3.06, 3.065, 3.07, 3.075, 3.08, 3.085, 3.09, 3.095, 3.1, 3.105, 3.11, 3.115, 3.12, 3.125, 3.13, 3.135, 3.14, 3.145, 3.15, 3.155, 3.16, 3.165, 3.17, 3.175, 3.18, 3.185, 3.19, 3.195, 3.2, 3.205, 3.21, 3.215, 3.22, 3.225, 3.23, 3.235, 3.24, 3.245, 3.25, 3.255, 3.26, 3.265, 3.27, 3.275, 3.28, 3.285, 3.29, 3.295, 3.3, 3.305, 3.31, 3.315, 3.32, 3.325, 3.33, 3.335, 3.34, 3.345, 3.35, 3.355, 3.36, 3.365, 3.37, 3.375, 3.38, 3.385, 3.39, 3.395, 3.4, 3.405, 3.41, 3.415, 3.42, 3.425, 3.43, 3.435, 3.44, 3.445, 3.45, 3.455, 3.46, 3.465, 3.47, 3.475, 3.48, 3.485, 3.49, 3.495, 3.5, 3.505, 3.51, 3.515, 3.52, 3.525, 3.53, 3.535, 3.54, 3.545, 3.55, 3.555, 3.56, 3.565, 3.57, 3.575, 3.58, 3.585, 3.59, 3.595, 3.6, 3.605, 3.61, 3.615, 3.62, 3.625, 3.63, 3.635, 3.64, 3.645, 3.65, 3.655, 3.66, 3.665, 3.67, 3.675, 3.68, 3.685, 3.69, 3.695, 3.7, 3.705, 3.71, 3.715, 3.72, 3.725, 3.73, 3.735, 3.74, 3.745, 3.75, 3.755, 3.76, 3.765, 3.77, 3.775, 3.78, 3.785, 3.79, 3.795, 3.8, 3.805, 3.81, 3.815, 3.82, 3.825, 3.83, 3.835, 3.84, 3.845, 3.85, 3.855, 3.86, 3.865, 3.87, 3.875, 3.88, 3.885, 3.89, 3.895, 3.9, 3.905, 3.91, 3.915, 3.92, 3.925, 3.93, 3.935, 3.94, 3.945, 3.95, 3.955, 3.96, 3.965, 3.97, 3.975, 3.98, 3.985, 3.99, 3.995, 4.000};
	vector<Double_t> Mee__newEdges = {0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.16,0.20,0.30,0.35,0.40,0.50,0.60,0.64,0.68,0.72,0.76,0.82,0.86,0.96,1.0,1.02,1.04,1.06,1.1,1.2,1.6,2.0,2.6,3.0, 3.04,3.08,3.10,3.12,3.14,3.18,3.20,3.26,3.3,4.0};//size()=38
	Int_t Mee_bins = Mee__newEdges.size() - 1;

	//vector<Double_t> Pt__newEdges =  {0,0.05,0.1,0.15,0.20,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1,1.05,1.1,1.15,1.2,1.25,1.3,1.35,1.4,1.45,1.5,1.55,1.6,1.65,1.7,1.75,1.8,1.85,1.9,1.95,2,2.05,2.1,2.15,2.2,2.25,2.3,2.35,2.4,2.45,2.5,2.55,2.6,2.65,2.7,2.75,2.8,2.85,2.9,2.95,3,3.05,3.1,3.15,3.2,3.25,3.3,3.35,3.4,3.45,3.5,3.55,3.6,3.65,3.7,3.75,3.8,3.85,3.9,3.95,4,4.05,4.1,4.15,4.2,4.25,4.3,4.35,4.4,4.45,4.5,4.55,4.6,4.65,4.7,4.75,4.8,4.85,4.9,4.95,5};
	//vector<Double_t> Pt__newEdges = {0,0.05,0.1,0.15,0.20,0.25,0.30,0.35,0.40, 0.45,0.50,0.55,0.60,0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.95, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.5, 4.0, 5.0};//size()=40
	//vector<Double_t> Pt__newEdges = {0,0.05,0.1,0.15,0.20,0.25,0.30,0.40,0.50, 0.7, 0.90, 1.2, 1.6, 2.0, 3.0, 5.0};
	vector<Double_t> Pt__newEdges = { 0,1.0,2.0,3.0,4.0,5.0};
	Int_t Pt_bins = Pt__newEdges.size() - 1;
	//                                 80   75   70   65   60   55   50   45   40   35   30    25    20    15    10    5     0   
	//vector<Double_t> Cen__newEdges = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
	//vector<Double_t> Cen__newEdges = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
	//vector<Double_t> Cen__newEdges = {8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
	vector<Double_t> Cen__newEdges = {0,2,4,8,16};
	Int_t Cen_bins = Cen__newEdges.size() - 1;
	// 从root文件中导入待拟合的直方图
	TFile *inFile = new TFile(inFileName);
	if (!inFile){cout << "The input file is not found! Exiting..." << endl; return;}
	// 导入直方图
	TH3F* h_Mee_Pt_Cen__unlikeSame  = (TH3F*)inFile->Get("h_Mee_Pt_Cen__unlikeSame");
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
	//Float_t NR_low_M = 0.3, NR_up_M = 1, NR_low_pt = 1, NR_up_pt = 3;//pAu2015
	//Float_t NR_low_M = 0.5, NR_up_M = 2, NR_low_pt = 0, NR_up_pt = 2;//d+Au
	Float_t NR_low_M = 0.5, NR_up_M = 3, NR_low_pt = 0, NR_up_pt = 2;//He3Au2014
	//OO from Zihan
	Float_t scale = ComputeMixEventScale(h_Mee_Pt_Cen__likepp_Rebin, h_Mee_Pt_Cen__likemm_Rebin,h_Mee_Pt_Cen__likeppMixed_Rebin, h_Mee_Pt_Cen__likemmMixed_Rebin,h_Mee_Pt_Cen__unlikeMixed_Rebin, NR_low_M, NR_up_M, NR_low_pt, NR_up_pt, 1, 16);
	cout << "scale: " << scale << endl;
	//scale=0.0149;//p+Au_2015
	//scale=0.01126;//He3Au2014 Central
	//scale=0.0117;//He3Au2014 ZDCE
	// 3-D Unlike-MixedEvent背景
	h_Mee_Pt_Cen__unlikeMixed_Rebin->Scale(scale);
	h_Mee_Pt_Cen__likemmMixed_Rebin->Scale(scale);
	h_Mee_Pt_Cen__likeppMixed_Rebin->Scale(scale);

	// 1-D Unlike-MixedEvent背景
	// 构造5个不同scale的1-D UM背景：scale-5%, scale-3%, scale(原值), scale+3%, scale+5%
	Float_t scale1 = scale * 0.95;
	Float_t scale2 = scale * 0.97;
	Float_t scale3 = scale;
	Float_t scale4 = scale * 1.03;
	Float_t scale5 = scale * 1.05;
	TH1F* h_Mee__unlikeMixed_Rebin_scale1 = (TH1F*)h_Mee__unlikeMixed_Rebin->Clone("h_Mee__unlikeMixed_Rebin_scale1");
	TH1F* h_Mee__unlikeMixed_Rebin_scale2 = (TH1F*)h_Mee__unlikeMixed_Rebin->Clone("h_Mee__unlikeMixed_Rebin_scale2");
	TH1F* h_Mee__unlikeMixed_Rebin_scale4 = (TH1F*)h_Mee__unlikeMixed_Rebin->Clone("h_Mee__unlikeMixed_Rebin_scale4");
	TH1F* h_Mee__unlikeMixed_Rebin_scale5 = (TH1F*)h_Mee__unlikeMixed_Rebin->Clone("h_Mee__unlikeMixed_Rebin_scale5");
	h_Mee__unlikeMixed_Rebin_scale1->Scale(scale1);
	h_Mee__unlikeMixed_Rebin_scale2->Scale(scale2);
	h_Mee__unlikeMixed_Rebin_scale4->Scale(scale4);
	h_Mee__unlikeMixed_Rebin_scale5->Scale(scale5);
	// 原始1-D UM背景按原scale(scale3)缩放
	h_Mee__unlikeMixed_Rebin->Scale(scale3);

	// 去除背景，还原信号
	h_Mee_Pt_Cen__rmLS_Rebin->Add(h_Mee_Pt_Cen__unlikeSame_Rebin, h_Mee_Pt_Cen__LikeSame_Rebin, 1.0, -1.0);
	h_Mee_Pt_Cen__rmUM_Rebin->Add(h_Mee_Pt_Cen__unlikeSame_Rebin, h_Mee_Pt_Cen__unlikeMixed_Rebin, 1.0, -1.0);
	h_Mee__rmLS_Rebin->Add(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_Rebin, 1.0, -1.0);
	h_Mee__rmLS_PSACcorr_Rebin->Add(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, 1.0, -1.0);
	h_Mee__rmUM_Rebin->Add(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin, 1.0, -1.0);
	// 用不同scale的1-D UM背景构造对应的信号 (scale3即原scale，对应h_Mee__rmUM_Rebin)
	TH1F* h_Mee__rmUM_Rebin_scale1 = (TH1F*)h_Mee__unlikeSame_Rebin->Clone("h_Mee__rmUM_Rebin_scale1");	h_Mee__rmUM_Rebin_scale1->Add(h_Mee__unlikeMixed_Rebin_scale1, -1.0);
	TH1F* h_Mee__rmUM_Rebin_scale2 = (TH1F*)h_Mee__unlikeSame_Rebin->Clone("h_Mee__rmUM_Rebin_scale2");	h_Mee__rmUM_Rebin_scale2->Add(h_Mee__unlikeMixed_Rebin_scale2, -1.0);
	TH1F* h_Mee__rmUM_Rebin_scale4 = (TH1F*)h_Mee__unlikeSame_Rebin->Clone("h_Mee__rmUM_Rebin_scale4");	h_Mee__rmUM_Rebin_scale4->Add(h_Mee__unlikeMixed_Rebin_scale4, -1.0);
	TH1F* h_Mee__rmUM_Rebin_scale5 = (TH1F*)h_Mee__unlikeSame_Rebin->Clone("h_Mee__rmUM_Rebin_scale5");	h_Mee__rmUM_Rebin_scale5->Add(h_Mee__unlikeMixed_Rebin_scale5, -1.0);

	//计算dN/dM
	ResetBinContent(h_Mee__rmLS_Rebin);
	ResetBinContent(h_Mee__rmLS_PSACcorr_Rebin);
	ResetBinContent(h_Mee__rmUM_Rebin);
	ResetBinContent(h_Mee__unlikeSame_Rebin);
	ResetBinContent(h_Mee__LikeSame_Rebin);
	ResetBinContent(h_Mee__LikeSame_PSACcorr_Rebin);
	ResetBinContent(h_Mee__unlikeMixed_Rebin);

	ResetBinContent(h_Mee__rmUM_Rebin_scale1);
	ResetBinContent(h_Mee__rmUM_Rebin_scale2);
	ResetBinContent(h_Mee__rmUM_Rebin_scale4);
	ResetBinContent(h_Mee__rmUM_Rebin_scale5);
	ResetBinContent(h_Mee__unlikeMixed_Rebin_scale1);
	ResetBinContent(h_Mee__unlikeMixed_Rebin_scale2);
	ResetBinContent(h_Mee__unlikeMixed_Rebin_scale4);
	ResetBinContent(h_Mee__unlikeMixed_Rebin_scale5);

	// 计算不同背景下的信号显著性
	TH1F* h_Mee__Signif_LS = (TH1F*)CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, "h_Mee__Signif_LS");
	TH1F* h_Mee__Signif_UM = (TH1F*)CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin, "h_Mee__Signif_UM");
	Float_t x_low_LS = 0.4, x_up_LS = 1.0;
	auto[signif_LS, signif_err2_LS, N_LS, N_err2_LS, B_LS, B_err2_LS] = CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_Rebin, x_low_LS, x_up_LS);
	auto[signif_LS_PSACcorr, signif_err2_LS_PSACcorr, N_LS_PSACcorr, N_err2_LS_PSACcorr, B_LS_PSACcorr, B_err2_LS_PSACcorr] = CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, x_low_LS, x_up_LS);
	Float_t x_low_UM = 1.0, x_up_UM = 2.8;
	auto[signif_UM, signif_err2_UM, N_UM, N_err2_UM, B_UM, B_err2_UM] = CalSignificance(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin, x_low_UM, x_up_UM);

	// 将 likemm same-event 与 mixed-event 投影到 (Mee, pT)，用"e"选项按误差传播给出每个bin的误差
	TH2F* h_Mee_Pt__likemmSame_e  = (TH2F*)h_Mee_Pt_Cen__likemm_Rebin->Project3D("yx e");
	TH2F* h_Mee_Pt__likemmMix_e   = (TH2F*)h_Mee_Pt_Cen__likemmMixed_Rebin->Project3D("yx e");
	h_Mee_Pt__likemmSame_e->SetDirectory(nullptr);
	h_Mee_Pt__likemmMix_e->SetDirectory(nullptr);
	// 构造二维 pull 图：pull = (Same - Mixed) / sqrt(errSame^2 + errMix^2)
	TH2F* h_Mee_Pt__likemm_Pull = (TH2F*)h_Mee_Pt__likemmSame_e->Clone("h_Mee_Pt__likemm_Pull");
	h_Mee_Pt__likemm_Pull->Reset();//保留轴，清空内容
	const Int_t nPullX = h_Mee_Pt__likemm_Pull->GetNbinsX();
	const Int_t nPullY = h_Mee_Pt__likemm_Pull->GetNbinsY();
	for (Int_t iPullX = 1; iPullX <= nPullX; ++iPullX)
	{
		for (Int_t iPullY = 1; iPullY <= nPullY; ++iPullY)
		{
			Double_t valSame = h_Mee_Pt__likemmSame_e->GetBinContent(iPullX, iPullY);
			Double_t valMix  = h_Mee_Pt__likemmMix_e->GetBinContent(iPullX, iPullY);
			Double_t errSame = h_Mee_Pt__likemmSame_e->GetBinError(iPullX, iPullY);
			Double_t errMix  = h_Mee_Pt__likemmMix_e->GetBinError(iPullX, iPullY);
			Double_t errDiff = TMath::Sqrt(errSame * errSame + errMix * errMix);
			Double_t pull    = (errDiff > 0) ? (valSame - valMix) / errDiff : 0.0;
			h_Mee_Pt__likemm_Pull->SetBinContent(iPullX, iPullY, pull);
			h_Mee_Pt__likemm_Pull->SetBinError(iPullX, iPullY, 0.0);
		}
	}
	//计算各种比例
	TH1F *h_Mee__BKGRatio_Rebin = new TH1F(*h_Mee__LikeSame_PSACcorr_Rebin);
	*h_Mee__BKGRatio_Rebin = *h_Mee__LikeSame_PSACcorr_Rebin / *h_Mee__unlikeMixed_Rebin;//背景比

	TH1F *h_Mee__SBR_LS_Rebin = new TH1F(*h_Mee__rmLS_Rebin);
	*h_Mee__SBR_LS_Rebin = *h_Mee__rmLS_Rebin / *h_Mee__LikeSame_PSACcorr_Rebin;//LS信背比

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
			h_Mee__SamePMix_mm_Rebin[iPt]->GetXaxis()->SetTitle("M_{ee} (GeV/c^{2})");
			h_Mee__SamePMix_mm_Rebin[iPt]->GetYaxis()->SetTitle("Same/PMix");

			h_Mee__SamePMix_pp_Rebin[iPt] = (TH1F*)h_Mee__likepp_Rebin[iPt]->Clone(TString::Format("h_Mee__SamePMix_pp_Rebin_pt%d", iPt));
			h_Mee__SamePMix_pp_Rebin[iPt]->Divide(h_Mee__likepp_Rebin[iPt], h_Mee__likeppMixed_Rebin[iPt], 1.0, 1.0, "B");
			h_Mee__SamePMix_pp_Rebin[iPt]->SetDirectory(nullptr);
			h_Mee__SamePMix_pp_Rebin[iPt]->SetTitle(TString::Format("SamePMix pp, pT [%.1f,%.1f]", Pt__newEdges[iPt], Pt__newEdges[iPt + 1]));
			h_Mee__SamePMix_pp_Rebin[iPt]->GetXaxis()->SetTitle("M_{ee} (GeV/c^{2})");
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
			h_Mee__SamePMix_mm_Rebin[iPt]->SetMaximum(1.2);
			h_Mee__SamePMix_mm_Rebin[iPt]->SetMinimum(0.8);
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
	if (0)// Mee pT 2D-QA
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
	
	if (0)// 画一张图，pt范围是0-0.05GeV/c，Mee范围是0-4GeV/c^2
	{
		h_Mee_Pt_Cen__unlikeSame_Rebin->SetLineColor(1);		h_Mee_Pt_Cen__unlikeSame_Rebin->SetMarkerStyle(kOpenCircle);	h_Mee_Pt_Cen__unlikeSame_Rebin->SetMarkerColor(1); 		h_Mee_Pt_Cen__unlikeSame_Rebin->SetMarkerSize(0.1);
		h_Mee_Pt_Cen__LikeSame_Rebin->SetLineColor(2);			h_Mee_Pt_Cen__LikeSame_Rebin->SetMarkerStyle(kOpenSquare);		h_Mee_Pt_Cen__LikeSame_Rebin->SetMarkerColor(2); 		h_Mee_Pt_Cen__LikeSame_Rebin->SetMarkerSize(0.1);
		h_Mee_Pt_Cen__unlikeMixed_Rebin->SetLineColor(4);		h_Mee_Pt_Cen__unlikeMixed_Rebin->SetMarkerStyle(kCircle);		h_Mee_Pt_Cen__unlikeMixed_Rebin->SetMarkerColor(4);		h_Mee_Pt_Cen__unlikeMixed_Rebin->SetMarkerSize(0.1);
		h_Mee_Pt_Cen__rmLS_Rebin->SetLineColor(6);				h_Mee_Pt_Cen__rmLS_Rebin->SetMarkerStyle(kOpenCross);			h_Mee_Pt_Cen__rmLS_Rebin->SetMarkerColor(6); 			h_Mee_Pt_Cen__rmLS_Rebin->SetMarkerSize(0.1);
		h_Mee_Pt_Cen__rmLS_PSACcorr_Rebin->SetLineColor(9);		h_Mee_Pt_Cen__rmLS_PSACcorr_Rebin->SetMarkerStyle(kOpenCross);	h_Mee_Pt_Cen__rmLS_PSACcorr_Rebin->SetMarkerColor(9);	h_Mee_Pt_Cen__rmLS_PSACcorr_Rebin->SetMarkerSize(0.1);
		h_Mee_Pt_Cen__rmUM_Rebin->SetLineColor(3);				h_Mee_Pt_Cen__rmUM_Rebin->SetMarkerStyle(kOpenStar);			h_Mee_Pt_Cen__rmUM_Rebin->SetMarkerColor(3); 			h_Mee_Pt_Cen__rmUM_Rebin->SetMarkerSize(0.1);
		
		//画图
		TCanvas *c_Pt = new TCanvas("c_Pt", "c_Pt", 600, 800);
		c_Pt->Divide(1,2);
		c_Pt->cd(1);
		gPad->SetLogy(1);
		gStyle->SetOptStat(0);
		Float_t Cen_bin_low = 0, Cen_bin_up = 16;
		Draw_Mee_Ptslice(h_Mee_Pt_Cen__unlikeSame_Rebin, h_Mee_Pt_Cen__LikeSame_Rebin, h_Mee_Pt_Cen__unlikeMixed_Rebin, h_Mee_Pt_Cen__rmLS_Rebin, h_Mee_Pt_Cen__rmUM_Rebin,0.0,5,Cen_bin_low,Cen_bin_up);
		c_Pt->cd(2);
		gPad->SetLogy(1);
		gStyle->SetOptStat(0);
		Draw_Mee_Ptslice(h_Mee_Pt_Cen__unlikeSame_Rebin, h_Mee_Pt_Cen__unlikeMixed_Rebin, h_Mee_Pt_Cen__unlikeMixed_Rebin, h_Mee_Pt_Cen__rmUM_Rebin, h_Mee_Pt_Cen__rmUM_Rebin,0.0,5,Cen_bin_low,Cen_bin_up);
		
		c_Pt->SaveAs(Form("roots/%d_RawSignal_pT_0_5_Cen_0_80.png", number));
	}
	if (0)// 画信号，背景1/2，信号-背景1/2，背景1/背景2
	{
		//设置直方图格式
		h_Mee__unlikeSame_Rebin->SetLineColor(1);			h_Mee__unlikeSame_Rebin->SetMarkerStyle(kOpenCircle);			h_Mee__unlikeSame_Rebin->SetMarkerColor(1); 		h_Mee__unlikeSame_Rebin->SetMarkerSize(0.5);
		h_Mee__LikeSame_PSACcorr_Rebin->SetLineColor(2);	h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerStyle(kOpenSquare);	h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerColor(2);	h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerSize(0.5);
		h_Mee__unlikeMixed_Rebin->SetLineColor(4);			h_Mee__unlikeMixed_Rebin->SetMarkerStyle(kCircle);				h_Mee__unlikeMixed_Rebin->SetMarkerColor(4);		h_Mee__unlikeMixed_Rebin->SetMarkerSize(0.5);
		h_Mee__rmLS_Rebin->SetLineColor(6);					h_Mee__rmLS_Rebin->SetMarkerStyle(kOpenCross);					h_Mee__rmLS_Rebin->SetMarkerColor(6);				h_Mee__rmLS_Rebin->SetMarkerSize(0.5);
		h_Mee__rmLS_PSACcorr_Rebin->SetLineColor(9);		h_Mee__rmLS_PSACcorr_Rebin->SetMarkerStyle(kOpenCross);			h_Mee__rmLS_PSACcorr_Rebin->SetMarkerColor(9);		h_Mee__rmLS_PSACcorr_Rebin->SetMarkerSize(0.5);
		h_Mee__rmUM_Rebin->SetLineColor(3);					h_Mee__rmUM_Rebin->SetMarkerStyle(kOpenStar);					h_Mee__rmUM_Rebin->SetMarkerColor(3);				h_Mee__rmUM_Rebin->SetMarkerSize(0.5);
		h_Mee__Signif_LS->SetLineColor(kBlack);   h_Mee__Signif_LS->SetMarkerStyle(kOpenCircle); h_Mee__Signif_LS->SetMarkerColor(kBlack);
		h_Mee__Signif_UM->SetLineColor(kRed);	  h_Mee__Signif_UM->SetMarkerStyle(kOpenSquare);   h_Mee__Signif_UM->SetMarkerColor(kRed);
		
		h_Mee__rmLS_Rebin->SetTitle(";M_{ee} (GeV/c^{2});dN/dM_{ee} (GeV/c^{2})^{-1}");
		h_Mee__rmUM_Rebin->SetTitle(";M_{ee} (GeV/c^{2});dN/dM_{ee} (GeV/c^{2})^{-1}");
		h_Mee__unlikeSame_Rebin->SetTitle(";M_{ee} (GeV/c^{2});dN/dM_{ee} (GeV/c^{2})^{-1}");
		h_Mee__LikeSame_PSACcorr_Rebin->SetTitle(";M_{ee} (GeV/c^{2});dN/dM_{ee} (GeV/c^{2})^{-1}");
		h_Mee__CorrLS_Rebin->SetTitle("PSAC vs M_{ee};M_{ee} (GeV/c^{2});PSAC");
		h_Mee__Signif_LS->SetTitle("Signifcance vs M_{ee};M_{ee} (GeV/c^{2});Significance");

		//画图
		TCanvas *c2 = new TCanvas("c2", "c2", 1400, 1200);
		c2->Divide(3, 3);
		c2->cd(1);//背景+信号
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		//h_Mee__rmLS_PSACcorr_Rebin->SetMaximum(1e9);
		//h_Mee__rmLS_PSACcorr_Rebin->SetMinimum(1);
		//h_Mee__rmUM_Rebin->SetMaximum(1e9);
		//h_Mee__rmUM_Rebin->SetMinimum(1);

		h_Mee__rmUM_Rebin->DrawClone("PE");
		h_Mee__rmLS_Rebin->DrawClone("PE same");
		h_Mee__rmLS_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__LikeSame_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__unlikeMixed_Rebin->DrawClone("same PE");
		h_Mee__unlikeSame_Rebin->DrawClone("same PE");
		auto legend = new TLegend(0.60, 0.55, 0.85, 0.85);
		legend->SetFillColor(0); legend->SetBorderSize(0);
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
		//h_Mee__rmLS_Rebin->SetMaximum(1e9);
		//h_Mee__rmLS_Rebin->SetMinimum(1);
		auto legend2 = new TLegend(0.60, 0.55, 0.85, 0.85);
		legend2->SetFillColor(0); legend2->SetBorderSize(0);	legend2->SetMargin(0.20);	gStyle->SetLegendTextSize(0.04);
		legend2->AddEntry(h_Mee__unlikeSame_Rebin, "\t UM", "lp");
		legend2->AddEntry(h_Mee__LikeSame_PSACcorr_Rebin, "\t LS", "lp");
		legend2->AddEntry(h_Mee__rmLS_Rebin, "\t UM-LS(not PSAC corr)", "lp");
		legend2->AddEntry(h_Mee__rmLS_PSACcorr_Rebin, "\t UM-LS(PSAC corr)", "lp");
		h_Mee__rmLS_Rebin->DrawClone("PE");
		h_Mee__rmLS_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__LikeSame_PSACcorr_Rebin->DrawClone("same PE");
		h_Mee__unlikeSame_Rebin->DrawClone("same PE");
		legend2->Draw("same");
		TPaveText *pt2 = new TPaveText(0.48, 0.65, 0.85, 0.96, "NDC NB");
		pt2->SetFillColorAlpha(0, 0);   // 透明底
		pt2->SetBorderSize(0);
		pt2->SetTextFont(42);
		pt2->SetTextSize(0.032);
		pt2->SetTextAlign(12);
		pt2->AddText("d+Au@200GeV");
		pt2->AddText("Cen:0~80% 0<p_{T}^{ee}<5");
		//pt2->AddText("p_{T}^{e}>0.2,|#eta|<1.0, |y_{ee}|<1.0");
		pt2->AddText(Form("Focused region:%.1f<M_{ee}<%.1f", x_low_LS, x_up_LS));
		pt2->AddText(Form("S=%.1f B=%.1f", N_LS - B_LS, B_LS));
		pt2->AddText(Form("S/B=%.4f S/#sqrt{S+2B}=%.1f or %.1f", (N_LS - B_LS) / B_LS, signif_LS, signif_LS_PSACcorr));
		//pt2->DrawClone("same");

		c2->cd(3);//背景+信号
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		//h_Mee__rmUM_Rebin->SetMaximum(1e9);
		//h_Mee__rmUM_Rebin->SetMinimum(1);
		h_Mee__rmUM_Rebin->DrawClone("PE");
		h_Mee__unlikeMixed_Rebin->DrawClone("same PE");
		h_Mee__unlikeSame_Rebin->DrawClone("same PE");
		TPaveText *pt3 = new TPaveText(0.48, 0.65, 0.81, 0.96, "NDC NB");
		pt3->SetFillColorAlpha(0, 0);   // 透明底
		pt3->SetBorderSize(0);
		pt3->SetTextFont(42);
		pt3->SetTextSize(0.032);
		pt3->SetTextAlign(12);
		pt3->AddText("d+Au@200GeV");
		pt3->AddText("Cen:0~80% 0<p_{T}^{ee}<5");
		//pt3->AddText("p_{T}^{e}>0.2,|#eta|<1.0, |y_{ee}|<1.0");
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
		h_Mee__LikeSame_PSACcorr_Rebin->DrawClone("PE");
		h_Mee__unlikeMixed_Rebin->DrawClone("same PE");
		auto legend_BR = new TLegend(0.15, 0.15, 0.25, 0.45);
		legend_BR->SetFillColor(0); legend_BR->SetBorderSize(0); legend_BR->SetFillStyle(0);
		legend_BR->AddEntry(h_Mee__LikeSame_PSACcorr_Rebin, "\t Like-Sign Same-Event", "lp");
		legend_BR->AddEntry(h_Mee__unlikeMixed_Rebin, "\t Unlike-Sign Mixed-Event", "lp");
		legend_BR->SetMargin(0.45); //legend_BR->SetTextAlign(12);
		gStyle->SetLegendTextSize(0.04);
		legend_BR->Draw("same");

		c2->cd(7);//信号-背景比例
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gPad->SetLogy(1);
		gStyle->SetOptStat(0);
		h_Mee__BKGRatio_Rebin->SetTitle(";M_{ee} (GeV/c^{2});LS/UM");
		//h_Mee__BKGRatio_Rebin->SetMaximum(2);
		//h_Mee__BKGRatio_Rebin->SetMinimum(0.9);
		h_Mee__BKGRatio_Rebin->GetYaxis()->SetNdivisions(505);
		h_Mee__BKGRatio_Rebin->DrawClone("PE");


		c2->cd(5);//负信号_rmLS
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		TH1F* h_Mee__rmLS_Rebin_test = (TH1F*)h_Mee__rmLS_Rebin->Clone("h_Mee__rmLS_Rebin_test");
		TH1F* h_Mee__rmLS_PSACcorr_Rebin_test = (TH1F*)h_Mee__rmLS_PSACcorr_Rebin->Clone("h_Mee__rmLS_PSACcorr_Rebin_test");
		NegateBinContents(h_Mee__rmLS_Rebin_test);
		NegateBinContents(h_Mee__rmLS_PSACcorr_Rebin_test);
		h_Mee__rmLS_Rebin_test->SetTitle(";M_{ee} (GeV/c^{2});- dN/dM_{ee} (GeV/c^{2})^{-1}");
		//h_Mee__rmLS_Rebin_test->SetMaximum(1e9);
		//h_Mee__rmLS_Rebin_test->SetMinimum(1);
		h_Mee__rmLS_Rebin_test->DrawClone("PE");
		h_Mee__rmLS_PSACcorr_Rebin_test->DrawClone("PE same");

		c2->cd(6);//负信号_rmUM
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		TH1F* h_Mee__rmUM_Rebin_test = (TH1F*)h_Mee__rmUM_Rebin->Clone("h_Mee__rmUM_Rebin_test");
		NegateBinContents(h_Mee__rmUM_Rebin_test);
		h_Mee__rmUM_Rebin_test->SetTitle(";M_{ee} (GeV/c^{2});- dN/dM_{ee} (GeV/c^{2})^{-1}");
		//h_Mee__rmUM_Rebin_test->SetMaximum(1e9);
		//h_Mee__rmUM_Rebin_test->SetMinimum(1);
		h_Mee__rmUM_Rebin_test->DrawClone("PE");

		c2->cd(8);//likemm Same-Event 与 Mixed-Event 的二维pull图（替换原PSAC 2D分布）
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gStyle->SetOptStat(0);
		h_Mee_Pt__likemm_Pull->SetTitle("(Lmm_{Same}-Lmm_{Mix})/#sigma_{diff};M_{ee} (GeV/c^{2});p_{T} (GeV/c)");
		h_Mee_Pt__likemm_Pull->SetMinimum(-20.0);
		h_Mee_Pt__likemm_Pull->SetMaximum(20.0);
		h_Mee_Pt__likemm_Pull->DrawClone("col z");

		c2->cd(9);//LS背景修正因子check
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		gStyle->SetOptStat(0);
		//h_Mee__CorrLS_Rebin->Scale(1.0 / ((Cen__newEdges.size() - 1)*(Pt__newEdges.size() - 1)));
		h_Mee__CorrLS_Rebin->SetLineColor(kBlack);  h_Mee__CorrLS_Rebin->SetMarkerStyle(kOpenCircle); h_Mee__CorrLS_Rebin->SetMarkerColor(kBlack);
		//h_Mee__CorrLS_Rebin->SetMaximum(1.02);
		//h_Mee__CorrLS_Rebin->SetMinimum(0.96);
		h_Mee__CorrLS_Rebin->DrawClone();


		c2->SaveAs(Form("roots/%d_Mee_PSAC.png", number));
	}

	if (1)// 不同scale的1-D UM背景对信号(US-UM)的影响
	{
		// 设置直方图格式
		h_Mee__unlikeSame_Rebin->SetLineColor(1);			h_Mee__unlikeSame_Rebin->SetMarkerStyle(kOpenCircle);			h_Mee__unlikeSame_Rebin->SetMarkerColor(1); 		h_Mee__unlikeSame_Rebin->SetMarkerSize(0.5);
		h_Mee__LikeSame_PSACcorr_Rebin->SetLineColor(2);	h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerStyle(kOpenSquare);	h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerColor(2);	h_Mee__LikeSame_PSACcorr_Rebin->SetMarkerSize(0.5);
		h_Mee__unlikeMixed_Rebin->SetLineColor(4);			h_Mee__unlikeMixed_Rebin->SetMarkerStyle(kCircle);				h_Mee__unlikeMixed_Rebin->SetMarkerColor(4);		h_Mee__unlikeMixed_Rebin->SetMarkerSize(0.5);
		h_Mee__rmLS_Rebin->SetLineColor(6);					h_Mee__rmLS_Rebin->SetMarkerStyle(kOpenCross);					h_Mee__rmLS_Rebin->SetMarkerColor(6);				h_Mee__rmLS_Rebin->SetMarkerSize(0.5);
		h_Mee__rmLS_PSACcorr_Rebin->SetLineColor(9);		h_Mee__rmLS_PSACcorr_Rebin->SetMarkerStyle(kOpenCross);			h_Mee__rmLS_PSACcorr_Rebin->SetMarkerColor(9);		h_Mee__rmLS_PSACcorr_Rebin->SetMarkerSize(0.5);
		h_Mee__rmUM_Rebin->SetLineColor(3);					h_Mee__rmUM_Rebin->SetMarkerStyle(kOpenStar);					h_Mee__rmUM_Rebin->SetMarkerColor(3);				h_Mee__rmUM_Rebin->SetMarkerSize(0.5);
		
		h_Mee__unlikeMixed_Rebin_scale1->SetLineColor(4);			h_Mee__unlikeMixed_Rebin_scale1->SetMarkerStyle(kCircle);				h_Mee__unlikeMixed_Rebin_scale1->SetMarkerColor(4);		h_Mee__unlikeMixed_Rebin_scale1->SetMarkerSize(0.5);
		h_Mee__unlikeMixed_Rebin_scale2->SetLineColor(4);			h_Mee__unlikeMixed_Rebin_scale2->SetMarkerStyle(kCircle);				h_Mee__unlikeMixed_Rebin_scale2->SetMarkerColor(4);		h_Mee__unlikeMixed_Rebin_scale2->SetMarkerSize(0.5);
		h_Mee__unlikeMixed_Rebin_scale4->SetLineColor(4);			h_Mee__unlikeMixed_Rebin_scale4->SetMarkerStyle(kCircle);				h_Mee__unlikeMixed_Rebin_scale4->SetMarkerColor(4);		h_Mee__unlikeMixed_Rebin_scale4->SetMarkerSize(0.5);
		h_Mee__unlikeMixed_Rebin_scale5->SetLineColor(4);			h_Mee__unlikeMixed_Rebin_scale5->SetMarkerStyle(kCircle);				h_Mee__unlikeMixed_Rebin_scale5->SetMarkerColor(4);		h_Mee__unlikeMixed_Rebin_scale5->SetMarkerSize(0.5);
		h_Mee__rmUM_Rebin_scale1->SetLineColor(3);		h_Mee__rmUM_Rebin_scale1->SetMarkerStyle(kOpenStar);		h_Mee__rmUM_Rebin_scale1->SetMarkerColor(3);		h_Mee__rmUM_Rebin_scale1->SetMarkerSize(0.1);
		h_Mee__rmUM_Rebin_scale2->SetLineColor(3);		h_Mee__rmUM_Rebin_scale2->SetMarkerStyle(kOpenStar);		h_Mee__rmUM_Rebin_scale2->SetMarkerColor(3);		h_Mee__rmUM_Rebin_scale2->SetMarkerSize(0.1);
		h_Mee__rmUM_Rebin_scale4->SetLineColor(3);		h_Mee__rmUM_Rebin_scale4->SetMarkerStyle(kOpenStar);		h_Mee__rmUM_Rebin_scale4->SetMarkerColor(3);		h_Mee__rmUM_Rebin_scale4->SetMarkerSize(0.1);
		h_Mee__rmUM_Rebin_scale5->SetLineColor(3);		h_Mee__rmUM_Rebin_scale5->SetMarkerStyle(kOpenStar);		h_Mee__rmUM_Rebin_scale5->SetMarkerColor(3);		h_Mee__rmUM_Rebin_scale5->SetMarkerSize(0.1);

		TCanvas* c_scale = new TCanvas("c_scale", "c_scale", 1800, 1200);
		c_scale->Divide(3, 2);
		Float_t Cen_bin_low = 0, Cen_bin_up = 16;
		// cd(1): US-LS(PSAC corr)
		c_scale->cd(1);
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.05);
		Draw_1DMee(h_Mee__unlikeSame_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, h_Mee__LikeSame_PSACcorr_Rebin, h_Mee__rmLS_PSACcorr_Rebin, h_Mee__rmLS_PSACcorr_Rebin);

		// cd(2): US-UM (scale-5%)
		c_scale->cd(2);
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.05);
		Draw_1DMee(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin_scale1, h_Mee__unlikeMixed_Rebin_scale1, h_Mee__rmUM_Rebin_scale1, h_Mee__rmUM_Rebin_scale1);

		// cd(3): US-UM (scale-3%)
		c_scale->cd(3);
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.05);
		Draw_1DMee(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin_scale2, h_Mee__unlikeMixed_Rebin_scale2, h_Mee__rmUM_Rebin_scale2, h_Mee__rmUM_Rebin_scale2);

		// cd(4): US-UM (scale原值)
		c_scale->cd(4);
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.05);
		Draw_1DMee(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin, h_Mee__unlikeMixed_Rebin, h_Mee__rmUM_Rebin, h_Mee__rmUM_Rebin);

		// cd(5): US-UM (scale+3%)
		c_scale->cd(5);
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.05);
		Draw_1DMee(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin_scale4, h_Mee__unlikeMixed_Rebin_scale4, h_Mee__rmUM_Rebin_scale4, h_Mee__rmUM_Rebin_scale4);

		// cd(6): US-UM (scale+5%)
		c_scale->cd(6);
		gPad->SetLogy(1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.05);
		Draw_1DMee(h_Mee__unlikeSame_Rebin, h_Mee__unlikeMixed_Rebin_scale5, h_Mee__unlikeMixed_Rebin_scale5, h_Mee__rmUM_Rebin_scale5, h_Mee__rmUM_Rebin_scale5);

		c_scale->SaveAs(Form("roots/%d_rmUM_scale.png", number));
	}
}